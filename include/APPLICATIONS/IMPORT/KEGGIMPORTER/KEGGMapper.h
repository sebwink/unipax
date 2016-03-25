// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UniPAX
// --------------------------------------------------------------------------
//  Copyright (C) 2011 -- Oliver Kohlbacher, Hans-Peter Lenhof
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Id:$
// $Author:$
// $Maintainer:$
// --------------------------------------------------------------------------
//

#ifndef KEGGMAPPER_H_
#define KEGGMAPPER_H_


#include <APPLICATIONS/IMPORT/KEGGIMPORTER/DBConnection.h>

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/COMMON/PersistenceManager.h>

#include <UNIPAX/KERNEL/all.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlError>
#include <QtCore/QVariant>

#include <boost/tr1/unordered_map.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <exception>

namespace UniPAX
{

class UNIPAX_EXPORT KEGGMapper
{
public:

	KEGGMapper(PersistenceManager& manager);

	void setKEGGDatabase(DBConnection* connection, std::string version);

	void setPreviousImportSource(boost::shared_ptr<ImportSource> previous);

	void import(std::vector<std::string> organisms);

	void setPersistenceManager(PersistenceManager& manager);

	PersistenceManager& getPersistenceManager();

	const PersistenceManager& getPersistenceManager() const;


private:

	typedef std::set<std::string> StringSet;
	typedef std::vector<std::string> StringVector;
	typedef std::tr1::unordered_map<std::string, std::string> StringUMap;
	typedef std::map<std::string, std::string> StringMap;
	typedef std::tr1::unordered_multimap<std::string, std::string> StringUMultiMap;
	typedef std::multimap<std::string, std::string> StringMultiMap;

	typedef std::pair<StringUMultiMap::const_iterator, StringUMultiMap::const_iterator> StringUMultiMapEqualRange;

	DBConnection* kegg_connection;

	PersistenceManager& manager;

	boost::shared_ptr<Provenance> kegg;

	boost::shared_ptr<ImportSource> previous;

	boost::shared_ptr<ImportSource> current;

	template<typename _Container> static inline std::string collate(const _Container & container, std::string separator, bool sort = true)
	{
		StringVector v(container.begin(), container.end());

		if (sort)
		{
			std::sort(v.begin(), v.end());
		}

		return boost::algorithm::join(v, separator);
	}

	template<typename _Container> static inline StringVector prefix(const _Container &  container, std::string prefix)
	{

		StringVector v(container.begin(), container.end());

		for (StringVector::iterator it = v.begin(); it != v.end(); ++it) {
			it->insert(0, prefix);
		}

		return v;
	}

	template<typename _Container> static inline StringVector suffix(const _Container &  container, std::string suffix)
	{

		StringVector v(container.begin(), container.end());


		for (StringVector::iterator it = v.begin(); it != v.end(); ++it) {
			it->append(suffix);
		}

		return v;
	}



	template<typename _Container, typename _Tp> static inline bool contains(_Container& _container, const _Tp& __val)
	{
		return std::find(_container.begin(), _container.end(), __val) != _container.end();
	}

	struct Entry {

		typedef StringVector::const_iterator ComponentIter;
		typedef StringVector::const_iterator GeneIdIter;

		std::string pathwayId;
		std::string ori;
		std::string id;
		std::string type;

		StringVector geneIds;
		StringVector components;

		Entry(std::string _ori, std::string _pathwayId, std::string _id) : ori(_ori), pathwayId(_pathwayId), id(_id)
		{ }

		std::string toString()
		{
			return ori + ":" + pathwayId + " " + id + "@" + type + " (" + collate(geneIds, ",", false) + ":" + collate(components, ",", false) + ")";
		}
	};

	struct Relation {
		std::string entry_id1;
		std::string entry_id2;
		std::string relation_type;

		StringVector subtypes;
		StringVector subtype_values;

		Relation(std::string _entry_id1, std::string _entry_id2) : entry_id1(_entry_id1), entry_id2(_entry_id2)
		{
		}

		std::string getSubtypeValue(std::string subtype)
		{
			for (int i = 0; i < subtypes.size(); ++i)
			{
				if (subtypes[i] == subtype)
					return subtype_values[i];
			}

			return "";
		}

		std::string toString()
		{
			return relation_type + ": " + entry_id1 + " -> " + entry_id2 + "(" + collate(subtypes, ",", false) + ":" + collate(subtype_values, ",", false) + ")";
		}
	};

	UnipaxId next_free_id;

	std::vector<boost::shared_ptr<BiochemicalReaction> > nonEnzymaticReactions;
	std::tr1::unordered_map<std::string, boost::shared_ptr<BiochemicalReaction> > reactionMap;

	std::tr1::unordered_map<std::string, boost::shared_ptr<Pathway> > pathwayMapOrg;

	std::string current_ori;
	boost::shared_ptr<BioSource> current_org;

	// this map stores small molecule references using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<SmallMoleculeReference> > smallMoleculeReferenceMap;

	// this map stores the default small molecule instance using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<SmallMolecule> > defaultSmallMoleculeInstanceMap;

	// this map stores the modified small molecules instance using kegg ids/modifications
	std::tr1::unordered_map<std::pair<std::string, StringSet>, std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<SmallMolecule> > > modifiedSmallMoleculeInstanceMap;


	// this map stores protein references using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<ProteinReference> > proteinReferenceMapOrg;

	// this map stores the default protein instance using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<Protein> > defaultProteinInstanceMapOrg;

	// this map stores the modified protein instance using kegg ids/modifications
	std::tr1::unordered_map<std::pair<std::string, StringSet>, std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Protein> > > modifiedProteinInstanceMapOrg;


	// this map stores protein complexes using a set of containing physical entities
	std::tr1::unordered_map<std::set<boost::shared_ptr<PhysicalEntity> >, boost::shared_ptr<Complex> > defaultProteinComplexInstanceMapOrg;

	// this map stores protein complexes using a set of containing physical entities/modifications
	std::tr1::unordered_map<std::pair<std::set<boost::shared_ptr<PhysicalEntity> >, StringSet>, std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Complex> > > modifiedProteinComplexInstanceMapOrg;

	std::tr1::unordered_map<boost::shared_ptr<Complex>, boost::shared_ptr<ComplexAssembly> > proteinComplexAssemblyMapOrg;

	std::tr1::unordered_map<boost::shared_ptr<Complex>, boost::shared_ptr<ComplexAssembly> > proteinComplexDisassemblyMapOrg;


	std::tr1::unordered_map<boost::shared_ptr<PhysicalEntity>, boost::shared_ptr<TemplateReaction> > templateReactionMapOrg;



	// this map stores protein family references using a set kegg ids
	std::tr1::unordered_map<StringSet, boost::shared_ptr<ProteinReference> > proteinFamilyReferenceMapOrg;

	// this map stores the default protein family instance using a set of kegg ids
	std::tr1::unordered_map<StringSet, boost::shared_ptr<Protein> > defaultProteinFamilyInstanceMapOrg;

	// this map stores the modified protein family instance using a set of kegg ids/modifications
	std::tr1::unordered_map<std::pair<StringSet, StringSet>, std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Protein> > > modifiedProteinFamilyInstanceMapOrg;



	std::tr1::unordered_map<std::string, boost::shared_ptr<DnaRegionReference> > dnaRegionReferenceMapOrg;


	// this map stores RNA references using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<RnaReference> > rnaReferenceMapOrg;

	// this map stores the default RNA instance using kegg ids
	std::tr1::unordered_map<std::string, boost::shared_ptr<Rna> > defaultRnaInstanceMapOrg;

	// this map stores the modified RNA instance using kegg ids/modifications
	std::tr1::unordered_map<std::pair<std::string, StringSet>, std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Rna> > > modifiedRnaInstanceMapOrg;



	StringUMultiMap geneKOMapOrg;
	StringUMultiMap koGeneMapOrg;

	StringUMap koNameMapOrg;
	StringUMap koDescriptionMapOrg;




	boost::shared_ptr<EntityReference> getEntityReference(std::string id);

	boost::shared_ptr<SmallMolecule> createSmallMolecule(boost::shared_ptr<SmallMoleculeReference> & reference);

	boost::shared_ptr<Protein> createProtein(boost::shared_ptr<ProteinReference> & reference);

	boost::shared_ptr<Rna> createRna(boost::shared_ptr<RnaReference> & reference);

	boost::shared_ptr<Protein> createProteinFamily(boost::shared_ptr<ProteinReference> & reference);

	boost::shared_ptr<ProteinReference> createProteinFamilyReference(StringSet & members);

	template<typename _Container> boost::shared_ptr<Complex> createComplex(_Container & components);

	boost::shared_ptr<Complex> getDefaultComplexInstance(std::set<boost::shared_ptr<PhysicalEntity> > components);

	std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Complex> > getModifiedComplexInstance(std::set<boost::shared_ptr<PhysicalEntity> > components, StringSet modifications);

	boost::shared_ptr<ComplexAssembly> getComplexAssembly(boost::shared_ptr<Complex> complex);

	boost::shared_ptr<ComplexAssembly> getComplexDisassembly(boost::shared_ptr<Complex> complex);

	boost::shared_ptr<TemplateReaction> getTemplateReaction(boost::shared_ptr<PhysicalEntity> target);

	void addModificationFeature(boost::shared_ptr<PhysicalEntity> physicalEntity, std::string modification);

	boost::shared_ptr<ProteinReference> getProteinReference(std::string kegg_id);

	boost::shared_ptr<PhysicalEntity> getDefaultInstance(std::string kegg_id);

	boost::shared_ptr<PhysicalEntity> getDefaultInstance(std::tr1::unordered_map<std::string, boost::shared_ptr<Entry> > & entry_map, boost::shared_ptr<Entry> & entry);

	std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<PhysicalEntity> > getModifiedInstance(std::tr1::unordered_map<std::string, boost::shared_ptr<Entry> > & entry_map, boost::shared_ptr<Entry> & entry, StringSet modifications);


	void registerEntity(boost::shared_ptr<Entity> entity)
	{
//		thing->set_introducedBy(current);
		entity->setDataSource(kegg);
	}

	template<class T> boost::shared_ptr<T> createInstance(std::string id) {
		bool created = false;

		boost::shared_ptr<T> o = manager.createInstance<T>(T::type() + ":" + id, created);

//		if (!created)
//			std::cout << "Already existing: " << T::type() << ":" << id << std::endl;

		return o;
	}

	template<class T> boost::shared_ptr<T> createInstance(std::string prefix, std::string appendix) {

		UnipaxId id = ++next_free_id;

		std::stringstream ss;
		ss << id;
		std::string _id;
		ss >> _id;

		bool created = false;

		boost::shared_ptr<T> o = manager.createInstance<T>(T::type() + ":" + prefix + _id + appendix, created);

		return o;
	}

	void createCrossReference(boost::shared_ptr<Entity> entity, std::string dbName, std::string id);
	void createCrossReference(boost::shared_ptr<EntityReference> entityReference, std::string dbName, std::string id);

	boost::shared_ptr<EntityReferenceTypeVocabulary> getEntityReferenceTypeVocabulary(std::string term);
	boost::shared_ptr<SequenceModificationVocabulary> getSequenceModificationVocabulary(std::string term);


	template <typename T> StringSet getKOIds(T & geneids)
	{
		StringSet koIds;
		for (typename T::const_iterator it = geneids.begin(); it != geneids.end(); it++)
		{
			if (geneKOMapOrg.find(*it) != geneKOMapOrg.end())
			{
				for (StringUMultiMapEqualRange p = geneKOMapOrg.equal_range(*it); p.first != p.second; ++p.first)
				{
					koIds.insert(p.first->second);
				}
			}
		}

		return koIds;
	}

	template <typename T> std::string getProteinFamilyName(T & geneids)
	{
		StringSet names;

		for (typename T::const_iterator it = geneids.begin(); it != geneids.end(); it++)
		{
			if (geneKOMapOrg.find(*it) != geneKOMapOrg.end())
			{
				for (StringUMultiMapEqualRange p = geneKOMapOrg.equal_range(*it); p.first != p.second; ++p.first)
				{
					if (koNameMapOrg.find(p.first->second) != koNameMapOrg.end())
					{
						names.insert(koNameMapOrg[p.first->second]);
					}
				}
			}
		}

		if (names.size() > 0) {

			// find common substring
			if (names.size() > 1)
			{
				StringSet::const_iterator it = names.begin();

				std::string final = *it;
				it++;

				// second test: check if they have common substring
				for (; it != names.end(); it++)
				{
					std::string current = *it;

					for (size_t pos = 0; pos < final.length() && pos < current.length(); pos++)
					{
						if (final[pos] != current[pos])
						{
							final = final.substr(0, pos);
							break;
						}
					}

					if (final.length() <= 2)
						break;
				}

				if (final.length() > 2)
				{
					return final;
				}
			}

			std::string final = *(names.begin());

			StringVector name_split;
			boost::split(name_split, final, boost::is_any_of(","));
			if (name_split.size() == 1)
			{
				return final;
			}

			for (size_t i = 0; i < name_split.size(); ++i) {
				if (name_split[i].length() > 3)
				{
					if (name_split[i][0] != 'E' && name_split[i][2] != '.' )
						return name_split[i];
				}
				else
				{
					return name_split[i];
				}
			}

			return final;
		}

		return "";

	}

	void readKOMapOrg();

	int readCompounds();
	int readReactions();
	int readReactionsWithoutEC();

	int readGenesOrg();
	int readReactionsOrg();
	int readMetabolicPathwaysOrg();
	int readRegulatoryPathwaysOrg();

};


}


#endif /* KEGGMAPPER_H_ */

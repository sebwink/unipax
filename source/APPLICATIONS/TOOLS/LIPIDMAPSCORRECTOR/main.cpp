#include <UNIPAX/IMPORT/BIOPAX/BIOPAXReader.h>
#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#include <UNIPAX/IMPORT/SBML/MiriamLinkREST.h>
#include <UNIPAX/IMPORT/BridgeDBLinkREST.h>
#include <UNIPAX/KERNEL/all.h>

#include <UNIPAX/COMMON/MergerInputAdapter.h>

#include<Qt/QtCore>
#include<Qt/QtNetwork>
#include <QApplication>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <string>
#include <iostream>

typedef std::multimap<std::string, std::string> str_str_t;


UniPAX::MiriamLink miriam;
UnipaxId id = 0;

UnipaxId nextId()
{
	return id++;
}

bool removeMergedObjects(UniPAX::MergerInputAdapter & mia)
{
	typedef std::map<UniPAX::UPBasePtr, UnipaxId> ptr_id_t;
	for (ptr_id_t::iterator it = mia.getPtrIdMap().begin(); it != mia.getPtrIdMap().end(); ++it)
	{
		if (mia.getPersistenceManager()->isMerged(it->first))
		{
			if(!mia.removeInstance(it->first))
				return false;
		}
		else
		{
			it->first->update(*mia.getPersistenceManager());
		}
	}
	return true;
}


template <class ER = UniPAX::ProteinReference>
bool mergeReferences(str_str_t type_ids, UnipaxPtr<UniPAX::PersistenceManager>::type pm)
{
	str_str_t::const_iterator er = type_ids.find(ER::type());
	typedef std::map<UnipaxId, std::vector<typename UnipaxPtr<ER>::type> > id_ptrlist_t;
	id_ptrlist_t uxref_protRef;
	while (er != type_ids.end() && er->first == ER::type())
	{
		typename UnipaxPtr<ER>::type protRef = boost::dynamic_pointer_cast<ER>(pm->getInstance(er->second, er->first));
		if (protRef == 0)
		{
			std::cerr << "No " << ER::type() << " with id " << er->second << " registered." << std::endl;
			return false;
		}
		// Create UnificationXref to ProteinReference mapping
		for (std::vector<UniPAX::XrefPtr>::const_iterator xref = protRef->getXrefs().begin(); xref != protRef->getXrefs().end(); xref++)
		{
			if ((*xref)->getTypeID() == UniPAX::ClassType::idUnificationXref)
			{
				// if no entry for this UnificationXref, create it.
				if (uxref_protRef.find((*xref)->getUnipaxId()) == uxref_protRef.end())
				{
					std::vector<typename UnipaxPtr<ER>::type> pr_vec;
					pr_vec.push_back(protRef);
					uxref_protRef.insert(std::pair<UnipaxId, std::vector<typename UnipaxPtr<ER>::type> >((*xref)->getUnipaxId(), pr_vec));
				}
				// else we should have found a doubled entry
				else
				{
					uxref_protRef[(*xref)->getUnipaxId()].push_back(protRef);
				}
			}
		}
		++er;
	}
	// now we can try to merge all entries from uxref_protRef with more than one ProteinReferencePtr attached
	for (typename id_ptrlist_t::const_iterator lit = uxref_protRef.begin(); lit != uxref_protRef.end(); lit++)
	{
		if (lit->second.size() > 1)
		{
			std::cout << ER::type() << "s with ids ";
			typedef std::vector<typename UnipaxPtr<ER>::type> vec_prptr_t;
			for (typename vec_prptr_t::const_iterator pit = lit->second.begin(); pit != lit->second.end(); pit++)
			{
				std::cout << " " << (*pit)->getUnipaxId() << ",";
			}
			std::cout << " share the same UnificationXref with id " << lit->first << ". Trying to merge them..." << std::endl;
			typename UnipaxPtr<ER>::type keep = *(lit->second.begin());
			if (pm->isMerged(keep))
			{
				std::cout << keep->getUnipaxId() << " has already been merged. Skipping it." << std::endl;
			}
			else
			{
				keep->update(*pm);
				typename vec_prptr_t::const_iterator pit = lit->second.begin()+1;
				while (pit != lit->second.end())
				{
					if (!pm->isMerged(*pit))
					{
						(*pit)->update(*pm);
						if (!keep->merge(*(*pit)))
						{
							std::cout << "Merge of objects " << keep->getUnipaxId() << " and " << (*pit)->getUnipaxId() << " failed." << std::endl;
							// we must return here since 'keep' may already have been altered.
							return false;
						}
						else
						{
							std::cout << "Merge of objects " << keep->getUnipaxId() << " and " << (*pit)->getUnipaxId() << " succeeded." << std::endl;
							pm->addMerge(*pit, keep);
						}
					}
					else
					{
						std::cout << "Object " << (*pit)->getUnipaxId() << " has already been merged." << std::endl;
					}
					++pit;
				}
			}
		}
	}
	return true;
}

template <class E = UniPAX::Protein>
bool mergeByReference(str_str_t type_ids, UnipaxPtr<UniPAX::PersistenceManager>::type pm)
{
	str_str_t::const_iterator e = type_ids.find(E::type());
	typedef std::map<UnipaxId, std::vector<typename UnipaxPtr<E>::type> > id_ptrlist_t;
	id_ptrlist_t ref_prot;
	while (e != type_ids.end() && e->first == E::type())
	{
		typename UnipaxPtr<E>::type prot = boost::dynamic_pointer_cast<E>(pm->getInstance(e->second, e->first));
		if (prot == 0)
		{
			std::cerr << "No " << E::type() << " with id " << e->second << "registered." << std::endl;
			return false;
		}
		prot->update(*pm);
		// Create ProteinReference to Protein mapping
		for (std::vector<UniPAX::EntityReferencePtr>::const_iterator ref = prot->getEntityReferences().begin(); ref != prot->getEntityReferences().end(); ref++)
		{
			//if ((*ref)->getTypeID() == UniPAX::ClassType::idUnificationXref) no cause with ProteinReferences
			{
				// if no entry for this UnificationXref, create it.
				if (ref_prot.find((*ref)->getUnipaxId()) == ref_prot.end())
				{
					std::vector<typename UnipaxPtr<E>::type> p_vec;
					p_vec.push_back(prot);
					ref_prot.insert(std::pair<UnipaxId, std::vector<typename UnipaxPtr<E>::type> >((*ref)->getUnipaxId(), p_vec));
				}
				// else we should have found a doubled entry
				else
				{
					ref_prot[(*ref)->getUnipaxId()].push_back(prot);
				}
			}
		}
		++e;
	}
	// now we can try to merge all entries from ref_prot with more than one Protein attached
	for (typename id_ptrlist_t::const_iterator lit = ref_prot.begin(); lit != ref_prot.end(); lit++)
	{
		if (lit->second.size() > 1)
		{
			std::cout << E::type();
			typedef std::vector<typename UnipaxPtr<E>::type> vec_pptr_t;
			for (typename vec_pptr_t::const_iterator pit = lit->second.begin(); pit != lit->second.end(); pit++)
			{
				std::cout << " " << (*pit)->getUnipaxId() << ",";
			}
			std::cout << " share the same EntityReference. Trying to merge them..." << std::endl;
			typename UnipaxPtr<E>::type keep = *(lit->second.begin());
			keep->update(*pm);
			typename vec_pptr_t::const_iterator pit = lit->second.begin()+1;
			while (pit != lit->second.end())
			{
				if (!pm->isMerged(*pit))
				{
					(*pit)->update(*pm);
					if (!keep->merge(*(*pit)))
					{
						std::cout << "Merge of objects " << keep->getUnipaxId() << " and " << (*pit)->getUnipaxId() << " failed." << std::endl;
						// we must return here since 'keep' may already have been altered.
						return false;
					}
					else
					{
						std::cout << "Merge of objects " << keep->getUnipaxId() << " and " << (*pit)->getUnipaxId() << " succeeded." << std::endl;
						pm->addMerge(*pit, keep);
					}
				}
				else
				{
					std::cout << "Object " << (*pit)->getUnipaxId() << " has already been merged." << std::endl;
				}
				++pit;
			}
		}
	}
	return true;
}

template <class E = UniPAX::Protein, class ER = UniPAX::ProteinReference>
bool splitByUXref(str_str_t type_ids, UniPAX::MergerInputAdapter & mia)
{
	std::vector<UniPAX::UPBasePtr> pathways;
	if (!mia.getObjectsByType(pathways, "Pathway"))
	{
		std::cerr << "splitByUXref: " << "Could not retrieve Pathway objects." << std::endl;
		return false;
	}
	std::vector<UniPAX::UPBasePtr> catalyses;
	if (!mia.getObjectsByType(catalyses, "Catalysis"))
	{
		std::cerr << "splitByUXref: " << "Could not retrieve Catalysis objects." << std::endl;
		return false;
	}
	UnipaxPtr<UniPAX::PersistenceManager>::type pm = mia.getPersistenceManager();
	boost::char_separator<char> sep("/");
	str_str_t::const_iterator e = type_ids.find(E::type());
	// iterate over all Entities
	while (e != type_ids.end() && e->first == E::type())
	{
		typename UnipaxPtr<E>::type prot = boost::dynamic_pointer_cast<E>(pm->getInstance(e->second, e->first));
		boost::tokenizer<boost::char_separator<char> > tokens(prot->getStandardName(), sep);
		std::vector<std::string> prot_names(tokens.begin(), tokens.end());
		if (prot_names.size() == 1)
		{
			e++;
			continue;
		}
		if (prot->getEntityReferences().size() == 0)
		{
			std::cerr << "splitByUXref: " << E::type() << ": " <<  prot->getStandardName() << " has no EnityReference object linked." << std::endl;
			return false;
		}
		typename UnipaxPtr<ER>::type ref = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(*prot->getEntityReferences().begin());
		if (ref->getXrefs().size() == 0)
		{
			std::cerr << "splitByUXref: " << E::type() << ": " <<  prot->getStandardName() << " has an EntityReference object without Xref objects linked." << std::endl;
			return false;
		}
		std::vector<UniPAX::UnificationXrefPtr> uxrefs;
		for (std::vector<UniPAX::XrefPtr>::const_iterator it = ref->getXrefs().begin(); it != ref->getXrefs().end(); ++it)
		{
			if ((*it)->getTypeID() == UniPAX::ClassType::idUnificationXref)
			{
				uxrefs.push_back(boost::dynamic_pointer_cast<UniPAX::UnificationXref>(*it));
			}
		}
		if (uxrefs.size() == 0)
		{
			std::cerr << "splitByUXref: " << E::type() << ": " <<  prot->getStandardName() << " has an EntityReference object without UnificationXref objects linked." << std::endl;
			return false;
		}
		if (uxrefs.size() == 1)
		{
			e++;
			continue;
		}
		// else we have more than 1 UXref object.
		if (uxrefs.size() != prot_names.size())
		{
			std::cerr << "splitByUXref: " << E::type() << ": Number of names for " <<  prot->getStandardName() << " does not meet number of UnificationXref objects linked." << std::endl;
			return false;
		}
		std::vector<UniPAX::CatalysisPtr> cat_vec;
		// find relevant catalyses
		for (std::vector<UniPAX::UPBasePtr>::const_iterator it = catalyses.begin(); it != catalyses.end(); ++it)
		{
			UniPAX::CatalysisPtr cat = boost::dynamic_pointer_cast<UniPAX::Catalysis>(*it);
			for (std::vector<UniPAX::EntityPtr>::const_iterator ctr = cat->getControllers().begin(); ctr != cat->getControllers().end(); ctr++)
			{
				if (*ctr == prot)
				{
					cat_vec.push_back(cat);
					break;
				}
			}
		}
		if (cat_vec.empty())
		{
			std::cerr << "splitByUXref: Could not find a Catalysis linking the object." << std::endl;
			return false;
		}
		// iterate over all uxrefs of the ProtRef to create own objects for each uxref
		for (std::vector<UniPAX::UnificationXrefPtr>::const_iterator uxr = uxrefs.begin(); uxr != uxrefs.end(); ++uxr)
		{
			// check that db name is correct via MIRIAM
			std::vector<std::string> uris = miriam.getDataTypeURIs((*uxr)->getDb());
			if (uris.empty())
			{
				std::cerr << "splitByUXref: UnificationXref.db='" << (*uxr)->getDb() << "' is not an official db name." << std::endl;
				return false;
			}
			std::string official_uri = miriam.getOfficialURI(*uris.begin());
			std::string db_name = miriam.getName(official_uri);
			QUrl endpoint;
			endpoint.setHost(QString("webservice.bridgedb.org"));
			endpoint.setPort(80);
			endpoint.setScheme(QString("http"));
			UniPAX::BridgeDBLink bridge(endpoint);
			std::multimap<std::string, std::string> tag_value;
			std::string db_symbol;
			if (!bridge.getDbSymbol(db_symbol, db_name))
			{
				std::cerr << "splitByUXref: No 'db symbol' to db name '" << db_name << "' found." << std::endl;
				return false;
			}
			bridge.attributes(tag_value, ref->getOrganism()->getStandardName(), db_symbol, (*uxr)->getId(), "Symbol");
			if (tag_value.empty())
			{
				std::cerr << "splitByUXref: No 'symbol' to id '" << (*uxr)->getId() << "' of db '" << db_symbol << "' found." << std::endl;
				return false;
			}
			std::string name_symbol = tag_value.begin()->second;
			// add new EntityReference object
			bool created = false;

			typename UnipaxPtr<ER>::type new_ref = mia.createInstance<ER>(created);
			if (!created)
			{
				std::cerr << "splitByUXref: Could not create a new EntityReference object." << std::endl;
				return false;
			}
			std::cout << "splitByUXref: Created a new EntityReference object with id " << new_ref->getUnipaxId() << std::endl;
			UnipaxId save = new_ref->getUnipaxId();
			*new_ref = *ref;
			new_ref->setUnipaxId(save);
			// set correct UXref
			new_ref->getXrefs().clear();
			new_ref->addXref(*uxr);
			// set correctName
			new_ref->getNames().clear();
			new_ref->addName(name_symbol);
			new_ref->setStandardName(name_symbol);
			new_ref->setDisplayName(name_symbol);
			// add new Entity object
			created = false;
			typename UnipaxPtr<E>::type new_ety = mia.createInstance<E>(created);
			if (!created)
			{
				std::cerr << "splitByUXref: Could not create a new Entity object." << std::endl;
				return false;
			}
			std::cout << "splitByUXref: Created a new Entity object with id " << new_ety->getUnipaxId() << std::endl;
			save = new_ety->getUnipaxId();
			*new_ety = *prot;
			new_ety->setUnipaxId(save);
			// set correct ER
			new_ety->getEntityReferences().clear();
			new_ety->addEntityReference(new_ref);
			// set correctName
			new_ety->getNames().clear();
			new_ety->addName(name_symbol);
			new_ety->setStandardName(name_symbol);
			new_ety->setDisplayName(name_symbol);
			// add new Catalysis objects

			for (std::vector<UniPAX::CatalysisPtr>::const_iterator cit = cat_vec.begin(); cit != cat_vec.end(); ++cit)
			{
				UniPAX::CatalysisPtr cat = *cit;
				created = false;
				UniPAX::CatalysisPtr new_cat = mia.createInstance<UniPAX::Catalysis>(created);
				if (!created)
				{
					std::cerr << "splitByUXref: Could not create a new Catalysis object." << std::endl;
					return false;
				}
				std::cout << "splitByUXref: Created a new Catalysis object with id " << new_cat->getUnipaxId() << std::endl;
				save = new_cat->getUnipaxId();
				*new_cat = *cat;
				new_cat->setUnipaxId(save);
				new_cat->getControllers().clear();
				new_cat->addController(new_ety);
				// Find relevant Pathway object and link new Catalysis object
				UniPAX::PathwayPtr pwy;
				for (std::vector<UniPAX::UPBasePtr>::const_iterator it = pathways.begin(); it != pathways.end(); ++it)
				{
					UniPAX::PathwayPtr some_pwy = boost::dynamic_pointer_cast<UniPAX::Pathway>(*it);
					for (std::vector<UniPAX::EntityPtr>::iterator et = some_pwy->getPathwayComponents().begin(); et != some_pwy->getPathwayComponents().end(); et++)
					{
						if ((*et)->getTypeID() == UniPAX::ClassType::idCatalysis)
						{
							if (boost::dynamic_pointer_cast<UniPAX::Catalysis>(*et) == cat)
							{
								pwy = some_pwy;
							}
						}
					}
				}
				if (pwy == 0)
				{
					std::cerr << "splitByUXref: Could not find a Pathway linking the object." << std::endl;
					return false;
				}
				pwy->addPathwayComponent(new_cat);
			}
		}
		// delete link to cat in pw
		for (std::vector<UniPAX::UPBasePtr>::const_iterator it = pathways.begin(); it != pathways.end(); ++it)
		{
			UniPAX::PathwayPtr some_pwy = boost::dynamic_pointer_cast<UniPAX::Pathway>(*it);
			for (std::vector<UniPAX::EntityPtr>::iterator et = some_pwy->getPathwayComponents().begin(); et != some_pwy->getPathwayComponents().end(); et++)
			{
				if ((*et)->getTypeID() == UniPAX::ClassType::idCatalysis)
				{
					for (std::vector<UniPAX::CatalysisPtr>::const_iterator cit = cat_vec.begin(); cit != cat_vec.end(); ++cit)
					{
						UniPAX::CatalysisPtr cat = *cit;

						if (boost::dynamic_pointer_cast<UniPAX::Catalysis>(*et) == cat)
						{
							some_pwy->getPathwayComponents().erase(et);
							break;
						}
					}
				}
			}
		}
		// delete cat, prot, ref
		for (std::vector<UniPAX::CatalysisPtr>::const_iterator cit = cat_vec.begin(); cit != cat_vec.end(); ++cit)
		{
			if (!mia.removeInstance(*cit))
			{
				std::cerr << "splitByUXref: Could not remove old objects from PersistenceManager." << std::endl;
				return false;
			}
		}
		if (!(mia.removeInstance(prot) && mia.removeInstance(ref)))
		{
			std::cerr << "splitByUXref: Could not remove old objects from PersistenceManager." << std::endl;
			return false;
		}


//		std::vector<std::string> uris = miriam.getDataTypeURIs("UniProt");
//		for (std::vector<std::string>::const_iterator it = uris.begin(); it != uris.end(); ++it)
//		{
//			std::cout << *it << std::endl;
//		}
//		QUrl endpoint;
//		endpoint.setHost(QString("http://webservice.bridgedb.org"));
//		endpoint.setPort(80);
//		UniPAX::BridgeDBLink bridge(endpoint);
		e++;
	}
	return true;
}

int main(int argC, char** argV)
{
	QApplication a(argC, argV);

	boost::program_options::options_description desc("Allowed options");
	bool debug = false;
	std::string input_file;
	std::string db_host, db_name, db_user, db_passw, output_file, id, service_name;
	int db_port;
	desc.add_options()
						("help,h", "produce help message")
						("debug,d", "use debug modus. Prints out debug information during parse.")
						("strict,s", "use strict modus. Will exit on data inconsistency.")
						("input-file,i", boost::program_options::value< std::string >(&input_file), "BioPAX input file to parse")
						("output-file,o", boost::program_options::value< std::string >(&output_file), "output file to write to")
						;
	boost::program_options::positional_options_description pod;
	pod.add("input-file", -1);
	pod.add("output-file", -1);
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (argC == 1 || vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}
	if (vm.count("debug"))
	{
		debug = true;
		std::cout << "Debug output activated." << std::endl;
	}
	UniPAX::MergerInputAdapter mip;
	UnipaxPtr<UniPAX::PersistenceManager>::type pm;
	// Read in file
	{
		UniPAX::BIOPAXReader reader;
		reader.setDebug(debug);
		reader.setErrorOnInconsistentData(vm.count("strict"));
		{
			reader.createObjectsOnly(true);
			reader.setFilename(input_file);
			reader.parse();

			std::cout << "Number of parsed objects (first round): " << reader.getData().size() << std::endl;

			reader.createObjectsOnly(false);
			reader.parse();

			std::cout << "Number of parsed objects: " << reader.getData().size() << std::endl;

		}
		pm = UnipaxPtr<UniPAX::PersistenceManager>::type(new UniPAX::PersistenceManager(reader.getPersistenceManager()));
		mip = UniPAX::MergerInputAdapter(pm, &nextId);
	}

	// Do corrections to data:
	// issues to solve:
	// ProteinReferences are missing organism property values
	// Add missing BioSource to ProteinReferences
	{
		bool created = false;
		UniPAX::UnificationXrefPtr uxr = mip.createInstance<UniPAX::UnificationXref>(created);
		if (!created)
		{
			std::cerr << "Could not create UnificationXref object." << std::endl;
			return 1;
		}
		uxr->setId("10090");
		uxr->setDb("Taxonomy");

		created = false;
		UniPAX::BioSourcePtr org = mip.createInstance<UniPAX::BioSource>(created);
		if (!created)
		{
			std::cerr << "Could not create BioSource object." << std::endl;
			return 1;
		}
		org->addXref(uxr);
		org->setDisplayName("Mouse");
		org->setStandardName("Mus musculus");

		std::vector<UniPAX::UPBasePtr> proteinReferences;
		if (!mip.getObjectsByType(proteinReferences, "ProteinReference"))
		{
			std::cerr << "Could not retrieve ProteinReference objects." << std::endl;
			return 1;
		}
		for (std::vector<UniPAX::UPBasePtr>::iterator pit = proteinReferences.begin(); pit != proteinReferences.end(); ++pit)
		{
			boost::dynamic_pointer_cast<UniPAX::ProteinReference>(*pit)->setOrganism(org);
		}
	}
	// Shared UnificationXref for multiple elements
	std::multimap<std::string, std::string> type_ids;
	for (std::map<UniPAX::UPBasePtr, UnipaxId>::const_iterator it = mip.getPtrIdMap().begin(); it != mip.getPtrIdMap().end(); ++it)
	{
		type_ids.insert(std::pair<std::string, std::string>(it->first->getType(), boost::lexical_cast<std::string>(it->second)));
	}

	if (!splitByUXref<UniPAX::Protein, UniPAX::ProteinReference>(type_ids, mip))
	{
		std::cerr << "Splitting ProteinReferences failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Splitting ProteinReferences succeded." << std::endl;
	}
	type_ids.clear();
	for (std::map<UniPAX::UPBasePtr, UnipaxId>::const_iterator it = mip.getPtrIdMap().begin(); it != mip.getPtrIdMap().end(); ++it)
	{
	//	std::cout << "it->first->getType(): " << it->first->getType() << " it->second: " << it->second << std::endl;
		type_ids.insert(std::pair<std::string, std::string>(it->first->getType(), boost::lexical_cast<std::string>(it->second)));
	}
	// Doubled ProteinReferences, doubled Proteins : Merge References
	if (!mergeReferences<UniPAX::ProteinReference>(type_ids, pm))
	{
		std::cerr << "Merge of ProteinReferences failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Merging ProteinReferences succeded." << std::endl;
	}
	// affected Proteins are updated in merge
	// Merge Proteins
	if (!mergeByReference<UniPAX::Protein>(type_ids, pm))
	{
		std::cerr << "Merge of Proteins failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Merging Proteins succeded." << std::endl;
	}
	// Update affected Catalysis objects!
	{
		std::vector<UniPAX::UPBasePtr> catalyses;
		if (!mip.getObjectsByType(catalyses, "Catalysis"))
		{
			std::cerr << "Could not retrieve Catalysis objects." << std::endl;
			return 1;
		}
		for (std::vector<UniPAX::UPBasePtr>::iterator it = catalyses.begin(); it != catalyses.end(); ++it)
		{
			UniPAX::CatalysisPtr cat = boost::dynamic_pointer_cast<UniPAX::Catalysis>(*it);
			cat->update(*pm);
		}
		std::cout << "Updated Catalyses." << std::endl;
	}
	// Doubled SmallMoleculeReferences, doubled SmallMolecules : Merge References
	if (!mergeReferences<UniPAX::SmallMoleculeReference>(type_ids, pm))
	{
		std::cerr << "Merge of SmallMoleculeReferences failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Merging SmallMoleculeReferences succeded." << std::endl;
	}
	// affected SmallMolecules are updated in merge
	// Merge SmallMolecules
	if (!mergeByReference<UniPAX::SmallMolecule>(type_ids, pm))
	{
		std::cerr << "Merge of SmallMolecules failed." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Merging SmallMolecules succeded." << std::endl;
	}
	// Update affected BiochemicalReaction and Stoichiometry objects!
	{
		std::vector<UniPAX::UPBasePtr> update_objects;
		if (!mip.getObjectsByType(update_objects, "Stoichiometry"))
		{
			std::cerr << "Could not retrieve Stoichiometry objects." << std::endl;
			return 1;
		}
		for (std::vector<UniPAX::UPBasePtr>::iterator it = update_objects.begin(); it != update_objects.end(); ++it)
		{
			UniPAX::StoichiometryPtr obj = boost::dynamic_pointer_cast<UniPAX::Stoichiometry>(*it);
			obj->update(*pm);
		}
		std::cout << "Updated Stoichiometries." << std::endl;
		update_objects.clear();
		if (!mip.getObjectsByType(update_objects, "BiochemicalReaction"))
		{
			std::cerr << "Could not retrieve BiochemicalReaction objects." << std::endl;
			return 1;
		}
		for (std::vector<UniPAX::UPBasePtr>::iterator it = update_objects.begin(); it != update_objects.end(); ++it)
		{
			UniPAX::BiochemicalReactionPtr obj = boost::dynamic_pointer_cast<UniPAX::BiochemicalReaction>(*it);
			obj->update(*pm);
		}
		std::cout << "Updated BiochemicalReactions	." << std::endl;
	}

	// Catalysis, BiochemicalReaction displayName="Unnamed process"
	{
		//TODO decide if this should really be fixed here!
	}
	// Remove merged objects
	if (!removeMergedObjects(mip))
	{
		std::cerr << "Could not remove merged objects." << std::endl;
		return 1;
	}
	// Write out file
	{
		UniPAX::BIOPAXWriter writer;
		writer.setDebug(debug);
		writer.setExportType(UniPAX::BIOPAXWriter::INTEGRATIVE_EXPORT);
		//	writer.setExportType(UniPAX::BIOPAXWriter::SERIAL_EXPORT);
		writer.setPersistenceManager(*pm);
		writer.write(output_file);
	}
	return 0;
}

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

#include <APPLICATIONS/IMPORT/KEGGIMPORTER/KEGGMapper.h>
#include <set>
#include <string>
#include <vector>


namespace UniPAX
{

KEGGMapper::KEGGMapper(PersistenceManager& _manager) :
								kegg_connection(),
								current(),
								previous(),
								kegg(),
								manager(_manager),
								next_free_id(0)
{
}

void KEGGMapper::setKEGGDatabase(DBConnection* connection, std::string version)
{
	this->kegg_connection = connection;
}

void KEGGMapper::setPreviousImportSource(boost::shared_ptr<ImportSource> _previous)
{
	this->previous = _previous;
}

PersistenceManager& KEGGMapper::getPersistenceManager()
{
	return manager;
}

const PersistenceManager& KEGGMapper::getPersistenceManager() const
{
	return manager;
}

void KEGGMapper::setPersistenceManager(PersistenceManager& manager)
{
	this->manager = manager;
}




void KEGGMapper::createCrossReference(boost::shared_ptr<UniPAX::Entity> entity, std::string dbName, std::string id)
{
	if (dbName == "NCBI-GI" || dbName == "NCBI-GeneID")
	{
		if (dbName == "NCBI-GeneID")
			dbName = "EntrezGene";
		boost::shared_ptr<UniPAX::RelationshipXref> xref = createInstance<UniPAX::RelationshipXref>(dbName + "_" + id);
		xref->setDb(dbName);
		xref->setId(id);
		entity->addXref(xref);

		return;
	}

	boost::shared_ptr<UniPAX::UnificationXref> xref = createInstance<UnificationXref>(dbName + "_" + id);
	xref->setDb(dbName);
	xref->setId(id);
	entity->addXref(xref);
}

void KEGGMapper::createCrossReference(boost::shared_ptr<UniPAX::EntityReference> entityReference, std::string dbName, std::string id)
{
	if (dbName == "NCBI-GI" || dbName == "NCBI-GeneID")
	{
		if (dbName == "NCBI-GeneID")
			dbName = "EntrezGene";
		boost::shared_ptr<UniPAX::RelationshipXref> xref = createInstance<RelationshipXref>(dbName + "_" + id);
		xref->setDb(dbName);
		xref->setId(id);
		entityReference->addXref(xref);

		return;
	}

	boost::shared_ptr<UniPAX::UnificationXref> xref = createInstance<UnificationXref>(dbName + "_" + id);
	xref->setDb(dbName);
	xref->setId(id);
	entityReference->addXref(xref);
}


boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> KEGGMapper::getEntityReferenceTypeVocabulary(std::string term)
{
	boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> voc = createInstance<EntityReferenceTypeVocabulary>(term);
	voc->setTerm(term);

	return voc;

}

boost::shared_ptr<UniPAX::SequenceModificationVocabulary> KEGGMapper::getSequenceModificationVocabulary(std::string term)
{
	boost::shared_ptr<UniPAX::SequenceModificationVocabulary> voc = createInstance<SequenceModificationVocabulary>(term);
	voc->setTerm(term);

	return voc;
}


template<typename _Container> boost::shared_ptr<Complex> KEGGMapper::createComplex(_Container & components)
{
	boost::shared_ptr<Complex> complex = createInstance<Complex>(current_ori, "");
	registerEntity(complex);

	StringVector component_names;

	for (typename _Container::const_iterator it = components.begin(); it != components.end(); ++it)
	{
		boost::shared_ptr<PhysicalEntity> component = boost::dynamic_pointer_cast<PhysicalEntity>(*it);
		if (component != 0)
		{
			if (component->getDisplayName() != "")
				component_names.push_back(component->getDisplayName());
			else if (component->getStandardName() != "")
				component_names.push_back(component->getStandardName());
			else if (component->getFirstName() != "")
				component_names.push_back(component->getFirstName());

			complex->addComponent(component);
		}
	}

	if (!component_names.empty())
	{
		complex->setDisplayName("[" + collate(component_names, ", ") + "]");
	}

	return complex;
}

boost::shared_ptr<EntityReference> KEGGMapper::getEntityReference(std::string id)
{
	if (proteinReferenceMapOrg.find(id) != proteinReferenceMapOrg.end())
	{
		return proteinReferenceMapOrg[id];
	}
	else if (rnaReferenceMapOrg.find(id) != rnaReferenceMapOrg.end())
	{
		return rnaReferenceMapOrg[id];
	}
	else if (dnaRegionReferenceMapOrg.find(id) != dnaRegionReferenceMapOrg.end())
	{
		return dnaRegionReferenceMapOrg[id];
	}
	else if (smallMoleculeReferenceMap.find(id) != smallMoleculeReferenceMap.end())
	{
		return smallMoleculeReferenceMap[id];
	}
	else
	{
		return boost::shared_ptr<EntityReference>();
	}
}

boost::shared_ptr<SmallMolecule> KEGGMapper::createSmallMolecule(boost::shared_ptr<SmallMoleculeReference> & reference)
{
	boost::shared_ptr<SmallMolecule> small_molecule = createInstance<SmallMolecule>(current_ori, "");
	registerEntity(small_molecule);

	small_molecule->addEntityReference(reference);
	small_molecule->setNames(reference->getNames());
	if (reference->getStandardName() != "")
		small_molecule->setStandardName(reference->getStandardName());
	if (reference->getDisplayName() != "")
		small_molecule->setDisplayName(reference->getDisplayName());

	return small_molecule;
}


boost::shared_ptr<Protein> KEGGMapper::createProtein(boost::shared_ptr<ProteinReference> & reference)
{
	boost::shared_ptr<Protein> protein = createInstance<Protein>(current_ori, "");
	registerEntity(protein);

	protein->addEntityReference(reference);
	protein->setNames(reference->getNames());
	if (reference->getStandardName() != "")
		protein->setStandardName(reference->getStandardName());
	if (reference->getDisplayName() != "")
		protein->setDisplayName(reference->getDisplayName());

	return protein;
}

boost::shared_ptr<Rna> KEGGMapper::createRna(boost::shared_ptr<RnaReference> & reference)
{
	boost::shared_ptr<Rna> rna = createInstance<Rna>(current_ori, "");
	registerEntity(rna);

	rna->addEntityReference(reference);
	rna->setNames(reference->getNames());
	if (reference->getStandardName() != "")
		rna->setStandardName(reference->getStandardName());
	if (reference->getDisplayName() != "")
		rna->setDisplayName(reference->getDisplayName());

	return rna;
}

boost::shared_ptr<Protein> KEGGMapper::createProteinFamily(boost::shared_ptr<ProteinReference> & reference)
{
	boost::shared_ptr<Protein> family = createInstance<Protein>(current_ori, "");
	registerEntity(family);

	family->addEntityReference(reference);
	family->setNames(reference->getNames());
	if (reference->getStandardName() != "")
		family->setStandardName(reference->getStandardName());
	if (reference->getDisplayName() != "")
		family->setDisplayName(reference->getDisplayName());

	return family;
}

boost::shared_ptr<ProteinReference> KEGGMapper::createProteinFamilyReference(StringSet & members)
{
	boost::shared_ptr<ProteinReference> family = createInstance<ProteinReference>(current_ori, "");
	family->setOrganism(current_org);

	StringSet names;

	for (StringSet::const_iterator it = members.begin(); it != members.end(); ++it)
	{
		boost::shared_ptr<ProteinReference> ref = getProteinReference(*it);
		family->addMemberEntityReference(ref);

		if (ref->getDisplayName() != "")
		{
			names.insert(ref->getDisplayName());
		}
	}

	std::string family_name = getProteinFamilyName(members);
	if (family_name != "")
		family->setDisplayName(family_name);

	if (!names.empty())
	{
		family->setStandardName("{" + collate(names, ", ") + "}");
	}

	StringSet koIds = getKOIds(members);
	if (koIds.size() > 0)
	{
		for (StringSet::const_iterator it = koIds.begin(); it != koIds.end(); ++it)
		{
			family->addName(*it);
			createCrossReference(family, "KO", *it);
		}
	}



	return family;
}



void KEGGMapper::addModificationFeature(boost::shared_ptr<PhysicalEntity> physicalEntity, std::string modification)
{
	if (modification == "active" || modification == "inactive" || modification == "activated" || modification == "inactivated")
	{
		if (QString::fromStdString(modification).startsWith("activ"))
		{
			boost::shared_ptr<UniPAX::EntityFeature> feature = createInstance<EntityFeature>(current_ori, "active");
			feature->addComment("ACTIVE");
			physicalEntity->addFeature(feature);
		}
		else
		{
			boost::shared_ptr<UniPAX::EntityFeature> feature = createInstance<EntityFeature>(current_ori, "inactive");
			feature->addComment("INACTIVE");
			physicalEntity->addFeature(feature);
		}
	}
	else
	{
		boost::shared_ptr<UniPAX::ModificationFeature> feature = createInstance<ModificationFeature>(current_ori, modification);
		feature->setModificationType(getSequenceModificationVocabulary(modification));
		physicalEntity->addFeature(feature);
	}
}

boost::shared_ptr<ProteinReference> KEGGMapper::getProteinReference(std::string kegg_id)
{
	if (proteinReferenceMapOrg.find(kegg_id) != proteinReferenceMapOrg.end())
	{
		return proteinReferenceMapOrg[kegg_id];
	}

	throw std::runtime_error("Unable to find protein reference of " + kegg_id);
}

boost::shared_ptr<PhysicalEntity> KEGGMapper::getDefaultInstance(std::string kegg_id)
{
	if (proteinReferenceMapOrg.find(kegg_id) != proteinReferenceMapOrg.end())
	{
		if (defaultProteinInstanceMapOrg.find(kegg_id) == defaultProteinInstanceMapOrg.end()) {
			boost::shared_ptr<Protein> protein = createProtein(proteinReferenceMapOrg[kegg_id]);
			createCrossReference(boost::dynamic_pointer_cast<Entity>(protein), std::string("KEGG"), std::string(current_ori + "_" + kegg_id));
			defaultProteinInstanceMapOrg[kegg_id] = protein;
		}

		return defaultProteinInstanceMapOrg[kegg_id];
	}

	if (smallMoleculeReferenceMap.find(kegg_id) != smallMoleculeReferenceMap.end())
	{
		if (defaultSmallMoleculeInstanceMap.find(kegg_id) == defaultSmallMoleculeInstanceMap.end()) {
			boost::shared_ptr<SmallMolecule> sm = createSmallMolecule(smallMoleculeReferenceMap[kegg_id]);
			createCrossReference(boost::dynamic_pointer_cast<Entity>(sm), std::string("KEGG"), std::string(kegg_id));
			defaultSmallMoleculeInstanceMap[kegg_id] = sm;
		}

		return defaultSmallMoleculeInstanceMap[kegg_id];
	}

	//throw std::runtime_error("Unable to find reference instance for " + kegg_id);
	return boost::shared_ptr<PhysicalEntity>();
}


boost::shared_ptr<PhysicalEntity> KEGGMapper::getDefaultInstance(std::tr1::unordered_map<std::string, boost::shared_ptr<Entry> > & entry_map, boost::shared_ptr<Entry> & entry)
{
	if (entry->type == "compound")
	{
		std::string compound_id = entry->geneIds[0];

		if (smallMoleculeReferenceMap.find(compound_id) != smallMoleculeReferenceMap.end())
		{
			boost::shared_ptr<SmallMoleculeReference> reference = smallMoleculeReferenceMap[compound_id];

			if (defaultSmallMoleculeInstanceMap.find(compound_id) == defaultSmallMoleculeInstanceMap.end())
			{

				boost::shared_ptr<SmallMolecule> small_molecule = createSmallMolecule(reference);

				createCrossReference(boost::dynamic_pointer_cast<Entity>(small_molecule), std::string("KEGG"), compound_id);

				defaultSmallMoleculeInstanceMap[compound_id] = small_molecule;
			}

			return defaultSmallMoleculeInstanceMap[compound_id];
		}
		else
		{
			throw std::runtime_error("Small molecule reference " + compound_id + " not found for entry " + entry->toString());
		}
	}
	else if (entry->type == "protein")
	{
		std::string protein_id = entry->geneIds[0];

		if (proteinReferenceMapOrg.find(protein_id) != proteinReferenceMapOrg.end())
		{
			boost::shared_ptr<ProteinReference> reference = proteinReferenceMapOrg[protein_id];

			if (defaultProteinInstanceMapOrg.find(protein_id) == defaultProteinInstanceMapOrg.end())
			{

				boost::shared_ptr<Protein> protein = createProtein(reference);

				createCrossReference(boost::dynamic_pointer_cast<Entity>(protein), std::string("KEGG"), std::string(current_ori + "_" + protein_id));

				defaultProteinInstanceMapOrg[protein_id] = protein;
			}

			return defaultProteinInstanceMapOrg[protein_id];
		}
		else if (rnaReferenceMapOrg.find(protein_id) != rnaReferenceMapOrg.end())
		{
			boost::shared_ptr<RnaReference> reference = rnaReferenceMapOrg[protein_id];

			if (defaultRnaInstanceMapOrg.find(protein_id) == defaultRnaInstanceMapOrg.end())
			{

				boost::shared_ptr<Rna> rna = createRna(reference);

				createCrossReference(boost::dynamic_pointer_cast<Entity>(rna), std::string("KEGG"), std::string(current_ori + "_" + protein_id));

				defaultRnaInstanceMapOrg[protein_id] = rna;
			}

			return defaultRnaInstanceMapOrg[protein_id];
		}
		else
		{
			throw std::runtime_error("Protein/Rna reference " + protein_id + " not found for entry " + entry->toString());
		}
	}
	else if (entry->type == "complex")
	{
		std::set<boost::shared_ptr<PhysicalEntity> > components;

		for (Entry::ComponentIter it = entry->components.begin(); it != entry->components.end(); ++it)
		{
			if (entry_map.find(*it) != entry_map.end())
			{
				components.insert(getDefaultInstance(entry_map, entry_map[*it]));
			}
			else
			{
				throw std::runtime_error("Unable to find complex component entry " + *it + " of entry " + entry->toString());
			}
		}

		for (Entry::GeneIdIter it = entry->geneIds.begin(); it != entry->geneIds.end(); ++it)
		{
			components.insert(getDefaultInstance(*it));
		}

		if (defaultProteinComplexInstanceMapOrg.find(components) == defaultProteinComplexInstanceMapOrg.end())
		{
			boost::shared_ptr<Complex> complex = createComplex(components);
			defaultProteinComplexInstanceMapOrg[components] = complex;
		}

		return defaultProteinComplexInstanceMapOrg[components];

	}
	else if (entry->type == "family")
	{
		StringSet members(entry->geneIds.begin(), entry->geneIds.end());

		if (proteinFamilyReferenceMapOrg.find(members) == proteinFamilyReferenceMapOrg.end())
		{
			proteinFamilyReferenceMapOrg[members] = createProteinFamilyReference(members);
		}

		if (defaultProteinFamilyInstanceMapOrg.find(members) == defaultProteinFamilyInstanceMapOrg.end())
		{
			boost::shared_ptr<Protein> family = createProteinFamily(proteinFamilyReferenceMapOrg[members]);

			createCrossReference(boost::dynamic_pointer_cast<Entity>(family), std::string("KEGG"), collate(prefix(members, current_ori + "_"), std::string(","), true));

			defaultProteinFamilyInstanceMapOrg[members] = family;
		}

		return defaultProteinFamilyInstanceMapOrg[members];
	}

	throw std::runtime_error("Unable to create default instance for entry " + entry->toString());
}

boost::shared_ptr<Complex> KEGGMapper::getDefaultComplexInstance(std::set<boost::shared_ptr<PhysicalEntity> > components)
{
	if (defaultProteinComplexInstanceMapOrg.find(components) == defaultProteinComplexInstanceMapOrg.end())
	{
		defaultProteinComplexInstanceMapOrg[components] = createComplex(components);
	}

	return defaultProteinComplexInstanceMapOrg[components];
}

std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<Complex> > KEGGMapper::getModifiedComplexInstance(std::set<boost::shared_ptr<PhysicalEntity> > components, StringSet modifications)
{

	std::pair<std::set<boost::shared_ptr<PhysicalEntity> >, StringSet> key = std::make_pair(components, modifications);

	if (modifiedProteinComplexInstanceMapOrg.find(key) == modifiedProteinComplexInstanceMapOrg.end())
	{
		boost::shared_ptr<Complex> complex = createComplex(components);

		for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
			addModificationFeature(complex, *it);

		boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
		registerEntity(conversion);

		conversion->addLeft(getDefaultComplexInstance(components));
		conversion->addRight(complex);



		modifiedProteinComplexInstanceMapOrg[key] = std::make_pair(conversion, complex);
	}

	return modifiedProteinComplexInstanceMapOrg[key];
}

boost::shared_ptr<ComplexAssembly> KEGGMapper::getComplexAssembly(boost::shared_ptr<Complex> complex)
{
	if (proteinComplexAssemblyMapOrg.find(complex) == proteinComplexAssemblyMapOrg.end())
	{
		boost::shared_ptr<ComplexAssembly> assembly = createInstance<ComplexAssembly>(current_ori, "");
		registerEntity(assembly);

		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > components = complex->getComponents();
		for (std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::const_iterator it = components.begin(); it != components.end(); ++it)
		{
			assembly->addLeft(*it);
		}

		assembly->addRight(complex);

		proteinComplexAssemblyMapOrg[complex] = assembly;
	}

	return proteinComplexAssemblyMapOrg[complex];
}

boost::shared_ptr<ComplexAssembly> KEGGMapper::getComplexDisassembly(boost::shared_ptr<Complex> complex)
{
	if (proteinComplexDisassemblyMapOrg.find(complex) == proteinComplexDisassemblyMapOrg.end())
	{
		boost::shared_ptr<ComplexAssembly> disassembly = createInstance<ComplexAssembly>(current_ori, "");
		registerEntity(disassembly);

		disassembly->addLeft(complex);

		std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> > components = complex->getComponents();
		for (std::vector<boost::shared_ptr<UniPAX::PhysicalEntity> >::const_iterator it = components.begin(); it != components.end(); ++it)
		{
			disassembly->addRight(*it);
		}

		proteinComplexDisassemblyMapOrg[complex] = disassembly;
	}

	return proteinComplexDisassemblyMapOrg[complex];
}


boost::shared_ptr<TemplateReaction> KEGGMapper::getTemplateReaction(boost::shared_ptr<PhysicalEntity> target)
{
	if (templateReactionMapOrg.find(target) == templateReactionMapOrg.end())
	{
		boost::shared_ptr<TemplateReaction> templateReaction = createInstance<TemplateReaction>(current_ori, "");
		registerEntity(templateReaction);

		// TODO: templateReaction->setTemplateEntity()

		templateReaction->addProduct(target);

		templateReactionMapOrg[target] = templateReaction;
	}

	return templateReactionMapOrg[target];
}

std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<PhysicalEntity> > KEGGMapper::getModifiedInstance(std::tr1::unordered_map<std::string, boost::shared_ptr<Entry> > & entry_map, boost::shared_ptr<Entry> & entry, StringSet modifications)
{
	if (entry->type == "compound")
	{
		std::string compound_id = entry->geneIds[0];

		if (smallMoleculeReferenceMap.find(compound_id) != smallMoleculeReferenceMap.end())
		{
			boost::shared_ptr<SmallMoleculeReference> reference = smallMoleculeReferenceMap[compound_id];

			std::pair<std::string, StringSet> key = std::make_pair(compound_id, modifications);

			if (modifiedSmallMoleculeInstanceMap.find(key) == modifiedSmallMoleculeInstanceMap.end())
			{

				boost::shared_ptr<SmallMolecule> small_molecule = createSmallMolecule(reference);

				for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
					addModificationFeature(small_molecule, *it);

				if (modifications.empty())
					addModificationFeature(small_molecule, "unknown");

				createCrossReference(boost::dynamic_pointer_cast<Entity>(small_molecule), std::string("KEGG"), compound_id);

				boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
				registerEntity(conversion);

				conversion->addLeft(getDefaultInstance(entry_map, entry));
				conversion->addRight(small_molecule);

				modifiedSmallMoleculeInstanceMap[key] = std::make_pair(conversion, small_molecule);
			}

			return modifiedSmallMoleculeInstanceMap[key];
		}
		else
		{
			throw std::runtime_error("Small molecule reference " + compound_id + " not found.");
		}
	}
	else if (entry->type == "protein")
	{
		std::string protein_id = entry->geneIds[0];

		if (proteinReferenceMapOrg.find(protein_id) != proteinReferenceMapOrg.end())
		{
			boost::shared_ptr<ProteinReference> reference = proteinReferenceMapOrg[protein_id];

			std::pair<std::string, StringSet> key = std::make_pair(protein_id, modifications);

			if (modifiedProteinInstanceMapOrg.find(key) == modifiedProteinInstanceMapOrg.end())
			{

				boost::shared_ptr<Protein> protein = createProtein(reference);

				for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
					addModificationFeature(protein, *it);

				if (modifications.empty())
					addModificationFeature(protein, "unknown");

				createCrossReference(boost::dynamic_pointer_cast<Entity>(protein), std::string("KEGG"), std::string(current_ori + "_" + protein_id));


				boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
				registerEntity(conversion);

				conversion->addLeft(getDefaultInstance(entry_map, entry));
				conversion->addRight(protein);

				modifiedProteinInstanceMapOrg[key] = std::make_pair(conversion, protein);
			}

			return modifiedProteinInstanceMapOrg[key];
		}
		else if (rnaReferenceMapOrg.find(protein_id) != rnaReferenceMapOrg.end())
		{
			boost::shared_ptr<RnaReference> reference = rnaReferenceMapOrg[protein_id];

			std::pair<std::string, StringSet> key = std::make_pair(protein_id, modifications);

			if (modifiedRnaInstanceMapOrg.find(key) == modifiedRnaInstanceMapOrg.end())
			{

				boost::shared_ptr<Rna> rna = createRna(reference);

				for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
					addModificationFeature(rna, *it);

				if (modifications.empty())
					addModificationFeature(rna, "unknown");

				createCrossReference(boost::dynamic_pointer_cast<Entity>(rna), std::string("KEGG"), std::string(current_ori + "_" + protein_id));


				boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
				registerEntity(conversion);

				conversion->addLeft(getDefaultInstance(entry_map, entry));
				conversion->addRight(rna);

				modifiedRnaInstanceMapOrg[key] = std::make_pair(conversion, rna);
			}

			return modifiedRnaInstanceMapOrg[key];
		}
		else
		{
			throw std::runtime_error("Protein/Rna reference " + protein_id + " not found.");
		}
	}
	else if (entry->type == "complex")
	{
		std::set<boost::shared_ptr<PhysicalEntity> > components;

		for (Entry::ComponentIter it = entry->components.begin(); it != entry->components.end(); ++it)
		{
			if (entry_map.find(*it) != entry_map.end())
			{
				components.insert(getDefaultInstance(entry_map, entry_map[*it]));
			}
			else
			{
				throw std::runtime_error("Unable to find complex component entry " + *it + " of entry " + entry->toString());
			}
		}

		for (Entry::GeneIdIter it = entry->geneIds.begin(); it != entry->geneIds.end(); ++it)
		{
			components.insert(getDefaultInstance(*it));
		}

		std::pair<std::set<boost::shared_ptr<PhysicalEntity> >, StringSet> key = std::make_pair(components, modifications);

		if (modifiedProteinComplexInstanceMapOrg.find(key) == modifiedProteinComplexInstanceMapOrg.end())
		{
			boost::shared_ptr<Complex> complex = createComplex(components);

			for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
				addModificationFeature(complex, *it);

			if (modifications.empty())
				addModificationFeature(complex, "unknown");

			boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
			registerEntity(conversion);

			conversion->addLeft(getDefaultInstance(entry_map, entry));
			conversion->addRight(complex);

			modifiedProteinComplexInstanceMapOrg[key] = std::make_pair(conversion, complex);
		}

		return modifiedProteinComplexInstanceMapOrg[key];

	}
	else if (entry->type == "family")
	{
		StringSet members(entry->geneIds.begin(), entry->geneIds.end());

		if (proteinFamilyReferenceMapOrg.find(members) == proteinFamilyReferenceMapOrg.end())
		{
			proteinFamilyReferenceMapOrg[members] = createProteinFamilyReference(members);
		}

		std::pair<StringSet, StringSet> key = std::make_pair(members, modifications);

		if (modifiedProteinFamilyInstanceMapOrg.find(key) == modifiedProteinFamilyInstanceMapOrg.end())
		{
			boost::shared_ptr<Protein> family = createProteinFamily(proteinFamilyReferenceMapOrg[members]);

			for (StringSet::const_iterator it = modifications.begin(); it != modifications.end(); ++it)
				addModificationFeature(family, *it);

			if (modifications.empty())
				addModificationFeature(family, "unknown");

			createCrossReference(boost::dynamic_pointer_cast<Entity>(family), std::string("KEGG"), std::string(collate(prefix(members, current_ori + "_"), ",")));

			boost::shared_ptr<Conversion> conversion = createInstance<Conversion>(current_ori, "");
			registerEntity(conversion);

			conversion->addLeft(getDefaultInstance(entry_map, entry));
			conversion->addRight(family);

			modifiedProteinFamilyInstanceMapOrg[key] = std::make_pair(conversion, family);
		}

		return modifiedProteinFamilyInstanceMapOrg[key];
	}
	else if (entry->type == "pathway")
	{
		// TODO: think about this
	}

	throw std::runtime_error("Unable to create modified instance for entry " + entry->toString());
}


void KEGGMapper::import(std::vector<std::string> organisms)
{
	kegg = createInstance<Provenance>("KEGG");
	kegg->addName("KEGG");
	kegg->setStandardName("KEGG");
	kegg->setDisplayName("KEGG");

	int count = 0;

	std::cout << "Creating compounds... " << std::flush;
	count = readCompounds();
	std::cout << count << "." << std::endl;

	std::cout << "Creating reactions... " << std::flush;
	count = readReactions();
	std::cout << count << "." << std::endl;

	std::cout << "Creating non-enzymatic reactions... " << std::flush;
	count = readReactionsWithoutEC();
	std::cout << count << "." << std::endl;

	for (StringVector::const_iterator org_iter = organisms.begin(); org_iter != organisms.end(); org_iter++)
	{
		current_ori = *org_iter;

		pathwayMapOrg.clear();

		dnaRegionReferenceMapOrg.clear();

		proteinReferenceMapOrg.clear();
		defaultProteinInstanceMapOrg.clear();
		modifiedProteinInstanceMapOrg.clear();

		defaultProteinComplexInstanceMapOrg.clear();
		modifiedProteinComplexInstanceMapOrg.clear();

		proteinFamilyReferenceMapOrg.clear();
		defaultProteinFamilyInstanceMapOrg.clear();
		modifiedProteinFamilyInstanceMapOrg.clear();

		rnaReferenceMapOrg.clear();
		defaultRnaInstanceMapOrg.clear();
		modifiedRnaInstanceMapOrg.clear();


		proteinComplexAssemblyMapOrg.clear();
		proteinComplexDisassemblyMapOrg.clear();
		templateReactionMapOrg.clear();

		koDescriptionMapOrg.clear();
		koNameMapOrg.clear();
		koGeneMapOrg.clear();
		geneKOMapOrg.clear();


		QSqlQuery* query = kegg_connection->exec("SELECT * FROM Organisms WHERE three_letter_code = ?", current_ori);
		if (query->next())
		{

			std::string abbr = query->value(1).toString().toStdString();

			std::string fullname = query->value(2).toString().toStdString();

			// Create the organism...
			boost::shared_ptr<UniPAX::BioSource> org = createInstance<BioSource>(current_ori);
			org->addName(current_ori);

			if (abbr != "")
			{
				org->setDisplayName(abbr);
			}

			if (fullname != "")
			{
				org->setStandardName(fullname);
			}


			current_org = org;

			std::cout << "Importing organism " << fullname << " (" << current_ori << ")..." << std::endl;

			int count = 0;

			std::cout << "\tReading KO Map... " << std::flush;
			readKOMapOrg();
			std::cout << "done." << std::endl;

			std::cout << "\tReading Genes... " << std::flush;
			count = readGenesOrg();
			std::cout << count << std::endl;

			std::cout << "\tReading Metabolic Pathways... " << std::flush;
			count = readMetabolicPathwaysOrg();
			std::cout << count << std::endl;

			std::cout << "\tReading Reactions... " << std::flush;
			count = readReactionsOrg();
			std::cout << count << std::endl;

			std::cout << "\tReading Regulatory Pathways... " << std::flush;
			count = readRegulatoryPathwaysOrg();
			std::cout << count << std::endl;
		}
	}

}


int KEGGMapper::readCompounds()
{
	int count = 0;

	// Create all KEGG Compounds

	boost::shared_ptr<QSqlQuery> query(kegg_connection->exec("SELECT compoundID FROM Compound"));
	while (query->next())
	{
		count++;

		std::string compoundID = query->value(0).toString().toStdString();

		boost::shared_ptr<UniPAX::SmallMoleculeReference> ref = createInstance<SmallMoleculeReference>(compoundID);

		QSqlQuery* query2 = kegg_connection->exec("SELECT compoundName FROM CompoundName WHERE compoundID = ? ORDER BY LENGTH(compoundName)", compoundID);
		if (query2->next())
		{
			std::string compoundName = query2->value(0).toString().toStdString();
			ref->setDisplayName(compoundName);
		}

		while (query2->next())
		{
			std::string compoundName = query2->value(0).toString().toStdString();
			ref->addName(compoundName);
		}

		query2 = kegg_connection->exec("SELECT compoundFormula FROM CompoundFormula WHERE compoundID= ?", compoundID);
		if (query2->next())
		{
			std::string compoundFormula = query2->value(0).toString().toStdString();

			ref->setChemicalFormula(compoundFormula);
		}

		query2 = kegg_connection->exec("SELECT dbName, linkID FROM CompoundDBLink WHERE compoundID= ?", compoundID);
		while (query2->next())
		{
			std::string dbName = query2->value(0).toString().toStdString();
			std::string linkID = query2->value(1).toString().toStdString();

			createCrossReference(boost::dynamic_pointer_cast<EntityReference>(ref), dbName, linkID);
		}

		query2 = kegg_connection->exec("SELECT compoundMass FROM CompoundMass WHERE compoundID= ?", compoundID);
		if (query2->next())
		{
			double compoundMass = query2->value(0).toDouble();
			ref->setMolecularWeight(compoundMass);
		}

		smallMoleculeReferenceMap[compoundID] = ref;
	}
	query->clear();

	return count;
}


int KEGGMapper::readReactions()
{
	int count = 0;

	// Create KEGG MetaReactions...

	QSqlQuery * query = kegg_connection->exec("SELECT DISTINCT reactionID, equation, direction FROM join5 ORDER BY 1,2");
	while (query->next())
	{
		count++;
		StringVector pathwayIDs;
		StringVector ECs;

		std::string reactionID = query->value(0).toString().toStdString();
		std::string equation_value = query->value(1).toString().toStdString();
		std::string direction = query->value(2).toString().toStdString();

		QSqlQuery* query2;
		if (direction != "")
		{
			query2 = kegg_connection->exec("SELECT DISTINCT pathwayID FROM join4 WHERE reactionID= ? AND direction = ?", reactionID, direction);
		}
		else
		{
			query2 = kegg_connection->exec("SELECT DISTINCT pathwayID FROM join4 WHERE reactionID= ? AND direction IS NULL", reactionID);
		}

		while (query2->next())
		{
			pathwayIDs.push_back(query2->value(0).toString().toStdString());
		}

		if (direction != "")
		{
			query2 = kegg_connection->exec("SELECT DISTINCT EC FROM join5 WHERE reactionID= ? AND direction = ?", reactionID, direction);
		}
		else
		{
			query2 = kegg_connection->exec("SELECT DISTINCT EC FROM join5 WHERE reactionID= ? AND direction IS NULL", reactionID);
		}
		while (query2->next())
		{
			ECs.push_back(query2->value(0).toString().toStdString());
		}

		boost::shared_ptr<UniPAX::BiochemicalReaction> reaction = createInstance<BiochemicalReaction>(reactionID);
		registerEntity(reaction);

		createCrossReference(boost::dynamic_pointer_cast<Entity>(reaction), "KEGG", reactionID);

		if (ECs.size() > 0)
		{
			std::string enzymeclasses = "";

			for (StringVector::size_type i = 0; i < ECs.size(); i++)
			{
				if (enzymeclasses.length() > 0)
					enzymeclasses.append(", ");

				enzymeclasses.append(ECs[i]);
			}

			if (enzymeclasses.length() > 0)
				reaction->setECNumber(enzymeclasses);
		}

		if (direction == "" || direction == "<=>")
		{
			reaction->setConversionDirection("REVERSIBLE");
		}
		else if (direction == "=>")
		{
			reaction->setConversionDirection("LEFT-TO-RIGHT");
		}
		else if (direction == "<=")
		{
			reaction->setConversionDirection("RIGHT-TO-LEFT");
		}

		reaction->addName(equation_value);

		query2 = kegg_connection->exec("SELECT reactionName FROM ReactionName WHERE reactionID = ?", reactionID);
		while (query2->next())
		{
			std::string reactionName = query2->value(0).toString().toStdString();
			reaction->addName(reactionName);
		}

		query2 = kegg_connection->exec("SELECT compoundID, stoich_coeff, type FROM Substrates WHERE reactionID = ?", reactionID);
		while (query2->next())
		{

			std::string compoundID = query2->value(0).toString().toStdString();
			int stoich_coeff = query2->value(1).toInt();
			std::string role_type = query2->value(2).toString().toStdString();
			try {
				boost::shared_ptr<UniPAX::SmallMolecule> sm = boost::dynamic_pointer_cast<SmallMolecule>(getDefaultInstance(compoundID));
				if (sm) {
					if (role_type == "Educt")
						reaction->addLeft(sm);
					else if (role_type == "Product")
						reaction->addRight(sm);
					else if (role_type == "MainEduct")
						reaction->addLeft(sm);
					else if (role_type == "SideEduct")
						reaction->addLeft(sm);
					else if (role_type == "MainProduct")
						reaction->addRight(sm);
					else if (role_type == "SideProduct")
						reaction->addRight(sm);
					else
						std::cout << "Unknown role type: " << role_type << " for reaction/compound " << reactionID << "/" << compoundID << std::endl;
	
					std::stringstream ss;
					ss << reactionID << "_" << compoundID << "_" << stoich_coeff;
					std::string s;
					ss >> s;
					boost::shared_ptr<UniPAX::Stoichiometry> stoi = createInstance<Stoichiometry>(s);
					stoi->setStoichiometricCoefficient(stoich_coeff);
					stoi->setPhysicalEntity(sm);
	
					reaction->addParticipantStoichiometry(stoi);	
				}
				else
				{
					std::cout << "Missing compound: " << compoundID << " for reaction " << reactionID << std::endl;
				}
			}
			catch (...)
			{
				std::cout << "ERROR: Missing compound: " << compoundID << " for reaction " << reactionID << std::endl;
			}
		}

		reactionMap[reactionID] = reaction;
		for (StringVector::const_iterator iter = pathwayIDs.begin(); iter != pathwayIDs.end(); ++iter)
		{
			reactionMap[reactionID + "_" + (*iter)] = reaction;
		}

	}
	query->clear();

	return count;
}


int KEGGMapper::readReactionsWithoutEC()
{
	int count = 0;
	// Create all KEGG MetaReactions without EC


	QSqlQuery * query = kegg_connection->exec("SELECT DISTINCT reactionID, equation, direction, nonEnzymatic FROM join7 ORDER BY 1");
	while (query->next())
	{
		count++;
		std::vector <std::string> pathwayIDs;
		std::string reactionID = query->value(0).toString().toStdString();
		std::string equation_value = query->value(1).toString().toStdString();
		std::string direction = query->value(2).toString().toStdString();
		int nonEnzymatic = query->value(3).toInt();

		QSqlQuery* query2;

		if (direction != "")
			query2 = kegg_connection->exec("SELECT DISTINCT pathwayID FROM join6 WHERE reactionID = ?  AND direction = ? ORDER BY 1", reactionID, direction);
		else
			query2 = kegg_connection->exec("SELECT DISTINCT pathwayID FROM join6 WHERE reactionID = ? AND direction is NULL ORDER BY 1", reactionID);

		while (query2->next())
			pathwayIDs.push_back(query2->value(0).toString().toStdString());

		boost::shared_ptr<UniPAX::BiochemicalReaction> reaction = createInstance<BiochemicalReaction>(reactionID);
		registerEntity(reaction);

		createCrossReference(boost::dynamic_pointer_cast<Entity>(reaction), "KEGG", reactionID);

		if (direction == "" || direction == "<=>")
		{
			reaction->setConversionDirection("REVERSIBLE");
		}
		else if (direction == "=>")
		{
			reaction->setConversionDirection("LEFT-TO-RIGHT");
		}
		else if (direction == "<=")
		{
			reaction->setConversionDirection("RIGHT-TO-LEFT");
		}

		reaction->addName(equation_value);

		query2 = kegg_connection->exec("SELECT reactionName FROM ReactionName WHERE reactionID = ?", reactionID);
		while (query2->next())
		{
			std::string reactionName = query2->value(0).toString().toStdString();
			reaction->addName(reactionName);
		}

		query2 = kegg_connection->exec("SELECT compoundID, stoich_coeff, type FROM Substrates WHERE reactionID = ?", reactionID);
		while (query2->next())
		{

			std::string compoundID = query2->value(0).toString().toStdString();
			int stoich_coeff = query2->value(1).toInt();
			std::string role_type = query2->value(2).toString().toStdString();

			try {
				boost::shared_ptr<UniPAX::SmallMolecule> sm = boost::dynamic_pointer_cast<SmallMolecule>(getDefaultInstance(compoundID));


				if (sm)
				{
					if (role_type == "Educt")
						reaction->addLeft(sm);
					else if (role_type == "Product")
						reaction->addRight(sm);
					else if (role_type == "MainEduct")
						reaction->addLeft(sm);
					else if (role_type == "SideEduct")
						reaction->addLeft(sm);
					else if (role_type == "MainProduct")
						reaction->addRight(sm);
					else if (role_type == "SideProduct")
						reaction->addRight(sm);
					else
						std::cout << "Unknown role type: " << role_type << " for reaction/compound " << reactionID << "/" << compoundID << std::endl;
	
					std::stringstream ss;
					ss << reactionID << "_" << compoundID << "_" << stoich_coeff;
					std::string s;
					ss >> s;
					boost::shared_ptr<UniPAX::Stoichiometry> stoi = createInstance<Stoichiometry>(s);
					stoi->setStoichiometricCoefficient(stoich_coeff);
					stoi->setPhysicalEntity(sm);
	
					reaction->addParticipantStoichiometry(stoi);
				}
				else
				{
					std::cout << "Missing compound: " << compoundID << std::endl;
				}
			}
			catch (...)
			{
				std::cout << "Error: Missing compound: " << compoundID << std::endl;
			}
		}

		reactionMap[reactionID] = reaction;
		for (StringVector::const_iterator iter = pathwayIDs.begin(); iter != pathwayIDs.end(); ++iter)
		{
			reactionMap[reactionID + "_" + (*iter)] = reaction;
		}

		if (nonEnzymatic == 1)
		{
			nonEnzymaticReactions.push_back(reaction);
		}
	}
	query->clear();

	return count;
}

void KEGGMapper::readKOMapOrg()
{
	QSqlQuery* query = kegg_connection->exec("SELECT ko_id, name, description, kegg_id FROM KOEntries WHERE ori = ?", current_ori);
	while (query->next())
	{
		std::string ko_id = query->value(0).toString().toStdString();
		std::string name = query->value(1).toString().toStdString();
		std::string description = query->value(2).toString().toStdString();
		std::string kegg_id = query->value(3).toString().toStdString();

		koGeneMapOrg.insert(std::make_pair(ko_id, kegg_id));
		koNameMapOrg.insert(std::make_pair(ko_id, name));;
		koDescriptionMapOrg[ko_id] = description;

		geneKOMapOrg.insert(std::make_pair(kegg_id, ko_id));
	}
}


int KEGGMapper::readMetabolicPathwaysOrg()
{
	int count = 0;
	int emptyCount = 0;

	// Create KEGG Pathways

	QSqlQuery * query = kegg_connection->exec("SELECT DISTINCT pathwayID, pathwayName FROM join3 WHERE ori = ? ORDER BY 1", current_ori);
	while (query->next())
	{

		std::string pathwayID = query->value(0).toString().toStdString();
		std::string pathwayName = query->value(1).toString().toStdString();

		boost::shared_ptr<UniPAX::Pathway> pathway = createInstance<Pathway>(current_ori + "_" + pathwayID);
		pathway->addName(pathwayName);
		pathway->setStandardName(pathwayName);
		pathway->setDisplayName(pathwayName);
		pathway->setOrganism(current_org);

		++count;

		pathwayMapOrg[pathwayID] = pathway;

		registerEntity(pathway);

		createCrossReference(boost::dynamic_pointer_cast<Entity>(pathway), "KEGG", pathwayID);

	}

	return count;
}


int KEGGMapper::readGenesOrg()
{
	int count = 0;

	QSqlQuery * query = kegg_connection->exec("SELECT ID, type FROM GeneType WHERE ori = ?", current_ori);

	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();
		QString type = query->value(1).toString();

		if (type == "CDS")
		{
			if (dnaRegionReferenceMapOrg.find(id) == dnaRegionReferenceMapOrg.end())
			{
				boost::shared_ptr<UniPAX::DnaRegionReference> dnaRegionReference = createInstance<UniPAX::DnaRegionReference>(current_ori + "_" + id);
				dnaRegionReference->setOrganism(current_org);
				createCrossReference(boost::dynamic_pointer_cast<EntityReference>(dnaRegionReference), std::string("KEGG"), std::string(current_ori + "_" + id));

				dnaRegionReferenceMapOrg[id] = dnaRegionReference;
			}

			if (proteinReferenceMapOrg.find(id) == proteinReferenceMapOrg.end())
			{
				boost::shared_ptr<UniPAX::ProteinReference> proteinReference = createInstance<UniPAX::ProteinReference>(current_ori + "_" + id);
				proteinReference->setOrganism(current_org);
				createCrossReference(boost::dynamic_pointer_cast<EntityReference>(proteinReference), std::string("KEGG"), std::string(current_ori + "_" + id));

				proteinReferenceMapOrg[id] = proteinReference;
			}

			++count;
		}
		else if (type == "gene")
		{
			if (dnaRegionReferenceMapOrg.find(id) == dnaRegionReferenceMapOrg.end())
			{
				boost::shared_ptr<UniPAX::DnaRegionReference> dnaRegionReference = createInstance<UniPAX::DnaRegionReference>(current_ori + "_" + id);
				dnaRegionReference->setOrganism(current_org);
				createCrossReference(boost::dynamic_pointer_cast<EntityReference>(dnaRegionReference), std::string("KEGG"), std::string(current_ori + "_" + id));

				dnaRegionReferenceMapOrg[id] = dnaRegionReference;
			}

			++count;
		}
		else if (type.endsWith("RNA"))
		{
			if (rnaReferenceMapOrg.find(id) == rnaReferenceMapOrg.end())
			{
				boost::shared_ptr<UniPAX::RnaReference> rnaReference = createInstance<UniPAX::RnaReference>(current_ori + "_" + id);
				rnaReference->setOrganism(current_org);
				rnaReference->setEntityReferenceType(getEntityReferenceTypeVocabulary(type.toStdString()));

				createCrossReference(boost::dynamic_pointer_cast<EntityReference>(rnaReference), std::string("KEGG"), std::string(current_ori + "_" + id));

				rnaReferenceMapOrg[id] = rnaReference;
			}

			++count;
		}
	}

	// assign amino acid sequences to ProteinReferences
	query = kegg_connection->exec(std::string("SELECT ID, seq FROM ProteinSequence WHERE ori = ?"), current_ori);
	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();
		std::string sequence_pep = query->value(1).toString().toStdString();

		if (proteinReferenceMapOrg.find(id) != proteinReferenceMapOrg.end())
		{
			proteinReferenceMapOrg[id]->setSequence(sequence_pep);
		}

	}

	query = kegg_connection->exec(std::string("SELECT ID, seq FROM GeneSequence WHERE ori = ?"), current_ori);
	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();
		std::string sequence_nuc = query->value(1).toString().toStdString();

		if (dnaRegionReferenceMapOrg.find(id) != dnaRegionReferenceMapOrg.end())
		{
			dnaRegionReferenceMapOrg[id]->setSequence(sequence_nuc);
		}
		else if (rnaReferenceMapOrg.find(id) != rnaReferenceMapOrg.end())
		{
			rnaReferenceMapOrg[id]->setSequence(sequence_nuc);
		}
	}

	query = kegg_connection->exec("SELECT ID, name FROM GeneName WHERE ori = ?", current_ori);
	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();
		if (!query->value(1).isNull())
		{
			std::string geneName = query->value(1).toString().toStdString();

			if (geneName != "")
			{

				boost::shared_ptr<EntityReference> reference = getEntityReference(id);

				if (reference)
				{
					if (reference->getNames().size() == 0)
					{
						reference->setStandardName(geneName);
						reference->setDisplayName(geneName);
					}
					else
					{
						reference->addName(geneName);
					}
				}

			}
		}
	}


	query = kegg_connection->exec(std::string("SELECT ID, description FROM GeneDescription WHERE ori = ?"), current_ori);
	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();


		if (!query->value(1).isNull())
		{
			std::string geneDesc = query->value(1).toString().toStdString();

			if (geneDesc != "")
			{
				boost::shared_ptr<EntityReference> reference = getEntityReference(id);

				if (reference)
				{
					reference->addComment(geneDesc);
				}
			}
		}
	}

	query = kegg_connection->exec(std::string("SELECT ID, dbName, linkID FROM GeneProteinDBLink WHERE ori = ?"), current_ori);
	while (query->next())
	{
		std::string id = query->value(0).toString().toStdString();
		std::string dbName = query->value(1).toString().toStdString();
		std::string linkID = query->value(2).toString().toStdString();

		boost::shared_ptr<EntityReference> reference = getEntityReference(id);

		if (reference)
		{
			createCrossReference(reference, dbName, linkID);
		}
	}

	return count;
}

int KEGGMapper::readReactionsOrg()
{
	// Create KEGG Reactions
	int count = 0;

	QSqlQuery * query = kegg_connection->exec("SELECT DISTINCT pathwayID, reactionID, equation, direction FROM join1 WHERE ori = ? ORDER BY 1,2", current_ori);

	while (query->next())
	{
		std::string pathwayID = query->value(0).toString().toStdString();
		std::string reactionID = query->value(1).toString().toStdString();
		std::string equation_value = query->value(2).toString().toStdString();
		std::string direction = query->value(3).toString().toStdString();


		if (pathwayMapOrg.find(pathwayID) != pathwayMapOrg.end())
		{
			boost::shared_ptr<UniPAX::Pathway> pathway = pathwayMapOrg[pathwayID];

			if (reactionMap.find(reactionID) != reactionMap.end()) {
				boost::shared_ptr<UniPAX::BiochemicalReaction> reaction = reactionMap[reactionID];
				count++;
				pathway->addPathwayComponent(reaction);

				QSqlQuery* query2 = kegg_connection->exec("SELECT EC, geneID FROM join2 WHERE ori = ? AND reactionID = ? AND pathwayID = ?", current_ori, reactionID, pathwayID);
				while (query2->next())
				{
					std::string EC = query2->value(0).toString().toStdString();

					if (!query2->value(1).isNull())
					{
						std::string geneID = query2->value(1).toString().toStdString();

						boost::shared_ptr<UniPAX::PhysicalEntity> enzyme = getDefaultInstance(geneID);

						if (enzyme)
						{
							boost::shared_ptr<UniPAX::Catalysis> catalysis = createInstance<Catalysis>(current_ori + "_" + reactionID + "_" + geneID);
							registerEntity(catalysis);

							catalysis->addController(enzyme);
							catalysis->setControlled(boost::dynamic_pointer_cast<Interaction>(reaction));
							pathway->addPathwayComponent(catalysis);
						}
					}
				}
			}
			else
			{
				throw std::runtime_error("Could not find reaction " + reactionID + " for organism " + current_ori);
			}
		}
		else
		{
			throw std::runtime_error("Could not find pathway " + pathwayID + " for organism " + current_ori);
		}
	}

	return count;
}

int KEGGMapper::readRegulatoryPathwaysOrg()
{
	int count = 0;
	int emptyCount = 0;

	// Create KEGG Regulatory reference Pathways

	std::tr1::unordered_map<std::string, boost::shared_ptr<UniPAX::Pathway> > newPathways;

	std::tr1::unordered_map<std::set<boost::shared_ptr<UniPAX::PhysicalEntity> >, boost::shared_ptr<UniPAX::Complex> > protein_complex_map;
	std::map<boost::shared_ptr<UniPAX::Complex> , boost::shared_ptr<UniPAX::ComplexAssembly> > px_association_reaction_map;
	std::map<boost::shared_ptr<UniPAX::Complex> , boost::shared_ptr<UniPAX::ComplexAssembly> > px_dissociation_reaction_map;

	std::tr1::unordered_map<std::set<boost::shared_ptr<UniPAX::SmallMolecule> >, boost::shared_ptr<UniPAX::Complex> > compound_complex_map;

	std::tr1::unordered_map<StringSet, boost::shared_ptr<UniPAX::Entity> > family_map;

	// This query loads all available non-metabolic pathway IDs for a given organism, containing at keast one relation from kgml.
	QSqlQuery * query = kegg_connection->exec("SELECT DISTINCT pt.pathwayID FROM PathwayType pt, KEGGMLRelations rel WHERE pt.pathwayID = rel.pathwayID AND rel.ori = ? AND pt.metabolic = 0 ORDER BY 1", current_ori);
	while (query->next())
	{
		std::string pathwayID = query->value(0).toString().toStdString();

		std::tr1::unordered_map<std::string, boost::shared_ptr<Entry> > entry_map;

		boost::shared_ptr<UniPAX::Pathway> pathway;

		bool newPathway = false;

		if (pathwayMapOrg.find(pathwayID) != pathwayMapOrg.end())
		{
			pathway = pathwayMapOrg[pathwayID];
		}
		else
		{
			newPathway = true;
			if (newPathways.find(pathwayID) != newPathways.end())
				pathway = newPathways[pathwayID];
			else
			{
				pathway = createInstance<Pathway>(current_ori + "_" + pathwayID);
			}
			// registering later
		}


//		std::cout << "Processing pathway: " << pathwayID << std::endl;

		// genes will be proteins/protein families
		QSqlQuery* query2 = kegg_connection->exec("SELECT DISTINCT entry_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_type = ? ORDER BY CAST(entry_id AS UNSIGNED)", current_ori, pathwayID, "gene");
		while (query2->next())
		{
			std::string entry_id = query2->value(0).toString().toStdString();

			if (entry_map.find(entry_id) == entry_map.end())
			{
				boost::shared_ptr<Entry> entry = boost::shared_ptr<Entry>(new Entry(current_ori, pathwayID, entry_id));

				// load all genes of this entry_id

				QSqlQuery * query3 = kegg_connection->exec("SELECT kegg_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_id = ? AND entry_type = ?", current_ori, pathwayID, entry_id, "gene");
				while (query3->next())
				{
					entry->geneIds.push_back(query3->value(0).toString().toStdString());
				}

				if (entry->geneIds.size() == 1)
				{	// just one protein
					entry->type = "protein";
					entry_map[entry->id] = entry;
				} else if (entry->geneIds.size() > 1)
				{ 	// a protein family
					entry->type = "family";
					entry_map[entry->id] = entry;
				}
			}
		}

		// compounds will be compounds or complexes of compounds
		query2 = kegg_connection->exec("SELECT DISTINCT entry_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_type = ? ORDER BY CAST(entry_id AS UNSIGNED)", current_ori, pathwayID, "compound");
		while (query2->next())
		{
			std::string entry_id = query2->value(0).toString().toStdString();

			if (entry_map.find(entry_id) == entry_map.end()) {

				boost::shared_ptr<Entry> entry = boost::shared_ptr<Entry>(new Entry(current_ori, pathwayID, entry_id));

				StringVector kegg_ids;

				QSqlQuery * query3 = kegg_connection->exec("SELECT kegg_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_id = ?", current_ori, pathwayID, entry_id);
				while (query3->next())
				{
					kegg_ids.push_back(query3->value(0).toString().toStdString());
				}

				if (kegg_ids.size() == 1)
				{
					entry->geneIds = kegg_ids;
					entry->type = "compound";
					entry_map[entry_id] = entry;
				}
				else if (kegg_ids.size() > 1)
				{
					entry->geneIds = kegg_ids;
					entry->type = "complex";
					entry_map[entry_id] = entry;
				}
			}
		}

		// groups will be protein complexes
		query2 = kegg_connection->exec("SELECT DISTINCT entry_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_type = ? ORDER BY CAST(entry_id AS UNSIGNED)", current_ori, pathwayID, "group");
		while (query2->next())
		{
			std::string entry_id = query2->value(0).toString().toStdString();

			if (entry_map.find(entry_id) == entry_map.end()) {

				boost::shared_ptr<Entry> entry = boost::shared_ptr<Entry>(new Entry(current_ori, pathwayID, entry_id));
				entry->type = "complex";

				QSqlQuery * query3 = kegg_connection->exec("SELECT component_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_id = ?", current_ori, pathwayID, entry_id);
				while (query3->next())
				{
					entry->components.push_back(query3->value(0).toString().toStdString());
				}

				if (!entry->components.empty())
				{
					entry_map[entry->id] = entry;
				}
			}
		}

		// maps will be pathways
		query2 = kegg_connection->exec("SELECT DISTINCT entry_id, kegg_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_type = ? ORDER BY CAST(entry_id AS UNSIGNED)", current_ori, pathwayID, "map");
		while (query2->next())
		{
			std::string entry_id = query2->value(0).toString().toStdString();

			if (entry_map.find(entry_id) == entry_map.end()) {

				boost::shared_ptr<Entry> entry = boost::shared_ptr<Entry>(new Entry(current_ori, pathwayID, entry_id));

				QSqlQuery * query3 = kegg_connection->exec("SELECT component_id FROM KEGGMLEntries WHERE ori = ? AND pathwayID = ? AND entry_id = ?", current_ori, pathwayID, entry_id);
				while (query3->next())
				{
					entry->geneIds.push_back(query3->value(0).toString().toStdString());
				}

				if (!entry->geneIds.empty())
				{	// entry_id1 is a reference to a complex...
					entry->type = "pathway";
					entry_map[entry->id] = entry;
				}
			}
		}


		// Reading relations...

		std::map<std::pair<std::pair<std::set<boost::shared_ptr<UniPAX::Entity> >, std::set<boost::shared_ptr<UniPAX::Entity> > >, std::string >, std::vector<boost::shared_ptr<UniPAX::Interaction> > > key_event_map;

		std::map<std::pair<std::string, std::string>, boost::shared_ptr<Relation> > relation_map;

		query2 = kegg_connection->exec("SELECT DISTINCT entry_id1, entry_id2, relation_type, subtype, subtype_value FROM KEGGMLRelations WHERE ori = ? AND pathwayID = ? ORDER BY 1", current_ori, pathwayID);
		while (query2->next())
		{

			boost::shared_ptr<Relation> relation;

			std::string entry_id1 = query2->value(0).toString().toStdString();
			std::string entry_id2 = query2->value(1).toString().toStdString();

			std::pair<std::string, std::string> relation_key = std::make_pair(entry_id1, entry_id2);

			if (relation_map.find(relation_key) == relation_map.end())
			{
				relation.reset(new Relation(entry_id1, entry_id2));
				relation->relation_type = query2->value(2).toString().toStdString();

				relation_map[relation_key] = relation;
			}
			else
			{
				relation = relation_map[relation_key];
			}

			relation->subtypes.push_back(query2->value(3).toString().toStdString());
			relation->subtype_values.push_back(query2->value(4).toString().toStdString());
		}

		for (std::map<std::pair<std::string, std::string>, boost::shared_ptr<Relation> >::const_iterator it = relation_map.begin(); it != relation_map.end(); ++it)
		{
			boost::shared_ptr<Relation> relation = it->second;

			try {


				if (entry_map.find(relation->entry_id1) == entry_map.end())
				{
					throw std::runtime_error("Unable to find first entry of relation " + relation->toString());
				}

				if (entry_map.find(relation->entry_id2) == entry_map.end())
				{
					throw std::runtime_error("Unable to find second entry of relation " + relation->toString());
				}

				boost::shared_ptr<Entry> entry1 = entry_map[relation->entry_id1];
				boost::shared_ptr<Entry> entry2 = entry_map[relation->entry_id2];

				// create pathway links in the pathway
				if (relation->relation_type == "maplink")
				{
					continue;
				}

				std::vector<boost::shared_ptr<UniPAX::Interaction> > events;

				if (relation->relation_type == "PPrel" || relation->relation_type == "PCrel" || relation->relation_type == "GErel")
				{
					// protein-protein relation or protein-compound relations

					StringSet states;

					if (contains(relation->subtypes, "activation"))
					{
						states.insert("active");
					}

					if (contains(relation->subtypes, "inhibition"))
					{
						states.insert("inactive");
					}

					if (contains(relation->subtypes, "phosphorylation"))
					{
						states.insert("phosphorylated");
					}

					if (contains(relation->subtypes, "dephosphorylation"))
					{
						states.insert("dephosphorylated");
					}

					if (contains(relation->subtypes, "ubiquination"))
					{
						states.insert("ubiquinated");
					}

					if (contains(relation->subtypes, "deubiquination"))
					{
						states.insert("deubiquinated");
					}

					if (contains(relation->subtypes, "methylation"))
					{
						states.insert("methylated");
					}

					if (contains(relation->subtypes, "demethylation"))
					{
						states.insert("demethylated");
					}

					if (contains(relation->subtypes, "binding/association"))
					{
						boost::shared_ptr<PhysicalEntity> first_complex_component = getDefaultInstance(entry_map, entry1);
						boost::shared_ptr<PhysicalEntity> second_complex_component = getDefaultInstance(entry_map, entry2);

						std::set<boost::shared_ptr<PhysicalEntity> > components;
						components.insert(first_complex_component);
						components.insert(second_complex_component);

						if (states.empty())
						{
							events.push_back(getComplexAssembly(getDefaultComplexInstance(components)));
						}
						else
						{
							events.push_back(getComplexAssembly(getModifiedComplexInstance(components, states).second));
						}
					}
					else if (contains(relation->subtypes, "dissociation"))
					{
						boost::shared_ptr<PhysicalEntity> first_complex_component = getDefaultInstance(entry_map, entry1);
						boost::shared_ptr<PhysicalEntity> second_complex_component = getDefaultInstance(entry_map, entry2);

						std::set<boost::shared_ptr<PhysicalEntity> > components;
						components.insert(first_complex_component);
						components.insert(second_complex_component);

						if (states.empty())
						{
							events.push_back(getComplexDisassembly(getDefaultComplexInstance(components)));
						}
						else
						{
							events.push_back(getComplexDisassembly(getModifiedComplexInstance(components, states).second));
						}
					}
					else if (contains(relation->subtypes, "expression") || contains(relation->subtypes, "repression"))
					{
						boost::shared_ptr<PhysicalEntity> controller = getDefaultInstance(entry_map, entry1);

						boost::shared_ptr<PhysicalEntity> controlled;

						if (states.empty())
						{
							controlled = getDefaultInstance(entry_map, entry2);
						}
						else
						{
							controlled = getModifiedInstance(entry_map, entry2, states).second;
						}

						boost::shared_ptr<TemplateReaction> template_reaction = getTemplateReaction(controlled);

						boost::shared_ptr<TemplateReactionRegulation> regulation = createInstance<TemplateReactionRegulation>(current_ori, "");
						registerEntity(regulation);

						if (contains(relation->subtypes, "expression") || contains(relation->subtypes, "activation"))
						{
							regulation->setControlType("ACTIVATION");
						}
						else if (contains(relation->subtypes, "repression") || contains(relation->subtypes, "inhibition"))
						{
							regulation->setControlType("INHIBITION");
						}

						regulation->addController(controller);
						regulation->setControlled(boost::dynamic_pointer_cast<Interaction>(template_reaction));

						events.push_back(regulation);
					}
					else
					{
						boost::shared_ptr<PhysicalEntity> controller = getDefaultInstance(entry_map, entry1);


						if (contains(relation->subtypes, "compound"))
						{
							std::string compound_id = relation->getSubtypeValue("compound");

							if (entry_map.find(compound_id) == entry_map.end())
								throw std::runtime_error("Unable to find compound for relation " + relation->toString());

							std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<PhysicalEntity> > controlled_compound = getModifiedInstance(entry_map, entry_map[compound_id], states);

							boost::shared_ptr<Control> regulation1 = createInstance<Control>(current_ori, "");
							registerEntity(regulation1);
							events.push_back(regulation1);

							if (contains(relation->subtypes, "activation"))
							{
								regulation1->setControlType("ACTIVATION");
							}
							else if (contains(relation->subtypes, "inhibition"))
							{
								regulation1->setControlType("INHIBITION");
							}

							regulation1->addController(controller);
							regulation1->setControlled(boost::dynamic_pointer_cast<Interaction>(controlled_compound.first));

							std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<PhysicalEntity> > controlled = getModifiedInstance(entry_map, entry2, states);

							boost::shared_ptr<Control> regulation2 = createInstance<Control>(current_ori, "");
							registerEntity(regulation2);
							events.push_back(regulation2);

							if (contains(relation->subtypes, "activation"))
							{
								regulation2->setControlType("ACTIVATION");
							}
							else if (contains(relation->subtypes, "inhibition"))
							{
								regulation2->setControlType("INHIBITION");
							}

							regulation2->addController(controlled_compound.second);
							regulation2->setControlled(boost::dynamic_pointer_cast<Interaction>(controlled.first));
						}
						else
						{
							std::pair<boost::shared_ptr<Conversion>, boost::shared_ptr<PhysicalEntity> > controlled = getModifiedInstance(entry_map, entry2, states);

							boost::shared_ptr<Control> regulation = createInstance<Control>(current_ori, "");
							registerEntity(regulation);

							events.push_back(regulation);

							if (contains(relation->subtypes, "activation"))
							{
								regulation->setControlType("ACTIVATION");
							}
							else if (contains(relation->subtypes, "inhibition"))
							{
								regulation->setControlType("INHIBITION");
							}

							regulation->addController(controller);
							regulation->setControlled(boost::dynamic_pointer_cast<Interaction>(controlled.first));
						}
					}


				}
				if (!events.empty())
				{
					for (std::vector<boost::shared_ptr<UniPAX::Interaction> >::const_iterator it = events.begin(); it != events.end(); ++it)
						pathway->addPathwayComponent(*it);
				}
			}
			catch (std::exception& e)
			{
				std::cerr << "Skipping relation " + relation->toString() + " cause of exception: " + e.what() << std::endl;
			}
		}


		if (newPathway)
		{
			query2 = kegg_connection->exec("SELECT pathwayName FROM Pathway WHERE pathwayID = ?", pathwayID);
			query2->next();

			std::string pathwayName = query2->value(0).toString().toStdString();

			if (pathway->getPathwayComponents().size() > 0)
			{
				count++;

				pathwayMapOrg[pathwayID] = pathway;

				// connect with db
				pathway->setOrganism(current_org);
				pathway->addName(pathwayName);
				pathway->setStandardName(pathwayName);
				pathway->setDisplayName(pathwayName);
				registerEntity(pathway);

				createCrossReference(boost::dynamic_pointer_cast<Entity>(pathway), "KEGG", pathwayID);
			}
			else
			{
				emptyCount++;
			}
		}
	}

	return count;

}



}

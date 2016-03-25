// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UNIPAX
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


#include<UNIPAX/COMMON/PersistenceManager.h>
#include<UNIPAX/PERSISTENCE/DBManager.h>

#include<UNIPAX/KERNEL/all.h>

#include<iostream>
#include<sstream>
#include<boost/algorithm/string.hpp>


UniPAX::PersistenceManager::PersistenceManager() : skip_PathwaySteps(false) {
}

UniPAX::PersistenceManager::PersistenceManager(const PersistenceManager & arg) :
					pointer_map_(arg.pointer_map_),
					pointer_id_(arg.pointer_id_),
					pointer_type_map_(arg.pointer_type_map_),
					pointer_merged_map_(arg.pointer_merged_map_),
					skip_PathwaySteps(arg.skip_PathwaySteps)
{
}

UniPAX::PersistenceManager & UniPAX::PersistenceManager::operator =(const PersistenceManager & arg)
{
	pointer_map_ = arg.pointer_map_;
	pointer_id_ = arg.pointer_id_;
	pointer_type_map_ = arg.pointer_type_map_;
	pointer_merged_map_ = arg.pointer_merged_map_;

	skip_PathwaySteps = arg.skip_PathwaySteps;

	return *this;
}

UniPAX::PersistenceManager::~PersistenceManager()  {
}

void UniPAX::PersistenceManager::setError(std::string msg)
{
	errorMsgs.push_back(msg);
	std::cout << msg << std::endl;
}

std::vector<std::string> UniPAX::PersistenceManager::getErrors()
{
	return errorMsgs;
}

void UniPAX::PersistenceManager::clearErrors()
{
	errorMsgs.clear();
}

void UniPAX::PersistenceManager::printErrors(std::ostream& out, bool clear)
{
	for (std::vector<std::string>::iterator it = errorMsgs.begin(); it != errorMsgs.end(); ++it)
		out << *it << std::endl;

	if (clear)
		errorMsgs.clear();
}


// this is due to the misuse of pathwayOrder attribute in pathways by external data provider Reactome
void UniPAX::PersistenceManager::skipPathwaySteps(bool flag)
{
	skip_PathwaySteps = flag;

	return;
}

// this is due to the misuse of pathwayOrder attribute in pathways by external data provider Reactome
bool UniPAX::PersistenceManager::pathwayStepsSkipped()
{
	return skip_PathwaySteps;
}

// write the data objects into outstream
std::ostream& operator<<(std::ostream& os, const UniPAX::PersistenceManager& manager)
{
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator m;
	std::map<std::string, std::string>::iterator type_search;
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > data = manager.getData();
	std::map<std::string, std::string> types = manager.getIdToType();

	for (m = data.begin(); m != data.end(); m++)
	{
		type_search = types.find(m->first);
		if (type_search != types.end())
		{
			os << type_search->second << " - " << type_search->first << " : " << m->second << std::endl;
		}
		else
		{
			os << "type unknown - " << m->first << " : " << m->second << std::endl;

		}
	}

	return os;
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::PersistenceManager::createInstance(std::string id , std::string type) {
	bool created(true);
	return createInstance(id, type, created);
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::PersistenceManager::createInstance(std::string id , std::string type, bool& created) {

	// check if object already exists
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator object_search = pointer_map_.find(id);
	std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);

	created = false;

	if (object_search != pointer_map_.end())
	{
		if (type_search != pointer_type_map_.end())
		{
			if (type_search->second == type)
			{
				// found object of correct type
				return object_search->second;
			}
			else
			{
				// found object with this id but wrong type
				std::cerr << "wrong type for object with id " << id << " ... should be " << type << std::endl;
				return boost::shared_ptr<UniPAX::UPBase>();
			}
		}
		// found object but no type !
		std::cerr << "no type for object with id " << id << " ... should be " << type << std::endl;
		return boost::shared_ptr<UniPAX::UPBase>();
	}

	created = true;

	if (boost::iequals(type,"BindingFeature"))
	{
		boost::shared_ptr<UniPAX::BindingFeature> instance = boost::shared_ptr<UniPAX::BindingFeature>(new UniPAX::BindingFeature());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"BioSource"))
	{
		boost::shared_ptr<UniPAX::BioSource> instance = boost::shared_ptr<UniPAX::BioSource>(new UniPAX::BioSource());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"BiochemicalPathwayStep"))
	{
		boost::shared_ptr<UniPAX::BiochemicalPathwayStep> instance = boost::shared_ptr<UniPAX::BiochemicalPathwayStep>(new UniPAX::BiochemicalPathwayStep());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"BiochemicalReaction"))
	{
		boost::shared_ptr<UniPAX::BiochemicalReaction> instance = boost::shared_ptr<UniPAX::BiochemicalReaction>(new UniPAX::BiochemicalReaction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Catalysis"))
	{
		boost::shared_ptr<UniPAX::Catalysis> instance = boost::shared_ptr<UniPAX::Catalysis>(new UniPAX::Catalysis());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"CellVocabulary"))
	{
		boost::shared_ptr<UniPAX::CellVocabulary> instance = boost::shared_ptr<UniPAX::CellVocabulary>(new UniPAX::CellVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"CellularLocationVocabulary"))
	{
		boost::shared_ptr<UniPAX::CellularLocationVocabulary> instance = boost::shared_ptr<UniPAX::CellularLocationVocabulary>(new UniPAX::CellularLocationVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ChemicalStructure"))
	{
		boost::shared_ptr<UniPAX::ChemicalStructure> instance = boost::shared_ptr<UniPAX::ChemicalStructure>(new UniPAX::ChemicalStructure());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Complex"))
	{
		boost::shared_ptr<UniPAX::Complex> instance = boost::shared_ptr<UniPAX::Complex>(new UniPAX::Complex());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ComplexAssembly"))
	{
		boost::shared_ptr<UniPAX::ComplexAssembly> instance = boost::shared_ptr<UniPAX::ComplexAssembly>(new UniPAX::ComplexAssembly());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Control"))
	{
		boost::shared_ptr<UniPAX::Control> instance = boost::shared_ptr<UniPAX::Control>(new UniPAX::Control());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ControlledVocabulary"))
	{
		boost::shared_ptr<UniPAX::ControlledVocabulary> instance = boost::shared_ptr<UniPAX::ControlledVocabulary>(new UniPAX::ControlledVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Conversion"))
	{
		boost::shared_ptr<UniPAX::Conversion> instance = boost::shared_ptr<UniPAX::Conversion>(new UniPAX::Conversion());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"CovalentBindingFeature"))
	{
		boost::shared_ptr<UniPAX::CovalentBindingFeature> instance = boost::shared_ptr<UniPAX::CovalentBindingFeature>(new UniPAX::CovalentBindingFeature());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Degradation"))
	{
		boost::shared_ptr<UniPAX::Degradation> instance = boost::shared_ptr<UniPAX::Degradation>(new UniPAX::Degradation());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"DeltaG"))
	{
		boost::shared_ptr<UniPAX::DeltaG> instance = boost::shared_ptr<UniPAX::DeltaG>(new UniPAX::DeltaG());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Dna"))
	{
		boost::shared_ptr<UniPAX::Dna> instance = boost::shared_ptr<UniPAX::Dna>(new UniPAX::Dna());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"DnaReference"))
	{
		boost::shared_ptr<UniPAX::DnaReference> instance = boost::shared_ptr<UniPAX::DnaReference>(new UniPAX::DnaReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"DnaRegion"))
	{
		boost::shared_ptr<UniPAX::DnaRegion> instance = boost::shared_ptr<UniPAX::DnaRegion>(new UniPAX::DnaRegion());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"DnaRegionReference"))
	{
		boost::shared_ptr<UniPAX::DnaRegionReference> instance = boost::shared_ptr<UniPAX::DnaRegionReference>(new UniPAX::DnaRegionReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Entity"))
	{
		boost::shared_ptr<UniPAX::Entity> instance = boost::shared_ptr<UniPAX::Entity>(new UniPAX::Entity());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"EntityFeature"))
	{
		boost::shared_ptr<UniPAX::EntityFeature> instance = boost::shared_ptr<UniPAX::EntityFeature>(new UniPAX::EntityFeature());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"EntityReference"))
	{
		boost::shared_ptr<UniPAX::EntityReference> instance = boost::shared_ptr<UniPAX::EntityReference>(new UniPAX::EntityReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
	{
		boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary> instance = boost::shared_ptr<UniPAX::EntityReferenceTypeVocabulary>(new UniPAX::EntityReferenceTypeVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Evidence"))
	{
		boost::shared_ptr<UniPAX::Evidence> instance = boost::shared_ptr<UniPAX::Evidence>(new UniPAX::Evidence());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"EvidenceCodeVocabulary"))
	{
		boost::shared_ptr<UniPAX::EvidenceCodeVocabulary> instance = boost::shared_ptr<UniPAX::EvidenceCodeVocabulary>(new UniPAX::EvidenceCodeVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ExperimentalForm"))
	{
		boost::shared_ptr<UniPAX::ExperimentalForm> instance = boost::shared_ptr<UniPAX::ExperimentalForm>(new UniPAX::ExperimentalForm());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ExperimentalFormVocabulary"))
	{
		boost::shared_ptr<UniPAX::ExperimentalFormVocabulary> instance = boost::shared_ptr<UniPAX::ExperimentalFormVocabulary>(new UniPAX::ExperimentalFormVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"FragmentFeature"))
	{
		boost::shared_ptr<UniPAX::FragmentFeature> instance = boost::shared_ptr<UniPAX::FragmentFeature>(new UniPAX::FragmentFeature());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Gene"))
	{
		boost::shared_ptr<UniPAX::Gene> instance = boost::shared_ptr<UniPAX::Gene>(new UniPAX::Gene());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"GeneticInteraction"))
	{
		boost::shared_ptr<UniPAX::GeneticInteraction> instance = boost::shared_ptr<UniPAX::GeneticInteraction>(new UniPAX::GeneticInteraction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Interaction"))
	{
		boost::shared_ptr<UniPAX::Interaction> instance = boost::shared_ptr<UniPAX::Interaction>(new UniPAX::Interaction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"InteractionVocabulary"))
	{
		boost::shared_ptr<UniPAX::InteractionVocabulary> instance = boost::shared_ptr<UniPAX::InteractionVocabulary>(new UniPAX::InteractionVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"KPrime"))
	{
		boost::shared_ptr<UniPAX::KPrime> instance = boost::shared_ptr<UniPAX::KPrime>(new UniPAX::KPrime());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ModificationFeature"))
	{
		boost::shared_ptr<UniPAX::ModificationFeature> instance = boost::shared_ptr<UniPAX::ModificationFeature>(new UniPAX::ModificationFeature());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Modulation"))
	{
		boost::shared_ptr<UniPAX::Modulation> instance = boost::shared_ptr<UniPAX::Modulation>(new UniPAX::Modulation());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"MolecularInteraction"))
	{
		boost::shared_ptr<UniPAX::MolecularInteraction> instance = boost::shared_ptr<UniPAX::MolecularInteraction>(new UniPAX::MolecularInteraction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Pathway"))
	{
		boost::shared_ptr<UniPAX::Pathway> instance = boost::shared_ptr<UniPAX::Pathway>(new UniPAX::Pathway());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"PathwayStep"))
	{
		boost::shared_ptr<UniPAX::PathwayStep> instance = boost::shared_ptr<UniPAX::PathwayStep>(new UniPAX::PathwayStep());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"PhenotypeVocabulary"))
	{
		boost::shared_ptr<UniPAX::PhenotypeVocabulary> instance = boost::shared_ptr<UniPAX::PhenotypeVocabulary>(new UniPAX::PhenotypeVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"PhysicalEntity"))
	{
		boost::shared_ptr<UniPAX::PhysicalEntity> instance = boost::shared_ptr<UniPAX::PhysicalEntity>(new UniPAX::PhysicalEntity());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Protein"))
	{
		boost::shared_ptr<UniPAX::Protein> instance = boost::shared_ptr<UniPAX::Protein>(new UniPAX::Protein());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ProteinReference"))
	{
		boost::shared_ptr<UniPAX::ProteinReference> instance = boost::shared_ptr<UniPAX::ProteinReference>(new UniPAX::ProteinReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Provenance"))
	{
		boost::shared_ptr<UniPAX::Provenance> instance = boost::shared_ptr<UniPAX::Provenance>(new UniPAX::Provenance());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"PublicationXref"))
	{
		boost::shared_ptr<UniPAX::PublicationXref> instance = boost::shared_ptr<UniPAX::PublicationXref>(new UniPAX::PublicationXref());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RelationshipTypeVocabulary"))
	{
		boost::shared_ptr<UniPAX::RelationshipTypeVocabulary> instance = boost::shared_ptr<UniPAX::RelationshipTypeVocabulary>(new UniPAX::RelationshipTypeVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RelationshipXref"))
	{
		boost::shared_ptr<UniPAX::RelationshipXref> instance = boost::shared_ptr<UniPAX::RelationshipXref>(new UniPAX::RelationshipXref());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Rna"))
	{
		boost::shared_ptr<UniPAX::Rna> instance = boost::shared_ptr<UniPAX::Rna>(new UniPAX::Rna());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RnaReference"))
	{
		boost::shared_ptr<UniPAX::RnaReference> instance = boost::shared_ptr<UniPAX::RnaReference>(new UniPAX::RnaReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RnaRegion"))
	{
		boost::shared_ptr<UniPAX::RnaRegion> instance = boost::shared_ptr<UniPAX::RnaRegion>(new UniPAX::RnaRegion());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RnaRegionReference"))
	{
		boost::shared_ptr<UniPAX::RnaRegionReference> instance = boost::shared_ptr<UniPAX::RnaRegionReference>(new UniPAX::RnaRegionReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Score"))
	{
		boost::shared_ptr<UniPAX::Score> instance = boost::shared_ptr<UniPAX::Score>(new UniPAX::Score());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SequenceInterval"))
	{
		boost::shared_ptr<UniPAX::SequenceInterval> instance = boost::shared_ptr<UniPAX::SequenceInterval>(new UniPAX::SequenceInterval());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SequenceLocation"))
	{
		boost::shared_ptr<UniPAX::SequenceLocation> instance = boost::shared_ptr<UniPAX::SequenceLocation>(new UniPAX::SequenceLocation());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SequenceModificationVocabulary"))
	{
		boost::shared_ptr<UniPAX::SequenceModificationVocabulary> instance = boost::shared_ptr<UniPAX::SequenceModificationVocabulary>(new UniPAX::SequenceModificationVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SequenceRegionVocabulary"))
	{
		boost::shared_ptr<UniPAX::SequenceRegionVocabulary> instance = boost::shared_ptr<UniPAX::SequenceRegionVocabulary>(new UniPAX::SequenceRegionVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SequenceSite"))
	{
		boost::shared_ptr<UniPAX::SequenceSite> instance = boost::shared_ptr<UniPAX::SequenceSite>(new UniPAX::SequenceSite());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SmallMolecule"))
	{
		boost::shared_ptr<UniPAX::SmallMolecule> instance = boost::shared_ptr<UniPAX::SmallMolecule>(new UniPAX::SmallMolecule());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SmallMoleculeReference"))
	{
		boost::shared_ptr<UniPAX::SmallMoleculeReference> instance = boost::shared_ptr<UniPAX::SmallMoleculeReference>(new UniPAX::SmallMoleculeReference());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Stoichiometry"))
	{
		boost::shared_ptr<UniPAX::Stoichiometry> instance = boost::shared_ptr<UniPAX::Stoichiometry>(new UniPAX::Stoichiometry());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"TemplateReaction"))
	{
		boost::shared_ptr<UniPAX::TemplateReaction> instance = boost::shared_ptr<UniPAX::TemplateReaction>(new UniPAX::TemplateReaction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"TemplateReactionRegulation"))
	{
		boost::shared_ptr<UniPAX::TemplateReactionRegulation> instance = boost::shared_ptr<UniPAX::TemplateReactionRegulation>(new UniPAX::TemplateReactionRegulation());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Thing"))
	{
		boost::shared_ptr<UniPAX::Thing> instance = boost::shared_ptr<UniPAX::Thing>(new UniPAX::Thing());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"TissueVocabulary"))
	{
		boost::shared_ptr<UniPAX::TissueVocabulary> instance = boost::shared_ptr<UniPAX::TissueVocabulary>(new UniPAX::TissueVocabulary());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Transport"))
	{
		boost::shared_ptr<UniPAX::Transport> instance = boost::shared_ptr<UniPAX::Transport>(new UniPAX::Transport());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"TransportWithBiochemicalReaction"))
	{
		boost::shared_ptr<UniPAX::TransportWithBiochemicalReaction> instance = boost::shared_ptr<UniPAX::TransportWithBiochemicalReaction>(new UniPAX::TransportWithBiochemicalReaction());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"UnificationXref"))
	{
		boost::shared_ptr<UniPAX::UnificationXref> instance = boost::shared_ptr<UniPAX::UnificationXref>(new UniPAX::UnificationXref());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"UtilityClass"))
	{
		boost::shared_ptr<UniPAX::UtilityClass> instance = boost::shared_ptr<UniPAX::UtilityClass>(new UniPAX::UtilityClass());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Xref"))
	{
		boost::shared_ptr<UniPAX::Xref> instance = boost::shared_ptr<UniPAX::Xref>(new UniPAX::Xref());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}

	// EXT


	else if (boost::iequals(type,"AlgebraicRule"))
	{
		boost::shared_ptr<UniPAX::AlgebraicRule> instance = boost::shared_ptr<UniPAX::AlgebraicRule>(new UniPAX::AlgebraicRule());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"AssignmentRule"))
	{
		boost::shared_ptr<UniPAX::AssignmentRule> instance = boost::shared_ptr<UniPAX::AssignmentRule>(new UniPAX::AssignmentRule());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Constraint"))
	{
		boost::shared_ptr<UniPAX::Constraint> instance = boost::shared_ptr<UniPAX::Constraint>(new UniPAX::Constraint());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Delay"))
	{
		boost::shared_ptr<UniPAX::Delay> instance = boost::shared_ptr<UniPAX::Delay>(new UniPAX::Delay());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Event"))
	{
		boost::shared_ptr<UniPAX::Event> instance = boost::shared_ptr<UniPAX::Event>(new UniPAX::Event());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"EventAssignment"))
	{
		boost::shared_ptr<UniPAX::EventAssignment> instance = boost::shared_ptr<UniPAX::EventAssignment>(new UniPAX::EventAssignment());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Experiment"))
	{
		boost::shared_ptr<UniPAX::Experiment> instance = boost::shared_ptr<UniPAX::Experiment>(new UniPAX::Experiment());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"FunctionDefinition"))
	{
		boost::shared_ptr<UniPAX::FunctionDefinition> instance = boost::shared_ptr<UniPAX::FunctionDefinition>(new UniPAX::FunctionDefinition());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"IdMapping"))
	{
		boost::shared_ptr<UniPAX::IdMapping> instance = boost::shared_ptr<UniPAX::IdMapping>(new UniPAX::IdMapping());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ImportSource"))
	{
		boost::shared_ptr<UniPAX::ImportSource> instance = boost::shared_ptr<UniPAX::ImportSource>(new UniPAX::ImportSource());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"InitialAssignment"))
	{
		boost::shared_ptr<UniPAX::InitialAssignment> instance = boost::shared_ptr<UniPAX::InitialAssignment>(new UniPAX::InitialAssignment());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"KineticLaw"))
	{
		boost::shared_ptr<UniPAX::KineticLaw> instance = boost::shared_ptr<UniPAX::KineticLaw>(new UniPAX::KineticLaw());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"LocalParameter"))
	{
		boost::shared_ptr<UniPAX::LocalParameter> instance = boost::shared_ptr<UniPAX::LocalParameter>(new UniPAX::LocalParameter());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Math"))
	{
		boost::shared_ptr<UniPAX::Math> instance = boost::shared_ptr<UniPAX::Math>(new UniPAX::Math());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Model"))
	{
		boost::shared_ptr<UniPAX::Model> instance = boost::shared_ptr<UniPAX::Model>(new UniPAX::Model());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Parameter"))
	{
		boost::shared_ptr<UniPAX::Parameter> instance = boost::shared_ptr<UniPAX::Parameter>(new UniPAX::Parameter());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Priority"))
	{
		boost::shared_ptr<UniPAX::Priority> instance = boost::shared_ptr<UniPAX::Priority>(new UniPAX::Priority());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"RateRule"))
	{
		boost::shared_ptr<UniPAX::RateRule> instance = boost::shared_ptr<UniPAX::RateRule>(new UniPAX::RateRule());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"ResultObject"))
	{
		boost::shared_ptr<UniPAX::ResultObject> instance = boost::shared_ptr<UniPAX::ResultObject>(new UniPAX::ResultObject());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Rule"))
	{
		boost::shared_ptr<UniPAX::Rule> instance = boost::shared_ptr<UniPAX::Rule>(new UniPAX::Rule());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"SBase"))
	{
		boost::shared_ptr<UniPAX::SBase> instance = boost::shared_ptr<UniPAX::SBase>(new UniPAX::SBase());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Sample"))
	{
		boost::shared_ptr<UniPAX::Sample> instance = boost::shared_ptr<UniPAX::Sample>(new UniPAX::Sample());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Series"))
	{
		boost::shared_ptr<UniPAX::Series> instance = boost::shared_ptr<UniPAX::Series>(new UniPAX::Series());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Trigger"))
	{
		boost::shared_ptr<UniPAX::Trigger> instance = boost::shared_ptr<UniPAX::Trigger>(new UniPAX::Trigger());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"UPBase"))
	{
		boost::shared_ptr<UniPAX::UPBase> instance = boost::shared_ptr<UniPAX::UPBase>(new UniPAX::UPBase());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"Unit"))
	{
		boost::shared_ptr<UniPAX::Unit> instance = boost::shared_ptr<UniPAX::Unit>(new UniPAX::Unit());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}
	else if (boost::iequals(type,"UnitDefinition"))
	{
		boost::shared_ptr<UniPAX::UnitDefinition> instance = boost::shared_ptr<UniPAX::UnitDefinition>(new UniPAX::UnitDefinition());
		pointer_map_[id] = instance;
		pointer_id_[instance] = id;
		pointer_type_map_[id] = type;
		return boost::dynamic_pointer_cast<UniPAX::UPBase>(instance);
	}

	created = false;

	return boost::shared_ptr<UniPAX::UPBase>();

}


bool UniPAX::PersistenceManager::setAttribute(std::string id, std::string attribute, std::string value)
{
	// check if object already exists
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator object_search = pointer_map_.find(id);
	std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);

	if (object_search == pointer_map_.end())
	{
		// no such element generated
		std::cerr << "no object with id " << id << std::endl;
		return 0;
	}

	if (type_search == pointer_type_map_.end())
	{
		// no type available
		std::cerr << "no type for object with id " << id << std::endl;
		return 0;
	}

	std::string type = type_search->second;

	if (boost::iequals(type,"BindingFeature"))
	{
		return (boost::dynamic_pointer_cast<BindingFeature>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"BioSource"))
	{
		return (boost::dynamic_pointer_cast<BioSource>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"BiochemicalPathwayStep"))
	{
		return (boost::dynamic_pointer_cast<BiochemicalPathwayStep>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"BiochemicalReaction"))
	{
		return (boost::dynamic_pointer_cast<BiochemicalReaction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Catalysis"))
	{
		return (boost::dynamic_pointer_cast<Catalysis>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"CellVocabulary"))
	{
		return (boost::dynamic_pointer_cast<CellVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"CellularLocationVocabulary"))
	{
		return (boost::dynamic_pointer_cast<CellularLocationVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ChemicalStructure"))
	{
		return (boost::dynamic_pointer_cast<ChemicalStructure>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Complex"))
	{
		return (boost::dynamic_pointer_cast<Complex>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ComplexAssembly"))
	{
		return (boost::dynamic_pointer_cast<ComplexAssembly>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Control"))
	{
		return (boost::dynamic_pointer_cast<Control>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ControlledVocabulary"))
	{
		return (boost::dynamic_pointer_cast<ControlledVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Conversion"))
	{
		return (boost::dynamic_pointer_cast<Conversion>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"CovalentBindingFeature"))
	{
		return (boost::dynamic_pointer_cast<CovalentBindingFeature>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Degradation"))
	{
		return (boost::dynamic_pointer_cast<Degradation>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"DeltaG"))
	{
		return (boost::dynamic_pointer_cast<DeltaG>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Dna"))
	{
		return (boost::dynamic_pointer_cast<Dna>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"DnaReference"))
	{
		return (boost::dynamic_pointer_cast<DnaReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"DnaRegion"))
	{
		return (boost::dynamic_pointer_cast<DnaRegion>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"DnaRegionReference"))
	{
		return (boost::dynamic_pointer_cast<DnaRegionReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Entity"))
	{
		return (boost::dynamic_pointer_cast<Entity>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"EntityFeature"))
	{
		return (boost::dynamic_pointer_cast<EntityFeature>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"EntityReference"))
	{
		return (boost::dynamic_pointer_cast<EntityReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Evidence"))
	{
		return (boost::dynamic_pointer_cast<Evidence>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"EvidenceCodeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ExperimentalForm"))
	{
		return (boost::dynamic_pointer_cast<ExperimentalForm>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ExperimentalFormVocabulary"))
	{
		return (boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"FragmentFeature"))
	{
		return (boost::dynamic_pointer_cast<FragmentFeature>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Gene"))
	{
		return (boost::dynamic_pointer_cast<Gene>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"GeneticInteraction"))
	{
		return (boost::dynamic_pointer_cast<GeneticInteraction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Interaction"))
	{
		return (boost::dynamic_pointer_cast<Interaction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"InteractionVocabulary"))
	{
		return (boost::dynamic_pointer_cast<InteractionVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"KPrime"))
	{
		return (boost::dynamic_pointer_cast<KPrime>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ModificationFeature"))
	{
		return (boost::dynamic_pointer_cast<ModificationFeature>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Modulation"))
	{
		return (boost::dynamic_pointer_cast<Modulation>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"MolecularInteraction"))
	{
		return (boost::dynamic_pointer_cast<MolecularInteraction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Pathway"))
	{
		return (boost::dynamic_pointer_cast<Pathway>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"PathwayStep"))
	{
		return (boost::dynamic_pointer_cast<PathwayStep>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"PhenotypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<PhenotypeVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"PhysicalEntity"))
	{
		return (boost::dynamic_pointer_cast<PhysicalEntity>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Protein"))
	{
		return (boost::dynamic_pointer_cast<Protein>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"ProteinReference"))
	{
		return (boost::dynamic_pointer_cast<ProteinReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Provenance"))
	{
		return (boost::dynamic_pointer_cast<Provenance>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"PublicationXref"))
	{
		return (boost::dynamic_pointer_cast<PublicationXref>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"RelationshipTypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"RelationshipXref"))
	{
		return (boost::dynamic_pointer_cast<RelationshipXref>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Rna"))
	{
		return (boost::dynamic_pointer_cast<Rna>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"RnaReference"))
	{
		return (boost::dynamic_pointer_cast<RnaReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"RnaRegion"))
	{
		return (boost::dynamic_pointer_cast<RnaRegion>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"RnaRegionReference"))
	{
		return (boost::dynamic_pointer_cast<RnaRegionReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Score"))
	{
		return (boost::dynamic_pointer_cast<Score>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SequenceInterval"))
	{
		return (boost::dynamic_pointer_cast<SequenceInterval>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SequenceLocation"))
	{
		return (boost::dynamic_pointer_cast<SequenceLocation>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SequenceModificationVocabulary"))
	{
		return (boost::dynamic_pointer_cast<SequenceModificationVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SequenceRegionVocabulary"))
	{
		return (boost::dynamic_pointer_cast<SequenceRegionVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SequenceSite"))
	{
		return (boost::dynamic_pointer_cast<SequenceSite>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SmallMolecule"))
	{
		return (boost::dynamic_pointer_cast<SmallMolecule>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"SmallMoleculeReference"))
	{
		return (boost::dynamic_pointer_cast<SmallMoleculeReference>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Stoichiometry"))
	{
		return (boost::dynamic_pointer_cast<Stoichiometry>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"TemplateReaction"))
	{
		return (boost::dynamic_pointer_cast<TemplateReaction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"TemplateReactionRegulation"))
	{
		return (boost::dynamic_pointer_cast<TemplateReactionRegulation>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Thing"))
	{
		return (boost::dynamic_pointer_cast<Thing>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"TissueVocabulary"))
	{
		return (boost::dynamic_pointer_cast<TissueVocabulary>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Transport"))
	{
		return (boost::dynamic_pointer_cast<Transport>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"TransportWithBiochemicalReaction"))
	{
		return (boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"UnificationXref"))
	{
		return (boost::dynamic_pointer_cast<UnificationXref>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"UtilityClass"))
	{
		return (boost::dynamic_pointer_cast<UtilityClass>(object_search->second))->setAttribute(attribute,value, *this);
	}

	if (boost::iequals(type,"Xref"))
	{
		return (boost::dynamic_pointer_cast<Xref>(object_search->second))->setAttribute(attribute,value, *this);
	}

	return false;

}


bool UniPAX::PersistenceManager::getAttribute(std::string id, std::vector<std::pair<std::string,std::string> >& value)
{
	// check if object already exists
	std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >::iterator object_search = pointer_map_.find(id);
	std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);

	if (object_search == pointer_map_.end())
	{
		// no such element generated
		std::cerr << "no object with id " << id << std::endl;
		return 0;
	}

	if (type_search == pointer_type_map_.end())
	{
		// no type available
		std::cerr << "no type for object with id " << id << std::endl;
		return 0;
	}

	std::string type = type_search->second;

	if (boost::iequals(type,"BindingFeature"))
	{
		return (boost::dynamic_pointer_cast<BindingFeature>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"BioSource"))
	{
		return (boost::dynamic_pointer_cast<BioSource>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"BiochemicalPathwayStep"))
	{
		return (boost::dynamic_pointer_cast<BiochemicalPathwayStep>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"BiochemicalReaction"))
	{
		return (boost::dynamic_pointer_cast<BiochemicalReaction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Catalysis"))
	{
		return (boost::dynamic_pointer_cast<Catalysis>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"CellVocabulary"))
	{
		return (boost::dynamic_pointer_cast<CellVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"CellularLocationVocabulary"))
	{
		return (boost::dynamic_pointer_cast<CellularLocationVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ChemicalStructure"))
	{
		return (boost::dynamic_pointer_cast<ChemicalStructure>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Complex"))
	{
		return (boost::dynamic_pointer_cast<Complex>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ComplexAssembly"))
	{
		return (boost::dynamic_pointer_cast<ComplexAssembly>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Control"))
	{
		return (boost::dynamic_pointer_cast<Control>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ControlledVocabulary"))
	{
		return (boost::dynamic_pointer_cast<ControlledVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Conversion"))
	{
		return (boost::dynamic_pointer_cast<Conversion>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"CovalentBindingFeature"))
	{
		return (boost::dynamic_pointer_cast<CovalentBindingFeature>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Degradation"))
	{
		return (boost::dynamic_pointer_cast<Degradation>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"DeltaG"))
	{
		return (boost::dynamic_pointer_cast<DeltaG>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Dna"))
	{
		return (boost::dynamic_pointer_cast<Dna>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"DnaReference"))
	{
		return (boost::dynamic_pointer_cast<DnaReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"DnaRegion"))
	{
		return (boost::dynamic_pointer_cast<DnaRegion>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"DnaRegionReference"))
	{
		return (boost::dynamic_pointer_cast<DnaRegionReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Entity"))
	{
		return (boost::dynamic_pointer_cast<Entity>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"EntityFeature"))
	{
		return (boost::dynamic_pointer_cast<EntityFeature>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"EntityReference"))
	{
		return (boost::dynamic_pointer_cast<EntityReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	//	if (boost::iequals(type,"Event"))
	//	{
	//		return (boost::dynamic_pointer_cast<Event>(object_search->second))->getAttribute(value, *this);
	//	}

	if (boost::iequals(type,"Evidence"))
	{
		return (boost::dynamic_pointer_cast<Evidence>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"EvidenceCodeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ExperimentalForm"))
	{
		return (boost::dynamic_pointer_cast<ExperimentalForm>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ExperimentalFormVocabulary"))
	{
		return (boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"FragmentFeature"))
	{
		return (boost::dynamic_pointer_cast<FragmentFeature>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Gene"))
	{
		return (boost::dynamic_pointer_cast<Gene>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"GeneticInteraction"))
	{
		return (boost::dynamic_pointer_cast<GeneticInteraction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Interaction"))
	{
		return (boost::dynamic_pointer_cast<Interaction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"InteractionVocabulary"))
	{
		return (boost::dynamic_pointer_cast<InteractionVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"KPrime"))
	{
		return (boost::dynamic_pointer_cast<KPrime>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ModificationFeature"))
	{
		return (boost::dynamic_pointer_cast<ModificationFeature>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Modulation"))
	{
		return (boost::dynamic_pointer_cast<Modulation>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"MolecularInteraction"))
	{
		return (boost::dynamic_pointer_cast<MolecularInteraction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Pathway"))
	{
		return (boost::dynamic_pointer_cast<Pathway>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"PathwayStep"))
	{
		return (boost::dynamic_pointer_cast<PathwayStep>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"PhenotypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<PhenotypeVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"PhysicalEntity"))
	{
		return (boost::dynamic_pointer_cast<PhysicalEntity>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Protein"))
	{
		return (boost::dynamic_pointer_cast<Protein>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"ProteinReference"))
	{
		return (boost::dynamic_pointer_cast<ProteinReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Provenance"))
	{
		return (boost::dynamic_pointer_cast<Provenance>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"PublicationXref"))
	{
		return (boost::dynamic_pointer_cast<PublicationXref>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"RelationshipTypeVocabulary"))
	{
		return (boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"RelationshipXref"))
	{
		return (boost::dynamic_pointer_cast<RelationshipXref>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Rna"))
	{
		return (boost::dynamic_pointer_cast<Rna>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"RnaReference"))
	{
		return (boost::dynamic_pointer_cast<RnaReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"RnaRegion"))
	{
		return (boost::dynamic_pointer_cast<RnaRegion>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"RnaRegionReference"))
	{
		return (boost::dynamic_pointer_cast<RnaRegionReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Score"))
	{
		return (boost::dynamic_pointer_cast<Score>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SequenceInterval"))
	{
		return (boost::dynamic_pointer_cast<SequenceInterval>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SequenceLocation"))
	{
		return (boost::dynamic_pointer_cast<SequenceLocation>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SequenceModificationVocabulary"))
	{
		return (boost::dynamic_pointer_cast<SequenceModificationVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SequenceRegionVocabulary"))
	{
		return (boost::dynamic_pointer_cast<SequenceRegionVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SequenceSite"))
	{
		return (boost::dynamic_pointer_cast<SequenceSite>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SmallMolecule"))
	{
		return (boost::dynamic_pointer_cast<SmallMolecule>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"SmallMoleculeReference"))
	{
		return (boost::dynamic_pointer_cast<SmallMoleculeReference>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Stoichiometry"))
	{
		return (boost::dynamic_pointer_cast<Stoichiometry>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"TemplateReaction"))
	{
		return (boost::dynamic_pointer_cast<TemplateReaction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"TemplateReactionRegulation"))
	{
		return (boost::dynamic_pointer_cast<TemplateReactionRegulation>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Thing"))
	{
		return (boost::dynamic_pointer_cast<Thing>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"TissueVocabulary"))
	{
		return (boost::dynamic_pointer_cast<TissueVocabulary>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Transport"))
	{
		return (boost::dynamic_pointer_cast<Transport>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"TransportWithBiochemicalReaction"))
	{
		return (boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"UnificationXref"))
	{
		return (boost::dynamic_pointer_cast<UnificationXref>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"UtilityClass"))
	{
		return (boost::dynamic_pointer_cast<UtilityClass>(object_search->second))->getAttribute(value, *this);
	}

	if (boost::iequals(type,"Xref"))
	{
		return (boost::dynamic_pointer_cast<Xref>(object_search->second))->getAttribute(value, *this);
	}

	// EXT classes:

	if (boost::iequals(type, "AlgebraicRule"))
	{
		return (boost::dynamic_pointer_cast<AlgebraicRule>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "AssignmentRule"))
	{
		return (boost::dynamic_pointer_cast<AssignmentRule>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Constraint"))
	{
		return (boost::dynamic_pointer_cast<Constraint>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Delay"))
	{
		return (boost::dynamic_pointer_cast<Delay>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Event"))
	{
		return (boost::dynamic_pointer_cast<Event>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "EventAssignment"))
	{
		return (boost::dynamic_pointer_cast<EventAssignment>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Experiment"))
	{
		return (boost::dynamic_pointer_cast<Experiment>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "FunctionDefinition"))
	{
		return (boost::dynamic_pointer_cast<FunctionDefinition>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "IdMapping"))
	{
		return (boost::dynamic_pointer_cast<IdMapping>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "ImportSource"))
	{
		return (boost::dynamic_pointer_cast<ImportSource>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "InitialAssignment"))
	{
		return (boost::dynamic_pointer_cast<InitialAssignment>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "KineticLaw"))
	{
		return (boost::dynamic_pointer_cast<KineticLaw>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "LocalParameter"))
	{
		return (boost::dynamic_pointer_cast<LocalParameter>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Math"))
	{
		return (boost::dynamic_pointer_cast<Math>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Model"))
	{
		return (boost::dynamic_pointer_cast<Model>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Parameter"))
	{
		return (boost::dynamic_pointer_cast<Parameter>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Priority"))
	{
		return (boost::dynamic_pointer_cast<Priority>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "RateRule"))
	{
		return (boost::dynamic_pointer_cast<RateRule>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "ResultObject"))
	{
		return (boost::dynamic_pointer_cast<ResultObject>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Rule"))
	{
		return (boost::dynamic_pointer_cast<Rule>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "SBase"))
	{
		return (boost::dynamic_pointer_cast<SBase>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Sample"))
	{
		return (boost::dynamic_pointer_cast<Sample>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Series"))
	{
		return (boost::dynamic_pointer_cast<Series>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Trigger"))
	{
		return (boost::dynamic_pointer_cast<Trigger>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "UPBase"))
	{
		return (boost::dynamic_pointer_cast<UPBase>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "Unit"))
	{
		return (boost::dynamic_pointer_cast<Unit>(object_search->second))->getAttribute(value, *this);
	}
	if (boost::iequals(type, "UnitDefinition"))
	{
		return (boost::dynamic_pointer_cast<UnitDefinition>(object_search->second))->getAttribute(value, *this);
	}

	return false;

}

bool UniPAX::PersistenceManager::getId(boost::shared_ptr<UPBase> object, std::string& id)
{
	id.clear();
	std::map<boost::shared_ptr<UPBase>, std::string>::iterator object_search = pointer_id_.find(object);

	if (object_search == pointer_id_.end())
	{
		std::stringstream ss;
		ss << "PersistenceManager: Object not known" << object;
		std::string s;
		ss >> s;
		setError(s);
		return false;
	}

	id = object_search->second;
	return true;
}

bool UniPAX::PersistenceManager::add(boost::shared_ptr<UPBase> object, UniPAX::DBManager* db)
{
	std::vector<std::pair<std::string,std::string> > value;
	std::map<boost::shared_ptr<UPBase>, std::string>::iterator object_search = pointer_id_.find(object);
	std::string id;

	if (object_search == pointer_id_.end())
	{
		db->assignId(object);

		std::stringstream ss;
		ss << object->getUnipaxId();
		ss >> id;
		pointer_id_[object] = id;
		pointer_map_[id] = object;
		pointer_type_map_[id] = object->getType();

		return true;
	}

	return false;
}

bool UniPAX::PersistenceManager::update(boost::shared_ptr<UPBase> object)
{
	std::vector<std::pair<std::string,std::string> > value;
	std::map<boost::shared_ptr<UPBase>, std::string>::iterator object_search = pointer_id_.find(object);
	std::string id;
	std::stringstream ss;
	ss << object->getUnipaxId();
	ss >> id;

	if (object_search != pointer_id_.end())
	{
		if (object_search->second == id)
			return false;

		pointer_map_.erase(object_search->second);
		pointer_type_map_.erase(object_search->second);
	}

	pointer_id_[object] = id;
	pointer_map_[id] = object;
	pointer_type_map_[id] = object->getType();

	return true;
}


bool UniPAX::PersistenceManager::updateAll()
{
	std::map<boost::shared_ptr<UPBase>, std::string>::iterator object_search;
	for (object_search = pointer_id_.begin(); object_search != pointer_id_.end(); object_search++)
	{
		boost::shared_ptr<UPBase> object = object_search->first;
		std::string type = pointer_type_map_[object_search->second];

		// BIOPAX classes:

		if (boost::iequals(type,"BindingFeature"))
		{
			update(boost::dynamic_pointer_cast<BindingFeature>(object));
		}

		if (boost::iequals(type,"BioSource"))
		{
			update(boost::dynamic_pointer_cast<BioSource>(object));
		}

		if (boost::iequals(type,"BiochemicalPathwayStep"))
		{
			update(boost::dynamic_pointer_cast<BiochemicalPathwayStep>(object));
		}

		if (boost::iequals(type,"BiochemicalReaction"))
		{
			update(boost::dynamic_pointer_cast<BiochemicalReaction>(object));
		}

		if (boost::iequals(type,"Catalysis"))
		{
			update(boost::dynamic_pointer_cast<Catalysis>(object));
		}

		if (boost::iequals(type,"CellVocabulary"))
		{
			update(boost::dynamic_pointer_cast<CellVocabulary>(object));
		}

		if (boost::iequals(type,"CellularLocationVocabulary"))
		{
			update(boost::dynamic_pointer_cast<CellularLocationVocabulary>(object));
		}

		if (boost::iequals(type,"ChemicalStructure"))
		{
			update(boost::dynamic_pointer_cast<ChemicalStructure>(object));
		}

		if (boost::iequals(type,"Complex"))
		{
			update(boost::dynamic_pointer_cast<Complex>(object));
		}

		if (boost::iequals(type,"ComplexAssembly"))
		{
			update(boost::dynamic_pointer_cast<ComplexAssembly>(object));
		}

		if (boost::iequals(type,"Control"))
		{
			update(boost::dynamic_pointer_cast<Control>(object));
		}

		if (boost::iequals(type,"ControlledVocabulary"))
		{
			update(boost::dynamic_pointer_cast<ControlledVocabulary>(object));
		}

		if (boost::iequals(type,"Conversion"))
		{
			update(boost::dynamic_pointer_cast<Conversion>(object));
		}

		if (boost::iequals(type,"CovalentBindingFeature"))
		{
			update(boost::dynamic_pointer_cast<CovalentBindingFeature>(object));
		}

		if (boost::iequals(type,"Degradation"))
		{
			update(boost::dynamic_pointer_cast<Degradation>(object));
		}

		if (boost::iequals(type,"DeltaG"))
		{
			update(boost::dynamic_pointer_cast<DeltaG>(object));
		}

		if (boost::iequals(type,"Dna"))
		{
			update(boost::dynamic_pointer_cast<Dna>(object));
		}

		if (boost::iequals(type,"DnaReference"))
		{
			update(boost::dynamic_pointer_cast<DnaReference>(object));
		}

		if (boost::iequals(type,"DnaRegion"))
		{
			update(boost::dynamic_pointer_cast<DnaRegion>(object));
		}

		if (boost::iequals(type,"DnaRegionReference"))
		{
			update(boost::dynamic_pointer_cast<DnaRegionReference>(object));
		}

		if (boost::iequals(type,"Entity"))
		{
			update(boost::dynamic_pointer_cast<Entity>(object));
		}

		if (boost::iequals(type,"EntityFeature"))
		{
			update(boost::dynamic_pointer_cast<EntityFeature>(object));
		}

		if (boost::iequals(type,"EntityReference"))
		{
			update(boost::dynamic_pointer_cast<EntityReference>(object));
		}

		if (boost::iequals(type,"EntityReferenceTypeVocabulary"))
		{
			update(boost::dynamic_pointer_cast<EntityReferenceTypeVocabulary>(object));
		}

		if (boost::iequals(type,"Evidence"))
		{
			update(boost::dynamic_pointer_cast<Evidence>(object));
		}

		if (boost::iequals(type,"EvidenceCodeVocabulary"))
		{
			update(boost::dynamic_pointer_cast<EvidenceCodeVocabulary>(object));
		}

		if (boost::iequals(type,"ExperimentalForm"))
		{
			update(boost::dynamic_pointer_cast<ExperimentalForm>(object));
		}

		if (boost::iequals(type,"ExperimentalFormVocabulary"))
		{
			update(boost::dynamic_pointer_cast<ExperimentalFormVocabulary>(object));
		}

		if (boost::iequals(type,"FragmentFeature"))
		{
			update(boost::dynamic_pointer_cast<FragmentFeature>(object));
		}

		if (boost::iequals(type,"Gene"))
		{
			update(boost::dynamic_pointer_cast<Gene>(object));
		}

		if (boost::iequals(type,"GeneticInteraction"))
		{
			update(boost::dynamic_pointer_cast<GeneticInteraction>(object));
		}

		if (boost::iequals(type,"Interaction"))
		{
			update(boost::dynamic_pointer_cast<Interaction>(object));
		}

		if (boost::iequals(type,"InteractionVocabulary"))
		{
			update(boost::dynamic_pointer_cast<InteractionVocabulary>(object));
		}

		if (boost::iequals(type,"KPrime"))
		{
			update(boost::dynamic_pointer_cast<KPrime>(object));
		}

		if (boost::iequals(type,"ModificationFeature"))
		{
			update(boost::dynamic_pointer_cast<ModificationFeature>(object));
		}

		if (boost::iequals(type,"Modulation"))
		{
			update(boost::dynamic_pointer_cast<Modulation>(object));
		}

		if (boost::iequals(type,"MolecularInteraction"))
		{
			update(boost::dynamic_pointer_cast<MolecularInteraction>(object));
		}

		if (boost::iequals(type,"Pathway"))
		{
			update(boost::dynamic_pointer_cast<Pathway>(object));
		}

		if (boost::iequals(type,"PathwayStep"))
		{
			update(boost::dynamic_pointer_cast<PathwayStep>(object));
		}

		if (boost::iequals(type,"PhenotypeVocabulary"))
		{
			update(boost::dynamic_pointer_cast<PhenotypeVocabulary>(object));
		}

		if (boost::iequals(type,"PhysicalEntity"))
		{
			update(boost::dynamic_pointer_cast<PhysicalEntity>(object));
		}

		if (boost::iequals(type,"Protein"))
		{
			update(boost::dynamic_pointer_cast<Protein>(object));
		}

		if (boost::iequals(type,"ProteinReference"))
		{
			update(boost::dynamic_pointer_cast<ProteinReference>(object));
		}

		if (boost::iequals(type,"Provenance"))
		{
			update(boost::dynamic_pointer_cast<Provenance>(object));
		}

		if (boost::iequals(type,"PublicationXref"))
		{
			update(boost::dynamic_pointer_cast<PublicationXref>(object));
		}

		if (boost::iequals(type,"RelationshipTypeVocabulary"))
		{
			update(boost::dynamic_pointer_cast<RelationshipTypeVocabulary>(object));
		}

		if (boost::iequals(type,"RelationshipXref"))
		{
			update(boost::dynamic_pointer_cast<RelationshipXref>(object));
		}

		if (boost::iequals(type,"Rna"))
		{
			update(boost::dynamic_pointer_cast<Rna>(object));
		}

		if (boost::iequals(type,"RnaReference"))
		{
			update(boost::dynamic_pointer_cast<RnaReference>(object));
		}

		if (boost::iequals(type,"RnaRegion"))
		{
			update(boost::dynamic_pointer_cast<RnaRegion>(object));
		}

		if (boost::iequals(type,"RnaRegionReference"))
		{
			update(boost::dynamic_pointer_cast<RnaRegionReference>(object));
		}

		if (boost::iequals(type,"Score"))
		{
			update(boost::dynamic_pointer_cast<Score>(object));
		}

		if (boost::iequals(type,"SequenceInterval"))
		{
			update(boost::dynamic_pointer_cast<SequenceInterval>(object));
		}

		if (boost::iequals(type,"SequenceLocation"))
		{
			update(boost::dynamic_pointer_cast<SequenceLocation>(object));
		}

		if (boost::iequals(type,"SequenceModificationVocabulary"))
		{
			update(boost::dynamic_pointer_cast<SequenceModificationVocabulary>(object));
		}

		if (boost::iequals(type,"SequenceRegionVocabulary"))
		{
			update(boost::dynamic_pointer_cast<SequenceRegionVocabulary>(object));
		}

		if (boost::iequals(type,"SequenceSite"))
		{
			update(boost::dynamic_pointer_cast<SequenceSite>(object));
		}

		if (boost::iequals(type,"SmallMolecule"))
		{
			update(boost::dynamic_pointer_cast<SmallMolecule>(object));
		}

		if (boost::iequals(type,"SmallMoleculeReference"))
		{
			update(boost::dynamic_pointer_cast<SmallMoleculeReference>(object));
		}

		if (boost::iequals(type,"Stoichiometry"))
		{
			update(boost::dynamic_pointer_cast<Stoichiometry>(object));
		}

		if (boost::iequals(type,"TemplateReaction"))
		{
			update(boost::dynamic_pointer_cast<TemplateReaction>(object));
		}

		if (boost::iequals(type,"TemplateReactionRegulation"))
		{
			update(boost::dynamic_pointer_cast<TemplateReactionRegulation>(object));
		}

		if (boost::iequals(type,"Thing"))
		{
			update(boost::dynamic_pointer_cast<Thing>(object));
		}

		if (boost::iequals(type,"TissueVocabulary"))
		{
			update(boost::dynamic_pointer_cast<TissueVocabulary>(object));
		}

		if (boost::iequals(type,"Transport"))
		{
			update(boost::dynamic_pointer_cast<Transport>(object));
		}

		if (boost::iequals(type,"TransportWithBiochemicalReaction"))
		{
			update(boost::dynamic_pointer_cast<TransportWithBiochemicalReaction>(object));
		}

		if (boost::iequals(type,"UnificationXref"))
		{
			update(boost::dynamic_pointer_cast<UnificationXref>(object));
		}

		if (boost::iequals(type,"UtilityClass"))
		{
			update(boost::dynamic_pointer_cast<UtilityClass>(object));
		}

		if (boost::iequals(type,"Xref"))
		{
			update(boost::dynamic_pointer_cast<Xref>(object));
		}

		// EXT classes:

		if (boost::iequals(type,"AlgebraicRule"))
		{
			update(boost::dynamic_pointer_cast<AlgebraicRule>(object));
		}
		if (boost::iequals(type,"AssignmentRule"))
		{
			update(boost::dynamic_pointer_cast<AssignmentRule>(object));
		}
		if (boost::iequals(type,"Constraint"))
		{
			update(boost::dynamic_pointer_cast<Constraint>(object));
		}
		if (boost::iequals(type,"Delay"))
		{
			update(boost::dynamic_pointer_cast<Delay>(object));
		}
		if (boost::iequals(type,"Event"))
		{
			update(boost::dynamic_pointer_cast<Event>(object));
		}
		if (boost::iequals(type,"EventAssignment"))
		{
			update(boost::dynamic_pointer_cast<EventAssignment>(object));
		}
		if (boost::iequals(type,"Experiment"))
		{
			update(boost::dynamic_pointer_cast<Experiment>(object));
		}
		if (boost::iequals(type,"FunctionDefinition"))
		{
			update(boost::dynamic_pointer_cast<FunctionDefinition>(object));
		}
		if (boost::iequals(type,"IdMapping"))
		{
			update(boost::dynamic_pointer_cast<IdMapping>(object));
		}
		if (boost::iequals(type,"ImportSource"))
		{
			update(boost::dynamic_pointer_cast<ImportSource>(object));
		}
		if (boost::iequals(type,"InitialAssignment"))
		{
			update(boost::dynamic_pointer_cast<InitialAssignment>(object));
		}
		if (boost::iequals(type,"KineticLaw"))
		{
			update(boost::dynamic_pointer_cast<KineticLaw>(object));
		}
		if (boost::iequals(type,"LocalParameter"))
		{
			update(boost::dynamic_pointer_cast<LocalParameter>(object));
		}
		if (boost::iequals(type,"Math"))
		{
			update(boost::dynamic_pointer_cast<Math>(object));
		}
		if (boost::iequals(type,"Model"))
		{
			update(boost::dynamic_pointer_cast<Model>(object));
		}
		if (boost::iequals(type,"Parameter"))
		{
			update(boost::dynamic_pointer_cast<Parameter>(object));
		}
		if (boost::iequals(type,"Priority"))
		{
			update(boost::dynamic_pointer_cast<Priority>(object));
		}
		if (boost::iequals(type,"RateRule"))
		{
			update(boost::dynamic_pointer_cast<RateRule>(object));
		}
		if (boost::iequals(type,"ResultObject"))
		{
			update(boost::dynamic_pointer_cast<ResultObject>(object));
		}
		if (boost::iequals(type,"Rule"))
		{
			update(boost::dynamic_pointer_cast<Rule>(object));
		}
		if (boost::iequals(type,"SBase"))
		{
			update(boost::dynamic_pointer_cast<SBase>(object));
		}
		if (boost::iequals(type,"Sample"))
		{
			update(boost::dynamic_pointer_cast<Sample>(object));
		}
		if (boost::iequals(type,"Series"))
		{
			update(boost::dynamic_pointer_cast<Series>(object));
		}
		if (boost::iequals(type,"Trigger"))
		{
			update(boost::dynamic_pointer_cast<Trigger>(object));
		}
		if (boost::iequals(type,"UPBase"))
		{
			update(boost::dynamic_pointer_cast<UPBase>(object));
		}
		if (boost::iequals(type,"Unit"))
		{
			update(boost::dynamic_pointer_cast<Unit>(object));
		}
		if (boost::iequals(type,"UnitDefinition"))
		{
			update(boost::dynamic_pointer_cast<UnitDefinition>(object));
		}

	}

	return true;

}

bool UniPAX::PersistenceManager::remove(boost::shared_ptr<UPBase> object)
{
	std::map<boost::shared_ptr<UPBase>, std::string>::iterator object_search = pointer_id_.find(object);
	std::string id;
	std::stringstream ss;
	ss << object->getUnipaxId();
	ss >> id;

	if (object_search != pointer_id_.end())
	{
		if (object_search->second != id)
			return false;

		pointer_map_.erase(object_search->second);
		pointer_type_map_.erase(object_search->second);
		pointer_merged_map_.erase(object_search->second);
		pointer_id_.erase(object_search);
	}

	return true;
}





boost::shared_ptr<UniPAX::UPBase> UniPAX::PersistenceManager::getInstance(std::string id, std::string type)
{
	std::map<std::string, boost::shared_ptr<UPBase> >::iterator object_search = pointer_map_.find(id);
	std::map<std::string, std::string>::iterator type_search = pointer_type_map_.find(id);


	if (object_search == pointer_map_.end())
	{
		// no such element generated
		std::cerr << "no object with id " << id << std::endl;
		return boost::shared_ptr<UniPAX::UPBase>();
	}

	// check for type
	if (type_search == pointer_type_map_.end())
	{
		// type is irrelevant
		if (type.empty())
		{
			return object_search->second;
		}
		// no type available
		std::cerr << "no type for object with id " << id << " ... should be " << type << std::endl;
		return boost::shared_ptr<UniPAX::UPBase>();
	}

	// check if types are the same
	if (type.empty() || type_search->second == type)
	{
		return object_search->second;
	}

	return boost::shared_ptr<UniPAX::UPBase>();
}


int UniPAX::PersistenceManager::getInstanceCount()
{
	return pointer_map_.size();
}


std::map<std::string, boost::shared_ptr<UniPAX::UPBase> > & UniPAX::PersistenceManager::getData()
{
	return pointer_map_;
}
const std::map<std::string, boost::shared_ptr<UniPAX::UPBase> >& UniPAX::PersistenceManager::getData() const
{
	return pointer_map_;
}

std::map<boost::shared_ptr<UniPAX::UPBase> , std::string>& UniPAX::PersistenceManager::getPointerId()
{
	return pointer_id_;
}
const std::map<boost::shared_ptr<UniPAX::UPBase> , std::string>& UniPAX::PersistenceManager::getPointerId() const
{
	return pointer_id_;
}

std::map<std::string, std::string>& UniPAX::PersistenceManager::getIdToType()
{

	return pointer_type_map_;
}

const std::map<std::string, std::string>& UniPAX::PersistenceManager::getIdToType() const
{

	return pointer_type_map_;
}


const std::string UniPAX::PersistenceManager::getInstanceType(const std::string id)
{
	if (pointer_type_map_.find(id) != pointer_type_map_.end())
		return pointer_type_map_.find(id)->second;
	return "";
}


void UniPAX::PersistenceManager::addMerge(boost::shared_ptr<UniPAX::UPBase> old_object, boost::shared_ptr<UniPAX::UPBase> new_object)
{
	std::string new_id;
	std::stringstream ss;
	ss << new_object->getUnipaxId();
	ss >> new_id;

	std::string old_id;
	std::stringstream ss2;
	ss2 << old_object->getUnipaxId();
	ss2 >> old_id;

	pointer_merged_map_[old_id] = new_id;
}



bool UniPAX::PersistenceManager::isMerged(boost::shared_ptr<UniPAX::UPBase> object)
{
	if (object == 0)
	{
		//		std::cout << "object was null" << std::endl;
		return false;
	}

	std::string old_id;
	std::stringstream ss;
	ss << object->getUnipaxId();
	ss >> old_id;

	if (pointer_merged_map_.find(old_id) != pointer_merged_map_.end())
		return true;

	return false;
}

boost::shared_ptr<UniPAX::UPBase> UniPAX::PersistenceManager::getMergedObject(boost::shared_ptr<UniPAX::UPBase> object)
{
	std::string old_id;
	std::stringstream ss;
	ss << object->getUnipaxId();
	ss >> old_id;

	if (pointer_merged_map_.find(old_id) != pointer_merged_map_.end())
	{
		std::string new_id = pointer_merged_map_.find(old_id)->second;
		return getInstance(new_id);
	}

	return boost::shared_ptr<UniPAX::UPBase>();
}

bool UniPAX::PersistenceManager::convertAttribute(const std::string& value, UnipaxId& new_value)
{
	new_value = 0;
	if (value.empty())
		return true;
	std::stringstream ss;
	ss << value;

	return !(ss >> new_value).fail();
}

bool UniPAX::PersistenceManager::convertAttribute(const std::string& value, int& new_value)
{
	new_value = 0;
	if (value.empty())
		return true;
	std::stringstream ss;
	ss << value;

	return !(ss >> new_value).fail();
}


bool UniPAX::PersistenceManager::convertAttribute(const std::string& value, double& new_value)
{
	new_value = 0;
	if (value.empty())
		return true;
	std::stringstream ss;
	ss << value;

	return !(ss >> new_value).fail();
}


bool UniPAX::PersistenceManager::convertAttribute(const std::string& value, bool& new_value)
{
	new_value = false;
	if (value.empty())
		return true;
	std::stringstream ss;
	ss << value;

	return !(ss >> new_value).fail();
}


bool UniPAX::PersistenceManager::convertAttribute(const UnipaxId& value, std::string& new_value)
{
	new_value = "";
	std::stringstream ss;
	if ((ss << value).fail())
		return false;

	ss << "#integer";

	ss >> new_value;
	return true;

}


bool UniPAX::PersistenceManager::convertAttribute(const int& value, std::string& new_value)
{
	new_value = "";
	std::stringstream ss;
	if ((ss << value).fail())
		return false;

	ss << "#integer";

	ss >> new_value;
	return true;

}

bool UniPAX::PersistenceManager::convertAttribute(const double& value, std::string& new_value)
{
	new_value = "";
	std::stringstream ss;
	if ((ss << value).fail())
		return false;

	ss << "#double";

	ss >> new_value;
	return true;

}

bool UniPAX::PersistenceManager::convertAttribute(const bool& value, std::string& new_value)
{
	new_value = "";
	std::stringstream ss;
	if ((ss << value).fail())
		return false;

	ss << "#boolean";

	ss >> new_value;
	return true;

}


bool UniPAX::PersistenceManager::clear()
{
	pointer_map_.clear();
	pointer_id_.clear();
	pointer_type_map_.clear();
	pointer_merged_map_.clear();
	errorMsgs.clear();

	return true;
}

bool UniPAX::PersistenceManager::assignImportSource(UniPAX::ImportSourcePtr data_source)
{
	// link all children of UIBase type objects to the data_source
	std::set<std::string> types_with_is = UniPAX::Kernel::children("UIBase", true);
	typedef std::map<boost::shared_ptr<UniPAX::UPBase>, std::string> pointer_id_map_t;
	for (pointer_id_map_t::iterator pit = pointer_id_.begin(); pit != pointer_id_.end(); pit++)
	{
		if (types_with_is.find(pit->first->getType()) != types_with_is.end())
		{ // pit->first is an pointer to an object of a class type which is a child of UIBase
			boost::dynamic_pointer_cast<UIBase>(pit->first)->setUnipaxSource(data_source);
		}
	}
	// is already an ImportSource registered in the manager?
	std::map<std::string, std::string>::iterator find_is = pointer_type_map_.begin();
	while (find_is != pointer_type_map_.end())
	{
		if (boost::iequals(find_is->second, UniPAX::ImportSource::type()))
			break;
	}
	std::string id = "ImportSource";
	if (find_is != pointer_type_map_.end()) // found existing registered IS
	{
		id = find_is->first;
		UniPAX::UPBasePtr old_data_source = getInstance(id, "");
		remove(old_data_source);
	}
	// register new IS
	return registerInstance<UniPAX::ImportSource>(id, data_source);
}

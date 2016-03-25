#include <UNIPAX/KERNEL/Kernel.h>
#include <iostream>


static std::set<std::string> createTypes()
{
	std::set<std::string> set;

	set.insert("BindingFeature");
	set.insert("BioSource");
	set.insert("BiochemicalPathwayStep");
	set.insert("BiochemicalReaction");
	set.insert("Catalysis");
	set.insert("CellVocabulary");
	set.insert("CellularLocationVocabulary");
	set.insert("ChemicalStructure");
	set.insert("Complex");
	set.insert("ComplexAssembly");
	set.insert("Control");
	set.insert("ControlledVocabulary");
	set.insert("Conversion");
	set.insert("CovalentBindingFeature");
	set.insert("Degradation");
	set.insert("DeltaG");
	set.insert("Dna");
	set.insert("DnaReference");
	set.insert("DnaRegion");
	set.insert("DnaRegionReference");
	set.insert("Entity");
	set.insert("EntityFeature");
	set.insert("EntityReference");
	set.insert("EntityReferenceTypeVocabulary");
	set.insert("Evidence");
	set.insert("EvidenceCodeVocabulary");
	set.insert("ExperimentalForm");
	set.insert("ExperimentalFormVocabulary");
	set.insert("FragmentFeature");
	set.insert("Gene");
	set.insert("GeneticInteraction");
	set.insert("Interaction");
	set.insert("InteractionVocabulary");
	set.insert("KPrime");
	set.insert("ModificationFeature");
	set.insert("Modulation");
	set.insert("MolecularInteraction");
	set.insert("Pathway");
	set.insert("PathwayStep");
	set.insert("PhenotypeVocabulary");
	set.insert("PhysicalEntity");
	set.insert("Protein");
	set.insert("ProteinReference");
	set.insert("Provenance");
	set.insert("PublicationXref");
	set.insert("RelationshipTypeVocabulary");
	set.insert("RelationshipXref");
	set.insert("Rna");
	set.insert("RnaReference");
	set.insert("RnaRegion");
	set.insert("RnaRegionReference");
	set.insert("Score");
	set.insert("SequenceInterval");
	set.insert("SequenceLocation");
	set.insert("SequenceModificationVocabulary");
	set.insert("SequenceRegionVocabulary");
	set.insert("SequenceSite");
	set.insert("SmallMolecule");
	set.insert("SmallMoleculeReference");
	set.insert("Stoichiometry");
	set.insert("TemplateReaction");
	set.insert("TemplateReactionRegulation");
	set.insert("Thing");
	set.insert("TissueVocabulary");
	set.insert("Transport");
	set.insert("TransportWithBiochemicalReaction");
	set.insert("UnificationXref");
	set.insert("UtilityClass");
	set.insert("Xref");

	set.insert("AlgebraicRule");
	set.insert("AssignmentRule");
	set.insert("Constraint");
	set.insert("DataMatrix");
	set.insert("Delay");
	set.insert("EventAssignment");
	set.insert("Experiment");
	set.insert("FunctionDefinition");
	set.insert("IdMapping");
	set.insert("ImportSource");
	set.insert("InitialAssignment");
	set.insert("KineticLaw");
	set.insert("LocalParameter");
	set.insert("Math");
	set.insert("Model");
	set.insert("Parameter");
	set.insert("Priority");
	set.insert("RateRule");
	set.insert("ResultObject");
	set.insert("Rule");
	set.insert("Sample");
	set.insert("Series");
	set.insert("SBase");
	set.insert("Trigger");
	set.insert("UIBase");
	set.insert("UPBase");
	set.insert("Unit");
	set.insert("UnitDefinition");

	return set;
}

std::set<std::string> UniPAX::Kernel::_types = createTypes();

static std::map<std::string, std::vector<std::string> > createParents()
{
	std::map<std::string, std::vector<std::string> > map;

	map["BindingFeature"].push_back("EntityFeature");
	map["BiochemicalPathwayStep"].push_back("PathwayStep");
	map["BiochemicalReaction"].push_back("Conversion");
	map["BioSource"].push_back("UtilityClass");
	map["Catalysis"].push_back("Control");
	map["CellularLocationVocabulary"].push_back("ControlledVocabulary");
	map["CellVocabulary"].push_back("ControlledVocabulary");
	map["ChemicalStructure"].push_back("UtilityClass");
	map["ComplexAssembly"].push_back("Conversion");
	map["Complex"].push_back("PhysicalEntity");
	map["Control"].push_back("Interaction");
	map["ControlledVocabulary"].push_back("UtilityClass");
	map["Conversion"].push_back("Interaction");
	map["CovalentBindingFeature"].push_back("BindingFeature");
	map["Degradation"].push_back("Conversion");
	map["DeltaG"].push_back("UtilityClass");
	map["Dna"].push_back("PhysicalEntity");
	map["DnaReference"].push_back("EntityReference");
	map["DnaRegion"].push_back("PhysicalEntity");
	map["DnaRegionReference"].push_back("EntityReference");
	map["EntityFeature"].push_back("UtilityClass");
	map["Entity"].push_back("Thing");
	map["EntityReference"].push_back("UtilityClass");
	map["EntityReferenceTypeVocabulary"].push_back("ControlledVocabulary");
	map["EvidenceCodeVocabulary"].push_back("ControlledVocabulary");
	map["Evidence"].push_back("UtilityClass");
	map["ExperimentalForm"].push_back("UtilityClass");
	map["ExperimentalFormVocabulary"].push_back("ControlledVocabulary");
	map["FragmentFeature"].push_back("EntityFeature");
	map["Gene"].push_back("Entity");
	map["GeneticInteraction"].push_back("Interaction");
	map["Interaction"].push_back("Entity");
	map["InteractionVocabulary"].push_back("ControlledVocabulary");
	map["KPrime"].push_back("UtilityClass");
	map["ModificationFeature"].push_back("EntityFeature");
	map["Modulation"].push_back("Control");
	map["MolecularInteraction"].push_back("Interaction");
	map["Pathway"].push_back("Entity");
	map["PathwayStep"].push_back("UtilityClass");
	map["PhenotypeVocabulary"].push_back("ControlledVocabulary");
	map["PhysicalEntity"].push_back("Entity");
	map["Protein"].push_back("PhysicalEntity");
	map["ProteinReference"].push_back("EntityReference");
	map["Provenance"].push_back("UtilityClass");
	map["PublicationXref"].push_back("Xref");
	map["RelationshipTypeVocabulary"].push_back("ControlledVocabulary");
	map["RelationshipXref"].push_back("Xref");
	map["Rna"].push_back("PhysicalEntity");
	map["RnaReference"].push_back("EntityReference");
	map["RnaRegion"].push_back("PhysicalEntity");
	map["RnaRegionReference"].push_back("EntityReference");
	map["Score"].push_back("UtilityClass");
	map["SequenceInterval"].push_back("SequenceLocation");
	map["SequenceLocation"].push_back("UtilityClass");
	map["SequenceModificationVocabulary"].push_back("ControlledVocabulary");
	map["SequenceRegionVocabulary"].push_back("ControlledVocabulary");
	map["SequenceSite"].push_back("SequenceLocation");
	map["SmallMolecule"].push_back("PhysicalEntity");
	map["SmallMoleculeReference"].push_back("EntityReference");
	map["Stoichiometry"].push_back("UtilityClass");
	map["TemplateReaction"].push_back("Interaction");
	map["TemplateReactionRegulation"].push_back("Control");
	map["Thing"].push_back("UIBase");
	map["TissueVocabulary"].push_back("ControlledVocabulary");
	map["Transport"].push_back("Conversion");
	map["TransportWithBiochemicalReaction"].push_back("BiochemicalReaction");
	map["UnificationXref"].push_back("Xref");
	map["UtilityClass"].push_back("Thing");
	map["Xref"].push_back("UtilityClass");

	map["AlgebraicRule"].push_back("Rule");
	map["AssignmentRule"].push_back("Rule");
	map["Constraint"].push_back("SBase");
	map["Delay"].push_back("SBase");
	map["EventAssignment"].push_back("SBase");
	map["Event"].push_back("SBase");
	map["Experiment"].push_back("UPBase");
	map["FunctionDefinition"].push_back("SBase");
	map["IdMapping"].push_back("UPBase");
	map["ImportSource"].push_back("UPBase");
	map["InitialAssignment"].push_back("SBase");
	map["KineticLaw"].push_back("SBase");
	map["LocalParameter"].push_back("SBase");
	map["Math"].push_back("UPBase");
	map["Model"].push_back("SBase");
	map["Parameter"].push_back("SBase");
	map["Priority"].push_back("SBase");
	map["RateRule"].push_back("Rule");
	map["ResultObject"].push_back("UPBase");
	map["Rule"].push_back("SBase");
	map["Sample"].push_back("UIBase");
	map["SBase"].push_back("UIBase");
	map["Series"].push_back("Entity");
	map["Trigger"].push_back("SBase");
	map["UnitDefinition"].push_back("SBase");
	map["Unit"].push_back("SBase");
	map["UIBase"].push_back("UPBase");

	return map;
}

std::map<std::string, std::vector<std::string> > UniPAX::Kernel::_parents = createParents();


static std::map<std::string, std::vector<std::string> > createChildren()
{
	std::map<std::string, std::vector<std::string> > _parents = createParents();

	std::map<std::string, std::vector<std::string> > map;

	for (std::map<std::string, std::vector<std::string> >::iterator it = _parents.begin(); it != _parents.end(); ++it)
	{

		for (std::vector<std::string>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			map[*it2].push_back(it->first);
		}
	}

	return map;
}

std::map<std::string, std::vector<std::string> > UniPAX::Kernel::_children = createChildren();

static std::map<std::string, std::string> createShortType()
{
	std::map<std::string, std::string> map;

	map["CellularLocationVocabulary"] = "CellularLocationVocabulary";
	map["ControlledVocabulary"] = "ControlledVocabulary";
	map["CovalentBindingFeature"] = "CovalentBindingFeature";
	map["EntityReferenceTypeVocabulary"] = "EntityReferenceTypeVocabulary";
	map["EvidenceCodeVocabulary"] = "EvidenceCodeVocabulary";
	map["ExperimentalForm"] = "ExperimentalForm";
	map["ExperimentalFormVocabulary"] = "ExperimentalFormVocabulary";
	map["InteractionVocabulary"] = "InteractionVocabulary";
	map["PhenotypeVocabulary"] = "PhenotypeVocabulary";
	map["RelationshipTypeVocabulary"] = "RelationshipTypeVocabulary";
	map["SequenceModificationVocabulary"] = "SequenceModificationVocabulary";
	map["SequenceRegionVocabulary"] = "SequenceRegionVocabulary";
	map["SmallMoleculeReference"] = "SmallMoleculeReference";
	map["TemplateReactionRegulation"] = "TemplateReactionRegulation";
	map["TransportWithBiochemicalReaction"] = "TransportWithBiochemicalReaction";

	return map;
}

std::map<std::string, std::string> UniPAX::Kernel::_shortType = createShortType();

static std::map<std::string, UniPAX::ClassType::ID> createTypeId()
{

	std::map<std::string, UniPAX::ClassType::ID> map;

	// Thing
	map["Entity"] = UniPAX::ClassType::idEntity;
	map["Gene"] = UniPAX::ClassType::idGene;
	map["Interaction"] = UniPAX::ClassType::idInteraction;
	map["Pathway"] = UniPAX::ClassType::idPathway;
	map["PhysicalEntity"] = UniPAX::ClassType::idPhysicalEntity;
	map["Series"] = UniPAX::ClassType::idSeries; // ???

	map["Control"] = UniPAX::ClassType::idControl;
	map["Conversion"] = UniPAX::ClassType::idConversion;
	map["GeneticInteraction"] = UniPAX::ClassType::idGeneticInteraction;
	map["MolecularInteraction"] = UniPAX::ClassType::idMolecularInteraction;
	map["TemplateReaction"] = UniPAX::ClassType::idTemplateReaction;
	map["Catalysis"] = UniPAX::ClassType::idCatalysis;
	map["Modulation"] = UniPAX::ClassType::idModulation;
	map["TemplateReactionRegulation"] = UniPAX::ClassType::idTemplateReactionRegulation;
	map["BiochemicalReaction"] = UniPAX::ClassType::idBiochemicalReaction;
	map["ComplexAssembly"] = UniPAX::ClassType::idComplexAssembly;
	map["Degradation"] = UniPAX::ClassType::idDegradation;
	map["Transport"] = UniPAX::ClassType::idTransport;
	map["TransportWithBiochemicalReaction"] = UniPAX::ClassType::idTransportWithBiochemicalReaction;
	map["Complex"] = UniPAX::ClassType::idComplex;
	map["Dna"] = UniPAX::ClassType::idDna;
	map["DnaRegion"] = UniPAX::ClassType::idDnaRegion;
	map["Protein"] = UniPAX::ClassType::idProtein;
	map["Rna"] = UniPAX::ClassType::idRna;
	map["RnaRegion"] = UniPAX::ClassType::idRnaRegion;
	map["SmallMolecule"] = UniPAX::ClassType::idSmallMolecule;

	map["BioSource"] = UniPAX::ClassType::idBioSource;
	map["ChemicalStructure"] = UniPAX::ClassType::idChemicalStructure;
	map["ControlledVocabulary"] = UniPAX::ClassType::idControlledVocabulary;
	map["DeltaG"] = UniPAX::ClassType::idDeltaG;
	map["EntityFeature"] = UniPAX::ClassType::idEntityFeature;
	map["EntityReference"] = UniPAX::ClassType::idEntityReference;
	map["Evidence"] = UniPAX::ClassType::idEvidence;
	map["ExperimentalForm"] = UniPAX::ClassType::idExperimentalForm;
	map["KPrime"] = UniPAX::ClassType::idKPrime;
	map["PathwayStep"] = UniPAX::ClassType::idPathwayStep;
	map["Provenance"] = UniPAX::ClassType::idProvenance;
	map["Score"] = UniPAX::ClassType::idScore;
	map["SequenceLocation"] = UniPAX::ClassType::idSequenceLocation;
	map["Stoichiometry"] = UniPAX::ClassType::idStoichiometry;
	map["Xref"] = UniPAX::ClassType::idXref;

	map["CellVocabulary"] = UniPAX::ClassType::idCellVocabulary;
	map["CellularLocationVocabulary"] = UniPAX::ClassType::idCellularLocationVocabulary;
	map["EntityReferenceTypeVocabulary"] = UniPAX::ClassType::idEntityReferenceTypeVocabulary;
	map["EvidenceCodeVocabulary"] = UniPAX::ClassType::idEvidenceCodeVocabulary;
	map["ExperimentalFormVocabulary"] = UniPAX::ClassType::idExperimentalFormVocabulary;
	map["InteractionVocabulary"] = UniPAX::ClassType::idInteractionVocabulary;
	map["PhenotypeVocabulary"] = UniPAX::ClassType::idPhenotypeVocabulary;
	map["RelationshipTypeVocabulary"] = UniPAX::ClassType::idRelationshipTypeVocabulary;
	map["SequenceModificationVocabulary"] = UniPAX::ClassType::idSequenceModificationVocabulary;
	map["SequenceRegionVocabulary"] = UniPAX::ClassType::idSequenceRegionVocabulary;
	map["TissueVocabulary"] = UniPAX::ClassType::idTissueVocabulary;

	map["BindingFeature"] = UniPAX::ClassType::idBindingFeature;
	map["FragmentFeature"] = UniPAX::ClassType::idFragmentFeature;
	map["ModificationFeature"] = UniPAX::ClassType::idModificationFeature;
	map["CovalentBindingFeature"] = UniPAX::ClassType::idCovalentBindingFeature;

	map["DnaReference"] = UniPAX::ClassType::idDnaReference;
	map["DnaRegionReference"] = UniPAX::ClassType::idDnaRegionReference;
	map["ProteinReference"] = UniPAX::ClassType::idProteinReference;
	map["RnaReference"] = UniPAX::ClassType::idRnaReference;
	map["RnaRegionReference"] = UniPAX::ClassType::idRnaRegionReference;
	map["SmallMoleculeReference"] = UniPAX::ClassType::idSmallMoleculeReference;

	map["BiochemicalPathwayStep"] = UniPAX::ClassType::idBiochemicalPathwayStep;

	map["SequenceInterval"] = UniPAX::ClassType::idSequenceInterval;
	map["SequenceSite"] = UniPAX::ClassType::idSequenceSite;

	map["PublicationXref"] = UniPAX::ClassType::idPublicationXref;
	map["RelationshipXref"] = UniPAX::ClassType::idRelationshipXref;
	map["UnificationXref"] = UniPAX::ClassType::idUnificationXref;

	// SBase
	map["Experiment"] = UniPAX::ClassType::idExperiment;
	map["IdMapping"] = UniPAX::ClassType::idIdMapping;
	map["ImportSource"] = UniPAX::ClassType::idImportSource;
	map["Math"] = UniPAX::ClassType::idMath;
	map["ResultObject"] = UniPAX::ClassType::idResultObject;
	map["Sample"] = UniPAX::ClassType::idSample;

	map["Constraint"] = UniPAX::ClassType::idConstraint;
	map["Delay"] = UniPAX::ClassType::idDelay;
	map["Event"] = UniPAX::ClassType::idEvent;
	map["EventAssignment"] = UniPAX::ClassType::idEventAssignment;
	map["FunctionDefinition"] = UniPAX::ClassType::idFunctionDefinition;
	map["InitialAssignment"] = UniPAX::ClassType::idInitialAssignment;
	map["KineticLaw"] = UniPAX::ClassType::idKineticLaw;
	map["LocalParameter"] = UniPAX::ClassType::idLocalParameter;
	map["Model"] = UniPAX::ClassType::idModel;
	map["Parameter"] = UniPAX::ClassType::idParameter;
	map["Priority"] = UniPAX::ClassType::idPriority;
	map["Rule"] = UniPAX::ClassType::idRule;
	map["AlgebraicRule"] = UniPAX::ClassType::idAlgebraicRule;
	map["AssignmentRule"] = UniPAX::ClassType::idAssignmentRule;
	map["RateRule"] = UniPAX::ClassType::idRateRule;
	map["Trigger"] = UniPAX::ClassType::idTrigger;
	map["Unit"] = UniPAX::ClassType::idUnit;
	map["UnitDefinition"] = UniPAX::ClassType::idUnitDefinition;

	return map;
}

std::map<std::string, UniPAX::ClassType::ID> UniPAX::Kernel::_type_id = createTypeId();

static std::map<UniPAX::ClassType::ID, std::string> createIdType()
{
	std::map<std::string, UniPAX::ClassType::ID> _type_id = createTypeId();

	std::map<UniPAX::ClassType::ID, std::string> map;

	// reverse map
	for (std::map<std::string, UniPAX::ClassType::ID>::iterator it = _type_id.begin(); it != _type_id.end(); it++)
	{
		map[it->second] = it->first;
	}

	return map;
}

std::map<UniPAX::ClassType::ID, std::string> UniPAX::Kernel::_id_type = createIdType();


bool UniPAX::Kernel::isType(std::string type)
{
	return _types.find(type) != _types.end();
}

std::set<std::string> UniPAX::Kernel::classes()
{
	return _types;
}

std::set<std::string> UniPAX::Kernel::parents(std::string type, bool recursive)
{
	if (!isType(type))
		return std::set<std::string>();


	std::set<std::string> v;
	if (recursive)
	{
		parents(type, v);
	}
	else if (_parents.find(type) != _parents.end())
	{
		v.insert(_parents[type].begin(), _parents[type].end());
	}

	return v;
}

void UniPAX::Kernel::parents(std::string type, std::set<std::string> & v)
{
	if (_parents.find(type) != _parents.end())
	{
		for (std::vector<std::string>::iterator it = _parents[type].begin(); it != _parents[type].end(); ++it)
		{
			v.insert(*it);
			parents(*it, v);
		}
	}
}

std::set<std::string> UniPAX::Kernel::children(std::string type, bool recursive)
{

	if (!isType(type))
		return std::set<std::string>();

	std::set<std::string> v;

	if (recursive)
	{
		children(type, v);
	}
	else
	{
		if (_children.find(type) != _children.end())
		{
			v.insert(_children[type].begin(), _children[type].end());
		}
	}

	return v;
}

std::vector<std::string> UniPAX::Kernel::sorted_children(std::string type, bool recursive)
{
	if (!isType(type))
		return std::vector<std::string>();

	std::vector<std::string> v;

	if (recursive)
	{
		children(type, v);
	}
	else
	{
		if (_children.find(type) != _children.end())
		{
			for (std::vector<std::string>::iterator it = _children[type].begin(); it != _children[type].end(); ++it)
			{
				v.push_back(*it);
			}
		}
	}

	return v;
}

void UniPAX::Kernel::children(std::string type, std::set<std::string> & v)
{
	if (_children.find(type) != _children.end())
	{
		for (std::vector<std::string>::iterator it = _children[type].begin(); it != _children[type].end(); ++it)
		{
			v.insert(*it);
			children(*it, v);
		}
	}
}

void UniPAX::Kernel::children(std::string type, std::vector<std::string> & v)
{
	if (_children.find(type) != _children.end())
	{
		for (std::vector<std::string>::iterator it = _children[type].begin(); it != _children[type].end(); ++it)
		{
			v.push_back(*it);
			children(*it, v);
		}
	}
}



std::string UniPAX::Kernel::shortType(std::string type)
{
	if (!isType(type))
		throw std::runtime_error(type + " is not a valid UniPAX data type.");

	if (_shortType.find(type) != _shortType.end())
	{
		return _shortType[type];
	}

	return type;
}

UniPAX::ClassType::ID UniPAX::Kernel::classType(std::string type)
{
	if (_type_id.find(type) != _type_id.end())
	{
		return _type_id[type];
	}

	return ClassType::END_ENUM;
}

std::string UniPAX::Kernel::classType(UniPAX::ClassType::ID id, std::string default_value)
{
	if (_id_type.find(id) != _id_type.end())
	{
		return _id_type[id];
	}

	return default_value;
}

bool UniPAX::Kernel::isClassType(std::string type)
{
	return classType(type) != ClassType::END_ENUM;
}

bool UniPAX::Kernel::isClassType(UniPAX::ClassType::ID id)
{
	return id >= 0 && id < ClassType::END_ENUM;
}


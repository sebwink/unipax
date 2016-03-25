/*
 * All-odb.hxx
 *
 *  Created on: Jun 29, 2011
 *      Author: kuentzer
 */

#ifndef ALL_ODB_MYSQL_H_
#define ALL_ODB_MYSQL_H_

#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/BindingFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/BioSource-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/BiochemicalPathwayStep-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/BiochemicalReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Catalysis-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/CellVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/CellularLocationVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ChemicalStructure-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Complex-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ComplexAssembly-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Control-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ControlledVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Conversion-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/CovalentBindingFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Degradation-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/DeltaG-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Dna-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/DnaReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/DnaRegion-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/DnaRegionReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Entity-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/EntityFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/EntityReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/EntityReferenceTypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Evidence-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/EvidenceCodeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ExperimentalForm-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ExperimentalFormVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/FragmentFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Gene-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/GeneticInteraction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Interaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/InteractionVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/KPrime-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ModificationFeature-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Modulation-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/MolecularInteraction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Pathway-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/PathwayStep-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/PhenotypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/PhysicalEntity-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Protein-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/ProteinReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Provenance-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/PublicationXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/RelationshipTypeVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/RelationshipXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Rna-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/RnaReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/RnaRegion-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/RnaRegionReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Score-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SequenceInterval-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SequenceLocation-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SequenceModificationVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SequenceRegionVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SequenceSite-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SmallMolecule-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/SmallMoleculeReference-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Stoichiometry-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/TemplateReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/TemplateReactionRegulation-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Thing-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/TissueVocabulary-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Transport-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/TransportWithBiochemicalReaction-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/UnificationXref-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/UtilityClass-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/BIOPAX/Xref-odb.hxx>

#include <UNIPAX/PERSISTENCE/MYSQL/EXT/AlgebraicRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/AssignmentRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Constraint-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Delay-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Event-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/EventAssignment-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Experiment-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/FunctionDefinition-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/IdMapping-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/ImportSource-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/InitialAssignment-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/KineticLaw-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/LocalParameter-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Math-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Model-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Parameter-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Priority-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/RateRule-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/ResultObject-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Rule-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/SBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Sample-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/SampleData-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Series-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Trigger-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/UPBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/UIBase-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/Unit-odb.hxx>
#include <UNIPAX/PERSISTENCE/MYSQL/EXT/UnitDefinition-odb.hxx>



#endif /* ALL_ODB_MYSQL_H_ */

--<ScriptOptions statementTerminator=";"/>

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Stoichiometry_FK`;

ALTER TABLE `Database`.`Evidence` DROP FOREIGN KEY `Evidence_EntityReference_FK`;

ALTER TABLE `Database`.`Evidence` DROP FOREIGN KEY `Evidence_PathwayStep_FK`;

ALTER TABLE `Database`.`Trigger` DROP FOREIGN KEY `Trigger_Event_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_ExperimentalForm_FK`;

ALTER TABLE `Database`.`PublicationXref` DROP FOREIGN KEY `PublicationXref_Xref_FK`;

ALTER TABLE `Database`.`Event` DROP FOREIGN KEY `Event_Pathway_FK`;

ALTER TABLE `Database`.`Entity_x_PathwayStep` DROP FOREIGN KEY `Entity_x_PathwayStep_Entity_FK`;

ALTER TABLE `Database`.`ExperimentalForm` DROP FOREIGN KEY `ExperimentalForm_Evidence_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_Rna_FK`;

ALTER TABLE `Database`.`PathwayStep` DROP FOREIGN KEY `PathwayStep_PathwayStep_FK`;

ALTER TABLE `Database`.`ExperimentalFormVocabulary` DROP FOREIGN KEY `ExperimentalFormVocabulary_ExperimentalForm_FK`;

ALTER TABLE `Database`.`TissueVocabulary` DROP FOREIGN KEY `TissueVocabulary_BioSource_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_UtilityClass_FK`;

ALTER TABLE `Database`.`CovalentBindingFeature` DROP FOREIGN KEY `CovalentBindingFeature_BindingFeature_FK`;

ALTER TABLE `Database`.`EntityReferenceTypeVocabulary` DROP FOREIGN KEY `EntityReferenceTypeVocabulary_EntityReference_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_Provenance_FK`;

ALTER TABLE `Database`.`Pathway` DROP FOREIGN KEY `Pathway_Entity_FK1`;

ALTER TABLE `Database`.`TemplateReaction` DROP FOREIGN KEY `TemplateReaction_PhysicalEntity_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_ImportSource_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_BioSource_FK`;

ALTER TABLE `Database`.`EvidenceCodeVocabulary` DROP FOREIGN KEY `EvidenceCodeVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`DnaReference` DROP FOREIGN KEY `DnaReference_EntityReference_FK`;

ALTER TABLE `Database`.`SequenceLocation` DROP FOREIGN KEY `SequenceLocation_RnaRegionReference_FK`;

ALTER TABLE `Database`.`Unit` DROP FOREIGN KEY `Unit_UnitDefinition_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Conversion_FK1`;

ALTER TABLE `Database`.`Sample` DROP FOREIGN KEY `Sample_Experiment_FK`;

ALTER TABLE `Database`.`Dna` DROP FOREIGN KEY `Dna_PhysicalEntity_FK`;

ALTER TABLE `Database`.`InteractionVocabulary` DROP FOREIGN KEY `InteractionVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_Constraint_FK`;

ALTER TABLE `Database`.`PhenotypeVocabulary` DROP FOREIGN KEY `PhenotypeVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_SmallMolecule_FK`;

ALTER TABLE `Database`.`SmallMolecule` DROP FOREIGN KEY `SmallMolecule_PhysicalEntity_FK`;

ALTER TABLE `Database`.`UnificationXref` DROP FOREIGN KEY `UnificationXref_Xref_FK`;

ALTER TABLE `Database`.`FunctionDefinition` DROP FOREIGN KEY `FunctionDefinition_Pathway_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_Pathway_FK`;

ALTER TABLE `Database`.`KineticLaw` DROP FOREIGN KEY `KineticLaw_Conversion_FK`;

ALTER TABLE `Database`.`RnaReference` DROP FOREIGN KEY `RnaReference_EntityReference_FK1`;

ALTER TABLE `Database`.`SequenceSite` DROP FOREIGN KEY `SequenceSite_SequenceInterval_FK`;

ALTER TABLE `Database`.`UnitDefinition` DROP FOREIGN KEY `UnitDefinition_Pathway_FK`;

ALTER TABLE `Database`.`DeltaG` DROP FOREIGN KEY `DeltaG_UtilityClass_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_Evidence_FK`;

ALTER TABLE `Database`.`TemplateReaction` DROP FOREIGN KEY `TemplateReaction_Interaction_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_PublicationXref_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_UtilityClass_FK`;

ALTER TABLE `Database`.`Delay` DROP FOREIGN KEY `Delay_Event_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Catalysis_FK`;

ALTER TABLE `Database`.`Priority` DROP FOREIGN KEY `Priority_Event_FK`;

ALTER TABLE `Database`.`Entity_x_Control` DROP FOREIGN KEY `Entity_x_Control_Control_FK`;

ALTER TABLE `Database`.`Modulation` DROP FOREIGN KEY `Modulation_Control_FK`;

ALTER TABLE `Database`.`Provenance` DROP FOREIGN KEY `Provenance_Score_FK`;

ALTER TABLE `Database`.`RnaRegionReference` DROP FOREIGN KEY `RnaRegionReference_EntityReference_FK`;

ALTER TABLE `Database`.`ChemicalStructure` DROP FOREIGN KEY `ChemicalStructure_SmallMoleculeReference_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_Priority_FK`;

ALTER TABLE `Database`.`BindingFeature` DROP FOREIGN KEY `BindingFeature_EntityFeature_FK`;

ALTER TABLE `Database`.`SequenceModificationVocabulary` DROP FOREIGN KEY `SequenceModificationVocabulary_ModificationFeature_FK`;

ALTER TABLE `Database`.`CellVocabulary` DROP FOREIGN KEY `CellVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`DnaRegionReference` DROP FOREIGN KEY `DnaRegionReference_EntityReference_FK1`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_EntityFeature_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_DnaRegionReference_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_PhysicalEntity_FK`;

ALTER TABLE `Database`.`Score` DROP FOREIGN KEY `Score_GeneticInteraction_FK`;

ALTER TABLE `Database`.`PathwayStep` DROP FOREIGN KEY `PathwayStep_Pathway_FK`;

ALTER TABLE `Database`.`Entity` DROP FOREIGN KEY `Entity_Thing_FK`;

ALTER TABLE `Database`.`CellularLocationVocabulary` DROP FOREIGN KEY `CellularLocationVocabulary_PhysicalEntity_FK`;

ALTER TABLE `Database`.`SequenceSite` DROP FOREIGN KEY `SequenceSite_SequenceLocation_FK`;

ALTER TABLE `Database`.`Interaction` DROP FOREIGN KEY `Interaction_Entity_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_EntityReference_FK`;

ALTER TABLE `Database`.`BiochemicalPathwayStep` DROP FOREIGN KEY `BiochemicalPathwayStep_PathwayStep_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_PublicationXref_FK2`;

ALTER TABLE `Database`.`LocalParameter` DROP FOREIGN KEY `LocalParameter_KineticLaw_FK`;

ALTER TABLE `Database`.`ComplexAssembly` DROP FOREIGN KEY `ComplexAssembly_Conversion_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_Dna_FK`;

ALTER TABLE `Database`.`Protein` DROP FOREIGN KEY `Protein_PhysicalEntity_FK`;

ALTER TABLE `Database`.`GeneticInteraction` DROP FOREIGN KEY `GeneticInteraction_Interaction_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_Trigger_FK`;

ALTER TABLE `Database`.`InitialAssignment` DROP FOREIGN KEY `InitialAssignment_Math_FK`;

ALTER TABLE `Database`.`FunctionDefinition` DROP FOREIGN KEY `FunctionDefinition_SBase_FK`;

ALTER TABLE `Database`.`EventAssignment` DROP FOREIGN KEY `EventAssignment_SBase_FK`;

ALTER TABLE `Database`.`Stoichiometry` DROP FOREIGN KEY `Stoichiometry_Conversion_FK`;

ALTER TABLE `Database`.`Mapping` DROP FOREIGN KEY `Mapping_Experiment_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_Entity_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_Entity_FK`;

ALTER TABLE `Database`.`Control` DROP FOREIGN KEY `Control_Entity_FK`;

ALTER TABLE `Database`.`SequenceRegionVocabulary` DROP FOREIGN KEY `SequenceRegionVocabulary_DnaRegionReference_FK`;

ALTER TABLE `Database`.`AlgebraicRule` DROP FOREIGN KEY `AlgebraicRule_Rule_FK`;

ALTER TABLE `Database`.`SBase` DROP FOREIGN KEY `SBase_UPBase_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_EntityFeature_FK`;

ALTER TABLE `Database`.`Parameter` DROP FOREIGN KEY `Parameter_SBase_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_PhysicalEntity_FK`;

ALTER TABLE `Database`.`Evidence` DROP FOREIGN KEY `Evidence_EntityFeature_FK`;

ALTER TABLE `Database`.`Message` DROP FOREIGN KEY `Message_SBase_FK`;

ALTER TABLE `Database`.`Constraint` DROP FOREIGN KEY `Constraint_SBase_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_Protein_FK`;

ALTER TABLE `Database`.`Rule` DROP FOREIGN KEY `Rule_SBase_FK`;

ALTER TABLE `Database`.`Gene` DROP FOREIGN KEY `Gene_Entity_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_UPBase_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_RnaRegionReference_FK`;

ALTER TABLE `Database`.`RelationshipTypeVocabulary` DROP FOREIGN KEY `RelationshipTypeVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`CovalentBindingFeature` DROP FOREIGN KEY `CovalentBindingFeature_ModificationFeature_FK`;

ALTER TABLE `Database`.`ModificationFeature` DROP FOREIGN KEY `ModificationFeature_EntityFeature_FK`;

ALTER TABLE `Database`.`Transport` DROP FOREIGN KEY `Transport_Conversion_FK`;

ALTER TABLE `Database`.`Stoichiometry` DROP FOREIGN KEY `Stoichiometry_UtilityClass_FK`;

ALTER TABLE `Database`.`TransportWithBiochemicalReaction` DROP FOREIGN KEY `TransportWithBiochemicalReaction_BiochemicalReaction_FK`;

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` DROP FOREIGN KEY `Entity_x_ExperimentalForm_ExperimentalForm_FK`;

ALTER TABLE `Database`.`KPrime` DROP FOREIGN KEY `KPrime_UtilityClass_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_BioSource_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_Entity_FK2`;

ALTER TABLE `Database`.`Pathway` DROP FOREIGN KEY `Pathway_Entity_FK`;

ALTER TABLE `Database`.`Complex` DROP FOREIGN KEY `Complex_PhysicalEntity_FK`;

ALTER TABLE `Database`.`RateRule` DROP FOREIGN KEY `RateRule_Rule_FK`;

ALTER TABLE `Database`.`EvidenceCodeVocabulary` DROP FOREIGN KEY `EvidenceCodeVocabulary_Evidence_FK`;

ALTER TABLE `Database`.`SequenceLocation` DROP FOREIGN KEY `SequenceLocation_DnaRegionReference_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_Entity_FK`;

ALTER TABLE `Database`.`Conversion` DROP FOREIGN KEY `Conversion_Interaction_FK`;

ALTER TABLE `Database`.`Trigger` DROP FOREIGN KEY `Trigger_SBase_FK`;

ALTER TABLE `Database`.`SequenceRegionVocabulary` DROP FOREIGN KEY `SequenceRegionVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`Evidence` DROP FOREIGN KEY `Evidence_UtilityClass_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Conversion_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_UtilityClass_FK`;

ALTER TABLE `Database`.`RnaRegion` DROP FOREIGN KEY `RnaRegion_PhysicalEntity_FK`;

ALTER TABLE `Database`.`Event` DROP FOREIGN KEY `Event_SBase_FK`;

ALTER TABLE `Database`.`InteractionVocabulary` DROP FOREIGN KEY `InteractionVocabulary_Interaction_FK`;

ALTER TABLE `Database`.`PhenotypeVocabulary` DROP FOREIGN KEY `PhenotypeVocabulary_GeneticInteraction_FK`;

ALTER TABLE `Database`.`ExperimentalForm` DROP FOREIGN KEY `ExperimentalForm_UtilityClass_FK`;

ALTER TABLE `Database`.`ExperimentalFormVocabulary` DROP FOREIGN KEY `ExperimentalFormVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_RnaRegion_FK`;

ALTER TABLE `Database`.`TissueVocabulary` DROP FOREIGN KEY `TissueVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`Entity_x_Control` DROP FOREIGN KEY `Entity_x_Control_Entity_FK`;

ALTER TABLE `Database`.`RelationshipXref` DROP FOREIGN KEY `RelationshipXref_Xref_FK`;

ALTER TABLE `Database`.`ProteinReference` DROP FOREIGN KEY `ProteinReference_EntityReference_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_Gene_FK`;

ALTER TABLE `Database`.`EntityReferenceTypeVocabulary` DROP FOREIGN KEY `EntityReferenceTypeVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`RnaReference` DROP FOREIGN KEY `RnaReference_EntityReference_FK`;

ALTER TABLE `Database`.`DeltaG` DROP FOREIGN KEY `DeltaG_BiochemicalReaction_FK`;

ALTER TABLE `Database`.`TemplateReaction` DROP FOREIGN KEY `TemplateReaction_PhysicalEntity_FK1`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_EntityReference_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_ImportSource_FK1`;

ALTER TABLE `Database`.`DnaReference` DROP FOREIGN KEY `DnaReference_EntityReference_FK1`;

ALTER TABLE `Database`.`SequenceLocation` DROP FOREIGN KEY `SequenceLocation_UtilityClass_FK`;

ALTER TABLE `Database`.`Unit` DROP FOREIGN KEY `Unit_SBase_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Complex_FK`;

ALTER TABLE `Database`.`Catalysis` DROP FOREIGN KEY `Catalysis_Control_FK`;

ALTER TABLE `Database`.`Provenance` DROP FOREIGN KEY `Provenance_Entity_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_Delay_FK`;

ALTER TABLE `Database`.`BindingFeature` DROP FOREIGN KEY `BindingFeature_BindingFeature_FK`;

ALTER TABLE `Database`.`CellVocabulary` DROP FOREIGN KEY `CellVocabulary_BioSource_FK`;

ALTER TABLE `Database`.`SmallMoleculeReference` DROP FOREIGN KEY `SmallMoleculeReference_EntityReference_FK`;

ALTER TABLE `Database`.`DnaRegionReference` DROP FOREIGN KEY `DnaRegionReference_EntityReference_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_EntityReference_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_DnaReference_FK`;

ALTER TABLE `Database`.`DnaRegion` DROP FOREIGN KEY `DnaRegion_PhysicalEntity_FK`;

ALTER TABLE `Database`.`Score` DROP FOREIGN KEY `Score_Evidence_FK`;

ALTER TABLE `Database`.`KineticLaw` DROP FOREIGN KEY `KineticLaw_SBase_FK`;

ALTER TABLE `Database`.`SequenceSite` DROP FOREIGN KEY `SequenceSite_SequenceInterval_FK1`;

ALTER TABLE `Database`.`Entity` DROP FOREIGN KEY `Entity_Interaction_FK`;

ALTER TABLE `Database`.`InitialAssignment` DROP FOREIGN KEY `InitialAssignment_Pathway_FK`;

ALTER TABLE `Database`.`UnitDefinition` DROP FOREIGN KEY `UnitDefinition_SBase_FK`;

ALTER TABLE `Database`.`AssignmentRule` DROP FOREIGN KEY `AssignmentRule_Rule_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_Provenance_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_PublicationXref_FK1`;

ALTER TABLE `Database`.`FunctionDefinition` DROP FOREIGN KEY `FunctionDefinition_Math_FK`;

ALTER TABLE `Database`.`BiochemicalReaction` DROP FOREIGN KEY `BiochemicalReaction_Conversion_FK`;

ALTER TABLE `Database`.`Delay` DROP FOREIGN KEY `Delay_SBase_FK`;

ALTER TABLE `Database`.`PhysicalEntity` DROP FOREIGN KEY `PhysicalEntity_Entity_FK`;

ALTER TABLE `Database`.`Priority` DROP FOREIGN KEY `Priority_SBase_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_Rule_FK`;

ALTER TABLE `Database`.`Provenance` DROP FOREIGN KEY `Provenance_UtilityClass_FK`;

ALTER TABLE `Database`.`RnaRegionReference` DROP FOREIGN KEY `RnaRegionReference_EntityReference_FK1`;

ALTER TABLE `Database`.`ChemicalStructure` DROP FOREIGN KEY `ChemicalStructure_UtilityClass_FK`;

ALTER TABLE `Database`.`SequenceInterval` DROP FOREIGN KEY `SequenceInterval_SequenceLocation_FK`;

ALTER TABLE `Database`.`EventAssignment` DROP FOREIGN KEY `EventAssignment_Event_FK`;

ALTER TABLE `Database`.`TemplateReactionRegulation` DROP FOREIGN KEY `TemplateReactionRegulation_Control_FK`;

ALTER TABLE `Database`.`SequenceModificationVocabulary` DROP FOREIGN KEY `SequenceModificationVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`UtilityClass` DROP FOREIGN KEY `UtilityClass_Thing_FK`;

ALTER TABLE `Database`.`FragmentFeature` DROP FOREIGN KEY `FragmentFeature_EntityFeature_FK`;

ALTER TABLE `Database`.`SequenceRegionVocabulary` DROP FOREIGN KEY `SequenceRegionVocabulary_EntityFeature_FK`;

ALTER TABLE `Database`.`Parameter` DROP FOREIGN KEY `Parameter_Pathway_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_PhysicalEntity_FK1`;

ALTER TABLE `Database`.`Score` DROP FOREIGN KEY `Score_UtilityClass_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_ProteinReference_FK`;

ALTER TABLE `Database`.`PathwayStep` DROP FOREIGN KEY `PathwayStep_UtilityClass_FK`;

ALTER TABLE `Database`.`Evidence` DROP FOREIGN KEY `Evidence_Entity_FK`;

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` DROP FOREIGN KEY `Entity_x_ExperimentalForm_Entity_FK`;

ALTER TABLE `Database`.`Thing` DROP FOREIGN KEY `Thing_UPBase_FK`;

ALTER TABLE `Database`.`Message` DROP FOREIGN KEY `Message_Constraint_FK`;

ALTER TABLE `Database`.`Xref` DROP FOREIGN KEY `Xref_UtilityClass_FK`;

ALTER TABLE `Database`.`CellularLocationVocabulary` DROP FOREIGN KEY `CellularLocationVocabulary_ControlledVocabulary_FK`;

ALTER TABLE `Database`.`ControlledVocabulary` DROP FOREIGN KEY `ControlledVocabulary_UtilityClass_FK`;

ALTER TABLE `Database`.`Constraint` DROP FOREIGN KEY `Constraint_Pathway_FK`;

ALTER TABLE `Database`.`Degradation` DROP FOREIGN KEY `Degradation_Conversion_FK`;

ALTER TABLE `Database`.`EntityReference` DROP FOREIGN KEY `EntityReference_DnaRegion_FK`;

ALTER TABLE `Database`.`LocalParameter` DROP FOREIGN KEY `LocalParameter_SBase_FK`;

ALTER TABLE `Database`.`MolecularInteraction` DROP FOREIGN KEY `MolecularInteraction_Interaction_FK`;

ALTER TABLE `Database`.`Rule` DROP FOREIGN KEY `Rule_Pathway_FK`;

ALTER TABLE `Database`.`RelationshipTypeVocabulary` DROP FOREIGN KEY `RelationshipTypeVocabulary_RelationshipXref_FK`;

ALTER TABLE `Database`.`Math` DROP FOREIGN KEY `Math_EventAssignment_FK`;

ALTER TABLE `Database`.`BioSource` DROP FOREIGN KEY `BioSource_RnaReference_FK`;

ALTER TABLE `Database`.`Stoichiometry` DROP FOREIGN KEY `Stoichiometry_Complex_FK`;

ALTER TABLE `Database`.`TransportWithBiochemicalReaction` DROP FOREIGN KEY `TransportWithBiochemicalReaction_Transport_FK`;

ALTER TABLE `Database`.`Rna` DROP FOREIGN KEY `Rna_PhysicalEntity_FK`;

ALTER TABLE `Database`.`InitialAssignment` DROP FOREIGN KEY `InitialAssignment_SBase_FK`;

ALTER TABLE `Database`.`KPrime` DROP FOREIGN KEY `KPrime_BiochemicalReaction_FK`;

ALTER TABLE `Database`.`StringCollection` DROP FOREIGN KEY `StringCollection_UtilityClass_FK`;

ALTER TABLE `Database`.`ImportSource` DROP FOREIGN KEY `ImportSource_Entity_FK1`;

ALTER TABLE `Database`.`SequenceLocation` DROP FOREIGN KEY `SequenceLocation_EntityFeature_FK`;

ALTER TABLE `Database`.`Control` DROP FOREIGN KEY `Control_Interaction_FK`;

ALTER TABLE `Database`.`Conversion` DROP FOREIGN KEY `Conversion_BiochemicalPathwayStep_FK`;

ALTER TABLE `Database`.`SequenceRegionVocabulary` DROP FOREIGN KEY `SequenceRegionVocabulary_RnaRegionReference_FK`;

ALTER TABLE `Database`.`EntityFeature` DROP FOREIGN KEY `EntityFeature_EntityReference_FK`;

ALTER TABLE `Database`.`SmallMolecule` DROP PRIMARY KEY;

ALTER TABLE `Database`.`AlgebraicRule` DROP PRIMARY KEY;

ALTER TABLE `Database`.`FunctionDefinition` DROP PRIMARY KEY;

ALTER TABLE `Database`.`UnificationXref` DROP PRIMARY KEY;

ALTER TABLE `Database`.`KineticLaw` DROP PRIMARY KEY;

ALTER TABLE `Database`.`UnitDefinition` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SequenceSite` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Delay` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RnaRegionReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Priority` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Entity_x_Control` DROP PRIMARY KEY;

ALTER TABLE `Database`.`EntityFeature` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ChemicalStructure` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Modulation` DROP PRIMARY KEY;

ALTER TABLE `Database`.`EntityReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Interaction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SequenceModificationVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`BiochemicalPathwayStep` DROP PRIMARY KEY;

ALTER TABLE `Database`.`CellularLocationVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`GeneticInteraction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SBase` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Protein` DROP PRIMARY KEY;

ALTER TABLE `Database`.`LocalParameter` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ComplexAssembly` DROP PRIMARY KEY;

ALTER TABLE `Database`.`PhysicalEntity` DROP PRIMARY KEY;

ALTER TABLE `Database`.`PathwayStep` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Stoichiometry` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Control` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ImportSource` DROP PRIMARY KEY;

ALTER TABLE `Database`.`StringCollection` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Pathway` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ModificationFeature` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Gene` DROP PRIMARY KEY;

ALTER TABLE `Database`.`UPBase` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Conversion` DROP PRIMARY KEY;

ALTER TABLE `Database`.`TransportWithBiochemicalReaction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Transport` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Complex` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Xref` DROP PRIMARY KEY;

ALTER TABLE `Database`.`EvidenceCodeVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RateRule` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RnaRegion` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ExperimentalForm` DROP PRIMARY KEY;

ALTER TABLE `Database`.`InteractionVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`PhenotypeVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`BioSource` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ExperimentalFormVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RelationshipXref` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ProteinReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RnaReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Entity_x_PathwayStep` DROP PRIMARY KEY;

ALTER TABLE `Database`.`DeltaG` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Entity` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Provenance` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Catalysis` DROP PRIMARY KEY;

ALTER TABLE `Database`.`BindingFeature` DROP PRIMARY KEY;

ALTER TABLE `Database`.`DnaRegionReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SmallMoleculeReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`CellVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Rule` DROP PRIMARY KEY;

ALTER TABLE `Database`.`DnaRegion` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Score` DROP PRIMARY KEY;

ALTER TABLE `Database`.`UtilityClass` DROP PRIMARY KEY;

ALTER TABLE `Database`.`BiochemicalReaction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`InitialAssignment` DROP PRIMARY KEY;

ALTER TABLE `Database`.`AssignmentRule` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SequenceInterval` DROP PRIMARY KEY;

ALTER TABLE `Database`.`EventAssignment` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Evidence` DROP PRIMARY KEY;

ALTER TABLE `Database`.`ControlledVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`TemplateReactionRegulation` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SequenceRegionVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`FragmentFeature` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Thing` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Parameter` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Constraint` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Message` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Degradation` DROP PRIMARY KEY;

ALTER TABLE `Database`.`MolecularInteraction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`RelationshipTypeVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Rna` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Math` DROP PRIMARY KEY;

ALTER TABLE `Database`.`SequenceLocation` DROP PRIMARY KEY;

ALTER TABLE `Database`.`KPrime` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Event` DROP PRIMARY KEY;

ALTER TABLE `Database`.`PublicationXref` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Trigger` DROP PRIMARY KEY;

ALTER TABLE `Database`.`TissueVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`CovalentBindingFeature` DROP PRIMARY KEY;

ALTER TABLE `Database`.`EntityReferenceTypeVocabulary` DROP PRIMARY KEY;

ALTER TABLE `Database`.`TemplateReaction` DROP PRIMARY KEY;

ALTER TABLE `Database`.`DnaReference` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Unit` DROP PRIMARY KEY;

ALTER TABLE `Database`.`Dna` DROP PRIMARY KEY;

DROP TABLE `Database`.`Pathway`;

DROP TABLE `Database`.`PhenotypeVocabulary`;

DROP TABLE `Database`.`UnificationXref`;

DROP TABLE `Database`.`Rule`;

DROP TABLE `Database`.`RnaReference`;

DROP TABLE `Database`.`SmallMoleculeReference`;

DROP TABLE `Database`.`EntityReference`;

DROP TABLE `Database`.`SequenceRegionVocabulary`;

DROP TABLE `Database`.`Modulation`;

DROP TABLE `Database`.`DnaRegionReference`;

DROP TABLE `Database`.`BindingFeature`;

DROP TABLE `Database`.`TransportWithBiochemicalReaction`;

DROP TABLE `Database`.`GeneticInteraction`;

DROP TABLE `Database`.`SequenceLocation`;

DROP TABLE `Database`.`ExperimentalForm`;

DROP TABLE `Database`.`LocalParameter`;

DROP TABLE `Database`.`Protein`;

DROP TABLE `Database`.`EvidenceCodeVocabulary`;

DROP TABLE `Database`.`RateRule`;

DROP TABLE `Database`.`ImportSource`;

DROP TABLE `Database`.`Mapping`;

DROP TABLE `Database`.`ComplexAssembly`;

DROP TABLE `Database`.`EventAssignment`;

DROP TABLE `Database`.`InteractionVocabulary`;

DROP TABLE `Database`.`Trigger`;

DROP TABLE `Database`.`SequenceSite`;

DROP TABLE `Database`.`ExperimentalFormVocabulary`;

DROP TABLE `Database`.`ProteinReference`;

DROP TABLE `Database`.`Xref`;

DROP TABLE `Database`.`Entity`;

DROP TABLE `Database`.`PublicationXref`;

DROP TABLE `Database`.`ModificationFeature`;

DROP TABLE `Database`.`UPBase`;

DROP TABLE `Database`.`Catalysis`;

DROP TABLE `Database`.`DeltaG`;

DROP TABLE `Database`.`ControlledVocabulary`;

DROP TABLE `Database`.`Gene`;

DROP TABLE `Database`.`Complex`;

DROP TABLE `Database`.`Message`;

DROP TABLE `Database`.`Transport`;

DROP TABLE `Database`.`TemplateReaction`;

DROP TABLE `Database`.`AlgebraicRule`;

DROP TABLE `Database`.`CellVocabulary`;

DROP TABLE `Database`.`Parameter`;

DROP TABLE `Database`.`UnitDefinition`;

DROP TABLE `Database`.`RnaRegion`;

DROP TABLE `Database`.`Entity_x_Control`;

DROP TABLE `Database`.`UtilityClass`;

DROP TABLE `Database`.`RelationshipXref`;

DROP TABLE `Database`.`ChemicalStructure`;

DROP TABLE `Database`.`Constraint`;

DROP TABLE `Database`.`DnaReference`;

DROP TABLE `Database`.`BioSource`;

DROP TABLE `Database`.`DnaRegion`;

DROP TABLE `Database`.`RelationshipTypeVocabulary`;

DROP TABLE `Database`.`SBase`;

DROP TABLE `Database`.`Stoichiometry`;

DROP TABLE `Database`.`Conversion`;

DROP TABLE `Database`.`SequenceInterval`;

DROP TABLE `Database`.`StringCollection`;

DROP TABLE `Database`.`KPrime`;

DROP TABLE `Database`.`RnaRegionReference`;

DROP TABLE `Database`.`Thing`;

DROP TABLE `Database`.`Provenance`;

DROP TABLE `Database`.`Entity_x_ExperimentalForm`;

DROP TABLE `Database`.`TemplateReactionRegulation`;

DROP TABLE `Database`.`CovalentBindingFeature`;

DROP TABLE `Database`.`TissueVocabulary`;

DROP TABLE `Database`.`EntityReferenceTypeVocabulary`;

DROP TABLE `Database`.`FragmentFeature`;

DROP TABLE `Database`.`Evidence`;

DROP TABLE `Database`.`Experiment`;

DROP TABLE `Database`.`Control`;

DROP TABLE `Database`.`Degradation`;

DROP TABLE `Database`.`MolecularInteraction`;

DROP TABLE `Database`.`Rna`;

DROP TABLE `Database`.`InitialAssignment`;

DROP TABLE `Database`.`KineticLaw`;

DROP TABLE `Database`.`PhysicalEntity`;

DROP TABLE `Database`.`Delay`;

DROP TABLE `Database`.`Priority`;

DROP TABLE `Database`.`PathwayStep`;

DROP TABLE `Database`.`AssignmentRule`;

DROP TABLE `Database`.`Event`;

DROP TABLE `Database`.`Sample`;

DROP TABLE `Database`.`SequenceModificationVocabulary`;

DROP TABLE `Database`.`CellularLocationVocabulary`;

DROP TABLE `Database`.`BiochemicalPathwayStep`;

DROP TABLE `Database`.`BiochemicalReaction`;

DROP TABLE `Database`.`Interaction`;

DROP TABLE `Database`.`Score`;

DROP TABLE `Database`.`Dna`;

DROP TABLE `Database`.`Unit`;

DROP TABLE `Database`.`EntityFeature`;

DROP TABLE `Database`.`Math`;

DROP TABLE `Database`.`FunctionDefinition`;

DROP TABLE `Database`.`SmallMolecule`;

DROP TABLE `Database`.`Entity_x_PathwayStep`;

CREATE TABLE `Database`.`Pathway` (
	`unipaxId` INT NOT NULL,
	`componentUnipaxId` INT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`PhenotypeVocabulary` (
	`unipaxId` INT NOT NULL,
	`patoData` VARCHAR(4000),
	`geneticInteractionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`UnificationXref` (
	`utilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`Rule` (
	`unipaxId` INT NOT NULL,
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RnaReference` (
	`unipaxId` INT NOT NULL,
	`sequence` TEXT,
	`subRegionUnipaxId` INT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SmallMoleculeReference` (
	`unipaxId` INT NOT NULL,
	`chemicalFormula` VARCHAR(4000),
	`molecularWeight` DOUBLE,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`EntityReference` (
	`unipaxId` INT NOT NULL,
	`standardName` VARCHAR(4000),
	`displayName` VARCHAR(4000),
	`dnaUnipaxId` INT NOT NULL,
	`dnaRegionUnipaxId` INT NOT NULL,
	`proteinUnipaxId` INT NOT NULL,
	`rnaUnipaxId` INT NOT NULL,
	`rnaRegionUnipaxId` INT NOT NULL,
	`smallMoleculeUnipaxId` INT NOT NULL,
	`unipaxId1` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SequenceRegionVocabulary` (
	`unipaxId` INT NOT NULL,
	`entityFeatureUnipaxId` INT NOT NULL,
	`dnaRegionReferenceUnipaxId` INT NOT NULL,
	`rnaRegionReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Modulation` (
	`interactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`interactionUnipaxId`)
);

CREATE TABLE `Database`.`DnaRegionReference` (
	`unipaxId` INT NOT NULL,
	`sequence` TEXT,
	`subRegionUnipaxId` INT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`BindingFeature` (
	`unipaxId` INT NOT NULL,
	`intraMolecular` TINYINT,
	`unipaxId1` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`TransportWithBiochemicalReaction` (
	`transportUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`transportUnipaxId`,`unipaxId`)
);

CREATE TABLE `Database`.`GeneticInteraction` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SequenceLocation` (
	`unipaxId` INT NOT NULL,
	`entityFeatureUnipaxId` INT NOT NULL,
	`dnaRegionReferenceUnipaxId` INT NOT NULL,
	`rnaRegionReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`ExperimentalForm` (
	`unipaxId` INT NOT NULL,
	`utilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`LocalParameter` (
	`unipaxId` INT NOT NULL,
	`id` VARCHAR(4000),
	`name` VARCHAR(4000),
	`value` DOUBLE,
	`unit` VARCHAR(4000),
	`kineticLawUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Protein` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`EvidenceCodeVocabulary` (
	`unipaxId` INT NOT NULL,
	`utilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RateRule` (
	`unipaxId` INT NOT NULL,
	`variable` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`ImportSource` (
	`utilityClassUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	`entityUnipaxId` INT NOT NULL,
	`entity1UnipaxId` INT NOT NULL,
	`utilityClassUnipaxId1` INT NOT NULL,
	`utilityClassUnipaxId2` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`Mapping` (
	`idType` VARCHAR(4000),
	`mapping` BLOB
);

CREATE TABLE `Database`.`ComplexAssembly` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`EventAssignment` (
	`eventUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	`variable` VARCHAR(4000),
	PRIMARY KEY (`eventUnipaxId`,`unipaxId`)
);

CREATE TABLE `Database`.`InteractionVocabulary` (
	`controlledVocabularyUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`controlledVocabularyUnipaxId`)
);

CREATE TABLE `Database`.`Trigger` (
	`unipaxId` INT NOT NULL,
	`initialValue` DOUBLE,
	`persistent` TINYINT,
	`eventUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SequenceSite` (
	`unipaxId` INT NOT NULL,
	`positionStatus` VARCHAR(4000),
	`sequencePosition` INT,
	`sequenceIntervalUnipaxId` INT NOT NULL,
	`sequenceInterval1UnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`ExperimentalFormVocabulary` (
	`unipaxId` INT NOT NULL,
	`experimentalFormUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`ProteinReference` (
	`unipaxId` INT NOT NULL,
	`sequence` TEXT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Xref` (
	`utilityClassUnipaxId` INT NOT NULL,
	`idVersion` VARCHAR(4000),
	`id` VARCHAR(4000),
	`dbVersion` VARCHAR(4000),
	`db` VARCHAR(4000),
	`unipaxId` INT NOT NULL,
	`bioSourceUnipaxId` INT NOT NULL,
	`controlledVocabularyUnipaxId` INT NOT NULL,
	`evidenceUtilityClassUnipaxId` INT NOT NULL,
	`provenanceUtilityClassUnipaxId` INT NOT NULL,
	`entityReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`Entity` (
	`unipaxId` INT NOT NULL,
	`availability` VARCHAR(4000),
	`comment` VARCHAR(4000),
	`displayName` VARCHAR(4000),
	`standardName` VARCHAR(4000),
	`interactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`PublicationXref` (
	`utilityClassUnipaxId` INT NOT NULL,
	`title` VARCHAR(4000),
	`year` INT,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`ModificationFeature` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`UPBase` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Catalysis` (
	`interactionUnipaxId` INT NOT NULL,
	`catalysisDirection` VARCHAR(4000),
	PRIMARY KEY (`interactionUnipaxId`)
);

CREATE TABLE `Database`.`DeltaG` (
	`unipaxId` INT NOT NULL,
	`deltaGPrime0` DOUBLE,
	`ionicStrength` DOUBLE,
	`ph` DOUBLE,
	`pMg` DOUBLE,
	`temperature` DOUBLE,
	`biochemicalReactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`ControlledVocabulary` (
	`unipaxId` INT NOT NULL,
	`term` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Gene` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Complex` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Message` (
	`unipaxId` INT NOT NULL,
	`message` VARCHAR(4000),
	`constraintUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Transport` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`TemplateReaction` (
	`unipaxId` INT NOT NULL,
	`templateDirection` VARCHAR(4000),
	`templateUnipaxId` INT,
	`productUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`AlgebraicRule` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`CellVocabulary` (
	`controlledVocabularyUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`controlledVocabularyUnipaxId`)
);

CREATE TABLE `Database`.`Parameter` (
	`unipaxId` INT NOT NULL,
	`constant` TINYINT,
	`id` VARCHAR(4000),
	`name` VARCHAR(4000),
	`value` DOUBLE,
	`units` VARCHAR(4000),
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`UnitDefinition` (
	`unipaxId` INT NOT NULL,
	`id` VARCHAR(4000),
	`name` VARCHAR(4000),
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RnaRegion` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Entity_x_Control` (
	`unipaxId` INT NOT NULL,
	`interactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`,`interactionUnipaxId`)
);

CREATE TABLE `Database`.`UtilityClass` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RelationshipXref` (
	`utilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`ChemicalStructure` (
	`unipaxId` INT NOT NULL,
	`structureData` VARCHAR(4000),
	`structureFormat` VARCHAR(4000),
	`smallMoleculeReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Constraint` (
	`unipaxId` INT NOT NULL,
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`DnaReference` (
	`unipaxId` INT NOT NULL,
	`sequence` TEXT,
	`subRegionUnipaxId` INT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`BioSource` (
	`unipaxId` INT NOT NULL,
	`standardName` VARCHAR(4000),
	`displayName` VARCHAR(4000),
	`geneUnipaxId` INT NOT NULL,
	`pathwayUnipaxId` INT NOT NULL,
	`dnaReferenceUnipaxId` INT NOT NULL,
	`dnaRegionReferenceUnipaxId` INT NOT NULL,
	`proteinReferenceUnipaxId` INT NOT NULL,
	`rnaReferenceUnipaxId` INT NOT NULL,
	`rnaRegionReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`DnaRegion` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RelationshipTypeVocabulary` (
	`unipaxId` INT NOT NULL,
	`utilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SBase` (
	`unipaxId` INT NOT NULL,
	`metaId` VARCHAR(4000),
	`sboTerm` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Stoichiometry` (
	`unipaxId` INT NOT NULL,
	`stoichiometricCoefficient` INT,
	`conversionUnipaxId` INT NOT NULL,
	`complexUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Conversion` (
	`unipaxId` INT NOT NULL,
	`conversionDirection` VARCHAR(4000),
	`spontaneous` VARCHAR(4000),
	`biochemicalPathwayStepUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SequenceInterval` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`StringCollection` (
	`unipaxId` INT NOT NULL,
	`entry` VARCHAR(4000),
	`utilityClassUnipaxId` INT NOT NULL,
	`bioSourceUnipaxId` INT NOT NULL,
	`provenanceUtilityClassUnipaxId` INT NOT NULL,
	`entityReferenceUnipaxId` INT NOT NULL,
	`publicationXrefUtilityClassUnipaxId` INT NOT NULL,
	`publicationXref1UtilityClassUnipaxId` INT NOT NULL,
	`publicationXref2UtilityClassUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`KPrime` (
	`unipaxId` INT NOT NULL,
	`ionicStrength` DOUBLE,
	`kPrime` DOUBLE,
	`ph` DOUBLE,
	`pMg` DOUBLE,
	`temperature` DOUBLE,
	`biochemicalReactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`RnaRegionReference` (
	`unipaxId` INT NOT NULL,
	`sequence` TEXT,
	`subRegionUnipaxId` INT,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Thing` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Provenance` (
	`utilityClassUnipaxId` INT NOT NULL,
	`displayName` VARCHAR(4000),
	`standardName` VARCHAR(4000),
	`unipaxId` INT NOT NULL,
	`scoreUnipaxId` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`Entity_x_ExperimentalForm` (
	`unipaxId` INT NOT NULL,
	`unipaxId1` INT NOT NULL,
	PRIMARY KEY (`unipaxId`,`unipaxId1`)
);

CREATE TABLE `Database`.`TemplateReactionRegulation` (
	`interactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`interactionUnipaxId`)
);

CREATE TABLE `Database`.`CovalentBindingFeature` (
	`modificationFeatureUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`modificationFeatureUnipaxId`,`unipaxId`)
);

CREATE TABLE `Database`.`TissueVocabulary` (
	`controlledVocabularyUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`controlledVocabularyUnipaxId`)
);

CREATE TABLE `Database`.`EntityReferenceTypeVocabulary` (
	`unipaxId` INT NOT NULL,
	`entityReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`FragmentFeature` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Evidence` (
	`utilityClassUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	`entityFeatureUnipaxId` INT NOT NULL,
	`pathwayStepUnipaxId` INT NOT NULL,
	`entityReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`utilityClassUnipaxId`)
);

CREATE TABLE `Database`.`Experiment` (
	`experimentId` INT,
	`name` VARCHAR(4000),
	`shortDescription` VARCHAR(4000),
	`source` VARCHAR(4000),
	`user` VARCHAR(4000),
	`metaInfos` TEXT,
	`valuesPerSample` INT,
	`defaultMapping` BLOB
);

CREATE TABLE `Database`.`Control` (
	`interactionUnipaxId` INT NOT NULL,
	`controlType` VARCHAR(4000),
	`unipaxId` INT,
	PRIMARY KEY (`interactionUnipaxId`)
);

CREATE TABLE `Database`.`Degradation` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`MolecularInteraction` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Rna` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`InitialAssignment` (
	`unipaxId` INT NOT NULL,
	`symbol` VARCHAR(4000),
	`pathwayUnipaxId` INT NOT NULL,
	`eventUnipaxId` INT NOT NULL,
	`eventAssignmentUnipaxId` INT NOT NULL,
	`triggerUnipaxId` INT NOT NULL,
	`ruleUnipaxId` INT NOT NULL,
	`priorityUnipaxId` INT NOT NULL,
	`delayUnipaxId` INT NOT NULL,
	`mathUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`KineticLaw` (
	`unipaxId` INT NOT NULL,
	`conversionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`PhysicalEntity` (
	`unipaxId` INT NOT NULL,
	`unipaxId1` INT NOT NULL,
	`stoichiometryUnipaxId` INT NOT NULL,
	`conversionUnipaxId` INT NOT NULL,
	`conversion1UnipaxId` INT NOT NULL,
	`complexUnipaxId` INT NOT NULL,
	`interactionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Delay` (
	`unipaxId` INT NOT NULL,
	`eventUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Priority` (
	`unipaxId` INT NOT NULL,
	`eventUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`PathwayStep` (
	`unipaxId` INT NOT NULL,
	`unipaxId1` INT NOT NULL,
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`AssignmentRule` (
	`unipaxId` INT NOT NULL,
	`variable` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Event` (
	`unipaxId` INT NOT NULL,
	`useValuesFromTriggerTime` TINYINT,
	`id` VARCHAR(4000),
	`name` VARCHAR(4000),
	`pathwayUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Sample` (
	`indexInExperiment` INT,
	`name` VARCHAR(4000),
	`description` VARCHAR(4000),
	`user` VARCHAR(4000),
	`metaInfos` TEXT,
	`dataType` VARCHAR(4000),
	`data` BLOB
);

CREATE TABLE `Database`.`SequenceModificationVocabulary` (
	`unipaxId` INT NOT NULL,
	`modificationFeatureUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`CellularLocationVocabulary` (
	`controlledVocabularyUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`controlledVocabularyUnipaxId`)
);

CREATE TABLE `Database`.`BiochemicalPathwayStep` (
	`unipaxId` INT NOT NULL,
	`stepDirection` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`BiochemicalReaction` (
	`unipaxId` INT NOT NULL,
	`deltaH` DOUBLE,
	`deltaS` DOUBLE,
	`eCNumber` VARCHAR(4000),
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Interaction` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Score` (
	`unipaxId` INT NOT NULL,
	`value` VARCHAR(4000),
	`utilityClassUnipaxId` INT NOT NULL,
	`geneticInteractionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Dna` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Unit` (
	`unipaxId` INT NOT NULL,
	`exponent` INT,
	`kind` VARCHAR(4000),
	`multiplier` DOUBLE,
	`scale` DOUBLE,
	`unitDefinitionUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`EntityFeature` (
	`unipaxId` INT NOT NULL,
	`physicalEntityUnipaxId` INT NOT NULL,
	`physicalEntity1UnipaxId` INT NOT NULL,
	`unipaxId1` INT NOT NULL,
	`experimentalFormUnipaxId` INT NOT NULL,
	`entityReferenceUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Math` (
	`eventUnipaxId` INT NOT NULL,
	`eventAssignmentUnipaxId` INT NOT NULL,
	`triggerUnipaxId` INT NOT NULL,
	`ruleUnipaxId` INT NOT NULL,
	`priorityUnipaxId` INT NOT NULL,
	`delayUnipaxId` INT NOT NULL,
	`unipaxId` INT NOT NULL,
	`mathML` BLOB,
	`constraintUnipaxId` INT NOT NULL,
	PRIMARY KEY (`eventUnipaxId`,`eventAssignmentUnipaxId`,`triggerUnipaxId`,`ruleUnipaxId`,`priorityUnipaxId`,`delayUnipaxId`,`unipaxId`)
);

CREATE TABLE `Database`.`FunctionDefinition` (
	`unipaxId` INT NOT NULL,
	`id` VARCHAR(4000),
	`name` VARCHAR(4000),
	`pathwayUnipaxId` INT NOT NULL,
	`eventUnipaxId` INT NOT NULL,
	`eventAssignmentUnipaxId` INT NOT NULL,
	`triggerUnipaxId` INT NOT NULL,
	`ruleUnipaxId` INT NOT NULL,
	`priorityUnipaxId` INT NOT NULL,
	`delayUnipaxId` INT NOT NULL,
	`mathUnipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`SmallMolecule` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

CREATE TABLE `Database`.`Entity_x_PathwayStep` (
	`unipaxId` INT NOT NULL,
	PRIMARY KEY (`unipaxId`)
);

ALTER TABLE `Database`.`SmallMolecule` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`AlgebraicRule` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`FunctionDefinition` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`KineticLaw` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`UnitDefinition` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`SequenceSite` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Delay` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`RnaRegionReference` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Priority` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_Control` ADD PRIMARY KEY (`unipaxId`, `interactionUnipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`ChemicalStructure` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Interaction` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`SequenceModificationVocabulary` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`BiochemicalPathwayStep` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`CellularLocationVocabulary` ADD PRIMARY KEY (`controlledVocabularyUnipaxId`);

ALTER TABLE `Database`.`SBase` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`PathwayStep` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Stoichiometry` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Control` ADD PRIMARY KEY (`interactionUnipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Conversion` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` ADD PRIMARY KEY (`unipaxId`, `unipaxId1`);

ALTER TABLE `Database`.`BioSource` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_PathwayStep` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Provenance` ADD PRIMARY KEY (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Score` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`BiochemicalReaction` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`InitialAssignment` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`AssignmentRule` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD PRIMARY KEY (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Math` ADD PRIMARY KEY (`eventUnipaxId`, `eventAssignmentUnipaxId`, `triggerUnipaxId`, `ruleUnipaxId`, `priorityUnipaxId`, `delayUnipaxId`, `unipaxId`);

ALTER TABLE `Database`.`Event` ADD PRIMARY KEY (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Stoichiometry_FK` FOREIGN KEY (`stoichiometryUnipaxId`)
	REFERENCES `Database`.`Stoichiometry` (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD CONSTRAINT `Evidence_EntityReference_FK` FOREIGN KEY (`entityReferenceUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD CONSTRAINT `Evidence_PathwayStep_FK` FOREIGN KEY (`pathwayStepUnipaxId`)
	REFERENCES `Database`.`PathwayStep` (`unipaxId`);

ALTER TABLE `Database`.`Trigger` ADD CONSTRAINT `Trigger_Event_FK` FOREIGN KEY (`eventUnipaxId`)
	REFERENCES `Database`.`Event` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_ExperimentalForm_FK` FOREIGN KEY (`experimentalFormUnipaxId`)
	REFERENCES `Database`.`ExperimentalForm` (`unipaxId`);

ALTER TABLE `Database`.`PublicationXref` ADD CONSTRAINT `PublicationXref_Xref_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Xref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Event` ADD CONSTRAINT `Event_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_PathwayStep` ADD CONSTRAINT `Entity_x_PathwayStep_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`ExperimentalForm` ADD CONSTRAINT `ExperimentalForm_Evidence_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Evidence` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_Rna_FK` FOREIGN KEY (`rnaUnipaxId`)
	REFERENCES `Database`.`Rna` (`unipaxId`);

ALTER TABLE `Database`.`PathwayStep` ADD CONSTRAINT `PathwayStep_PathwayStep_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`PathwayStep` (`unipaxId`);

ALTER TABLE `Database`.`ExperimentalFormVocabulary` ADD CONSTRAINT `ExperimentalFormVocabulary_ExperimentalForm_FK` FOREIGN KEY (`experimentalFormUnipaxId`)
	REFERENCES `Database`.`ExperimentalForm` (`unipaxId`);

ALTER TABLE `Database`.`TissueVocabulary` ADD CONSTRAINT `TissueVocabulary_BioSource_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`BioSource` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`CovalentBindingFeature` ADD CONSTRAINT `CovalentBindingFeature_BindingFeature_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`BindingFeature` (`unipaxId`);

ALTER TABLE `Database`.`EntityReferenceTypeVocabulary` ADD CONSTRAINT `EntityReferenceTypeVocabulary_EntityReference_FK` FOREIGN KEY (`entityReferenceUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_Provenance_FK` FOREIGN KEY (`provenanceUtilityClassUnipaxId`)
	REFERENCES `Database`.`Provenance` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Pathway` ADD CONSTRAINT `Pathway_Entity_FK1` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`TemplateReaction` ADD CONSTRAINT `TemplateReaction_PhysicalEntity_FK` FOREIGN KEY (`templateUnipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_ImportSource_FK` FOREIGN KEY (`utilityClassUnipaxId1`)
	REFERENCES `Database`.`ImportSource` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_BioSource_FK` FOREIGN KEY (`bioSourceUnipaxId`)
	REFERENCES `Database`.`BioSource` (`unipaxId`);

ALTER TABLE `Database`.`EvidenceCodeVocabulary` ADD CONSTRAINT `EvidenceCodeVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`DnaReference` ADD CONSTRAINT `DnaReference_EntityReference_FK` FOREIGN KEY (`subRegionUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`SequenceLocation` ADD CONSTRAINT `SequenceLocation_RnaRegionReference_FK` FOREIGN KEY (`rnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`RnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`Unit` ADD CONSTRAINT `Unit_UnitDefinition_FK` FOREIGN KEY (`unitDefinitionUnipaxId`)
	REFERENCES `Database`.`UnitDefinition` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Conversion_FK1` FOREIGN KEY (`conversion1UnipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`Dna` ADD CONSTRAINT `Dna_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`InteractionVocabulary` ADD CONSTRAINT `InteractionVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`controlledVocabularyUnipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_Constraint_FK` FOREIGN KEY (`constraintUnipaxId`)
	REFERENCES `Database`.`Constraint` (`unipaxId`);

ALTER TABLE `Database`.`PhenotypeVocabulary` ADD CONSTRAINT `PhenotypeVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_SmallMolecule_FK` FOREIGN KEY (`smallMoleculeUnipaxId`)
	REFERENCES `Database`.`SmallMolecule` (`unipaxId`);

ALTER TABLE `Database`.`SmallMolecule` ADD CONSTRAINT `SmallMolecule_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`UnificationXref` ADD CONSTRAINT `UnificationXref_Xref_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Xref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`FunctionDefinition` ADD CONSTRAINT `FunctionDefinition_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`KineticLaw` ADD CONSTRAINT `KineticLaw_Conversion_FK` FOREIGN KEY (`conversionUnipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`RnaReference` ADD CONSTRAINT `RnaReference_EntityReference_FK1` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`SequenceSite` ADD CONSTRAINT `SequenceSite_SequenceInterval_FK` FOREIGN KEY (`sequenceIntervalUnipaxId`)
	REFERENCES `Database`.`SequenceInterval` (`unipaxId`);

ALTER TABLE `Database`.`UnitDefinition` ADD CONSTRAINT `UnitDefinition_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`DeltaG` ADD CONSTRAINT `DeltaG_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_Evidence_FK` FOREIGN KEY (`evidenceUtilityClassUnipaxId`)
	REFERENCES `Database`.`Evidence` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`TemplateReaction` ADD CONSTRAINT `TemplateReaction_Interaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_PublicationXref_FK` FOREIGN KEY (`publicationXrefUtilityClassUnipaxId`)
	REFERENCES `Database`.`PublicationXref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_UtilityClass_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`Delay` ADD CONSTRAINT `Delay_Event_FK` FOREIGN KEY (`eventUnipaxId`)
	REFERENCES `Database`.`Event` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Catalysis_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Catalysis` (`interactionUnipaxId`);

ALTER TABLE `Database`.`Priority` ADD CONSTRAINT `Priority_Event_FK` FOREIGN KEY (`eventUnipaxId`)
	REFERENCES `Database`.`Event` (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_Control` ADD CONSTRAINT `Entity_x_Control_Control_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Control` (`interactionUnipaxId`);

ALTER TABLE `Database`.`Modulation` ADD CONSTRAINT `Modulation_Control_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Control` (`interactionUnipaxId`);

ALTER TABLE `Database`.`Provenance` ADD CONSTRAINT `Provenance_Score_FK` FOREIGN KEY (`scoreUnipaxId`)
	REFERENCES `Database`.`Score` (`unipaxId`);

ALTER TABLE `Database`.`RnaRegionReference` ADD CONSTRAINT `RnaRegionReference_EntityReference_FK` FOREIGN KEY (`subRegionUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`ChemicalStructure` ADD CONSTRAINT `ChemicalStructure_SmallMoleculeReference_FK` FOREIGN KEY (`smallMoleculeReferenceUnipaxId`)
	REFERENCES `Database`.`SmallMoleculeReference` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_Priority_FK` FOREIGN KEY (`priorityUnipaxId`)
	REFERENCES `Database`.`Priority` (`unipaxId`);

ALTER TABLE `Database`.`BindingFeature` ADD CONSTRAINT `BindingFeature_EntityFeature_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`SequenceModificationVocabulary` ADD CONSTRAINT `SequenceModificationVocabulary_ModificationFeature_FK` FOREIGN KEY (`modificationFeatureUnipaxId`)
	REFERENCES `Database`.`ModificationFeature` (`unipaxId`);

ALTER TABLE `Database`.`CellVocabulary` ADD CONSTRAINT `CellVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`controlledVocabularyUnipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`DnaRegionReference` ADD CONSTRAINT `DnaRegionReference_EntityReference_FK1` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_EntityFeature_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_DnaRegionReference_FK` FOREIGN KEY (`dnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`DnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_PhysicalEntity_FK` FOREIGN KEY (`physicalEntityUnipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`Score` ADD CONSTRAINT `Score_GeneticInteraction_FK` FOREIGN KEY (`geneticInteractionUnipaxId`)
	REFERENCES `Database`.`GeneticInteraction` (`unipaxId`);

ALTER TABLE `Database`.`PathwayStep` ADD CONSTRAINT `PathwayStep_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`Entity` ADD CONSTRAINT `Entity_Thing_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Thing` (`unipaxId`);

ALTER TABLE `Database`.`CellularLocationVocabulary` ADD CONSTRAINT `CellularLocationVocabulary_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`SequenceSite` ADD CONSTRAINT `SequenceSite_SequenceLocation_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SequenceLocation` (`unipaxId`);

ALTER TABLE `Database`.`Interaction` ADD CONSTRAINT `Interaction_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_EntityReference_FK` FOREIGN KEY (`entityReferenceUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`BiochemicalPathwayStep` ADD CONSTRAINT `BiochemicalPathwayStep_PathwayStep_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PathwayStep` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_PublicationXref_FK2` FOREIGN KEY (`publicationXref2UtilityClassUnipaxId`)
	REFERENCES `Database`.`PublicationXref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`LocalParameter` ADD CONSTRAINT `LocalParameter_KineticLaw_FK` FOREIGN KEY (`kineticLawUnipaxId`)
	REFERENCES `Database`.`KineticLaw` (`unipaxId`);

ALTER TABLE `Database`.`ComplexAssembly` ADD CONSTRAINT `ComplexAssembly_Conversion_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_Dna_FK` FOREIGN KEY (`dnaUnipaxId`)
	REFERENCES `Database`.`Dna` (`unipaxId`);

ALTER TABLE `Database`.`Protein` ADD CONSTRAINT `Protein_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`GeneticInteraction` ADD CONSTRAINT `GeneticInteraction_Interaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_Trigger_FK` FOREIGN KEY (`triggerUnipaxId`)
	REFERENCES `Database`.`Trigger` (`unipaxId`);

ALTER TABLE `Database`.`InitialAssignment` ADD CONSTRAINT `InitialAssignment_Math_FK` FOREIGN KEY (`eventUnipaxId`, `eventAssignmentUnipaxId`, `triggerUnipaxId`, `ruleUnipaxId`, `priorityUnipaxId`, `delayUnipaxId`, `mathUnipaxId`)
	REFERENCES `Database`.`Math` (`eventUnipaxId`, `eventAssignmentUnipaxId`, `triggerUnipaxId`, `ruleUnipaxId`, `priorityUnipaxId`, `delayUnipaxId`, `unipaxId`);

ALTER TABLE `Database`.`FunctionDefinition` ADD CONSTRAINT `FunctionDefinition_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`EventAssignment` ADD CONSTRAINT `EventAssignment_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`Stoichiometry` ADD CONSTRAINT `Stoichiometry_Conversion_FK` FOREIGN KEY (`conversionUnipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Control` ADD CONSTRAINT `Control_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`SequenceRegionVocabulary` ADD CONSTRAINT `SequenceRegionVocabulary_DnaRegionReference_FK` FOREIGN KEY (`dnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`DnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`AlgebraicRule` ADD CONSTRAINT `AlgebraicRule_Rule_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Rule` (`unipaxId`);

ALTER TABLE `Database`.`SBase` ADD CONSTRAINT `SBase_UPBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UPBase` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_EntityFeature_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`Parameter` ADD CONSTRAINT `Parameter_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_PhysicalEntity_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD CONSTRAINT `Evidence_EntityFeature_FK` FOREIGN KEY (`entityFeatureUnipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`Message` ADD CONSTRAINT `Message_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`Constraint` ADD CONSTRAINT `Constraint_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_Protein_FK` FOREIGN KEY (`proteinUnipaxId`)
	REFERENCES `Database`.`Protein` (`unipaxId`);

ALTER TABLE `Database`.`Rule` ADD CONSTRAINT `Rule_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`Gene` ADD CONSTRAINT `Gene_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_UPBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UPBase` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_RnaRegionReference_FK` FOREIGN KEY (`rnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`RnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`RelationshipTypeVocabulary` ADD CONSTRAINT `RelationshipTypeVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`CovalentBindingFeature` ADD CONSTRAINT `CovalentBindingFeature_ModificationFeature_FK` FOREIGN KEY (`modificationFeatureUnipaxId`)
	REFERENCES `Database`.`ModificationFeature` (`unipaxId`);

ALTER TABLE `Database`.`ModificationFeature` ADD CONSTRAINT `ModificationFeature_EntityFeature_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`Transport` ADD CONSTRAINT `Transport_Conversion_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`Stoichiometry` ADD CONSTRAINT `Stoichiometry_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`TransportWithBiochemicalReaction` ADD CONSTRAINT `TransportWithBiochemicalReaction_BiochemicalReaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`BiochemicalReaction` (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` ADD CONSTRAINT `Entity_x_ExperimentalForm_ExperimentalForm_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`ExperimentalForm` (`unipaxId`);

ALTER TABLE `Database`.`KPrime` ADD CONSTRAINT `KPrime_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_BioSource_FK` FOREIGN KEY (`bioSourceUnipaxId`)
	REFERENCES `Database`.`BioSource` (`unipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_Entity_FK2` FOREIGN KEY (`entity1UnipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Pathway` ADD CONSTRAINT `Pathway_Entity_FK` FOREIGN KEY (`componentUnipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Complex` ADD CONSTRAINT `Complex_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`RateRule` ADD CONSTRAINT `RateRule_Rule_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Rule` (`unipaxId`);

ALTER TABLE `Database`.`EvidenceCodeVocabulary` ADD CONSTRAINT `EvidenceCodeVocabulary_Evidence_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Evidence` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`SequenceLocation` ADD CONSTRAINT `SequenceLocation_DnaRegionReference_FK` FOREIGN KEY (`dnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`DnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Conversion` ADD CONSTRAINT `Conversion_Interaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`Trigger` ADD CONSTRAINT `Trigger_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`SequenceRegionVocabulary` ADD CONSTRAINT `SequenceRegionVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD CONSTRAINT `Evidence_UtilityClass_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Conversion_FK` FOREIGN KEY (`conversionUnipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`RnaRegion` ADD CONSTRAINT `RnaRegion_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`Event` ADD CONSTRAINT `Event_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`InteractionVocabulary` ADD CONSTRAINT `InteractionVocabulary_Interaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`PhenotypeVocabulary` ADD CONSTRAINT `PhenotypeVocabulary_GeneticInteraction_FK` FOREIGN KEY (`geneticInteractionUnipaxId`)
	REFERENCES `Database`.`GeneticInteraction` (`unipaxId`);

ALTER TABLE `Database`.`ExperimentalForm` ADD CONSTRAINT `ExperimentalForm_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`ExperimentalFormVocabulary` ADD CONSTRAINT `ExperimentalFormVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_RnaRegion_FK` FOREIGN KEY (`rnaRegionUnipaxId`)
	REFERENCES `Database`.`RnaRegion` (`unipaxId`);

ALTER TABLE `Database`.`TissueVocabulary` ADD CONSTRAINT `TissueVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`controlledVocabularyUnipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_Control` ADD CONSTRAINT `Entity_x_Control_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`RelationshipXref` ADD CONSTRAINT `RelationshipXref_Xref_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Xref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`ProteinReference` ADD CONSTRAINT `ProteinReference_EntityReference_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_Gene_FK` FOREIGN KEY (`geneUnipaxId`)
	REFERENCES `Database`.`Gene` (`unipaxId`);

ALTER TABLE `Database`.`EntityReferenceTypeVocabulary` ADD CONSTRAINT `EntityReferenceTypeVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`RnaReference` ADD CONSTRAINT `RnaReference_EntityReference_FK` FOREIGN KEY (`subRegionUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`DeltaG` ADD CONSTRAINT `DeltaG_BiochemicalReaction_FK` FOREIGN KEY (`biochemicalReactionUnipaxId`)
	REFERENCES `Database`.`BiochemicalReaction` (`unipaxId`);

ALTER TABLE `Database`.`TemplateReaction` ADD CONSTRAINT `TemplateReaction_PhysicalEntity_FK1` FOREIGN KEY (`productUnipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_EntityReference_FK` FOREIGN KEY (`entityReferenceUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_ControlledVocabulary_FK` FOREIGN KEY (`controlledVocabularyUnipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_ImportSource_FK1` FOREIGN KEY (`utilityClassUnipaxId2`)
	REFERENCES `Database`.`ImportSource` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`DnaReference` ADD CONSTRAINT `DnaReference_EntityReference_FK1` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`SequenceLocation` ADD CONSTRAINT `SequenceLocation_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`Unit` ADD CONSTRAINT `Unit_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Complex_FK` FOREIGN KEY (`complexUnipaxId`)
	REFERENCES `Database`.`Complex` (`unipaxId`);

ALTER TABLE `Database`.`Catalysis` ADD CONSTRAINT `Catalysis_Control_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Control` (`interactionUnipaxId`);

ALTER TABLE `Database`.`Provenance` ADD CONSTRAINT `Provenance_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_Delay_FK` FOREIGN KEY (`delayUnipaxId`)
	REFERENCES `Database`.`Delay` (`unipaxId`);

ALTER TABLE `Database`.`BindingFeature` ADD CONSTRAINT `BindingFeature_BindingFeature_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`BindingFeature` (`unipaxId`);

ALTER TABLE `Database`.`CellVocabulary` ADD CONSTRAINT `CellVocabulary_BioSource_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`BioSource` (`unipaxId`);

ALTER TABLE `Database`.`SmallMoleculeReference` ADD CONSTRAINT `SmallMoleculeReference_EntityReference_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`DnaRegionReference` ADD CONSTRAINT `DnaRegionReference_EntityReference_FK` FOREIGN KEY (`subRegionUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_EntityReference_FK` FOREIGN KEY (`unipaxId1`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_DnaReference_FK` FOREIGN KEY (`dnaReferenceUnipaxId`)
	REFERENCES `Database`.`DnaReference` (`unipaxId`);

ALTER TABLE `Database`.`DnaRegion` ADD CONSTRAINT `DnaRegion_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`Score` ADD CONSTRAINT `Score_Evidence_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`Evidence` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`KineticLaw` ADD CONSTRAINT `KineticLaw_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`SequenceSite` ADD CONSTRAINT `SequenceSite_SequenceInterval_FK1` FOREIGN KEY (`sequenceInterval1UnipaxId`)
	REFERENCES `Database`.`SequenceInterval` (`unipaxId`);

ALTER TABLE `Database`.`Entity` ADD CONSTRAINT `Entity_Interaction_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`InitialAssignment` ADD CONSTRAINT `InitialAssignment_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`UnitDefinition` ADD CONSTRAINT `UnitDefinition_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`AssignmentRule` ADD CONSTRAINT `AssignmentRule_Rule_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Rule` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_Provenance_FK` FOREIGN KEY (`provenanceUtilityClassUnipaxId`)
	REFERENCES `Database`.`Provenance` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_PublicationXref_FK1` FOREIGN KEY (`publicationXref1UtilityClassUnipaxId`)
	REFERENCES `Database`.`PublicationXref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`FunctionDefinition` ADD CONSTRAINT `FunctionDefinition_Math_FK` FOREIGN KEY (`eventUnipaxId`, `eventAssignmentUnipaxId`, `triggerUnipaxId`, `ruleUnipaxId`, `priorityUnipaxId`, `delayUnipaxId`, `mathUnipaxId`)
	REFERENCES `Database`.`Math` (`eventUnipaxId`, `eventAssignmentUnipaxId`, `triggerUnipaxId`, `ruleUnipaxId`, `priorityUnipaxId`, `delayUnipaxId`, `unipaxId`);

ALTER TABLE `Database`.`BiochemicalReaction` ADD CONSTRAINT `BiochemicalReaction_Conversion_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`Delay` ADD CONSTRAINT `Delay_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`PhysicalEntity` ADD CONSTRAINT `PhysicalEntity_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Priority` ADD CONSTRAINT `Priority_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_Rule_FK` FOREIGN KEY (`ruleUnipaxId`)
	REFERENCES `Database`.`Rule` (`unipaxId`);

ALTER TABLE `Database`.`Provenance` ADD CONSTRAINT `Provenance_UtilityClass_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`RnaRegionReference` ADD CONSTRAINT `RnaRegionReference_EntityReference_FK1` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);

ALTER TABLE `Database`.`ChemicalStructure` ADD CONSTRAINT `ChemicalStructure_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`SequenceInterval` ADD CONSTRAINT `SequenceInterval_SequenceLocation_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SequenceLocation` (`unipaxId`);

ALTER TABLE `Database`.`EventAssignment` ADD CONSTRAINT `EventAssignment_Event_FK` FOREIGN KEY (`eventUnipaxId`)
	REFERENCES `Database`.`Event` (`unipaxId`);

ALTER TABLE `Database`.`TemplateReactionRegulation` ADD CONSTRAINT `TemplateReactionRegulation_Control_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Control` (`interactionUnipaxId`);

ALTER TABLE `Database`.`SequenceModificationVocabulary` ADD CONSTRAINT `SequenceModificationVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`UtilityClass` ADD CONSTRAINT `UtilityClass_Thing_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Thing` (`unipaxId`);

ALTER TABLE `Database`.`FragmentFeature` ADD CONSTRAINT `FragmentFeature_EntityFeature_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`SequenceRegionVocabulary` ADD CONSTRAINT `SequenceRegionVocabulary_EntityFeature_FK` FOREIGN KEY (`entityFeatureUnipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`Parameter` ADD CONSTRAINT `Parameter_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_PhysicalEntity_FK1` FOREIGN KEY (`physicalEntity1UnipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`Score` ADD CONSTRAINT `Score_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_ProteinReference_FK` FOREIGN KEY (`proteinReferenceUnipaxId`)
	REFERENCES `Database`.`ProteinReference` (`unipaxId`);

ALTER TABLE `Database`.`PathwayStep` ADD CONSTRAINT `PathwayStep_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`Evidence` ADD CONSTRAINT `Evidence_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Entity_x_ExperimentalForm` ADD CONSTRAINT `Entity_x_ExperimentalForm_Entity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`Thing` ADD CONSTRAINT `Thing_UPBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UPBase` (`unipaxId`);

ALTER TABLE `Database`.`Message` ADD CONSTRAINT `Message_Constraint_FK` FOREIGN KEY (`constraintUnipaxId`)
	REFERENCES `Database`.`Constraint` (`unipaxId`);

ALTER TABLE `Database`.`Xref` ADD CONSTRAINT `Xref_UtilityClass_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`CellularLocationVocabulary` ADD CONSTRAINT `CellularLocationVocabulary_ControlledVocabulary_FK` FOREIGN KEY (`controlledVocabularyUnipaxId`)
	REFERENCES `Database`.`ControlledVocabulary` (`unipaxId`);

ALTER TABLE `Database`.`ControlledVocabulary` ADD CONSTRAINT `ControlledVocabulary_UtilityClass_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`Constraint` ADD CONSTRAINT `Constraint_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`Degradation` ADD CONSTRAINT `Degradation_Conversion_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Conversion` (`unipaxId`);

ALTER TABLE `Database`.`EntityReference` ADD CONSTRAINT `EntityReference_DnaRegion_FK` FOREIGN KEY (`dnaRegionUnipaxId`)
	REFERENCES `Database`.`DnaRegion` (`unipaxId`);

ALTER TABLE `Database`.`LocalParameter` ADD CONSTRAINT `LocalParameter_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`MolecularInteraction` ADD CONSTRAINT `MolecularInteraction_Interaction_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`Rule` ADD CONSTRAINT `Rule_Pathway_FK` FOREIGN KEY (`pathwayUnipaxId`)
	REFERENCES `Database`.`Pathway` (`unipaxId`);

ALTER TABLE `Database`.`RelationshipTypeVocabulary` ADD CONSTRAINT `RelationshipTypeVocabulary_RelationshipXref_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`RelationshipXref` (`utilityClassUnipaxId`);

ALTER TABLE `Database`.`Math` ADD CONSTRAINT `Math_EventAssignment_FK` FOREIGN KEY (`eventUnipaxId`, `eventAssignmentUnipaxId`)
	REFERENCES `Database`.`EventAssignment` (`eventUnipaxId`, `unipaxId`);

ALTER TABLE `Database`.`BioSource` ADD CONSTRAINT `BioSource_RnaReference_FK` FOREIGN KEY (`rnaReferenceUnipaxId`)
	REFERENCES `Database`.`RnaReference` (`unipaxId`);

ALTER TABLE `Database`.`Stoichiometry` ADD CONSTRAINT `Stoichiometry_Complex_FK` FOREIGN KEY (`complexUnipaxId`)
	REFERENCES `Database`.`Complex` (`unipaxId`);

ALTER TABLE `Database`.`TransportWithBiochemicalReaction` ADD CONSTRAINT `TransportWithBiochemicalReaction_Transport_FK` FOREIGN KEY (`transportUnipaxId`)
	REFERENCES `Database`.`Transport` (`unipaxId`);

ALTER TABLE `Database`.`Rna` ADD CONSTRAINT `Rna_PhysicalEntity_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`PhysicalEntity` (`unipaxId`);

ALTER TABLE `Database`.`InitialAssignment` ADD CONSTRAINT `InitialAssignment_SBase_FK` FOREIGN KEY (`unipaxId`)
	REFERENCES `Database`.`SBase` (`unipaxId`);

ALTER TABLE `Database`.`KPrime` ADD CONSTRAINT `KPrime_BiochemicalReaction_FK` FOREIGN KEY (`biochemicalReactionUnipaxId`)
	REFERENCES `Database`.`BiochemicalReaction` (`unipaxId`);

ALTER TABLE `Database`.`StringCollection` ADD CONSTRAINT `StringCollection_UtilityClass_FK` FOREIGN KEY (`utilityClassUnipaxId`)
	REFERENCES `Database`.`UtilityClass` (`unipaxId`);

ALTER TABLE `Database`.`ImportSource` ADD CONSTRAINT `ImportSource_Entity_FK1` FOREIGN KEY (`entityUnipaxId`)
	REFERENCES `Database`.`Entity` (`unipaxId`);

ALTER TABLE `Database`.`SequenceLocation` ADD CONSTRAINT `SequenceLocation_EntityFeature_FK` FOREIGN KEY (`entityFeatureUnipaxId`)
	REFERENCES `Database`.`EntityFeature` (`unipaxId`);

ALTER TABLE `Database`.`Control` ADD CONSTRAINT `Control_Interaction_FK` FOREIGN KEY (`interactionUnipaxId`)
	REFERENCES `Database`.`Interaction` (`unipaxId`);

ALTER TABLE `Database`.`Conversion` ADD CONSTRAINT `Conversion_BiochemicalPathwayStep_FK` FOREIGN KEY (`biochemicalPathwayStepUnipaxId`)
	REFERENCES `Database`.`BiochemicalPathwayStep` (`unipaxId`);

ALTER TABLE `Database`.`SequenceRegionVocabulary` ADD CONSTRAINT `SequenceRegionVocabulary_RnaRegionReference_FK` FOREIGN KEY (`rnaRegionReferenceUnipaxId`)
	REFERENCES `Database`.`RnaRegionReference` (`unipaxId`);

ALTER TABLE `Database`.`EntityFeature` ADD CONSTRAINT `EntityFeature_EntityReference_FK` FOREIGN KEY (`entityReferenceUnipaxId`)
	REFERENCES `Database`.`EntityReference` (`unipaxId`);


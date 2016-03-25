--<ScriptOptions statementTerminator=";"/>

ALTER TABLE "UniPAX"."AlgebraicRule" DROP CONSTRAINT "AlgebraicRule_Rule_FK";

ALTER TABLE "UniPAX"."AsgRule" DROP CONSTRAINT "AsgRule_Rule_FK";

ALTER TABLE "UniPAX"."BindFtr" DROP CONSTRAINT "BindFtr_EntityFtr_FK";

ALTER TABLE "UniPAX"."BchemPwStep" DROP CONSTRAINT "BchemPwStep_PwStep_FK";

ALTER TABLE "UniPAX"."BchemReac" DROP CONSTRAINT "BchemReac_Conversion_FK";

ALTER TABLE "UniPAX"."BioSource" DROP CONSTRAINT "BioSource_UtilityClass_FK";

ALTER TABLE "UniPAX"."Catalysis" DROP CONSTRAINT "Catalysis_Control_FK";

ALTER TABLE "UniPAX"."CellLocVoc" DROP CONSTRAINT "CellLocVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."CellVoc" DROP CONSTRAINT "CellVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."ChemStruct" DROP CONSTRAINT "ChemStruct_UtilityClass_FK";

ALTER TABLE "UniPAX"."Complex" DROP CONSTRAINT "Complex_PhysEntity_FK";

ALTER TABLE "UniPAX"."ComplexAssembly" DROP CONSTRAINT "ComplexAssembly_Conversion_FK";

ALTER TABLE "UniPAX"."Constraint" DROP CONSTRAINT "Constraint_SBase_FK";

ALTER TABLE "UniPAX"."Control" DROP CONSTRAINT "Control_Intac_FK";

ALTER TABLE "UniPAX"."CtrdVoc" DROP CONSTRAINT "CtrdVoc_UtilityClass_FK";

ALTER TABLE "UniPAX"."Conversion" DROP CONSTRAINT "Conversion_Intac_FK";

ALTER TABLE "UniPAX"."CovalentBindFtr" DROP CONSTRAINT "CovalentBindFtr_BindFtr_FK";

ALTER TABLE "UniPAX"."CovalentBindFtr" DROP CONSTRAINT "CovalentBindFtr_ModFtr_FK";

ALTER TABLE "UniPAX"."Degradation" DROP CONSTRAINT "Degradation_Conversion_FK";

ALTER TABLE "UniPAX"."Delay" DROP CONSTRAINT "Delay_SBase_FK";

ALTER TABLE "UniPAX"."DeltaG" DROP CONSTRAINT "DeltaG_UtilityClass_FK";

ALTER TABLE "UniPAX"."Dna" DROP CONSTRAINT "Dna_PhysEntity_FK";

ALTER TABLE "UniPAX"."DnaRef" DROP CONSTRAINT "DnaRef_EntityRef_FK";

ALTER TABLE "UniPAX"."DnaRegion" DROP CONSTRAINT "DnaRegion_PhysEntity_FK";

ALTER TABLE "UniPAX"."DnaRegionRef" DROP CONSTRAINT "DnaRegionRef_EntityRef_FK";

ALTER TABLE "UniPAX"."Entity" DROP CONSTRAINT "Entity_Thing_FK";

ALTER TABLE "UniPAX"."EntityFtr" DROP CONSTRAINT "EntityFtr_UtilityClass_FK";

ALTER TABLE "UniPAX"."EntityRef" DROP CONSTRAINT "EntityRef_EntityFtr_FK";

ALTER TABLE "UniPAX"."EntityRefTypeVoc" DROP CONSTRAINT "EntityRefTypeVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."Event" DROP CONSTRAINT "Event_SBase_FK";

ALTER TABLE "UniPAX"."EventAsg" DROP CONSTRAINT "EventAsg_SBase_FK";

ALTER TABLE "UniPAX"."Evidence" DROP CONSTRAINT "Evidence_UtilityClass_FK";

ALTER TABLE "UniPAX"."EvidenceCodeVoc" DROP CONSTRAINT "EvidenceCodeVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."ExpForm" DROP CONSTRAINT "ExpForm_UtilityClass_FK";

ALTER TABLE "UniPAX"."ExpFormVoc" DROP CONSTRAINT "ExpFormVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."FragmentFtr" DROP CONSTRAINT "FragmentFtr_EntityFtr_FK";

ALTER TABLE "UniPAX"."FunctionDef" DROP CONSTRAINT "FunctionDef_SBase_FK";

ALTER TABLE "UniPAX"."Gene" DROP CONSTRAINT "Gene_Entity_FK";

ALTER TABLE "UniPAX"."GeneticIntac" DROP CONSTRAINT "GeneticIntac_Intac_FK";

ALTER TABLE "UniPAX"."ImportSource" DROP CONSTRAINT "ImportSource_UtilityClass_FK";

ALTER TABLE "UniPAX"."InitialAsg" DROP CONSTRAINT "InitialAsg_SBase_FK";

ALTER TABLE "UniPAX"."Intac" DROP CONSTRAINT "Intac_Entity_FK";

ALTER TABLE "UniPAX"."IntacVoc" DROP CONSTRAINT "IntacVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."KineticLaw" DROP CONSTRAINT "KineticLaw_SBase_FK";

ALTER TABLE "UniPAX"."KPrime" DROP CONSTRAINT "KPrime_UtilityClass_FK";

ALTER TABLE "UniPAX"."LocalParameter" DROP CONSTRAINT "LocalParameter_SBase_FK";

ALTER TABLE "UniPAX"."Math" DROP CONSTRAINT "Math_UPBase_FK";

ALTER TABLE "UniPAX"."Message" DROP CONSTRAINT "Message_SBase_FK";

ALTER TABLE "UniPAX"."ModFtr" DROP CONSTRAINT "ModFtr_EntityFtr_FK";

ALTER TABLE "UniPAX"."Modulation" DROP CONSTRAINT "Modulation_Control_FK";

ALTER TABLE "UniPAX"."MolrIntac" DROP CONSTRAINT "MolrIntac_Intac_FK";

ALTER TABLE "UniPAX"."Parameter" DROP CONSTRAINT "Parameter_SBase_FK";

ALTER TABLE "UniPAX"."Pw" DROP CONSTRAINT "Pw_Entity_FK";

ALTER TABLE "UniPAX"."PwStep" DROP CONSTRAINT "PwStep_UtilityClass_FK";

ALTER TABLE "UniPAX"."PhenotypeVoc" DROP CONSTRAINT "PhenotypeVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."PhysEntity" DROP CONSTRAINT "PhysEntity_Entity_FK";

ALTER TABLE "UniPAX"."Priority" DROP CONSTRAINT "Priority_SBase_FK";

ALTER TABLE "UniPAX"."Protein" DROP CONSTRAINT "Protein_PhysEntity_FK";

ALTER TABLE "UniPAX"."ProteinRef" DROP CONSTRAINT "ProteinRef_EntityRef_FK";

ALTER TABLE "UniPAX"."Provenance" DROP CONSTRAINT "Provenance_UtilityClass_FK";

ALTER TABLE "UniPAX"."PubXref" DROP CONSTRAINT "PubXref_Xref_FK";

ALTER TABLE "UniPAX"."RateRule" DROP CONSTRAINT "RateRule_Rule_FK";

ALTER TABLE "UniPAX"."RelshpTypeVoc" DROP CONSTRAINT "RelshpTypeVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."RelshpXref" DROP CONSTRAINT "RelshpXref_Xref_FK";

ALTER TABLE "UniPAX"."Rna" DROP CONSTRAINT "Rna_PhysEntity_FK";

ALTER TABLE "UniPAX"."RnaRef" DROP CONSTRAINT "RnaRef_EntityRef_FK";

ALTER TABLE "UniPAX"."RnaRegion" DROP CONSTRAINT "RnaRegion_PhysEntity_FK";

ALTER TABLE "UniPAX"."RnaRegionRef" DROP CONSTRAINT "RnaRegionRef_EntityRef_FK";

ALTER TABLE "UniPAX"."Rule" DROP CONSTRAINT "Rule_SBase_FK";

ALTER TABLE "UniPAX"."SBase" DROP CONSTRAINT "SBase_UPBase_FK";

ALTER TABLE "UniPAX"."Score" DROP CONSTRAINT "Score_UtilityClass_FK";

ALTER TABLE "UniPAX"."SeqInterval" DROP CONSTRAINT "SeqInterval_SeqLoc_FK";

ALTER TABLE "UniPAX"."SeqLoc" DROP CONSTRAINT "SeqLoc_UtilityClass_FK";

ALTER TABLE "UniPAX"."SeqModVoc" DROP CONSTRAINT "SeqModVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."SeqRegionVoc" DROP CONSTRAINT "SeqRegionVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."SeqSite" DROP CONSTRAINT "SeqSite_SeqLoc_FK";

ALTER TABLE "UniPAX"."SmallMol" DROP CONSTRAINT "SmallMol_PhysEntity_FK";

ALTER TABLE "UniPAX"."SmallMolRef" DROP CONSTRAINT "SmallMolRef_EntityRef_FK";

ALTER TABLE "UniPAX"."Stoic" DROP CONSTRAINT "Stoic_UtilityClass_FK";

ALTER TABLE "UniPAX"."TmpReac" DROP CONSTRAINT "TmpReac_Intac_FK";

ALTER TABLE "UniPAX"."TmpReacReg" DROP CONSTRAINT "TmpReacReg_Control_FK";

ALTER TABLE "UniPAX"."Thing" DROP CONSTRAINT "Thing_UPBase_FK";

ALTER TABLE "UniPAX"."TissueVoc" DROP CONSTRAINT "TissueVoc_CtrdVoc_FK";

ALTER TABLE "UniPAX"."Tsp" DROP CONSTRAINT "Tsp_Conversion_FK";

ALTER TABLE "UniPAX"."TspWithBchemReac" DROP CONSTRAINT "TspWithBchemReac_BchemReac_FK";

ALTER TABLE "UniPAX"."TspWithBchemReac" DROP CONSTRAINT "TspWithBchemReac_Tsp_FK";

ALTER TABLE "UniPAX"."Trigger" DROP CONSTRAINT "Trigger_SBase_FK";

ALTER TABLE "UniPAX"."UnificationXref" DROP CONSTRAINT "UnificationXref_Xref_FK";

ALTER TABLE "UniPAX"."Unit" DROP CONSTRAINT "Unit_SBase_FK";

ALTER TABLE "UniPAX"."UnitDef" DROP CONSTRAINT "UnitDef_SBase_FK";

ALTER TABLE "UniPAX"."UtilityClass" DROP CONSTRAINT "UtilityClass_Thing_FK";

ALTER TABLE "UniPAX"."Xref" DROP CONSTRAINT "Xref_UtilityClass_FK";

ALTER TABLE "UniPAX"."AlgebraicRule" DROP CONSTRAINT "AlgebraicRule_PK";

ALTER TABLE "UniPAX"."AsgRule" DROP CONSTRAINT "AsgRule_PK";

ALTER TABLE "UniPAX"."BindFtr" DROP CONSTRAINT "BindFtr_PK";

ALTER TABLE "UniPAX"."BchemPwStep" DROP CONSTRAINT "BchemPwStep_PK";

ALTER TABLE "UniPAX"."BchemReac" DROP CONSTRAINT "BchemReac_PK";

ALTER TABLE "UniPAX"."BioSource" DROP CONSTRAINT "BioSource_PK";

ALTER TABLE "UniPAX"."Catalysis" DROP CONSTRAINT "Catalysis_PK";

ALTER TABLE "UniPAX"."CellLocVoc" DROP CONSTRAINT "CellLocVoc_PK";

ALTER TABLE "UniPAX"."CellVoc" DROP CONSTRAINT "CellVoc_PK";

ALTER TABLE "UniPAX"."ChemStruct" DROP CONSTRAINT "ChemStruct_PK";

ALTER TABLE "UniPAX"."Complex" DROP CONSTRAINT "Complex_PK";

ALTER TABLE "UniPAX"."ComplexAssembly" DROP CONSTRAINT "ComplexAssembly_PK";

ALTER TABLE "UniPAX"."Constraint" DROP CONSTRAINT "Constraint_PK";

ALTER TABLE "UniPAX"."Control" DROP CONSTRAINT "Control_PK";

ALTER TABLE "UniPAX"."CtrdVoc" DROP CONSTRAINT "CtrdVoc_PK";

ALTER TABLE "UniPAX"."Conversion" DROP CONSTRAINT "Conversion_PK";

ALTER TABLE "UniPAX"."CovalentBindFtr" DROP CONSTRAINT "CovalentBindFtr_PK";

ALTER TABLE "UniPAX"."Degradation" DROP CONSTRAINT "Degradation_PK";

ALTER TABLE "UniPAX"."Delay" DROP CONSTRAINT "Delay_PK";

ALTER TABLE "UniPAX"."DeltaG" DROP CONSTRAINT "DeltaG_PK";

ALTER TABLE "UniPAX"."Dna" DROP CONSTRAINT "Dna_PK";

ALTER TABLE "UniPAX"."DnaRef" DROP CONSTRAINT "DnaRef_PK";

ALTER TABLE "UniPAX"."DnaRegion" DROP CONSTRAINT "DnaRegion_PK";

ALTER TABLE "UniPAX"."DnaRegionRef" DROP CONSTRAINT "DnaRegionRef_PK";

ALTER TABLE "UniPAX"."Entity" DROP CONSTRAINT "Entity_PK";

ALTER TABLE "UniPAX"."EntityFtr" DROP CONSTRAINT "EntityFtr_PK";

ALTER TABLE "UniPAX"."EntityRef" DROP CONSTRAINT "EntityRef_PK";

ALTER TABLE "UniPAX"."EntityRefTypeVoc" DROP CONSTRAINT "EntityRefTypeVoc_PK";

ALTER TABLE "UniPAX"."Event" DROP CONSTRAINT "Event_PK";

ALTER TABLE "UniPAX"."EventAsg" DROP CONSTRAINT "EventAsg_PK";

ALTER TABLE "UniPAX"."Evidence" DROP CONSTRAINT "Evidence_PK";

ALTER TABLE "UniPAX"."EvidenceCodeVoc" DROP CONSTRAINT "EvidenceCodeVoc_PK";

ALTER TABLE "UniPAX"."ExpForm" DROP CONSTRAINT "ExpForm_PK";

ALTER TABLE "UniPAX"."ExpFormVoc" DROP CONSTRAINT "ExpFormVoc_PK";

ALTER TABLE "UniPAX"."FragmentFtr" DROP CONSTRAINT "FragmentFtr_PK";

ALTER TABLE "UniPAX"."FunctionDef" DROP CONSTRAINT "FunctionDef_PK";

ALTER TABLE "UniPAX"."Gene" DROP CONSTRAINT "Gene_PK";

ALTER TABLE "UniPAX"."GeneticIntac" DROP CONSTRAINT "GeneticIntac_PK";

ALTER TABLE "UniPAX"."ImportSource" DROP CONSTRAINT "ImportSource_PK";

ALTER TABLE "UniPAX"."InitialAsg" DROP CONSTRAINT "InitialAsg_PK";

ALTER TABLE "UniPAX"."Intac" DROP CONSTRAINT "Intac_PK";

ALTER TABLE "UniPAX"."IntacVoc" DROP CONSTRAINT "IntacVoc_PK";

ALTER TABLE "UniPAX"."KineticLaw" DROP CONSTRAINT "KineticLaw_PK";

ALTER TABLE "UniPAX"."KPrime" DROP CONSTRAINT "KPrime_PK";

ALTER TABLE "UniPAX"."LocalParameter" DROP CONSTRAINT "LocalParameter_PK";

ALTER TABLE "UniPAX"."Math" DROP CONSTRAINT "Math_PK";

ALTER TABLE "UniPAX"."Message" DROP CONSTRAINT "Message_PK";

ALTER TABLE "UniPAX"."ModFtr" DROP CONSTRAINT "ModFtr_PK";

ALTER TABLE "UniPAX"."Modulation" DROP CONSTRAINT "Modulation_PK";

ALTER TABLE "UniPAX"."MolrIntac" DROP CONSTRAINT "MolrIntac_PK";

ALTER TABLE "UniPAX"."Parameter" DROP CONSTRAINT "Parameter_PK";

ALTER TABLE "UniPAX"."Pw" DROP CONSTRAINT "Pw_PK";

ALTER TABLE "UniPAX"."PwStep" DROP CONSTRAINT "PwStep_PK";

ALTER TABLE "UniPAX"."PhenotypeVoc" DROP CONSTRAINT "PhenotypeVoc_PK";

ALTER TABLE "UniPAX"."PhysEntity" DROP CONSTRAINT "PhysEntity_PK";

ALTER TABLE "UniPAX"."Priority" DROP CONSTRAINT "Priority_PK";

ALTER TABLE "UniPAX"."Protein" DROP CONSTRAINT "Protein_PK";

ALTER TABLE "UniPAX"."ProteinRef" DROP CONSTRAINT "ProteinRef_PK";

ALTER TABLE "UniPAX"."Provenance" DROP CONSTRAINT "Provenance_PK";

ALTER TABLE "UniPAX"."PubXref" DROP CONSTRAINT "PubXref_PK";

ALTER TABLE "UniPAX"."RateRule" DROP CONSTRAINT "RateRule_PK";

ALTER TABLE "UniPAX"."RelshpTypeVoc" DROP CONSTRAINT "RelshpTypeVoc_PK";

ALTER TABLE "UniPAX"."RelshpXref" DROP CONSTRAINT "RelshpXref_PK";

ALTER TABLE "UniPAX"."Rna" DROP CONSTRAINT "Rna_PK";

ALTER TABLE "UniPAX"."RnaRef" DROP CONSTRAINT "RnaRef_PK";

ALTER TABLE "UniPAX"."RnaRegion" DROP CONSTRAINT "RnaRegion_PK";

ALTER TABLE "UniPAX"."RnaRegionRef" DROP CONSTRAINT "RnaRegionRef_PK";

ALTER TABLE "UniPAX"."Rule" DROP CONSTRAINT "Rule_PK";

ALTER TABLE "UniPAX"."SBase" DROP CONSTRAINT "SBase_PK";

ALTER TABLE "UniPAX"."Score" DROP CONSTRAINT "Score_PK";

ALTER TABLE "UniPAX"."SeqInterval" DROP CONSTRAINT "SeqInterval_PK";

ALTER TABLE "UniPAX"."SeqLoc" DROP CONSTRAINT "SeqLoc_PK";

ALTER TABLE "UniPAX"."SeqModVoc" DROP CONSTRAINT "SeqModVoc_PK";

ALTER TABLE "UniPAX"."SeqRegionVoc" DROP CONSTRAINT "SeqRegionVoc_PK";

ALTER TABLE "UniPAX"."SeqSite" DROP CONSTRAINT "SeqSite_PK";

ALTER TABLE "UniPAX"."SmallMol" DROP CONSTRAINT "SmallMol_PK";

ALTER TABLE "UniPAX"."SmallMolRef" DROP CONSTRAINT "SmallMolRef_PK";

ALTER TABLE "UniPAX"."Stoic" DROP CONSTRAINT "Stoic_PK";

ALTER TABLE "UniPAX"."TmpReac" DROP CONSTRAINT "TmpReac_PK";

ALTER TABLE "UniPAX"."TmpReacReg" DROP CONSTRAINT "TmpReacReg_PK";

ALTER TABLE "UniPAX"."Thing" DROP CONSTRAINT "Thing_PK";

ALTER TABLE "UniPAX"."TissueVoc" DROP CONSTRAINT "TissueVoc_PK";

ALTER TABLE "UniPAX"."Tsp" DROP CONSTRAINT "Tsp_PK";

ALTER TABLE "UniPAX"."TspWithBchemReac" DROP CONSTRAINT "TspWithBchemReac_PK";

ALTER TABLE "UniPAX"."Trigger" DROP CONSTRAINT "Trigger_PK";

ALTER TABLE "UniPAX"."UnificationXref" DROP CONSTRAINT "UnificationXref_PK";

ALTER TABLE "UniPAX"."Unit" DROP CONSTRAINT "Unit_PK";

ALTER TABLE "UniPAX"."UnitDef" DROP CONSTRAINT "UnitDef_PK";

ALTER TABLE "UniPAX"."UPBase" DROP CONSTRAINT "UPBase_PK";

ALTER TABLE "UniPAX"."UtilityClass" DROP CONSTRAINT "UtilityClass_PK";

ALTER TABLE "UniPAX"."Xref" DROP CONSTRAINT "Xref_PK";

ALTER TABLE "UniPAX"."StringCollection" DROP CONSTRAINT "StringCollection_PK";

DROP TABLE "UniPAX"."AlgebraicRule";

DROP TABLE "UniPAX"."AsgRule";

DROP TABLE "UniPAX"."BindFtr";

DROP TABLE "UniPAX"."BchemPwStep";

DROP TABLE "UniPAX"."BchemReac";

DROP TABLE "UniPAX"."BioSource";

DROP TABLE "UniPAX"."Catalysis";

DROP TABLE "UniPAX"."CellLocVoc";

DROP TABLE "UniPAX"."CellVoc";

DROP TABLE "UniPAX"."ChemStruct";

DROP TABLE "UniPAX"."Complex";

DROP TABLE "UniPAX"."ComplexAssembly";

DROP TABLE "UniPAX"."Constraint";

DROP TABLE "UniPAX"."Control";

DROP TABLE "UniPAX"."CtrdVoc";

DROP TABLE "UniPAX"."Conversion";

DROP TABLE "UniPAX"."CovalentBindFtr";

DROP TABLE "UniPAX"."Degradation";

DROP TABLE "UniPAX"."Delay";

DROP TABLE "UniPAX"."DeltaG";

DROP TABLE "UniPAX"."Dna";

DROP TABLE "UniPAX"."DnaRef";

DROP TABLE "UniPAX"."DnaRegion";

DROP TABLE "UniPAX"."DnaRegionRef";

DROP TABLE "UniPAX"."Entity";

DROP TABLE "UniPAX"."EntityFtr";

DROP TABLE "UniPAX"."EntityRef";

DROP TABLE "UniPAX"."EntityRefTypeVoc";

DROP TABLE "UniPAX"."Event";

DROP TABLE "UniPAX"."EventAsg";

DROP TABLE "UniPAX"."Evidence";

DROP TABLE "UniPAX"."EvidenceCodeVoc";

DROP TABLE "UniPAX"."ExpForm";

DROP TABLE "UniPAX"."ExpFormVoc";

DROP TABLE "UniPAX"."FragmentFtr";

DROP TABLE "UniPAX"."FunctionDef";

DROP TABLE "UniPAX"."Gene";

DROP TABLE "UniPAX"."GeneticIntac";

DROP TABLE "UniPAX"."ImportSource";

DROP TABLE "UniPAX"."InitialAsg";

DROP TABLE "UniPAX"."Intac";

DROP TABLE "UniPAX"."IntacVoc";

DROP TABLE "UniPAX"."KineticLaw";

DROP TABLE "UniPAX"."KPrime";

DROP TABLE "UniPAX"."LocalParameter";

DROP TABLE "UniPAX"."Math";

DROP TABLE "UniPAX"."Message";

DROP TABLE "UniPAX"."ModFtr";

DROP TABLE "UniPAX"."Modulation";

DROP TABLE "UniPAX"."MolrIntac";

DROP TABLE "UniPAX"."Parameter";

DROP TABLE "UniPAX"."Pw";

DROP TABLE "UniPAX"."PwStep";

DROP TABLE "UniPAX"."PhenotypeVoc";

DROP TABLE "UniPAX"."PhysEntity";

DROP TABLE "UniPAX"."Priority";

DROP TABLE "UniPAX"."Protein";

DROP TABLE "UniPAX"."ProteinRef";

DROP TABLE "UniPAX"."Provenance";

DROP TABLE "UniPAX"."PubXref";

DROP TABLE "UniPAX"."RateRule";

DROP TABLE "UniPAX"."RelshpTypeVoc";

DROP TABLE "UniPAX"."RelshpXref";

DROP TABLE "UniPAX"."Rna";

DROP TABLE "UniPAX"."RnaRef";

DROP TABLE "UniPAX"."RnaRegion";

DROP TABLE "UniPAX"."RnaRegionRef";

DROP TABLE "UniPAX"."Rule";

DROP TABLE "UniPAX"."SBase";

DROP TABLE "UniPAX"."Score";

DROP TABLE "UniPAX"."SeqInterval";

DROP TABLE "UniPAX"."SeqLoc";

DROP TABLE "UniPAX"."SeqModVoc";

DROP TABLE "UniPAX"."SeqRegionVoc";

DROP TABLE "UniPAX"."SeqSite";

DROP TABLE "UniPAX"."SmallMol";

DROP TABLE "UniPAX"."SmallMolRef";

DROP TABLE "UniPAX"."Stoic";

DROP TABLE "UniPAX"."TmpReac";

DROP TABLE "UniPAX"."TmpReacReg";

DROP TABLE "UniPAX"."Thing";

DROP TABLE "UniPAX"."TissueVoc";

DROP TABLE "UniPAX"."Tsp";

DROP TABLE "UniPAX"."TspWithBchemReac";

DROP TABLE "UniPAX"."Trigger";

DROP TABLE "UniPAX"."UnificationXref";

DROP TABLE "UniPAX"."Unit";

DROP TABLE "UniPAX"."UnitDef";

DROP TABLE "UniPAX"."UPBase";

DROP TABLE "UniPAX"."UtilityClass";

DROP TABLE "UniPAX"."Xref";

DROP TABLE "UniPAX"."Experiment";

DROP TABLE "UniPAX"."StringCollection";

DROP TABLE "UniPAX"."Mapping";

DROP TABLE "UniPAX"."Sample";

CREATE TABLE "UniPAX"."AlgebraicRule" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."AsgRule" (
		"unipaxId" NUMBER NOT NULL,
		"variable" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."BindFtr" (
		"unipaxId" NUMBER NOT NULL,
		"intraMolr" CHAR(1),
		"unipaxId1" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."BchemPwStep" (
		"unipaxId" NUMBER NOT NULL,
		"stepDir" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."BchemReac" (
		"unipaxId" NUMBER NOT NULL,
		"deltaH" NUMBER,
		"deltaS" NUMBER,
		"eCNumber" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."BioSource" (
		"unipaxId" NUMBER NOT NULL,
		"standardName" VARCHAR2(4000),
		"displayName" VARCHAR2(4000),
		"geneUnipaxId" NUMBER NOT NULL,
		"pwUnipaxId" NUMBER NOT NULL,
		"dnaRefUnipaxId" NUMBER NOT NULL,
		"dnaRegionRefUnipaxId" NUMBER NOT NULL,
		"proteinRefUnipaxId" NUMBER NOT NULL,
		"rnaRefUnipaxId" NUMBER NOT NULL,
		"rnaRegionRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Catalysis" (
		"interactionUnipaxId" NUMBER NOT NULL,
		"catalysisDir" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."CellLocVoc" (
		"controlledVocUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."CellVoc" (
		"controlledVocUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ChemStruct" (
		"unipaxId" NUMBER NOT NULL,
		"structureData" VARCHAR2(4000),
		"structureFormat" VARCHAR2(4000),
		"smallMolRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Complex" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ComplexAssembly" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Constraint" (
		"unipaxId" NUMBER NOT NULL,
		"pwUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Control" (
		"interactionUnipaxId" NUMBER NOT NULL,
		"controlType" VARCHAR2(4000),
		"unipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."CtrdVoc" (
		"unipaxId" NUMBER NOT NULL,
		"term" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Conversion" (
		"unipaxId" NUMBER NOT NULL,
		"conversionDir" VARCHAR2(4000),
		"spontaneous" VARCHAR2(4000),
		"biochemicalPwStepUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."CovalentBindFtr" (
		"modificationFtrUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Degradation" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Delay" (
		"unipaxId" NUMBER NOT NULL,
		"eventUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."DeltaG" (
		"unipaxId" NUMBER NOT NULL,
		"deltaGPrime0" NUMBER,
		"ionicStrength" NUMBER,
		"ph" NUMBER,
		"pMg" NUMBER,
		"temperature" NUMBER,
		"biochemicalReacUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Dna" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."DnaRef" (
		"unipaxId" NUMBER NOT NULL,
		"sequence" CLOB,
		"subRegionUnipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."DnaRegion" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."DnaRegionRef" (
		"unipaxId" NUMBER NOT NULL,
		"sequence" CLOB,
		"subRegionUnipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Entity" (
		"unipaxId" NUMBER NOT NULL,
		"availability" VARCHAR2(4000),
		"comment" VARCHAR2(4000),
		"displayName" VARCHAR2(4000),
		"standardName" VARCHAR2(4000),
		"interactionUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."EntityFtr" (
		"unipaxId" NUMBER NOT NULL,
		"physicalEntityUnipaxId" NUMBER NOT NULL,
		"physicalEntity1UnipaxId" NUMBER NOT NULL,
		"unipaxId1" NUMBER NOT NULL,
		"experimentalFormUnipaxId" NUMBER NOT NULL,
		"entityRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."EntityRef" (
		"unipaxId" NUMBER NOT NULL,
		"standardName" VARCHAR2(4000),
		"displayName" VARCHAR2(4000),
		"dnaUnipaxId" NUMBER NOT NULL,
		"dnaRegionUnipaxId" NUMBER NOT NULL,
		"proteinUnipaxId" NUMBER NOT NULL,
		"rnaUnipaxId" NUMBER NOT NULL,
		"rnaRegionUnipaxId" NUMBER NOT NULL,
		"smallMolUnipaxId" NUMBER NOT NULL,
		"unipaxId1" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."EntityRefTypeVoc" (
		"unipaxId" NUMBER NOT NULL,
		"entityRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Event" (
		"unipaxId" NUMBER NOT NULL,
		"useValuesFromTriggerTime" CHAR(1),
		"id" VARCHAR2(4000),
		"name" VARCHAR2(4000),
		"pwUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."EventAsg" (
		"eventUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL,
		"variable" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Evidence" (
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL,
		"entityFtrUnipaxId" NUMBER NOT NULL,
		"pwStepUnipaxId" NUMBER NOT NULL,
		"entityRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."EvidenceCodeVoc" (
		"unipaxId" NUMBER NOT NULL,
		"utilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ExpForm" (
		"unipaxId" NUMBER NOT NULL,
		"utilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ExpFormVoc" (
		"unipaxId" NUMBER NOT NULL,
		"experimentalFormUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."FragmentFtr" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."FunctionDef" (
		"unipaxId" NUMBER NOT NULL,
		"id" VARCHAR2(4000),
		"name" VARCHAR2(4000),
		"pwUnipaxId" NUMBER NOT NULL,
		"eventUnipaxId" NUMBER NOT NULL,
		"eventAsgUnipaxId" NUMBER NOT NULL,
		"triggerUnipaxId" NUMBER NOT NULL,
		"ruleUnipaxId" NUMBER NOT NULL,
		"priorityUnipaxId" NUMBER NOT NULL,
		"delayUnipaxId" NUMBER NOT NULL,
		"mathUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Gene" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."GeneticIntac" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ImportSource" (
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL,
		"entityUnipaxId" NUMBER NOT NULL,
		"entity1UnipaxId" NUMBER NOT NULL,
		"utilityClassUnipaxId1" NUMBER NOT NULL,
		"utilityClassUnipaxId2" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."InitialAsg" (
		"unipaxId" NUMBER NOT NULL,
		"symbol" VARCHAR2(4000),
		"pwUnipaxId" NUMBER NOT NULL,
		"eventUnipaxId" NUMBER NOT NULL,
		"eventAsgUnipaxId" NUMBER NOT NULL,
		"triggerUnipaxId" NUMBER NOT NULL,
		"ruleUnipaxId" NUMBER NOT NULL,
		"priorityUnipaxId" NUMBER NOT NULL,
		"delayUnipaxId" NUMBER NOT NULL,
		"mathUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Intac" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."IntacVoc" (
		"controlledVocUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."KineticLaw" (
		"unipaxId" NUMBER NOT NULL,
		"conversionUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."KPrime" (
		"unipaxId" NUMBER NOT NULL,
		"ionicStrength" NUMBER,
		"kPrime" NUMBER,
		"ph" NUMBER,
		"pMg" NUMBER,
		"temperature" NUMBER,
		"biochemicalReacUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."LocalParameter" (
		"unipaxId" NUMBER NOT NULL,
		"id" VARCHAR2(4000),
		"name" VARCHAR2(4000),
		"value" NUMBER,
		"unit" VARCHAR2(4000),
		"kineticLawUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Math" (
		"eventUnipaxId" NUMBER NOT NULL,
		"eventAsgUnipaxId" NUMBER NOT NULL,
		"triggerUnipaxId" NUMBER NOT NULL,
		"ruleUnipaxId" NUMBER NOT NULL,
		"priorityUnipaxId" NUMBER NOT NULL,
		"delayUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL,
		"mathML" BLOB,
		"constraintUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Message" (
		"unipaxId" NUMBER NOT NULL,
		"message" VARCHAR2(4000),
		"constraintUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ModFtr" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Modulation" (
		"interactionUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."MolrIntac" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Parameter" (
		"unipaxId" NUMBER NOT NULL,
		"constant" CHAR(1),
		"id" VARCHAR2(4000),
		"name" VARCHAR2(4000),
		"value" NUMBER,
		"units" VARCHAR2(4000),
		"pwUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Pw" (
		"unipaxId" NUMBER NOT NULL,
		"componentUnipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."PwStep" (
		"unipaxId" NUMBER NOT NULL,
		"pwUnipaxId" NUMBER NOT NULL,
		"unipaxId1" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."PhenotypeVoc" (
		"unipaxId" NUMBER NOT NULL,
		"patoData" VARCHAR2(4000),
		"geneticIntacUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."PhysEntity" (
		"unipaxId" NUMBER NOT NULL,
		"unipaxId1" NUMBER NOT NULL,
		"stoichiometryUnipaxId" NUMBER NOT NULL,
		"conversionUnipaxId" NUMBER NOT NULL,
		"conversion1UnipaxId" NUMBER NOT NULL,
		"complexUnipaxId" NUMBER NOT NULL,
		"interactionUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Priority" (
		"unipaxId" NUMBER NOT NULL,
		"eventUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Protein" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."ProteinRef" (
		"unipaxId" NUMBER NOT NULL,
		"sequence" CLOB
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Provenance" (
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"displayName" VARCHAR2(4000),
		"standardName" VARCHAR2(4000),
		"unipaxId" NUMBER NOT NULL,
		"scoreUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."PubXref" (
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"title" VARCHAR2(4000),
		"year" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RateRule" (
		"unipaxId" NUMBER NOT NULL,
		"variable" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RelshpTypeVoc" (
		"unipaxId" NUMBER NOT NULL,
		"utilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RelshpXref" (
		"utilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Rna" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RnaRef" (
		"unipaxId" NUMBER NOT NULL,
		"sequence" CLOB,
		"subRegionUnipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RnaRegion" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."RnaRegionRef" (
		"unipaxId" NUMBER NOT NULL,
		"sequence" CLOB,
		"subRegionUnipaxId" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Rule" (
		"unipaxId" NUMBER NOT NULL,
		"pwUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SBase" (
		"unipaxId" NUMBER NOT NULL,
		"metaId" VARCHAR2(4000),
		"sboTerm" VARCHAR2(4000)
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Score" (
		"unipaxId" NUMBER NOT NULL,
		"value" VARCHAR2(4000),
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"geneticIntacUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SeqInterval" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SeqLoc" (
		"unipaxId" NUMBER NOT NULL,
		"entityFtrUnipaxId" NUMBER NOT NULL,
		"dnaRegionRefUnipaxId" NUMBER NOT NULL,
		"rnaRegionRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SeqModVoc" (
		"unipaxId" NUMBER NOT NULL,
		"modificationFtrUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SeqRegionVoc" (
		"unipaxId" NUMBER NOT NULL,
		"entityFtrUnipaxId" NUMBER NOT NULL,
		"dnaRegionRefUnipaxId" NUMBER NOT NULL,
		"rnaRegionRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SeqSite" (
		"unipaxId" NUMBER NOT NULL,
		"positionStatus" VARCHAR2(4000),
		"sequencePosition" NUMBER,
		"sequenceIntervalUnipaxId" NUMBER NOT NULL,
		"sequenceInterval1UnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SmallMol" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."SmallMolRef" (
		"unipaxId" NUMBER NOT NULL,
		"chemicalFormula" VARCHAR2(4000),
		"molecularWeight" NUMBER
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Stoic" (
		"unipaxId" NUMBER NOT NULL,
		"stoichiometricCoefficient" NUMBER,
		"conversionUnipaxId" NUMBER NOT NULL,
		"complexUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."TmpReac" (
		"unipaxId" NUMBER NOT NULL,
		"templateDir" VARCHAR2(4000),
		"templateUnipaxId" NUMBER,
		"productUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."TmpReacReg" (
		"interactionUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Thing" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."TissueVoc" (
		"controlledVocUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Tsp" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."TspWithBchemReac" (
		"transportUnipaxId" NUMBER NOT NULL,
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Trigger" (
		"unipaxId" NUMBER NOT NULL,
		"initialValue" NUMBER,
		"persistent" CHAR(1),
		"eventUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."UnificationXref" (
		"utilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Unit" (
		"unipaxId" NUMBER NOT NULL,
		"exponent" NUMBER,
		"kind" VARCHAR2(4000),
		"multiplier" NUMBER,
		"scale" NUMBER,
		"unitDefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."UnitDef" (
		"unipaxId" NUMBER NOT NULL,
		"id" VARCHAR2(4000),
		"name" VARCHAR2(4000),
		"pwUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."UPBase" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."UtilityClass" (
		"unipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Xref" (
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"idVersion" VARCHAR2(4000),
		"id" VARCHAR2(4000),
		"dbVersion" VARCHAR2(4000),
		"db" VARCHAR2(4000),
		"unipaxId" NUMBER NOT NULL,
		"bioSourceUnipaxId" NUMBER NOT NULL,
		"controlledVocUnipaxId" NUMBER NOT NULL,
		"evidenceUtilityClassUnipaxId" NUMBER NOT NULL,
		"provenanceUtilityClassUnipaxId" NUMBER NOT NULL,
		"entityRefUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Experiment" (
		"experimentId" NUMBER,
		"name" VARCHAR2(4000),
		"shortDescription" VARCHAR2(4000),
		"source" VARCHAR2(4000),
		"user" VARCHAR2(4000),
		"metaInfos" CLOB,
		"valuesPerSample" NUMBER,
		"defaultMapping" BLOB
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."StringCollection" (
		"unipaxId" NUMBER NOT NULL,
		"entry" VARCHAR2(4000),
		"utilityClassUnipaxId" NUMBER NOT NULL,
		"bioSourceUnipaxId" NUMBER NOT NULL,
		"provenanceUtilityClassUnipaxId" NUMBER NOT NULL,
		"entityRefUnipaxId" NUMBER NOT NULL,
		"pubXrefUtilityClassUnipaxId" NUMBER NOT NULL,
		"pubXref1UtilityClassUnipaxId" NUMBER NOT NULL,
		"pubXref2UtilityClassUnipaxId" NUMBER NOT NULL
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Mapping" (
		"idType" VARCHAR2(4000),
		"mapping" BLOB
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

CREATE TABLE "UniPAX"."Sample" (
		"indexInExperiment" NUMBER,
		"name" VARCHAR2(4000),
		"description" VARCHAR2(4000),
		"user" VARCHAR2(4000),
		"metaInfos" CLOB,
		"dataType" VARCHAR2(4000),
		"data" BLOB
	)
	PCTFREE 0
	PCTUSED 0
	LOGGING;

ALTER TABLE "UniPAX"."AlgebraicRule" ADD CONSTRAINT "AlgebraicRule_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."AsgRule" ADD CONSTRAINT "AsgRule_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."BindFtr" ADD CONSTRAINT "BindFtr_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."BchemPwStep" ADD CONSTRAINT "BchemPwStep_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."BchemReac" ADD CONSTRAINT "BchemReac_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."BioSource" ADD CONSTRAINT "BioSource_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Catalysis" ADD CONSTRAINT "Catalysis_PK" PRIMARY KEY
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."CellLocVoc" ADD CONSTRAINT "CellLocVoc_PK" PRIMARY KEY
	("controlledVocUnipaxId");

ALTER TABLE "UniPAX"."CellVoc" ADD CONSTRAINT "CellVoc_PK" PRIMARY KEY
	("controlledVocUnipaxId");

ALTER TABLE "UniPAX"."ChemStruct" ADD CONSTRAINT "ChemStruct_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Complex" ADD CONSTRAINT "Complex_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ComplexAssembly" ADD CONSTRAINT "ComplexAssembly_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Constraint" ADD CONSTRAINT "Constraint_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Control" ADD CONSTRAINT "Control_PK" PRIMARY KEY
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."CtrdVoc" ADD CONSTRAINT "CtrdVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Conversion" ADD CONSTRAINT "Conversion_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."CovalentBindFtr" ADD CONSTRAINT "CovalentBindFtr_PK" PRIMARY KEY
	("modificationFtrUnipaxId",
	 "unipaxId");

ALTER TABLE "UniPAX"."Degradation" ADD CONSTRAINT "Degradation_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Delay" ADD CONSTRAINT "Delay_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."DeltaG" ADD CONSTRAINT "DeltaG_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Dna" ADD CONSTRAINT "Dna_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRef" ADD CONSTRAINT "DnaRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRegion" ADD CONSTRAINT "DnaRegion_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRegionRef" ADD CONSTRAINT "DnaRegionRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Entity" ADD CONSTRAINT "Entity_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."EntityFtr" ADD CONSTRAINT "EntityFtr_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."EntityRef" ADD CONSTRAINT "EntityRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."EntityRefTypeVoc" ADD CONSTRAINT "EntityRefTypeVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Event" ADD CONSTRAINT "Event_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."EventAsg" ADD CONSTRAINT "EventAsg_PK" PRIMARY KEY
	("eventUnipaxId",
	 "unipaxId");

ALTER TABLE "UniPAX"."Evidence" ADD CONSTRAINT "Evidence_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."EvidenceCodeVoc" ADD CONSTRAINT "EvidenceCodeVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ExpForm" ADD CONSTRAINT "ExpForm_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ExpFormVoc" ADD CONSTRAINT "ExpFormVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."FragmentFtr" ADD CONSTRAINT "FragmentFtr_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."FunctionDef" ADD CONSTRAINT "FunctionDef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Gene" ADD CONSTRAINT "Gene_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."GeneticIntac" ADD CONSTRAINT "GeneticIntac_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ImportSource" ADD CONSTRAINT "ImportSource_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."InitialAsg" ADD CONSTRAINT "InitialAsg_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Intac" ADD CONSTRAINT "Intac_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."IntacVoc" ADD CONSTRAINT "IntacVoc_PK" PRIMARY KEY
	("controlledVocUnipaxId");

ALTER TABLE "UniPAX"."KineticLaw" ADD CONSTRAINT "KineticLaw_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."KPrime" ADD CONSTRAINT "KPrime_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."LocalParameter" ADD CONSTRAINT "LocalParameter_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Math" ADD CONSTRAINT "Math_PK" PRIMARY KEY
	("eventUnipaxId",
	 "eventAsgUnipaxId",
	 "triggerUnipaxId",
	 "ruleUnipaxId",
	 "priorityUnipaxId",
	 "delayUnipaxId",
	 "unipaxId");

ALTER TABLE "UniPAX"."Message" ADD CONSTRAINT "Message_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ModFtr" ADD CONSTRAINT "ModFtr_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Modulation" ADD CONSTRAINT "Modulation_PK" PRIMARY KEY
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."MolrIntac" ADD CONSTRAINT "MolrIntac_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Parameter" ADD CONSTRAINT "Parameter_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Pw" ADD CONSTRAINT "Pw_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."PwStep" ADD CONSTRAINT "PwStep_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."PhenotypeVoc" ADD CONSTRAINT "PhenotypeVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."PhysEntity" ADD CONSTRAINT "PhysEntity_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Priority" ADD CONSTRAINT "Priority_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Protein" ADD CONSTRAINT "Protein_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."ProteinRef" ADD CONSTRAINT "ProteinRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Provenance" ADD CONSTRAINT "Provenance_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."PubXref" ADD CONSTRAINT "PubXref_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."RateRule" ADD CONSTRAINT "RateRule_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."RelshpTypeVoc" ADD CONSTRAINT "RelshpTypeVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."RelshpXref" ADD CONSTRAINT "RelshpXref_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."Rna" ADD CONSTRAINT "Rna_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRef" ADD CONSTRAINT "RnaRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRegion" ADD CONSTRAINT "RnaRegion_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRegionRef" ADD CONSTRAINT "RnaRegionRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Rule" ADD CONSTRAINT "Rule_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SBase" ADD CONSTRAINT "SBase_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Score" ADD CONSTRAINT "Score_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SeqInterval" ADD CONSTRAINT "SeqInterval_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SeqLoc" ADD CONSTRAINT "SeqLoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SeqModVoc" ADD CONSTRAINT "SeqModVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SeqRegionVoc" ADD CONSTRAINT "SeqRegionVoc_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SeqSite" ADD CONSTRAINT "SeqSite_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SmallMol" ADD CONSTRAINT "SmallMol_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."SmallMolRef" ADD CONSTRAINT "SmallMolRef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Stoic" ADD CONSTRAINT "Stoic_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."TmpReac" ADD CONSTRAINT "TmpReac_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."TmpReacReg" ADD CONSTRAINT "TmpReacReg_PK" PRIMARY KEY
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."Thing" ADD CONSTRAINT "Thing_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."TissueVoc" ADD CONSTRAINT "TissueVoc_PK" PRIMARY KEY
	("controlledVocUnipaxId");

ALTER TABLE "UniPAX"."Tsp" ADD CONSTRAINT "Tsp_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."TspWithBchemReac" ADD CONSTRAINT "TspWithBchemReac_PK" PRIMARY KEY
	("transportUnipaxId",
	 "unipaxId");

ALTER TABLE "UniPAX"."Trigger" ADD CONSTRAINT "Trigger_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."UnificationXref" ADD CONSTRAINT "UnificationXref_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."Unit" ADD CONSTRAINT "Unit_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."UnitDef" ADD CONSTRAINT "UnitDef_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."UPBase" ADD CONSTRAINT "UPBase_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."UtilityClass" ADD CONSTRAINT "UtilityClass_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."Xref" ADD CONSTRAINT "Xref_PK" PRIMARY KEY
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."StringCollection" ADD CONSTRAINT "StringCollection_PK" PRIMARY KEY
	("unipaxId");

ALTER TABLE "UniPAX"."AlgebraicRule" ADD CONSTRAINT "AlgebraicRule_Rule_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Rule"
	("unipaxId");

ALTER TABLE "UniPAX"."AsgRule" ADD CONSTRAINT "AsgRule_Rule_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Rule"
	("unipaxId");

ALTER TABLE "UniPAX"."BindFtr" ADD CONSTRAINT "BindFtr_EntityFtr_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."BchemPwStep" ADD CONSTRAINT "BchemPwStep_PwStep_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PwStep"
	("unipaxId");

ALTER TABLE "UniPAX"."BchemReac" ADD CONSTRAINT "BchemReac_Conversion_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Conversion"
	("unipaxId");

ALTER TABLE "UniPAX"."BioSource" ADD CONSTRAINT "BioSource_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."Catalysis" ADD CONSTRAINT "Catalysis_Control_FK" FOREIGN KEY
	("interactionUnipaxId")
	REFERENCES "UniPAX"."Control"
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."CellLocVoc" ADD CONSTRAINT "CellLocVoc_CtrdVoc_FK" FOREIGN KEY
	("controlledVocUnipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."CellVoc" ADD CONSTRAINT "CellVoc_CtrdVoc_FK" FOREIGN KEY
	("controlledVocUnipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."ChemStruct" ADD CONSTRAINT "ChemStruct_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."Complex" ADD CONSTRAINT "Complex_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."ComplexAssembly" ADD CONSTRAINT "ComplexAssembly_Conversion_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Conversion"
	("unipaxId");

ALTER TABLE "UniPAX"."Constraint" ADD CONSTRAINT "Constraint_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Control" ADD CONSTRAINT "Control_Intac_FK" FOREIGN KEY
	("interactionUnipaxId")
	REFERENCES "UniPAX"."Intac"
	("unipaxId");

ALTER TABLE "UniPAX"."CtrdVoc" ADD CONSTRAINT "CtrdVoc_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."Conversion" ADD CONSTRAINT "Conversion_Intac_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Intac"
	("unipaxId");

ALTER TABLE "UniPAX"."CovalentBindFtr" ADD CONSTRAINT "CovalentBindFtr_BindFtr_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."BindFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."CovalentBindFtr" ADD CONSTRAINT "CovalentBindFtr_ModFtr_FK" FOREIGN KEY
	("modificationFtrUnipaxId")
	REFERENCES "UniPAX"."ModFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."Degradation" ADD CONSTRAINT "Degradation_Conversion_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Conversion"
	("unipaxId");

ALTER TABLE "UniPAX"."Delay" ADD CONSTRAINT "Delay_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."DeltaG" ADD CONSTRAINT "DeltaG_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."Dna" ADD CONSTRAINT "Dna_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRef" ADD CONSTRAINT "DnaRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRegion" ADD CONSTRAINT "DnaRegion_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."DnaRegionRef" ADD CONSTRAINT "DnaRegionRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."Entity" ADD CONSTRAINT "Entity_Thing_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Thing"
	("unipaxId");

ALTER TABLE "UniPAX"."EntityFtr" ADD CONSTRAINT "EntityFtr_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."EntityRef" ADD CONSTRAINT "EntityRef_EntityFtr_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."EntityRefTypeVoc" ADD CONSTRAINT "EntityRefTypeVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."Event" ADD CONSTRAINT "Event_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."EventAsg" ADD CONSTRAINT "EventAsg_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Evidence" ADD CONSTRAINT "Evidence_UtilityClass_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."EvidenceCodeVoc" ADD CONSTRAINT "EvidenceCodeVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."ExpForm" ADD CONSTRAINT "ExpForm_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."ExpFormVoc" ADD CONSTRAINT "ExpFormVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."FragmentFtr" ADD CONSTRAINT "FragmentFtr_EntityFtr_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."FunctionDef" ADD CONSTRAINT "FunctionDef_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Gene" ADD CONSTRAINT "Gene_Entity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Entity"
	("unipaxId");

ALTER TABLE "UniPAX"."GeneticIntac" ADD CONSTRAINT "GeneticIntac_Intac_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Intac"
	("unipaxId");

ALTER TABLE "UniPAX"."ImportSource" ADD CONSTRAINT "ImportSource_UtilityClass_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."InitialAsg" ADD CONSTRAINT "InitialAsg_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Intac" ADD CONSTRAINT "Intac_Entity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Entity"
	("unipaxId");

ALTER TABLE "UniPAX"."IntacVoc" ADD CONSTRAINT "IntacVoc_CtrdVoc_FK" FOREIGN KEY
	("controlledVocUnipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."KineticLaw" ADD CONSTRAINT "KineticLaw_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."KPrime" ADD CONSTRAINT "KPrime_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."LocalParameter" ADD CONSTRAINT "LocalParameter_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Math" ADD CONSTRAINT "Math_UPBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UPBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Message" ADD CONSTRAINT "Message_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."ModFtr" ADD CONSTRAINT "ModFtr_EntityFtr_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityFtr"
	("unipaxId");

ALTER TABLE "UniPAX"."Modulation" ADD CONSTRAINT "Modulation_Control_FK" FOREIGN KEY
	("interactionUnipaxId")
	REFERENCES "UniPAX"."Control"
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."MolrIntac" ADD CONSTRAINT "MolrIntac_Intac_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Intac"
	("unipaxId");

ALTER TABLE "UniPAX"."Parameter" ADD CONSTRAINT "Parameter_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Pw" ADD CONSTRAINT "Pw_Entity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Entity"
	("unipaxId");

ALTER TABLE "UniPAX"."PwStep" ADD CONSTRAINT "PwStep_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."PhenotypeVoc" ADD CONSTRAINT "PhenotypeVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."PhysEntity" ADD CONSTRAINT "PhysEntity_Entity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Entity"
	("unipaxId");

ALTER TABLE "UniPAX"."Priority" ADD CONSTRAINT "Priority_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Protein" ADD CONSTRAINT "Protein_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."ProteinRef" ADD CONSTRAINT "ProteinRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."Provenance" ADD CONSTRAINT "Provenance_UtilityClass_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."PubXref" ADD CONSTRAINT "PubXref_Xref_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."Xref"
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."RateRule" ADD CONSTRAINT "RateRule_Rule_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Rule"
	("unipaxId");

ALTER TABLE "UniPAX"."RelshpTypeVoc" ADD CONSTRAINT "RelshpTypeVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."RelshpXref" ADD CONSTRAINT "RelshpXref_Xref_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."Xref"
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."Rna" ADD CONSTRAINT "Rna_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRef" ADD CONSTRAINT "RnaRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRegion" ADD CONSTRAINT "RnaRegion_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."RnaRegionRef" ADD CONSTRAINT "RnaRegionRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."Rule" ADD CONSTRAINT "Rule_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."SBase" ADD CONSTRAINT "SBase_UPBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UPBase"
	("unipaxId");

ALTER TABLE "UniPAX"."Score" ADD CONSTRAINT "Score_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."SeqInterval" ADD CONSTRAINT "SeqInterval_SeqLoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SeqLoc"
	("unipaxId");

ALTER TABLE "UniPAX"."SeqLoc" ADD CONSTRAINT "SeqLoc_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."SeqModVoc" ADD CONSTRAINT "SeqModVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."SeqRegionVoc" ADD CONSTRAINT "SeqRegionVoc_CtrdVoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."SeqSite" ADD CONSTRAINT "SeqSite_SeqLoc_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SeqLoc"
	("unipaxId");

ALTER TABLE "UniPAX"."SmallMol" ADD CONSTRAINT "SmallMol_PhysEntity_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."PhysEntity"
	("unipaxId");

ALTER TABLE "UniPAX"."SmallMolRef" ADD CONSTRAINT "SmallMolRef_EntityRef_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."EntityRef"
	("unipaxId");

ALTER TABLE "UniPAX"."Stoic" ADD CONSTRAINT "Stoic_UtilityClass_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");

ALTER TABLE "UniPAX"."TmpReac" ADD CONSTRAINT "TmpReac_Intac_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Intac"
	("unipaxId");

ALTER TABLE "UniPAX"."TmpReacReg" ADD CONSTRAINT "TmpReacReg_Control_FK" FOREIGN KEY
	("interactionUnipaxId")
	REFERENCES "UniPAX"."Control"
	("interactionUnipaxId");

ALTER TABLE "UniPAX"."Thing" ADD CONSTRAINT "Thing_UPBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."UPBase"
	("unipaxId");

ALTER TABLE "UniPAX"."TissueVoc" ADD CONSTRAINT "TissueVoc_CtrdVoc_FK" FOREIGN KEY
	("controlledVocUnipaxId")
	REFERENCES "UniPAX"."CtrdVoc"
	("unipaxId");

ALTER TABLE "UniPAX"."Tsp" ADD CONSTRAINT "Tsp_Conversion_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Conversion"
	("unipaxId");

ALTER TABLE "UniPAX"."TspWithBchemReac" ADD CONSTRAINT "TspWithBchemReac_BchemReac_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."BchemReac"
	("unipaxId");

ALTER TABLE "UniPAX"."TspWithBchemReac" ADD CONSTRAINT "TspWithBchemReac_Tsp_FK" FOREIGN KEY
	("transportUnipaxId")
	REFERENCES "UniPAX"."Tsp"
	("unipaxId");

ALTER TABLE "UniPAX"."Trigger" ADD CONSTRAINT "Trigger_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."UnificationXref" ADD CONSTRAINT "UnificationXref_Xref_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."Xref"
	("utilityClassUnipaxId");

ALTER TABLE "UniPAX"."Unit" ADD CONSTRAINT "Unit_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."UnitDef" ADD CONSTRAINT "UnitDef_SBase_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."SBase"
	("unipaxId");

ALTER TABLE "UniPAX"."UtilityClass" ADD CONSTRAINT "UtilityClass_Thing_FK" FOREIGN KEY
	("unipaxId")
	REFERENCES "UniPAX"."Thing"
	("unipaxId");

ALTER TABLE "UniPAX"."Xref" ADD CONSTRAINT "Xref_UtilityClass_FK" FOREIGN KEY
	("utilityClassUnipaxId")
	REFERENCES "UniPAX"."UtilityClass"
	("unipaxId");


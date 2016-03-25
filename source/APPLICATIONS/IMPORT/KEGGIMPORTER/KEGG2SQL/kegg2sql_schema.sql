drop table if exists GeneEC;
create table GeneEC (
	ori varchar(5),
	geneID varchar(100),
	EC varchar(15),
	pathwayID varchar(10)
);

drop table if exists GeneName;
create table GeneName (
	ori varchar(5),
	ID varchar(100),
	name text
);

drop table if exists GeneSequence;
create table GeneSequence (
	ori varchar(5),
	ID varchar(100),
	seq text
);

drop table if exists GeneDescription;
create table GeneDescription (
	ori varchar(5),
	ID varchar(100),
	description text
);

drop table if exists GeneType;
create table GeneType (
	ori varchar(5),
	ID varchar(100),
	type varchar(10)
);

drop table if exists GeneProteinDBLink;
CREATE TABLE GeneProteinDBLink (
	ori varchar(5),
	ID varchar(100),
	dbName varchar(100),
	linkID varchar(100)
);

drop table if exists ProteinSequence;
create table ProteinSequence (
	ori varchar(5),
	ID varchar(100),
	seq text
);

drop table if exists Pathway;
create table Pathway (
	pathwayID varchar(10),
	pathwayName text
);

drop table if exists Reaction;
create table Reaction (
	reactionID varchar(10),
	equation text
);

drop table if exists ReactionEC;
create table ReactionEC (
	EC varchar(15),
	reactionID varchar(10)
);

drop table if exists ReactionPathway;
create table ReactionPathway (
	reactionID varchar(10),
	pathwayID varchar(10),
	direction varchar(3)
);

drop table if exists ReactionWithoutEC;
create table ReactionWithoutEC (
	reactionID varchar(10),
	nonEnzymatic integer
);

drop table if exists ReactionComment;
create table ReactionComment (
	reactionID varchar(10),
	reactionComment text
);


drop table if exists ECPathway;
create table ECPathway (
	EC varchar(15),
	pathwayID varchar(10)
);

drop table if exists Compound;
create table Compound (
	compoundID varchar(10)
);

drop table if exists CompoundMass;
create table CompoundMass (
	compoundID varchar(10),
	compoundMass double(14,4)
);

drop table if exists CompoundName;
create table CompoundName (
	compoundID varchar(10),
	compoundName text
);

drop table if exists CompoundFormula;
create table CompoundFormula (
	compoundID varchar(10),
	compoundFormula text
);

drop table if exists CompoundDBLink;
CREATE TABLE CompoundDBLink (
	compoundID varchar(10),
	dbName varchar(100),
	linkID varchar(100)
);

drop table if exists ReactionName;
create table ReactionName (
	reactionID varchar(10),
	reactionName text
);

drop table if exists ECName;
create table ECName (
	EC varchar(15),
	ECName text
);

drop table if exists EC;
create table EC (
	EC varchar(15)
);

drop table if exists ECDBLink;
CREATE TABLE ECDBLink (
	EC varchar(15),
	dbName varchar(100),
	linkID varchar(100)
);

drop table if exists Substrates;
create table Substrates (
	reactionID varchar(10),
	compoundID varchar(10),
	stoich_coeff INTEGER,
	type varchar(20)
);

drop table if exists Organisms;
create table Organisms(
	three_letter_code varchar(5),
	abbreviation varchar(100),
	full_name text,
	taxonomy varchar(8)
);

drop table if exists KOEntries;
create table KOEntries(
	ko_id varchar(10),
	name text,
	description text,
	ori varchar(5),
	kegg_id varchar(100)
);

drop table if exists KEGGMLEntries;
create table KEGGMLEntries(
	ori varchar(5),
	pathwayID varchar(10),
	entry_type varchar(100),
	entry_id varchar(100),
	kegg_id varchar(1000),
	component_id varchar(10)
);	

drop table if exists KEGGMLRelations;
create table KEGGMLRelations(
	ori varchar(5),
	pathwayID varchar(10),
	entry_id1 varchar(100),
	entry_id2 varchar(100),
	relation_type varchar(100),
	subtype varchar(100),
	subtype_value varchar(100)
);

drop table if exists KEGGMLReactions;
create table KEGGMLReactions(
	ori varchar(5),
	pathwayID varchar(10),
	entry_id varchar(100),
	kegg_id varchar(100),
	reaction_type varchar(100),
	substrate_type varchar(100),
	substrate_id varchar(100)
);

drop table if exists PathwayType;
create table PathwayType(
	pathwayID varchar(10),
	metabolic integer
);


create index koentries_index on KOEntries(ko_id,ori,kegg_id);


create index genesequence_index on GeneSequence(ori,ID);
create index proteinsequence_index on ProteinSequence(ori,ID);
create index genedescription_index on GeneDescription(ori,ID);
create index genetype_index on GeneType(ori,ID);
create index genename_index on GeneName(ori,ID);
create index geneproteindblink_index2 on GeneProteinDBLink(ori,ID);

create index geneec_ec_index on GeneEC(EC);
create index geneec_id_index on GeneEC(geneID);

create index pathway_index on Pathway(pathwayID);
create index pathwaytype_index on PathwayType(pathwayID);

create index reactionpathway_reaction_index on ReactionPathway(reactionID);
create index reactionpathway_pathway_index on ReactionPathway(pathwayID);


create index compound_index on Compound(compoundID);
create index compoundname_index on CompoundName(compoundID);
create index compoundmass_index on CompoundMass(compoundID);
create index compoundformula_index on CompoundFormula(compoundID);
create index compounddblink_index2 on CompoundDBLink(compoundID);

create index ecdblink_index2 on ECDBLink(EC);
create index ec_index on EC(EC);
create index ecname_index on ECName(EC);

create index reactionname_index on ReactionName(reactionID);
create index reaction_pathway_index on ReactionPathway(reactionID,pathwayID);

create index substrates_index on Substrates(reactionID);
create index substrates_index2 on Substrates(reactionID,compoundID);

create index reaction_id_index on Reaction(reactionID);
create index reactioncomment_index on ReactionComment(reactionID);

create index reactionec_ec_index on ReactionEC(EC);
create index reactionec_id_index on ReactionEC(reactionID);
create index reactionwithoutec_id_index on ReactionWithoutEC(reactionID);

create index compounddblink_index on CompoundDBLink(dbName);
create index ecdblink_index on ECDBLink(dbName);
create index geneproteindblink_index on GeneProteinDBLink(dbName);

create index keggmlentries_index on KEGGMLEntries(ori,pathwayID,entry_id);
create index keggmlrelations_index on KEGGMLRelations(ori,pathwayID);

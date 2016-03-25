#!/bin/sed -f

# this sed script should be applied to the oracle db schema to shorten the class names.

s/Reference/Ref/g
s/Definition/Def/g
s/Vocabulary/Voc/g
s/Sequence/Seq/g
s/Modification/Mod/g
s/Molecule/Mol/g
s/Reaction/Reac/g
s/Regulation/Reg/g
s/Location/Loc/g
s/Direction/Dir/g
s/Feature/Ftr/g
s/Experimental/Exp/g
s/Assignment/Asg/g
s/Biochemical/Bchem/g
s/Template/Tmp/g
s/Stoichiometry/Stoic/g
s/Pathway/Pw/g
s/Cellular/Cell/g
s/Controlled/Ctrd/g
s/Chemical/Chem/g
s/Structure/Struct/g
s/Molecular/Molr/g
s/Physical/Phys/g
s/Relationship/Relshp/g
s/Transport/Tsp/g
s/Binding/Bind/g
s/Interaction/Intac/g
s/pathway/pw/g

import sys, os,re,string, MySQLdb

import common

def parse_reactions(cursor, kegg_path):
	cursor.execute("TRUNCATE ReactionPathway")
	cursor.execute("TRUNCATE ReactionEC")
	cursor.execute("TRUNCATE ReactionWithoutEC")
	cursor.execute("TRUNCATE ReactionName")
	cursor.execute("TRUNCATE ReactionComment")
	cursor.execute("TRUNCATE Substrates")
	
	file = open(kegg_path+"ligand/reaction/reaction","r")
	
	definition = ""
	names = []
	reactionID=""
	pathwayID=""
	pathwayIDs=[]
	ec_numbers=[]
	in_enzyme_part=0
	equation=""
	comment = ""
	educts=[]
	products=[]
	non_enzymatic = 0
	substrate_types = {}
	sc={}
	
	line = file.readline()
	while (line):
		if line.startswith("ENTRY"):
			reactionID = line[12:18]
		elif line.startswith("NAME"):
			name = ""
			while line[0] == " " or line.startswith("NAME"):
				name = name + line[12:len(line)].strip() + " "
				line = file.readline()
			names = name.split("; ")
			continue
		elif line.startswith("DEFINITION"):
			while line[0] == " " or line.startswith("DEFINITION"):
				definition = definition + line[12:len(line)].strip() + " "
				line = file.readline()
			definition = definition.strip()
			continue
		elif line.startswith("PATHWAY"):
			while line[0] == " " or line.startswith("PATHWAY"):
				pathwayIDs.append(line[14:19])
				line = file.readline()
			continue
		elif line.startswith("ENZYME"):
			while line.startswith("ENZYME") or line[0] == " ":
				EC = re.findall("[0-9|-]+\.[0-9|-]+\.[0-9|-]+\.[0-9|-]+",line)
				for i in range(0,len(EC)):
					ec_numbers.append(EC[i])
				line = file.readline()
			continue
		elif line.startswith("COMMENT"):
			comment = ""
			while line[0] == " " or line.startswith("COMMENT"):
				comment = comment + line[12:len(line)].strip() + " "
				line = file.readline()
			comment = comment.strip()
			if len(re.findall("non enzymatic", comment)) > 0 or len(re.findall("spontaneous",comment)) > 0:
				non_enzymatic=1
			continue
		elif line.startswith("EQUATION"):
			equation = ""
			while line.startswith(" ") or line.startswith("EQUATION"):
				equation = equation + line[12:len(line)].strip() + " "
				line = file.readline()
				
			tmp = []
			if "<=>" in equation:
				tmp = equation.split("<=>")
			elif "=>" in equation:
				tmp = equation.split("=>")
			elif "<=" in equation:				
				tmp = equation.split("<=")
			
			educts = tmp[0].split(" + ")
			products = tmp[1].split(" + ")
			
			for k in range(0,len(educts)):
				sc_value = re.findall("[0-9]+ [C|G]", educts[k])
				
				if len(sc_value) > 0:
					sc_value = re.sub(" [C|G]","",sc_value[0])
				elif len(re.findall("[0-9]+n [C|G]",educts[k]))>0:
					sc_value = re.findall("[0-9]+n [C|G]",educts[k])
					sc_value = "-"+re.sub("n [C|G]","",sc_value[0])
				elif len(re.findall("n [C|G]",educts[k]))>0:
					sc_value = "-1"
				else:
					sc_value = "1"
					
				educts[k] = re.findall("[C|G][0-9][0-9][0-9][0-9][0-9]",educts[k])[0]
				substrate_types["%s" %(educts[k])] = "Educt"
				sc["%s" %(educts[k])] = sc_value
			for k in range(0,len(products)):
				sc_value = re.findall("[0-9]+ [C|G]",products[k])
				
				if len(sc_value) > 0:
					sc_value = re.sub(" [C|G]","",sc_value[0])
				elif len(re.findall("[0-9]+n [C|G]",products[k]))>0:
					sc_value = re.findall("[0-9]+n [C|G]",products[k])
					sc_value = "-" + re.sub("n [C|G]","",sc_value[0])
				elif len(re.findall("n [C|G]",products[k]))>0:
					sc_value = "-1"
				else:
					sc_value = "1"
				
				products[k] = re.findall("[C|G][0-9][0-9][0-9][0-9][0-9]", products[k])[0]
				substrate_types["%s" %(products[k])] = "Product"
				sc["%s" %(products[k])] = sc_value
			continue
		elif line.startswith("RPAIR"):
			while line[0] == " " or line.startswith("RPAIR"):
				split = line[21:len(line)].strip().split()
				
				if split[1] == "main":
					substrates = split[0].split("_")
					if substrate_types["%s" %(substrates[0])] == "Educt":
						substrate_types["%s" %(substrates[0])] = "MainEduct"
					elif substrate_types["%s" %(substrates[0])] == "Product":
						substrate_types["%s" %(substrates[0])] = "MainProduct"
						
					if substrate_types["%s" %(substrates[1])] == "Educt":
						substrate_types["%s" %(substrates[1])] = "MainEduct"
					elif substrate_types["%s" %(substrates[1])] == "Product":
						substrate_types["%s" %(substrates[1])] = "MainProduct"

				line = file.readline()
			continue
		elif line.startswith("///"):
			if (definition != ""):
				cursor.execute("INSERT INTO Reaction VALUES(%s, %s)", (reactionID, definition))
			else:
				cursor.execute("INSERT INTO Reaction VALUES(%s, NULL)", (reactionID))
				
			if len(pathwayIDs)>0:
				for i in range(0,len(pathwayIDs)):
					cursor.execute("INSERT INTO ReactionPathway VALUES(%s, %s,'<=>')", (reactionID, pathwayIDs[i]))
					
			if len(ec_numbers)>0:
				for i in range(0,len(ec_numbers)):
					cursor.execute("INSERT INTO ReactionEC VALUES (%s, %s)", (ec_numbers[i],reactionID))
			else:
				cursor.execute("INSERT INTO ReactionWithoutEC VALUES (%s, %s)", (reactionID, non_enzymatic))

			if len(names) > 0:
				for i in range(0,len(names)):
					cursor.execute("INSERT INTO ReactionName VALUES(%s, %s)", (reactionID, names[i]))
					
			if comment != "":
				cursor.execute("INSERT INTO ReactionComment VALUES(%s, %s)", (reactionID, comment))
			
			for k in range(0,len(educts)):
				cursor.execute("INSERT INTO Substrates VALUES(%s, %s, %s, %s)", (reactionID, educts[k], sc["%s" %(educts[k])], substrate_types["%s" %(educts[k])]) )
		
			for k in range(0,len(products)):
				cursor.execute("INSERT INTO Substrates VALUES(%s,%s,%s,%s)", (reactionID, products[k], sc["%s" %(products[k])], substrate_types["%s" %(products[k])]) )
				
			reactionID = ""
			pathwayIDs=[]
			ec_numbers=[]
			in_enzyme_part=0
			non_enzymatic = 0
			definition = ""
			names = []
			comment = ""
			substrates = []
			subtrate_types = {}
			sc = {}

		line = file.readline()
	file.close()
	
	file = open(kegg_path+"ligand/reaction/reaction_mapformula.lst","r")
	
	while (1):
		line = file.readline()
		if not line:
			break
		reactionID=re.findall("^[^:]+:",line)[0]
		reactionID=re.sub(":","",reactionID)
		pathwayID=re.findall(":\s.+:",line)[0]
		pathwayID=re.sub(":|\s","",pathwayID)
		direction=re.findall("<?=>?",line)[0]
		compounds=re.findall("[C|G][0-9][0-9][0-9][0-9][0-9]",line)
		cursor.execute("SELECT type from Substrates where reactionID=%s AND compoundID=%s", (reactionID,compounds[0]))
		res=cursor.fetchall()
		if len(res)>0:
			type=res[0][0]
			if type=="Product" or type=="SideProduct":
				if direction=="=>":
					direction="<="
				elif direction=="<=":
					direction="=>"
			cursor.execute("UPDATE ReactionPathway set direction=%s WHERE reactionID=%s AND pathwayID=%s", (direction,reactionID,pathwayID))
	file.close()
	

def parse_enzymes(cursor, kegg_path):
	cursor.execute("TRUNCATE EC")
	cursor.execute("TRUNCATE ECDBLink")
	cursor.execute("TRUNCATE ECPathway")
	cursor.execute("TRUNCATE ECName")
	cursor.execute("TRUNCATE GeneEC")
	
	file = open(kegg_path+"ligand/enzyme/enzyme","r")
	
	EC=""
	pathwayID=""
	pathwayIDs=[]
	name=""
	gene_ori=""
	names=[]
	found_name_key=0
	found_gene_key=0
	found_dblink_key=0
	found_org_key=0
	dbName=""
	linkID=""
	dbNames=[]
	linkIDs=[]
	
	genes = []
	origins = []
	line = file.readline()
	while (line):
		if line.startswith("ENTRY"):
			EC = re.findall("[0-9|-]+\.[0-9|-]+\.[0-9|-]+\.[0-9|-]+",line)[0]
		elif line.startswith("DBLINKS"):
			while line[0] == " " or line.startswith("DBLINKS"):
				line = line[12:len(line)].strip()
				split = line.split(":")
				if len(split) == 2:
					dbName = split[0].strip()
					split = split[1].split()
				for i in range(0, len(split)):
					dbNames.append(dbName)
					linkIDs.append(split[i].strip())
				line = file.readline()			
			continue;
		elif line.startswith("NAME"):
			name = ""
			while line[0] == " " or line.startswith("NAME"):
				name = name + line[12:len(line)].strip() + " "
				line = file.readline()
			names = name.split("; ")
			continue
		elif line.startswith("GENES"):
			while line[0] == " " or line.startswith("GENES"):
				line = line[12:len(line)].strip()
				split = line.split(":")
				if len(split) == 2:
					gene_ori = split[0].strip().lower()
					split = split[1].split()
				else:
					split = line.split()
				for i in range(0, len(split)):
					tmp = split[i].split("(")[0]
					if len(tmp) > 0:
						origins.append(gene_ori)
						genes.append(tmp)
				
				line = file.readline()
			continue
		## ignoring reference organisms
		elif line.startswith("///"):
			cursor.execute("INSERT INTO EC VALUES(%s)", (EC))
			for i in range(0,len(dbNames)):
				cursor.execute("INSERT INTO ECDBLink VALUES(%s, %s, %s)", (EC,dbNames[i],linkIDs[i]))
			if len(names)>0:
				for i in range(0,len(names)):
					cursor.execute("INSERT INTO ECName VALUES(%s, %s)", (EC, names[i]))
			if len(genes)>0:
				for i in range(0,len(genes)):
					geneID=genes[i]
					origin= origins[i]
					cursor.execute("INSERT INTO GeneEC VALUES (%s,%s,%s,NULL)", (origin,geneID,EC))
			genes=[]
			origins=[]
			names=[]
			found_name_key=0
			found_dblink_key=0
			found_gene_key=0
			found_org_key=0
			EC=""
			pathwayIDs=[]
			dbNames=[]
			linkIDs=[]
			
		line = file.readline()
	
	file.close()

def parse_compounds(cursor, kegg_path):
	cursor.execute("TRUNCATE Compound")
	cursor.execute("TRUNCATE CompoundDBLink")
	cursor.execute("TRUNCATE CompoundName")
	cursor.execute("TRUNCATE CompoundFormula")
	cursor.execute("TRUNCATE CompoundMass")
	
	file = open(kegg_path+"ligand/compound/compound","r")
	
	compoundId=""
	formula=""
	name=""
	names=[]
	found_name_key=0
	found_dblink_key=0
	dbName=""
	linkID=""
	dbNames=[]
	linkIDs=[]
	
	line = file.readline()
	while (line):
		if line.startswith("ENTRY"):
			compoundId=re.findall("C[0-9][0-9][0-9][0-9][0-9]",line)[0].strip();
		elif line.startswith("DBLINKS"):
			while line[0] == " " or line.startswith("DBLINKS"):
				line = line[12:len(line)].strip()
				split = line.split(":")
				if len(split) == 2:
					dbName = split[0].strip()
					split = split[1].split()
				for i in range(0, len(split)):
					dbNames.append(dbName)
					linkIDs.append(split[i].strip())
				line = file.readline()			
			continue;
		elif line.startswith("NAME"):
			name = ""
			while line[0] == " " or line.startswith("NAME"):
				name = name + line[12:len(line)].strip() + " "
				line = file.readline()
			names = name.split("; ")
			continue
		elif line.startswith("FORMULA"):
			formula = line[12:len(line)].strip()	
		elif line.startswith("///"):
			cursor.execute("INSERT INTO Compound VALUES(%s)", (compoundId))
			for i in range(0,len(dbNames)):
				cursor.execute("INSERT INTO CompoundDBLink VALUES(%s, %s, %s)", (compoundId,dbNames[i],linkIDs[i]))
			if len(names)>0:
				for i in range(0,len(names)):
					cursor.execute("INSERT INTO CompoundName VALUES(%s, %s)", (compoundId, names[i]))
			if formula != "":
				cursor.execute("INSERT INTO CompoundFormula VALUES(%s, %s)", (compoundId, formula))
			compoundId=""
			formula=""
			names=[]
			name = ""
			found_name_key=0
			found_dblink_key=0
			dbNames=[]
			linkIDs=[]
		
		line = file.readline()
	file.close()
	
	file = open(kegg_path+"ligand/glycan/glycan","r")
	
	compoundId=""
	name=""
	className=""
	mass=""
	composition=""
	names=""
	found_name_key=0
	found_dblink_key=0
	dbName=""
	linkID=""
	dbNames=[]
	linkIDs=[]
	line = file.readline()
	while (line):
		if line.startswith("ENTRY"):
			compoundId=re.findall("G[0-9][0-9][0-9][0-9][0-9]",line)[0].strip()
		elif line.startswith("DBLINKS"):
			while line[0] == " " or line.startswith("DBLINKS"):
				line = line[12:len(line)].strip()
				split = line.split(":")
				if len(split) == 2:
					dbName = split[0].strip()
					split = split[1].split()
				for i in range(0, len(split)):
					dbNames.append(dbName)
					linkIDs.append(split[i].strip())
				line = file.readline()			
			continue
		elif line.startswith("NAME"):
			name = ""
			while line[0] == " " or line.startswith("NAME"):
				name = name + line[12:len(line)].strip() + " "
				line = file.readline()
			names = name.split("; ")
			continue
		elif line.startswith("COMPOSITION"):
			composition = line[12:len(line)].strip()
		elif line.startswith("MASS"):
			mass = line[12:len(line)].strip()
			mass = mass.split()[0]
		elif line.startswith("CLASS"):
			className = line[12:len(line)].strip()
		elif line.startswith("///"):
			cursor.execute("INSERT INTO Compound VALUES(%s)", (compoundId))
			for i in range(0,len(dbNames)):
				cursor.execute("INSERT INTO CompoundDBLink VALUES(%s, %s, %s)", (compoundId,dbNames[i],linkIDs[i]))
			if len(names)>0:
				for i in range(0,len(names)):
					cursor.execute("INSERT INTO CompoundName VALUES(%s, %s)", (compoundId, names[i]))
			if className != "":
				cursor.execute("INSERT INTO CompoundName VALUES(%s, %s)", (compoundId, className))

			if composition != "":
				cursor.execute("INSERT INTO CompoundFormula VALUES(%s, %s)", (compoundId, composition))
				
			if mass != "":
				cursor.execute("INSERT INTO CompoundMass VALUES(%s, %s)", (compoundId, mass))
			
			compoundId=""
			formula=""
			className=""
			mass=""
			composition=""
			names=""
			found_name_key=0
			found_dblink_key=0
			dbNames=[]
			linkIDs=[]
		line = file.readline()
	
	file.close()
	



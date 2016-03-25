import sys, os,re,string, MySQLdb, os.path, errno

from operator import itemgetter, attrgetter

import common

def load_pathway_types(cursor, kegg_path, organisms, pathways):
	cursor.execute("TRUNCATE PathwayType")
	
	orgs = sorted(organisms, key=itemgetter('three_letter_code'))
	
	found_pathways = []
	
	pathways2 = []
	
	for i in range(0,len(pathways)):
		if os.path.isfile(kegg_path+"xml/kgml/metabolic/ko/ko"+pathways[i]+".xml"):
			cursor.execute("INSERT INTO PathwayType VALUES (%s, %s)", (pathways[i], 1))
			found_pathways.append(pathways[i])
		elif os.path.isfile(kegg_path+"xml/kgml/non-metabolic/ko/ko"+pathways[i]+".xml"):
			cursor.execute("INSERT INTO PathwayType VALUES (%s, %s)", (pathways[i], 0))
			found_pathways.append(pathways[i])
		else:
			pathways2.append(pathways[i])
			 
							
	for k in range(0,len(orgs)):
		origin = orgs[k]['three_letter_code']
		abbr = orgs[k]['abbreviation']
		abbr = abbr.lower()
		pathways3 = pathways2
		pathways2 = []
		for i in range(0,len(pathways3)):
			if os.path.isfile(kegg_path+"xml/kgml/metabolic/organisms/"+origin+"/"+origin+pathways3[i]+".xml"):
				cursor.execute("UPDATE PathwayType SET metabolic = %s WHERE pathwayID = %s", (1, pathways3[i]))
				found_pathways.append(pathways3[i])
			elif os.path.isfile(kegg_path+"xml/kgml/non-metabolic/organisms/"+origin+"/"+origin+pathways[i]+".xml"):
				found_pathways.append(pathways3[i])
				cursor.execute("UPDATE PathwayType SET metabolic = %s WHERE pathwayID = %s", (0, pathways3[i]))
			else:
				pathways2.append(pathways3[i])
				
		if len(pathways2) == 0:
			break
	return found_pathways
			
def parse_entry(cursor, origin, pathway, entry):
	entry_id = re.findall("id=\"\d+\"", entry)[0]
	entry_id = re.sub("id=", "", entry_id)
	entry_id = re.sub("\"", "", entry_id)
	
	entry_name = re.findall("name=\"[^\"]+\"",entry)[0]
	entry_name = re.sub("name=", "", entry_name)
	entry_name = re.sub("\"", "", entry_name)
	
	entry_type = re.findall("type=\"[^\"]+\"",entry)[0]
	entry_type = re.sub("type=", "", entry_type)
	entry_type = re.sub("\"", "", entry_type)
	
	kegg_ids = []
	
	if entry_type == "ortholog":
		entry_name = re.sub("ko:", "", entry_name) 
	elif entry_type == "gene":
		entry_name = re.sub(origin+":", "", entry_name)
	elif entry_type == "map":
		entry_name = re.sub("path:"+origin, "", entry_name)
	elif entry_type == "compound":
		entry_name = re.sub("cpd:", "", entry_name)
	elif entry_type == "group":
		entry_name = None
	elif entry_type == "other":
		return
	else:
		print "Unknown entry type", entry_type, "in entry from", origin, pathway
		return
	
	if entry_type != "group":
		kegg_ids = entry_name.split()
		for i in range(0, len(kegg_ids)):
			cursor.execute("INSERT INTO KEGGMLEntries VALUES (%s,%s,%s,%s,%s,%s)", (origin, pathway, entry_type, entry_id, kegg_ids[i], None))
	else:
		components = re.findall("component id=\"\d+\"", entry)
		for i in range(0, len(components)):
			c = re.sub("component id=", "", components[i])
			c = re.sub("\"", "", c)
			cursor.execute("INSERT INTO KEGGMLEntries VALUES (%s,%s,%s,%s,%s,%s)", (origin, pathway, entry_type, entry_id, None, c))
				
def parse_relation(cursor, origin, pathway, relation):
	entry_id1 = re.findall("entry1=\"\d+\"", relation)[0]
	entry_id1 = re.sub("entry1=", "", entry_id1)
	entry_id1 = re.sub("\"", "", entry_id1)
	
	entry_id2 = re.findall("entry2=\"\d+\"", relation)[0]
	entry_id2 = re.sub("entry2=", "", entry_id2)
	entry_id2 = re.sub("\"", "", entry_id2)
	
	relation_type = re.findall("type=\"[^\"]+\"",relation)[0]
	relation_type = re.sub("type=", "", relation_type)
	relation_type = re.sub("\"", "", relation_type)
	
	subtype_names = re.findall("name=\"[^\"]+\"",relation)
	subtype_values = re.findall("value=\"[^\"]*\"",relation)
	if len(subtype_names) != len(subtype_values):
		print "Length of subtype names and values do not match! (" + origin+pathway+")", relation
		return
	if len(subtype_names) > 0:
		for i in range(0, len(subtype_names)):
			t = re.sub("name=", "", subtype_names[i])
			t = re.sub("\"", "", t)
			v = re.sub("value=", "", subtype_values[i])
			v = re.sub("\"", "", v)
			v = re.sub("&gt;", ">", v)
			if v == "":
				v = None
			cursor.execute("INSERT INTO KEGGMLRelations VALUES (%s,%s,%s,%s,%s,%s,%s)", (origin, pathway, entry_id1, entry_id2, relation_type, t, v))
	else:
		cursor.execute("INSERT INTO KEGGMLRelations VALUES (%s,%s,%s,%s,%s, %s, %s)", (origin, pathway, entry_id1, entry_id2, relation_type, None, None))
	
def parse_reaction(cursor, origin, pathway, reaction):
	reaction_id = re.findall("id=\"\d+\"", reaction)[0]
	reaction_id = re.sub("id=", "", reaction_id)
	reaction_id = re.sub("\"", "", reaction_id)
	
	reaction_name = re.findall("name=\"[^\"]+\"",reaction)[0]
	reaction_name = re.sub("name=", "", reaction_name)
	reaction_name = re.sub("\"", "", reaction_name)
	
	reaction_type = re.findall("type=\"[^\"]+\"",reaction)[0]
	reaction_type = re.sub("type=", "", reaction_type)
	reaction_type = re.sub("\"", "", reaction_type)
	
	kegg_ids = re.sub("rn:", "", reaction_name).split()
	
	
	educts = re.findall("substrate id=\"\d+\"", reaction)
	products = re.findall("product id=\"\d+\"", reaction)
	
	for j in range(0, len(kegg_ids)):
		for i in range(0, len(educts)):
			e = re.sub("substrate id=", "", educts[i])
			e = re.sub("\"", "", e)
			cursor.execute("INSERT INTO KEGGMLReactions VALUES (%s,%s,%s,%s,%s,%s,%s)", (origin, pathway, reaction_id, kegg_ids[j], reaction_type, "educt", e))
		for i in range(0, len(products)):
			p = re.sub("product id=", "", products[i])
			p = re.sub("\"", "", p)
			cursor.execute("INSERT INTO KEGGMLReactions VALUES (%s,%s,%s,%s,%s,%s,%s)", (origin, pathway, reaction_id, kegg_ids[j], reaction_type, "product", p))
		

def parse_kgml_file(cursor, file, origin, pathway):
	try:
		file = open(file, "r")
		
		entry = ""
		relation = ""
		reaction = ""
		
		line = file.readline()
		while line:
			if string.find(line,"<relation")>-1:
				relation = line
			elif string.find(line,"<entry")>-1:
				entry = line
			elif string.find(line,"<reaction")>-1:
				reaction = line
			elif relation != "":
				relation = relation + line
			elif entry != "":
				entry = entry + line
			elif reaction != "":
				reaction = reaction + line
			
			if string.find(line,"</relation>")>-1:
				parse_relation(cursor, origin, pathway, relation)
				relation = ""
			elif string.find(line,"</entry>")>-1:
				parse_entry(cursor, origin, pathway, entry)
				entry = ""
			elif string.find(line,"</reaction>")>-1:
				parse_reaction(cursor, origin, pathway, reaction)
				reaction = ""
					
			line = file.readline()
		file.close()
		return True
	except IOError, err:
		if err.errno != errno.ENOENT:
			print "Error while loading file", file
			raise
		#else:
		#	print err
		
	return False
	

def parse_kgml(cursor, kegg_path, organisms, pathways):
	cursor.execute("TRUNCATE KEGGMLRelations")
	cursor.execute("TRUNCATE KEGGMLEntries")
	cursor.execute("TRUNCATE KEGGMLReactions")
	orgs = sorted(organisms, key=itemgetter('three_letter_code'))
	
	# Loading reference pathways
	print "\t Loading reference pathways...",
	sys.stdout.flush()
	m = 0
	nm = 0
	
	for i in range(0,len(pathways)):
		metabolic = parse_kgml_file(cursor, kegg_path+"xml/kgml/metabolic/ko/ko"+pathways[i]+".xml", "ko", pathways[i])
		
		if metabolic:
			m = m + 1
		else:
			nonmetabolic = parse_kgml_file(cursor, kegg_path+"xml/kgml/non-metabolic/ko/ko"+pathways[i]+".xml", "ko", pathways[i])
			if nonmetabolic:
				nm = nm + 1
	
	print " found ", m, " metabolic and ", nm, " non-metabolic pathways."
				
	# Loading pathways...
	for k in range(0,len(orgs)):
		origin = orgs[k]['three_letter_code']
		abbr = orgs[k]['abbreviation']
		abbr = abbr.lower()
		print "\t Processing: ", abbr, " (", (k+1), "/", len(orgs),")... ",
		sys.stdout.flush()
		m = 0
		nm = 0

		for i in range(0,len(pathways)):
			metabolic = parse_kgml_file(cursor, kegg_path+"xml/kgml/metabolic/organisms/"+origin+"/"+origin+pathways[i]+".xml", origin, pathways[i])
			if metabolic:
				m = m + 1
			else:
				nonmetabolic = parse_kgml_file(cursor, kegg_path+"xml/kgml/non-metabolic/organisms/"+origin+"/"+origin+pathways[i]+".xml", origin, pathways[i])
				
				if nonmetabolic:
					nm = nm + 1
					
		print " found ", m, " metabolic and ", nm, " non-metabolic pathways."
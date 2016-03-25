import sys, os,re,string, MySQLdb
from operator import itemgetter, attrgetter
import gzip

def load_organisms(cursor, kegg_path):
	cursor.execute("TRUNCATE Organisms")
	preset_organisms = []
	
	if len(sys.argv) > 5:
		print "Will only load given organisms."
		for i in range(5,len(sys.argv)):
			preset_organisms.append(sys.argv[i])
	
	organisms = []
	
	file = open(kegg_path+"genes/taxonomy","r")
	i=0
	while (1):
		line = file.readline()
		if not line:
			break
		if line[0] != "#":
			res = line.strip().split("\t");
			ent = res[0].split("(")[0]
			try:
				if len(preset_organisms) == 0 or res[1] in preset_organisms:
					f = open(kegg_path+"genes/genes/%s.ent" %ent,"rb")
					cursor.execute("INSERT INTO Organisms VALUES (%s, %s, %s, %s)", (res[1],res[2],res[3],ent))
					organisms.append({})
					organisms[i]['ent']=ent
					organisms[i]['three_letter_code']=res[1]
					organisms[i]['abbreviation']=res[2]
					organisms[i]['full_name']=res[3]
					organisms[i]['file'] = kegg_path+"genes/genes/%s.ent" %ent
					i=i+1
					f.close()
			except IOError:
				try:
					f = open(kegg_path+"genes/genes/%s" %(res[2].lower()),"rb")
					cursor.execute("INSERT INTO Organisms VALUES (%s, %s, %s, %s)", (res[1],res[2],res[3],ent))
					organisms.append({})
					organisms[i]['ent']=ent
					organisms[i]['three_letter_code']=res[1]
					organisms[i]['abbreviation']=res[2]
					organisms[i]['full_name']=res[3]
					organisms[i]['file'] = kegg_path+"genes/genes/%s" %(res[2].lower())
					i=i+1
					f.close()
				except IOError:
					print "Skipping organism", res[3], "("+ent+")"
	file.close()
	print "Found ", i, " organisms."
	return organisms


def parse_ko(cursor, kegg_path):
	cursor.execute("TRUNCATE KOEntries")
	file = open(kegg_path+"genes/ko/ko","r")
	
	
	ko=""
	name=""
	description=""
	found_gene_key=0
	gene_ori=""
	genes=[]
	origins=[]
	
	line = file.readline()
	while (line):
		if line.startswith("ENTRY"):
			ko = re.findall("K[0-9]+",line)[0]
		elif line.startswith("NAME"):
			name = line[12:len(line)].strip()
		elif line.startswith("DEFINITION"):
			description = ""
			while line[0] == " " or line.startswith("DEFINITION"):
				description = description + line[12:len(line)].strip() + " "
				line = file.readline()
			description = description.strip()
			continue
		elif line.startswith("GENES"):
			while line[0] == " " or line.startswith("GENES"):
				if line[12] != " ":
					gene_ori = line[12:15].lower()
				
				split = line[17:len(line)].split()
								
				for i in range(0, len(split)):
					tmp = split[i].split("(")[0]
					if len(tmp) > 0:
						origins.append(gene_ori)
						genes.append(tmp)
				
				line = file.readline()
			continue
		elif line.startswith("///"):
			if ko != "":
				for  i in range(0,len(genes)):
					cursor.execute("INSERT INTO KOEntries VALUES(%s, %s, %s, %s, %s)", (ko,name,description,origins[i],genes[i]))
			genes = []
			origins = []
			ko = ""
			name = ""
			description = ""
		line = file.readline()
	file.close()
	
def parse_genes(cursor, kegg_path, organisms):
	cursor.execute("TRUNCATE GeneType")
	cursor.execute("TRUNCATE GeneName")
	cursor.execute("TRUNCATE GeneSequence")
	cursor.execute("TRUNCATE ProteinSequence")
	cursor.execute("TRUNCATE GeneProteinDBLink")
	
	orgs = sorted(organisms, key=itemgetter('ent'))
	
	for k in range(0,len(orgs)):
		origin=orgs[k]['three_letter_code']
		abbr=orgs[k]['abbreviation']
		ent=orgs[k]['ent']
		#abbr=abbr.lower()
	
		print "\t processing: ", abbr, " (", (k+1), "/", len(orgs),") ..."
		
		try:
			file_genes = open(orgs[k]['file'],"rb")
	
			ID = ""
			names = []
			type = ""
			descriptions = []
			nuc_sequence = ""
			aa_sequence = ""
			dbNames=[]
			linkIDs=[]
	
			line = file_genes.readline()
			while(line):
				if line.startswith("ENTRY"):
					split = line.split()
					ID = split[1].strip()
					type = split[2].strip()
				elif line.startswith("NAME"):
					name = ""
					while line:
						name = name + line[12:len(line)].strip()
						line = file_genes.readline()
						if line[0] != " ":
							break
						name = name + ", "
						
					names = name.split(", ")
					continue
				elif line.startswith("DEFINITION"):
					description = ""
					while line:
						description = description + line[12:len(line)].strip() + " "
						line = file_genes.readline()
						if line[0] != " ":
							break
						
					description = description.strip()
					descriptions.append(description)
					continue
				elif line.startswith("ORTHOLOGY"):
					description = ""
					while line:
						description = description + line[12:len(line)].strip() + " "
						line = file_genes.readline()
						if line[0] != " ":
							break
						
					description = description.strip()
					descriptions.append(description)
					continue
				elif line.startswith("NTSEQ"):
					nuc_sequence = ""
					# skip length attribute
					line = file_genes.readline()
					while line:
						nuc_sequence = nuc_sequence + line[12:len(line)].strip()
						line = file_genes.readline()
						if line[0] != " ":
							break
					continue
				elif line.startswith("AASEQ"):
					aa_sequence = ""
					# skip length attribute
					line = file_genes.readline()
					while line:
						aa_sequence = aa_sequence + line[12:len(line)].strip()
						line = file_genes.readline()
						if line[0] != " ":
							break
					continue
				elif line.startswith("ORTHOLOGY"):
					dbNames.append("KO");
					linkID = line.split()[1]
					linkIDs.append(linkID)
				elif line.startswith("DBLINKS"):
					while line:
						tmp = line[12:len(line)]
						if tmp[0] != " ":
							tmp = tmp.split(":", 1)
							dbName = tmp[0]
							tmp = tmp[1]
						
						split = tmp.split() 
										
						for i in range(0, len(split)):
							tmp = split[i].split("(")[0]
							if len(tmp) > 0:
								dbNames.append(dbName)
								linkIDs.append(tmp)
						
						line = file_genes.readline()
						if line[0] != " ":
							break
					continue		
				elif line.startswith("///"):
					cursor.execute("INSERT INTO GeneType VALUES(%s, %s, %s)", (origin, ID, type))
	
					if len(names) > 0:
						for i in range(0, len(names)):
							cursor.execute("INSERT INTO GeneName VALUES(%s, %s, %s)", (origin, ID, names[i]))
							
					if len(descriptions) > 0:
						for i in range(0, len(descriptions)):
							cursor.execute("INSERT INTO GeneDescription VALUES(%s, %s, %s)", (origin, ID, descriptions[i]))
	
					if nuc_sequence != "":
						cursor.execute("INSERT INTO GeneSequence VALUES(%s, %s, %s)", (origin, ID, nuc_sequence))
	
					if aa_sequence != "":
						cursor.execute("INSERT INTO ProteinSequence VALUES(%s, %s, %s)", (origin, ID, aa_sequence))
	
					if len(dbNames) > 0:
						for i in range(0,len(dbNames)):
							cursor.execute("INSERT INTO GeneProteinDBLink VALUES(%s, %s, %s, %s)", (origin,ID,dbNames[i],linkIDs[i]))
	
					nuc_sequence = ""
					aa_sequence = ""
					names = []
					ID = ""
					type = ""
					descriptions = []
					dbNames=[]
					linkIDs=[]
				line = file_genes.readline()
		
			file_genes.close()
			
		except IOError, e:
			if err.errno == errno.ENOENT:
				print "cannot open: " + kegg_path + "genes/%s\n" %abbr
			else:
				raise 


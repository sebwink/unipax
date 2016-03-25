import sys, os,re,string, MySQLdb

def load_pathways(cursor, path):
	file = open(path + "pathway/map_title.tab","r")
	
	pathways=[]
	line = file.readline()
	while (line):
		split = line.split("\t")
		pathwayID = split[0].strip()
		pathwayName = split[1].strip()
		
		pathways.append(pathwayID)
		line = file.readline()
	
	file.close()
	return pathways
	
def write_pathways(cursor, path, pathways):
	cursor.execute("TRUNCATE Pathway")
	file = open(path + "pathway/map_title.tab","r")
	
	pathway_map = {}
	line = file.readline()
	while (line):
		split = line.split("\t")
		pathwayID = split[0].strip()
		pathwayName = split[1].strip()
		
		pathway_map[pathwayID] = pathwayName
		
		line = file.readline()
	
	file.close()
	
	for i in pathways:
		cursor.execute("INSERT INTO Pathway VALUES (%s, %s)", (i, pathway_map[i]))
		
	return pathways

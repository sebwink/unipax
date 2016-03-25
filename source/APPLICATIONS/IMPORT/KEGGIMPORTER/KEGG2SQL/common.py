import sys, os,re,string, MySQLdb, urllib2

def connect(host, user, passwd, db):
	print "Init database...",
	try:
		# create a connection to the database
		db = MySQLdb.connect(host, user, passwd, db)
		
		# get a database cursor from that connection
		cursor = db.cursor()
		print "ok."
		return cursor
	except:
		print "failed. Unable to connect to database."
		sys.exit()

def db_query(statement):
	cursor.execute(statement)
	return cursor.fetchall()
	
def db_query(statement, args):
	cursor.execute(statement, args)
	return cursor.fetchall()


def check_files(kegg_path):
	
	print "Checking for necessary files in", kegg_path + "...", 
	
	"""
	at least, the following files and directories are needed:
	
	genes/taxonomy
	pathway/map_title.tab
	ligand/reaction/reaction
	ligand/reaction/reaction_map_formula.lst
	ligand/enzyme/enzyme
	ligand/compound/compound
	ligand/glycan/glycan
	genes/ko/ko
	
	kgml/metabolic/organisms/**/*
	kgml/metabolic/ko/*
	kgml/non-metabolic/organisms/**/*
	kgml/non-metabolic/ko/*
	"""
	
	if not os.path.isfile(kegg_path+"genes/taxonomy"):
		print "Error: File 'genes/taxonomy' not found."
		return False
	
	if not os.path.isfile(kegg_path+"pathway/map_title.tab"):
		print "Error: File 'pathway/map_title.tab' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/reaction/reaction"):
		print "Error: File 'ligand/reaction/reaction' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/reaction/reaction_mapformula.lst"):
		print "Error: File 'ligand/reaction/reaction_mapformula.lst' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/enzyme/enzyme"):
		print "Error: File 'ligand/enzyme/enzyme' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/compound/compound"):
		print "Error: File 'ligand/compound/compound' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/glycan/glycan"):
		print "Error: File 'ligand/glycan' not found."
		return False
		
	if not os.path.isfile(kegg_path+"genes/ko/ko"):
		print "Error: File 'genes/ko/ko' not found."
		return False
		
	if not os.path.isdir(kegg_path+"xml/kgml"):
		print "Error: Directory 'xml/kgml' not found."
		return False
		
	if not os.path.isdir(kegg_path+"xml/kgml/metabolic"):
		print "Error: Directory 'xml/kgml/metabolic' not found."
		return False
		
	if not os.path.isdir(kegg_path+"xml/kgml/non-metabolic"):
		print "Error: Directory 'xml/kgml/non-metabolic' not found."
		return False
	
	if not os.path.isdir(kegg_path+"xml/kgml/metabolic/ko"):
		print "Error: Directory 'xml/kgml/metabolic/ko' not found."
		return False
		
	if not os.path.isdir(kegg_path+"xml/kgml/non-metabolic/ko"):
		print "Error: Directory 'xml/kgml/non-metabolic/ko' not found."
		return False
	
	if not os.path.isdir(kegg_path+"xml/kgml/metabolic/organisms"):
		print "Error: Directory 'xml/kgml/metabolic/organisms' not found."
		return False
		
	if not os.path.isdir(kegg_path+"xml/kgml/non-metabolic/organisms"):
		print "Error: Directory 'xml/kgml/non-metabolic/organisms' not found."
		return False
		
	print "ok."
	return True

def download(url, target):
	u = urllib2.urlopen(url)
	f = open(target, 'w')
	meta = u.info()
	file_size = int(meta.getheaders("Content-Length")[0])
	print "Downloading %s to %s (%s bytes)" % (url, target, file_size)

	file_size_dl = 0
	block_sz = 8192
	while True:
		buffer = u.read(block_sz)
		if not buffer:
			break
		file_size_dl += block_sz
		f.write(buffer)
		status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
		status = status + chr(8)*(len(status)+1)
		print status,
	f.close()


def download_missing_files(kegg_path):
	
	
	
	print "Downloading missing files from KEGG..." 
	
	"""
	at least, the following files and directories are needed:
	
	genes/taxonomy
	pathways/map_title.tab
	ligand/reaction
	ligand/reaction_map_formula.lst
	ligand/enzyme
	ligand/compound
	ligand/glycan
	genes/ko
	
	kgml/metabolic/organisms/**/*
	kgml/metabolic/ko/*
	kgml/non-metabolic/organisms/**/*
	kgml/non-metabolic/ko/*
	"""
	
	if not os.path.isfile(kegg_path+"genes/taxonomy"):
		download("ftp://ftp.pathway.jp/genes/taxonomy", kegg_path+"genes/taxonomy");
	if not os.path.isfile(kegg_path+"genes/taxonomy"):
		print "Error: Unable to download file 'genes/taxonomy'."
		return False
	
	if not os.path.isfile(kegg_path+"pathway/map_title.tab"):
		os.mkdir(kegg_path+"pathway/")
		download("ftp://ftp.pathway.jp/pathway/map_title.tab", kegg_path+"pathway/map_title.tab");
	if not os.path.isfile(kegg_path+"pathway/map_title.tab"):
		print "Error: File 'pathways/map_title.tab' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/reaction"):
		download("ftp://ftp.pathway.jp/ligand/reaction/reaction", kegg_path+"ligand/reaction/reaction");
	if not os.path.isfile(kegg_path+"ligand/reaction"):
		print "Error: File 'ligand/reaction' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/reaction_mapformula.lst"):
		download("ftp://ftp.pathway.jp/ligand/reaction/reaction_mapformula.lst", kegg_path+"ligand/reaction/reaction_mapformula.lst");
	if not os.path.isfile(kegg_path+"ligand/reaction_mapformula.lst"):
		print "Error: File 'ligand/reaction_mapformula.lst' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/enzyme"):
		download("ftp://ftp.pathway.jp/ligand/enzyme/enzyme", kegg_path+"ligand/enzyme/enzyme");
	if not os.path.isfile(kegg_path+"ligand/enzyme"):
		print "Error: File 'ligand/enzyme' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/compound"):
		download("ftp://ftp.pathway.jp/ligand/compound/compound", kegg_path+"ligand/compound/compound");
	if not os.path.isfile(kegg_path+"ligand/compound"):
		print "Error: File 'ligand/compound' not found."
		return False
	
	if not os.path.isfile(kegg_path+"ligand/glycan"):
		download("ftp://ftp.pathway.jp/ligand/glycan/glycan", kegg_path+"ligand/glycan/glycan");
	if not os.path.isfile(kegg_path+"ligand/glycan"):
		print "Error: File 'ligand/glycan' not found."
		return False
		
	if not os.path.isfile(kegg_path+"genes/ko"):
		download("ftp://ftp.pathway.jp/genes/ko", kegg_path+"genes/ko");
	if not os.path.isfile(kegg_path+"genes/ko"):
		print "Error: File 'genes/ko' not found."
		return False
		
	if not os.path.isdir(kegg_path+"kgml"):
		print "Error: Directory 'kgml' not found."
		return False
		
	if not os.path.isdir(kegg_path+"kgml/metabolic"):
		print "Error: Directory 'kgml/metabolic' not found."
		return False
		
	if not os.path.isdir(kegg_path+"kgml/non-metabolic"):
		print "Error: Directory 'kgml/non-metabolic' not found."
		return False
	
	if not os.path.isdir(kegg_path+"kgml/metabolic/ko"):
		print "Error: Directory 'kgml/metabolic/ko' not found."
		return False
		
	if not os.path.isdir(kegg_path+"kgml/non-metabolic/ko"):
		print "Error: Directory 'kgml/non-metabolic/ko' not found."
		return False
	
	if not os.path.isdir(kegg_path+"kgml/metabolic/organisms"):
		print "Error: Directory 'kgml/metabolic/organisms' not found."
		return False
		
	if not os.path.isdir(kegg_path+"kgml/non-metabolic/organisms"):
		print "Error: Directory 'kgml/non-metabolic/organisms' not found."
		return False
		
	print "ok."
	return True



def perform_joins(cursor):
	cursor.execute("drop table if exists join1")
	cursor.execute("drop table if exists join2")
	cursor.execute("drop table if exists join3")
	cursor.execute("drop table if exists join4")
	cursor.execute("drop table if exists join5")
	cursor.execute("drop table if exists join6")
	cursor.execute("drop table if exists join7")
	cursor.execute("drop table if exists join8")
	
	sql="create table join1 \
	     select distinct gec.ori, rp.pathwayID, rec.reactionID, r.equation, rp.direction \
	     from GeneEC gec, ReactionEC rec, ReactionPathway rp, Reaction r \
	     where gec.EC = rec.EC and rp.reactionID = rec.reactionID \
	     and r.reactionID=rec.reactionID"
	cursor.execute(sql) 

	
	sql="create table join2 \
	     select distinct gec.ori, rp.pathwayID, rec.reactionID, gec.geneID, gec.EC \
	     from GeneEC gec, ReactionEC rec, ReactionPathway rp \
	     where gec.EC = rec.EC and rp.reactionID = rec.reactionID" 
	cursor.execute(sql)

	sql="create table join3 \
	     select distinct gec.ori, p.pathwayID, p.pathwayName, pt.metabolic \
	     from GeneEC gec, Pathway p, PathwayType pt, ReactionPathway rp, ReactionEC rec \
	     where p.pathwayID = pt.pathwayID and p.pathwayID = rp.pathwayID and rp.reactionID = rec.reactionID and gec.EC = rec.EC"
	cursor.execute(sql)
	
	
	sql="create table join4 \
	     select distinct rp.pathwayID, rp.reactionID, re.EC, r.equation, rp.direction \
	      from ReactionPathway rp, ReactionEC re, Reaction r \
	      where rp.reactionID = re.reactionID and r.reactionID=rp.reactionID"
	cursor.execute(sql)

	sql="create table join5 \
		select distinct re.reactionID, re.EC, r.equation, rp.direction \
		from (ReactionEC re join Reaction r on re.reactionID = r.reactionID) left outer join  ReactionPathway rp on r.reactionID=rp.reactionID"
	cursor.execute(sql)
	
	sql="create table join6 \
	     select distinct rp.pathwayID, rp.reactionID, r.equation, rp.direction, rwe.nonEnzymatic \
		 from ReactionPathway rp, ReactionWithoutEC rwe, Reaction r \
		 where rp.reactionID = rwe.reactionID  \
		     and r.reactionID=rp.reactionID"
	cursor.execute(sql)
	
	sql="create table join7 \
	    select distinct rwe.reactionID, r.equation, rp.direction, rwe.nonEnzymatic \
		    from (ReactionWithoutEC rwe join Reaction r on rwe.reactionID = r.reactionID) left outer join  ReactionPathway rp on r.reactionID=rp.reactionID"
	cursor.execute(sql)
	
	sql="create table join8 \
	     select distinct gec.ori, rec.reactionID \
		 from GeneEC gec, ReactionEC rec \
		 where gec.EC = rec.EC"
	cursor.execute(sql)
	
	sql="create index join1_index on join1(ori)"
	cursor.execute(sql)
	sql="create index join1b_index on join1(ori,reactionID)"
	cursor.execute(sql)
	sql="create index join2_index on join2(ori,pathwayID, reactionID)"
	cursor.execute(sql)
	sql="create index join2b_index on join2(ori,pathwayID)"
	cursor.execute(sql)
	sql="create index join3_index on join3(ori)"
	cursor.execute(sql)
	sql="create index join4_index on join4(pathwayID)"
	cursor.execute(sql)
	sql="create index join4b_index on join4(reactionID, EC, direction)"
	cursor.execute(sql)
	sql="create index join6_index on join6(pathwayID)"
	cursor.execute(sql)
	sql="create index join6b_index on join6(reactionID, direction)"
	cursor.execute(sql)
	sql="create index join8_index on join8(ori)"
	cursor.execute(sql)


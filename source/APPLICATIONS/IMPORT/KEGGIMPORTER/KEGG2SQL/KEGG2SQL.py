import sys, os,re,string, MySQLdb, getpass, gc

import common, genes, pathways, ligand, kgml

if len(sys.argv) < 5:
	print "Usage:", sys.argv[0], "<host>", "<user>", "<dbname>", "<path>", "[ori]+"
	print "\t Important: without any given ori, all organisms will be imported!"
	print ""
	print "\t Don't forget to create a database and load the kegg2sql_schema.sql file."
	sys.exit()
	
host = sys.argv[1]
user = sys.argv[2]
db = sys.argv[3]
kegg_path = sys.argv[4]

if not kegg_path.endswith("/"):
	kegg_path = kegg_path + "/"


gc.enable()

print ""
print "Welcome to the KEGG flat file parser."
print ""

if not common.check_files(kegg_path):
	if input("Download missing files? (y/n) ") == "y":
		if not common.download_missing_files(kegg_path):
			sys.exit()
	
print ""
print "Using database: ", user + "@" + host + "/" + db

print ""
print "Warning: this script will take some hours!"
print ""

passwd = getpass.getpass("Database password:")

cursor = common.connect(host, user, passwd, db)

# It is possible to skip some steps, if the import fails - just comment them out. 

# 1. always required
print "Loading organisms..."
organisms = genes.load_organisms(cursor, kegg_path)

# 2. always required
print "Loading pathways..."
paths = pathways.load_pathways(cursor, kegg_path)

# 3. will write the loaded pathways, this step is only required once
paths = kgml.load_pathway_types(cursor, kegg_path, organisms, paths)
pathways.write_pathways(cursor, kegg_path, paths)

# 4. will load and write all reactions, this step is only required once
print "Parsing reactions..."
ligand.parse_reactions(cursor, kegg_path)

# 5. will load and write all enzymes, this step is only required once
print "Parsing enzymes..."
ligand.parse_enzymes(cursor, kegg_path)

# 6. will load and write all compounds, this step is only required once
print "Parsing compounds..."
ligand.parse_compounds(cursor, kegg_path)

# 7. will load and write the kegg orthology, this step is only required once
print "Parsing ko..."
genes.parse_ko(cursor, kegg_path)

# 8. will load and write all genes of all organisms, this step is only required once
print "Parsing genes..."
genes.parse_genes(cursor, kegg_path, organisms)

# 9. will load and write all kgml pathways of all organisms, this step is only required once
print "Parsing kgml..."
kgml.parse_kgml(cursor, kegg_path, organisms, paths)

# 10. will join some tables, this step is only required if steps 3 to 8 have been executed
print "Joining tables..."
common.perform_joins(cursor)

cursor.close()
print "Successfully imported KEGG."

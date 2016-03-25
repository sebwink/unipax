#include <UNIPAX/IMPORT/BIOPAX/BIOPAXReader.h>
#include <UNIPAX/IMPORT/GRAPHML/GraphMLWriter.h>
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>

#include <string>
#include <iostream>

int main(int argc, const char* argv[])
{
	std::string filename;
	if (argc > 1)
		filename = argv[1];
	else
		std::cin >> filename;
	UniPAX::BIOPAXReader reader;
//	reader.setDebug(true);
	reader.createObjectsOnly(true);
	reader.setFilename(filename);
	reader.parse();

	std::cout << "Number of parsed objects (first round): " << reader.getData().size() << std::endl;

	reader.createObjectsOnly(false);
	reader.parse();

	std::cout << "Number of parsed objects: " << reader.getData().size() << std::endl;


	std::cout << "Start GraphML export" << std::endl;

	UniPAX::GraphMLWriter writer;
//	writer.setDebug(true);
	writer.setPersistenceManager(reader.getPersistenceManager());
	writer.write("export.graphml");


	std::cout << "done !" << std::endl;

	return 0;
}

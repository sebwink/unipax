#include <UNIPAX/IMPORT/BridgeDBWrapper.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <boost/filesystem.hpp>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <iostream>

class PublicBridgeDBWrapper : public UniPAX::BridgeDBWrapper
{
	public:
		PublicBridgeDBWrapper() : UniPAX::BridgeDBWrapper() {}
		PublicBridgeDBWrapper(std::string configFile) : UniPAX::BridgeDBWrapper(configFile) {}
		std::string getExecutablePath() { return executablePath; }
		std::string getMappingFilePath() { return mappingFilePath; }
		std::string getTmpFilePath() { return tmpFilePath; }
		std::map<std::string, std::string> & getIdSystems() { return idSystems; }
};

class TestBridgeDBWrapper : public ::testing::Test
{
	public:
		TestBridgeDBWrapper()
		{
		}

		virtual ~TestBridgeDBWrapper() {}

	protected:
		virtual void SetUp()
		{
			// set up config file
			std::cout << "Working dir is: " << boost::filesystem::current_path().string() << std::endl;

			bool found = false;
			for (boost::filesystem::recursive_directory_iterator itr(boost::filesystem::current_path().parent_path().parent_path());
								itr != boost::filesystem::recursive_directory_iterator();
						        ++itr)
						{
							std::string tmp_name = itr->path().string();
							if (boost::filesystem::is_directory(itr->status()) && itr->path().filename() == boost::filesystem::path("contrib"))
							{
								to_contrib = itr->path();
								if(boost::filesystem::exists(to_contrib/"BridgeDb"))
								{
									found = true;
								}

							}
						}
			ASSERT_TRUE(found) << "directory 'contrib/BridgeDb' not found";

			configFile = "test_configFile.txt";

			QFile file(QString(configFile.c_str()));
			ASSERT_TRUE(file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
				<< "test_BridgeDBWrapper : Cannot open config file";
			QTextStream out(&file);
			out << "executablePath=" << to_contrib.string().c_str() << "/BridgeDb/dist/org.bridgedb.tools.batchmapper.jar\n";
			out << "mappingFilePath=" << to_contrib.string().c_str() << "/BridgeDb/mapping-files/Hs_Derby_20120602.bridge\n";
			out << "tmpFilePath=" << to_contrib.string().c_str() << "/BridgeDb/tmp\n";

			std::cerr << "Initialization done." << std::endl;
		}

		virtual void TearDown()
		{
			boost::filesystem::path p(configFile);
			if (boost::filesystem::exists(p))
			{
					boost::filesystem::remove(p);
			}
		}
		
		std::string configFile;
		boost::filesystem::path to_contrib;
};

TEST_F(TestBridgeDBWrapper, parseConfigFile)
{
  PublicBridgeDBWrapper connector;
	connector.parseConfigFile(configFile);
	ASSERT_STREQ((to_contrib/"BridgeDb/dist/org.bridgedb.tools.batchmapper.jar").string().c_str(), connector.getExecutablePath().c_str())
		<< "Wrong 'executablePath'.";
	ASSERT_STREQ((to_contrib/"BridgeDb/mapping-files/Hs_Derby_20120602.bridge").string().c_str(), connector.getMappingFilePath().c_str())
		<< "Wrong 'mappingFilePath'.";
	ASSERT_STREQ((to_contrib/"BridgeDb/tmp").string().c_str(), connector.getTmpFilePath().c_str())
		<< "Wrong 'tmpFilePath'.";
}


TEST_F(TestBridgeDBWrapper, isMappingSupported)
{
	PublicBridgeDBWrapper connector;
	connector.parseConfigFile(configFile);
	EXPECT_TRUE(connector.isMappingSupported("HGNC", "Entrez Gene"))
		<< "Mapping from 'HGNC' to 'Entrez Gene' seems to be unsupported.";
//	for (std::map<std::string, std::string>::iterator it = connector.getIdSystems().begin(); it != connector.getIdSystems().end(); ++it)
//	{
//			std::cout << "\t" << it->first << " -> " << it->second << std::endl;
//	}
//	std::cout << "First entry of IdSystems map: " << connector.getIdSystems().begin()->first << " -> " << connector.getIdSystems().begin()->second << std::endl;
	ASSERT_TRUE(connector.getIdSystems().find("HGNC") != connector.getIdSystems().end())
		<< "Map does not contain 'HGNC'";
	ASSERT_TRUE(connector.getIdSystems().find("Entrez Gene") != connector.getIdSystems().end())
		<< "Map does not contain 'Entrez Gene'";
	ASSERT_FALSE(connector.isMappingSupported("Hodor", "Lannister"))
		<< "Hodor maps to Lannister? Something is really wrong.";
}

TEST_F(TestBridgeDBWrapper, mapIds)
{
	//EXPECT_TRUE(0) << "Not yet implemented...";
	PublicBridgeDBWrapper connector(configFile);
	std::vector<std::string> srcIds;
	srcIds.push_back("Q8TC26");
	srcIds.push_back("P68366");
	srcIds.push_back("P08575");
	std::multimap<std::string, std::string> idMapping;
	connector.mapIds("Uniprot/TrEMBL", srcIds, "Entrez Gene", idMapping);
	for (std::multimap<std::string, std::string>::iterator it = idMapping.begin(); it != idMapping.end(); ++it)
	{
			std::cout << it->first << " -> " << it->second << std::endl;
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

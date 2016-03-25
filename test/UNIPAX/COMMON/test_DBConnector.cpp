#include <UNIPAX/COMMON/DBConnector.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <UNIPAX/KERNEL/EXT/ResultObject.h>
#include <UNIPAX/COMMON/KernelClassSet.h>
#include <UNIPAX/COMMON/OrganismSet.h>
#include <UNIPAX/COMMON/PathwaySet.h>

#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>

#include <iostream>

class TestDBConnector : public ::testing::Test
{
	public:
		TestDBConnector()
		{
		}

		virtual ~TestDBConnector() {}

	protected:
		virtual void SetUp()
		{
			connector = UniPAX::DBConnectorPtr(new UniPAX::DBConnector("localhost", 3306, "unipax", "unipax", "unipax"));
			std::cerr << "Initialization done." << std::endl;
		}

		virtual void TearDown()
		{
		}
		
		UniPAX::DBConnectorPtr connector;
};

TEST_F(TestDBConnector, query)
{
	std::string db_reason = " This may be due to your DB settings.";
	UniPAX::KernelClassSet knl_set(connector);
	EXPECT_TRUE(knl_set.addById(UniPAX::ClassType::idPathway)) << "KernelClassSet could'nt be constructed." << db_reason;

	UniPAX::OrganismSet org_set(connector);
	EXPECT_TRUE(org_set.addByName("Homo sapiens")) << "OrganismSet could'nt be constructed." << db_reason;

	UniPAX::PathwaySet pwy_set(connector);
	EXPECT_TRUE(pwy_set.addByName("Glycolysis")) << "PathwaySet could'nt be constructed." << db_reason;

	UnipaxPtr<UniPAX::ResultObject>::type result = connector->query(org_set, pwy_set, knl_set);

	EXPECT_TRUE(0 < result->getObjectIds().size()) << "No matching ID in ResultObject." << db_reason;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include <UNIPAX/PERSISTENCE/ODBWorker.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>
#include <iostream>

class TestODBWorker : public ::testing::Test
{
public:
	TestODBWorker()
{
}

	virtual ~TestODBWorker() {}

protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

};

TEST_F(TestODBWorker, checkConsistencyOfMaps)
{
	try
	{
		UniPAX::ODBWorker::TypeInfo typeInfo(UniPAX::ODBWorker::typeInfo);
		for (std::map<std::string, UnipaxId>::const_iterator it = typeInfo.db_ids.begin(); it != typeInfo.db_ids.end(); ++it)
		{
			EXPECT_STREQ(it->first.c_str(), typeInfo.db_idtype.at(it->second).c_str())
																		<< "Map inconsistency: db_ids: " << it->first << " -> " << it->second
																		<< " db_idType: " << it->second << " -> " << typeInfo.db_idtype.at(it->second);
		}
	}
	catch (const std::out_of_range& oor)
	{
		EXPECT_TRUE(0) << "Out of Range error: " << oor.what() << '\n';
	}
}

TEST_F(TestODBWorker, getType)
{
	UniPAX::ODBWorker::TypeInfo typeInfo(UniPAX::ODBWorker::typeInfo);
	ASSERT_STREQ("ResultObject", typeInfo.getType(1459617794, "").c_str())
	<< "Object ID 1459617794 returns type '" << typeInfo.getType(1459617794, "") << "'";
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

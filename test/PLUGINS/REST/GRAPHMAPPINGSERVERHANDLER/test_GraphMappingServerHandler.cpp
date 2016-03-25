#include <PLUGINS/REST/GRAPHMAPPINGSERVERHANDLER/GraphMappingServerHandler.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

class TestGraphMappingServerHandler : public ::testing::Test
{
	public:
		TestGraphMappingServerHandler()
		{
		}

		virtual ~TestGraphMappingServerHandler() {}

	protected:
		virtual void SetUp()
		{
		}

		virtual void TearDown()
		{
		}
		
};

TEST_F(TestGraphMappingServerHandler, init)
{
	ADD_FAILURE() << "Not yet implemented.";
}

TEST_F(TestGraphMappingServerHandler, handle)
{
	ADD_FAILURE() << "Not yet implemented.";
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

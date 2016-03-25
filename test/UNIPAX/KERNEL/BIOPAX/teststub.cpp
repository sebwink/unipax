#include <gtest/gtest.h>

class TestStub : public ::testing::Test
{
	public:
		TestStub()
		{
		}

		virtual ~TestStub() {}

	protected:
		virtual void SetUp()
		{
		}

		virtual void TearDown()
		{
		}
};

TEST_F(TestStub, Test)
{
	EXPECT_EQ(0,0);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

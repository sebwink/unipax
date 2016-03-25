#include <UNIPAX/KERNEL/BIOPAX/BindingFeature.h>
#include <mock_PersistenceManager.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestBindingFeature : public ::testing::Test
{
	public:
		TestBindingFeature()
		{
		}

		virtual ~TestBindingFeature() {}

	protected:
		virtual void SetUp()
		{
			obj1.setIntraMolecular(true);
			boost::shared_ptr<UniPAX::BindingFeature> obj3_ptr (new UniPAX::BindingFeature(obj3));
			obj1.addBindsTo(obj3_ptr);

			obj2.setIntraMolecular(true);
            boost::shared_ptr<UniPAX::BindingFeature> obj3_ptr2 (new UniPAX::BindingFeature(obj3));
			obj2.addBindsTo(obj3_ptr2);

			obj3.setIntraMolecular(true);
		}

		virtual void TearDown()
		{
		}
		
		UniPAX::BindingFeature obj1;
		UniPAX::BindingFeature obj2;
		UniPAX::BindingFeature obj3;

};

TEST_F(TestBindingFeature, getType)
{
	UniPAX::BindingFeature obj;
	// both type functions
	ASSERT_EQ(0, obj.getType().compare("BindingFeature")) << "Wrong type info.";
	ASSERT_EQ(0, obj.type().compare("BindingFeature")) << "Wrong type info.";
}

TEST_F(TestBindingFeature, merge)
{
	// equal object should merge
	ASSERT_TRUE(obj1.merge(obj2)) << "Merge of equal objects failed.";

	// unequal ones should not
	obj2.setIntraMolecular(false);
	//EXPECT_FALSE(obj1.merge(obj2)) << "Merge of unequal objects did not fail.";

	obj2.setIntraMolecular(true);
	obj2.setBindsTos(std::vector<boost::shared_ptr<UniPAX::BindingFeature> > ());
	//EXPECT_FALSE(obj1.merge(obj2)) << "Merge of unequal objects did not fail.";
}

TEST_F(TestBindingFeature, setAttribute_intraMolecular)
{
	// does attribute setting work out?
	MockPersistenceManager mpm;
	// set intramolecular
	std::string attribute("intraMolecular");
	std::stringstream ss;
	ss << true << "#boolean";
	std::string value = ss.str();
	EXPECT_TRUE(obj1.setAttribute(attribute, value, mpm)) << "Try to set intramolecular returned false.";
}

TEST_F(TestBindingFeature, setAttribute_bindsTo)
{
	// does attribute setting work out?
	MockPersistenceManager mpm;
	std::string attribute = "bindsTo";
	std::string empty = "";
	std::string value = "#obj2";
	{
		::testing::InSequence dummy;
		EXPECT_CALL(mpm, getInstance(value, empty))
			.Times(1)
			.WillOnce(::testing::Return(boost::shared_ptr<UniPAX::UPBase>(new UniPAX::BindingFeature(obj2))));
	}
	// set bindsTo
	EXPECT_TRUE(obj1.setAttribute(attribute, value, mpm)) << "Try to set bindsTo returned false.";
}

TEST_F(TestBindingFeature, setAttribute_unknown)
{
	MockPersistenceManager mpm;
	// unknown attribute should return false
	std::string attribute = "no_attribute";
	std::string value = "";
	EXPECT_FALSE(obj1.setAttribute(attribute, value, mpm)) << "Try to set no_attribute returned true";
}

TEST_F(TestBindingFeature, getAttribute)
{
	// does Attribute getting work out?
	MockPersistenceManager mpm;
	std::vector<std::pair<std::string,std::string> > attribute_value;
	std::string return_address("");
	std::stringstream ss;
	ss << true << "#boolean";
	{
		::testing::InSequence dummy;
		EXPECT_CALL(mpm, getId(::testing::_, return_address))
			.Times(1)
			.WillOnce(::testing::Return(true));
	}
	EXPECT_TRUE(obj1.getAttribute(attribute_value, mpm));
	// correct values
	EXPECT_EQ(0, attribute_value.front().first.compare("#bindsTo"));
	EXPECT_EQ(0, attribute_value.front().second.compare(return_address));

	EXPECT_EQ(0, attribute_value.back().first.compare("intraMolecular"));
	EXPECT_EQ(0, attribute_value.back().second.compare(ss.str()))
		<< attribute_value.back().second 
		<< " != " 
		<< ss.str();
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

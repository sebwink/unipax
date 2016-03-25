#include <UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include <mock_PersistenceManager.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestBioSource : public ::testing::Test
{
	public:
		TestBioSource()
		{
		}

		virtual ~TestBioSource() {}

	protected:
		virtual void SetUp()
		{
			UnipaxId id = 0;
			obj1.setUnipaxId(id++);
			obj1.setTissue(UnipaxPtr<UniPAX::TissueVocabulary>::type(new UniPAX::TissueVocabulary()));
			obj1.getTissue()->setUnipaxId(id++);
			obj1.addCellType(UnipaxPtr<UniPAX::CellVocabulary>::type(new UniPAX::CellVocabulary()));
			obj1.addXref(UnipaxPtr<UniPAX::Xref>::type(new UniPAX::Xref()));
			obj1.addName("First");
			obj1.setStandardName("First");
			obj1.setDisplayName("First");

			obj2.setUnipaxId(id++);
			obj2.setTissue(UnipaxPtr<UniPAX::TissueVocabulary>::type(new UniPAX::TissueVocabulary()));
			obj2.getTissue()->setUnipaxId(id++);
			obj2.addCellType(UnipaxPtr<UniPAX::CellVocabulary>::type(new UniPAX::CellVocabulary()));
			obj2.addXref(UnipaxPtr<UniPAX::Xref>::type(new UniPAX::Xref()));
			obj2.addName("Second");
			obj2.setStandardName("Second");
			obj2.setDisplayName("Second");
		}

		virtual void TearDown()
		{
		}
		
		UniPAX::BioSource obj1;
		UniPAX::BioSource obj2;
		UniPAX::BioSource obj3;

};

TEST_F(TestBioSource, getType)
{
	UniPAX::BioSource obj;
	// both type functions
	ASSERT_EQ(0, obj.getType().compare("BioSource")) << "Wrong type info.";
	ASSERT_EQ(0, UniPAX::BioSource::type().compare("BioSource")) << "Wrong type info.";

	ASSERT_EQ(UniPAX::ClassType::idBioSource, obj.getTypeID()) << "Wrong type number.";
	ASSERT_EQ(UniPAX::ClassType::idBioSource, UniPAX::BioSource::typeID()) << "Wrong type number.";
}

TEST_F(TestBioSource, merge)
{
	obj3 = obj1;
	// equal object should merge
	ASSERT_TRUE(obj1.merge(obj3)) << "Merge of equal objects failed.";

	// unequal ones should not
	EXPECT_FALSE(obj1.merge(obj2)) << "Merge of unequal objects did not fail.";
}

TEST_F(TestBioSource, setAttributes)
{
	UniPAX::BioSource obj;
	std::string attribute = "tissue";
	std::string empty = "";
	std::string value = "#tissue1";
	// does attribute setting work out?
	MockPersistenceManager mpm;
	{
		::testing::InSequence dummy;
		EXPECT_CALL(mpm, getInstance(value, empty))
			.Times(1)
			.WillOnce(::testing::Return(boost::shared_ptr<UniPAX::UPBase>(new UniPAX::TissueVocabulary())));
			EXPECT_CALL(mpm, getInstance("#cellType1", empty))
			.Times(1)
			.WillOnce(::testing::Return(boost::shared_ptr<UniPAX::UPBase>(new UniPAX::CellVocabulary())));
		EXPECT_CALL(mpm, getInstance("#xref1", empty))
			.Times(1)
			.WillOnce(::testing::Return(boost::shared_ptr<UniPAX::UPBase>(new UniPAX::Xref())));
	}
	// set tissue
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set bindsTo returned false.";

	// set cellType
	attribute = "cellType";
	value = "#cellType1";
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set bindsTo returned false.";
	// set xref
	attribute = "xref";
	value = "#xref1";
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set bindsTo returned false.";
	// set name
	attribute = "standardName";
	value = "First";
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set standardName returned false.";
	ASSERT_EQ(0, obj.getStandardName().compare(value)) << "standardName attribute was not set.";
	attribute = "displayName";
	value = "First";
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set displayName returned false.";
	ASSERT_EQ(0, obj.getDisplayName().compare(value)) << "displayName attribute was not set.";
	attribute = "name";
	value = "First";
	EXPECT_TRUE(obj.setAttribute(attribute, value, mpm)) << "Try to set name returned false.";
	ASSERT_EQ(0, obj.getNames().at(0).compare(value)) << "name attribute was not set.";
	attribute = "no_attribute";
	value = "";
	// unknown attribute should return false
	EXPECT_FALSE(obj.setAttribute(attribute, value, mpm)) << "Try to set no_attribute returned true";
}

TEST_F(TestBioSource, getAttribute)
{
	// does Attribute getting work out?
	MockPersistenceManager mpm;
	//UniPAX::BioSource obj1;
	std::vector<std::pair<std::string,std::string> > attribute_value;
	UniPAX::UPBasePtr obj_ptr;
	std::string return_address("");
	{
		::testing::InSequence dummy;
		EXPECT_CALL(mpm, getId(::testing::_,return_address))
			//.Times(3)
			//.WillRepeatedly(::testing::Return(true))
			.WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(std::string("id1")), ::testing::Return(true)))
			.WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(std::string("id2")), ::testing::Return(true)))
			.WillOnce(::testing::DoAll(::testing::SetArgReferee<1>(std::string("id3")), ::testing::Return(true)));
	}

	ASSERT_TRUE(obj1.getAttribute(attribute_value, mpm));
	ASSERT_EQ(6, attribute_value.size());

	EXPECT_EQ(0, attribute_value.at(0).first.compare("#xref"));
	EXPECT_EQ(0, attribute_value.at(0).second.compare("id1"));

	EXPECT_EQ(0, attribute_value.at(1).first.compare("#cellType"));
	EXPECT_EQ(0, attribute_value.at(1).second.compare("id2"));

	EXPECT_EQ(0, attribute_value.at(2).first.compare("#tissue"));
	EXPECT_EQ(0, attribute_value.at(2).second.compare("id3"));

	EXPECT_EQ(0, attribute_value.at(3).first.compare("name"));
	EXPECT_EQ(0, attribute_value.at(3).second.compare("First"));

	EXPECT_EQ(0, attribute_value.at(4).first.compare("standardName"));
	EXPECT_EQ(0, attribute_value.at(4).second.compare("First"));

	EXPECT_EQ(0, attribute_value.at(5).first.compare("displayName"));
	EXPECT_EQ(0, attribute_value.at(5).second.compare("First"));

}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

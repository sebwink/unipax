#include <gmock/gmock.h>
#include <UNIPAX/COMMON/PersistenceManager.h>

class MockPersistenceManager : public UniPAX::PersistenceManager
{
		public:

				MOCK_METHOD2(getInstance, boost::shared_ptr<UniPAX::UPBase>(std::string, std::string));
				MOCK_METHOD2(getId, bool(boost::shared_ptr<UniPAX::UPBase>, std::string&));
				MOCK_METHOD1(isMerged, bool(boost::shared_ptr<UniPAX::UPBase>));
				MOCK_METHOD1(getMergedObject, boost::shared_ptr<UniPAX::UPBase>(boost::shared_ptr<UniPAX::UPBase>));

};

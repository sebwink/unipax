#ifndef FRAGMENTFEATURE_H
#define FRAGMENTFEATURE_H
//Begin section for file FragmentFeature.h
//TODO: Add definitions that you want preserved
//End section for file FragmentFeature.h
#include<UNIPAX/KERNEL/BIOPAX/EntityFeature.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT FragmentFeature : public EntityFeature {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "FragmentFeature";
	}

	static std::string type() {
		return std::string("FragmentFeature");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idFragmentFeature;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idFragmentFeature;
        }

        FragmentFeature();

	FragmentFeature(const FragmentFeature & arg);

	FragmentFeature & operator =(const FragmentFeature & arg);

	~FragmentFeature();

	bool merge(FragmentFeature& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef EntityFeature super;

};  //end class FragmentFeature

typedef UnipaxPtr<FragmentFeature>::type FragmentFeaturePtr;

}//end namespace UniPAX

#endif

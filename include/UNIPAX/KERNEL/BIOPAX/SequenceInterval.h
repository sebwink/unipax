#ifndef SEQUENCEINTERVAL_H
#define SEQUENCEINTERVAL_H
//Begin section for file SequenceInterval.h
//TODO: Add definitions that you want preserved
//End section for file SequenceInterval.h
#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<UNIPAX/KERNEL/BIOPAX/SequenceSite.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SequenceInterval : public SequenceLocation {

protected:

	UnipaxPtr<SequenceSite>::type sequenceIntervalBegin;

	UnipaxPtr<SequenceSite>::type sequenceIntervalEnd;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SequenceInterval";
	}

	static std::string type() {
		return std::string("SequenceInterval");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSequenceInterval;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSequenceInterval;
        }

        SequenceInterval();

	SequenceInterval(const SequenceInterval & arg);

	SequenceInterval & operator =(const SequenceInterval & arg);

	~SequenceInterval();

	bool merge(SequenceInterval& object);
	bool update(PersistenceManager& manager);


	//get sequenceIntervalBegin
	const UnipaxPtr<SequenceSite>::type getSequenceIntervalBegin() const;

	UnipaxPtr<SequenceSite>::type getSequenceIntervalBegin();

	void setSequenceIntervalBegin(UnipaxPtr<SequenceSite>::type _sequenceIntervalBegin);

	//get sequenceIntervalEnd
	const UnipaxPtr<SequenceSite>::type getSequenceIntervalEnd() const;

	UnipaxPtr<SequenceSite>::type getSequenceIntervalEnd();

	void setSequenceIntervalEnd(UnipaxPtr<SequenceSite>::type _sequenceIntervalEnd);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef SequenceLocation super;

};  //end class SequenceInterval

typedef UnipaxPtr<SequenceInterval>::type SequenceIntervalPtr;

}//end namespace UniPAX

#endif

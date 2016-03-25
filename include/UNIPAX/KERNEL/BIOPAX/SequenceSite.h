#ifndef SEQUENCESITE_H
#define SEQUENCESITE_H
//Begin section for file SequenceSite.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file SequenceSite.h
#include<UNIPAX/KERNEL/BIOPAX/SequenceLocation.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT SequenceSite : public SequenceLocation {

protected:

	std::string positionStatus;

	int sequencePosition;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "SequenceSite";
	}

	static std::string type() {
		return std::string("SequenceSite");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idSequenceSite;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idSequenceSite;
        }

        SequenceSite();

	SequenceSite(const SequenceSite & arg);

	SequenceSite & operator =(const SequenceSite & arg);

	~SequenceSite();

	bool merge(SequenceSite& object);
	bool update(PersistenceManager& manager);


	//get positionStatus
	const std::string & getPositionStatus() const;

	std::string & getPositionStatus();

	void setPositionStatus(std::string _positionStatus);

	const int getSequencePosition() const;

	//get sequencePosition
	int getSequencePosition();

	//set sequencePosition
	void setSequencePosition(int _sequencePosition);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef SequenceLocation super;

};  //end class SequenceSite

typedef UnipaxPtr<SequenceSite>::type SequenceSitePtr;

}//end namespace UniPAX

#endif

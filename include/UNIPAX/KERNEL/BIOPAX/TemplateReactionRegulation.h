#ifndef TEMPLATEREACTIONREGULATION_H
#define TEMPLATEREACTIONREGULATION_H
//Begin section for file TemplateReactionRegulation.h
//TODO: Add definitions that you want preserved
//End section for file TemplateReactionRegulation.h
#include<UNIPAX/KERNEL/BIOPAX/Control.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT TemplateReactionRegulation : public Control {

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "TemplateReactionRegulation";
	}

	static std::string type() {
		return std::string("TemplateReactionRegulation");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idTemplateReactionRegulation;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idTemplateReactionRegulation;
        }

        TemplateReactionRegulation();

	TemplateReactionRegulation(const TemplateReactionRegulation & arg);

	TemplateReactionRegulation & operator =(const TemplateReactionRegulation & arg);

	~TemplateReactionRegulation();

	bool merge(TemplateReactionRegulation& object);
	bool update(PersistenceManager& manager);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Control super;

};  //end class TemplateReactionRegulation

typedef UnipaxPtr<TemplateReactionRegulation>::type TemplateReactionRegulationPtr;

}//end namespace UniPAX

#endif

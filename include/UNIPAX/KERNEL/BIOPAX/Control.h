#ifndef CONTROL_H
#define CONTROL_H
//Begin section for file Control.h
//TODO: Add definitions that you want preserved
#include<string>
#include<vector>
//End section for file Control.h
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/KERNEL/BIOPAX/Pathway.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Control : public Interaction {

	//Begin section for UniPAX::Control
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Control

protected:

	std::string controlType;

	// std::vector<unsigned long long> id_controller;
//#pragma db transient
	std::vector<UnipaxPtr<Entity>::type > controller;

	//unsigned long long id_controlled;
//#pragma db transient
	UnipaxPtr<Entity>::type controlled;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Control";
	}

	static std::string type() {
		return std::string("Control");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idControl;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idControl;
        }

        Control();

	Control(const Control & arg);

	Control & operator =(const Control & arg);

	~Control();

	bool merge(Control& object);
	bool update(PersistenceManager& manager);


	//get controlType
	const std::string & getControlType() const;

	std::string & getControlType();

	void setControlType(std::string _controlType);

	//get controller
	std::vector<UnipaxPtr<Entity>::type > & getControllers();

	const std::vector<UnipaxPtr<Entity>::type > & getControllers() const;

	//set controller
	void setControllers(std::vector<UnipaxPtr<Entity>::type > _controllers);
	void addController(UnipaxPtr<Entity>::type  _controller);

	//get controlled
	UnipaxPtr<Entity>::type getControlled();

	const UnipaxPtr<Entity>::type getControlled() const;

	//set controlled
	void setControlled(UnipaxPtr<Interaction>::type _controlled);
	void setControlled(UnipaxPtr<Pathway>::type _controlled);

	virtual const std::vector<UnipaxPtr<Entity>::type > getParticipants() const;
	virtual std::vector<UnipaxPtr<Entity>::type > getParticipants();

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Interaction super;

};  //end class Control

typedef UnipaxPtr<Control>::type ControlPtr;

}//end namespace UniPAX

#endif

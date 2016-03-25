#ifndef COMPLEX_H
#define COMPLEX_H
//Begin section for file Complex.h
//TODO: Add definitions that you want preserved
//End section for file Complex.h
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/KERNEL/BIOPAX/Stoichiometry.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Complex : public PhysicalEntity {

	//Begin section for UniPAX::Complex
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::Complex

protected:

	// std::vector<unsigned long long> id_component;
//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > component;

	std::vector<UnipaxPtr<Stoichiometry>::type > componentStoichiometry;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Complex";
	}

	static std::string type() {
		return std::string("Complex");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idComplex;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idComplex;
        }

        Complex();

	Complex(const Complex & arg);

	Complex & operator =(const Complex & arg);

	~Complex();

	bool merge(Complex& object);
	bool update(PersistenceManager& manager);


	//get component
	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getComponents() const;

	std::vector<UnipaxPtr<PhysicalEntity>::type > & getComponents();

	void setComponents(std::vector<UnipaxPtr<PhysicalEntity>::type > _components);

	void addComponent(UnipaxPtr<PhysicalEntity>::type  _component);

	//get componentStoichiometry
	const std::vector<UnipaxPtr<Stoichiometry>::type > & getComponentStoichiometrys() const;

	std::vector<UnipaxPtr<Stoichiometry>::type > & getComponentStoichiometrys();

	void setComponentStoichiometrys(std::vector<UnipaxPtr<Stoichiometry>::type > _componentStoichiometrys);

	void addComponentStoichiometry(UnipaxPtr<Stoichiometry>::type  _componentStoichiometry);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
    bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef PhysicalEntity super;

};  //end class Complex

typedef UnipaxPtr<Complex>::type ComplexPtr;

}//end namespace UniPAX

#endif

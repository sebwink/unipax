#ifndef TEMPLATEREACTION_H
#define TEMPLATEREACTION_H
//Begin section for file TemplateReaction.h
//TODO: Add definitions that you want preserved
#include<string>
//End section for file TemplateReaction.h
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<UNIPAX/KERNEL/BIOPAX/PhysicalEntity.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT TemplateReaction : public Interaction {

protected:

	std::string templateDirection;

	//unsigned long long id_templateEntity;
//#pragma db transient
	UnipaxPtr<PhysicalEntity>::type templateEntity;

	// std::vector<unsigned long long> id_product;
//#pragma db transient
	std::vector<UnipaxPtr<PhysicalEntity>::type > product;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "TemplateReaction";
	}

	static std::string type() {
		return std::string("TemplateReaction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idTemplateReaction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idTemplateReaction;
        }

        TemplateReaction();

	TemplateReaction(const TemplateReaction & arg);

	TemplateReaction & operator =(const TemplateReaction & arg);

	~TemplateReaction();

	bool merge(TemplateReaction& object);
	bool update(PersistenceManager& manager);


	//get templateDirection
	const std::string & getTemplateDirection() const;

	std::string & getTemplateDirection();

	void setTemplateDirection(std::string & _templateDirection);

	const UnipaxPtr<PhysicalEntity>::type getTemplateEntity() const;

	//get template
	UnipaxPtr<PhysicalEntity>::type getTemplateEntity();

	//set template
	void setTemplateEntity(UnipaxPtr<PhysicalEntity>::type _templateEntity);

	const std::vector<UnipaxPtr<PhysicalEntity>::type > & getProducts() const;

	//get product
	std::vector<UnipaxPtr<PhysicalEntity>::type > & getProducts();

	//set product
	void setProducts(std::vector<UnipaxPtr<PhysicalEntity>::type > _products);

	void addProduct(UnipaxPtr<PhysicalEntity>::type  _product);

	virtual const std::vector<UnipaxPtr<Entity>::type > getParticipants() const;
	virtual std::vector<UnipaxPtr<Entity>::type > getParticipants();

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Interaction super;

};  //end class TemplateReaction

typedef UnipaxPtr<TemplateReaction>::type TemplateReactionPtr;

}//end namespace UniPAX

#endif

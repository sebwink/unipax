#ifndef PATHWAY_H
#define PATHWAY_H

#include<vector>
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/KERNEL/BIOPAX/PathwayStep.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/KERNEL/EXT/Model.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

class Entity;
class PathwayStep;
class BioSource;
class Model;


#pragma db object
class UNIPAX_EXPORT Pathway : public Entity {

protected:

	// std::vector<unsigned long long> id_modelExtensions;
	//#pragma db transient
	std::vector<UnipaxPtr<Model>::type > modelExtensions;

	// std::vector<unsigned long long> id_pathwayComponent;
//#pragma db transient
	std::vector<UnipaxPtr<Entity>::type > pathwayComponent;

	// std::vector<unsigned long long> id_pathwayOrder;
//#pragma db transient
	std::vector<UnipaxPtr<PathwayStep>::type > pathwayOrder;

	UnipaxPtr<BioSource>::type organism;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Pathway";
	}

	static std::string type() {
		return std::string("Pathway");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idPathway;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idPathway;
        }

        Pathway();

	Pathway(const Pathway & arg);

	Pathway & operator =(const Pathway & arg);

	~Pathway();

	bool merge(Pathway& object);
	bool update(PersistenceManager& manager);


	//get pathwayOrder
	const std::vector<UnipaxPtr<PathwayStep>::type > & getPathwayOrders() const;

	std::vector<UnipaxPtr<PathwayStep>::type > & getPathwayOrders();

	void setPathwayOrders(std::vector<UnipaxPtr<PathwayStep>::type > _pathwayOrders);

	void addPathwayOrder(UnipaxPtr<PathwayStep>::type  _pathwayOrder);


	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	// modelExtensions
	std::vector<UnipaxPtr<Model>::type > & getModelExtensions();

	const std::vector<UnipaxPtr<Model>::type > & getModelExtensions() const;

	void setModelExtensions(std::vector<UnipaxPtr<Model>::type > _modelExtensions);

	void addModelExtension(UnipaxPtr<Model>::type  _modelExtension);

	//get component
	std::vector<UnipaxPtr<Entity>::type > & getPathwayComponents();

	const std::vector<UnipaxPtr<Entity>::type > & getPathwayComponents() const;

	//set component
	void addPathwayComponent(UnipaxPtr<Entity>::type  _pathwayComponent);

	void setPathwayComponents(std::vector<UnipaxPtr<Entity>::type > _pathwayComponents);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);

	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Entity super;

};  //end class Pathway

typedef UnipaxPtr<Pathway>::type PathwayPtr;

}//end namespace UniPAX

#endif

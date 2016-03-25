#ifndef GENE_H
#define GENE_H
//Begin section for file Gene.h
//TODO: Add definitions that you want preserved
//End section for file Gene.h
#include<UNIPAX/KERNEL/BIOPAX/Entity.h>
#include<UNIPAX/KERNEL/BIOPAX/BioSource.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT Gene : public Entity {

protected:

	UnipaxPtr<BioSource>::type organism;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Gene";
	}

	static std::string type() {
		return std::string("Gene");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idGene;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idGene;
        }

        Gene();

	Gene(const Gene & arg);

	Gene & operator =(const Gene & arg);

	~Gene();

	bool merge(Gene& object);
	bool update(PersistenceManager& manager);


	//get organism
	const UnipaxPtr<BioSource>::type getOrganism() const;

	UnipaxPtr<BioSource>::type getOrganism();

	void setOrganism(UnipaxPtr<BioSource>::type _organism);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Entity super;

};  //end class Gene

typedef UnipaxPtr<Gene>::type GenePtr;

}//end namespace UniPAX

#endif

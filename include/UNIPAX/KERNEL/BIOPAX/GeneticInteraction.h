#ifndef GENETICINTERACTION_H
#define GENETICINTERACTION_H
//Begin section for file GeneticInteraction.h
//TODO: Add definitions that you want preserved
//End section for file GeneticInteraction.h
#include<UNIPAX/KERNEL/BIOPAX/Interaction.h>
#include<UNIPAX/KERNEL/BIOPAX/PhenotypeVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/Score.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object
class UNIPAX_EXPORT GeneticInteraction : public Interaction {

protected:

	std::vector<UnipaxPtr<PhenotypeVocabulary>::type > phenotype;
	std::vector<UnipaxPtr<Score>::type > interactionScore;

#pragma db member(GeneticInteraction::interactionScore) table("GeneticInteraction_score")
#pragma db member(GeneticInteraction::interactionType) table("GeneticInteraction_type")


friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "GeneticInteraction";
	}

	static std::string type() {
		return std::string("GeneticInteraction");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idGeneticInteraction;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idGeneticInteraction;
        }

        GeneticInteraction();

	GeneticInteraction(const GeneticInteraction & arg);

	GeneticInteraction & operator =(const GeneticInteraction & arg);

	~GeneticInteraction();

	bool merge(GeneticInteraction& object);
	bool update(PersistenceManager& manager);


	//get phenotype
	const std::vector<UnipaxPtr<PhenotypeVocabulary>::type > & getPhenotypes() const;

	std::vector<UnipaxPtr<PhenotypeVocabulary>::type > & getPhenotypes();

	void setPhenotypes(std::vector<UnipaxPtr<PhenotypeVocabulary>::type > _phenotypes);

	void addPhenotype(UnipaxPtr<PhenotypeVocabulary>::type  _phenotype);

	//get interactionScore
	const std::vector<UnipaxPtr<Score>::type > & getInteractionScores() const;

	std::vector<UnipaxPtr<Score>::type > & getInteractionScores();

	void setInteractionScores(std::vector<UnipaxPtr<Score>::type > _interactionScores);

	void addInteractionScore(UnipaxPtr<Score>::type  _interactionScore);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef Interaction super;

};  //end class GeneticInteraction

typedef UnipaxPtr<GeneticInteraction>::type GeneticInteractionPtr;

}//end namespace UniPAX

#endif

#ifndef SCORE_H
#define SCORE_H
//Begin section for file Score.h
//TODO: Add definitions that you want preserved
//End section for file Score.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/Provenance.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT Score : public UtilityClass {

protected:

	UnipaxPtr<Provenance>::type scoreSource;

	std::string value;

friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Score";
	}

	static std::string type() {
		return std::string("Score");
	}

        static UniPAX::ClassType::ID typeID() {
            return UniPAX::ClassType::idScore;
}

virtual UniPAX::ClassType::ID getTypeID() {
            return UniPAX::ClassType::idScore;
        }

        Score();

	Score(const Score & arg);

	Score & operator =(const Score & arg);

	~Score();

	bool merge(Score& object);
	bool update(PersistenceManager& manager);


	//get scoreSource
	const UnipaxPtr<Provenance>::type getScoreSource() const;

	UnipaxPtr<Provenance>::type getScoreSource();

	void setScoreSource(UnipaxPtr<Provenance>::type _scoreSource);


	const std::string getValue() const;

	std::string getValue();

	void setValue(std::string _value);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
    typedef UtilityClass super;

};  //end class Score

typedef UnipaxPtr<Score>::type ScorePtr;

}//end namespace UniPAX

#endif

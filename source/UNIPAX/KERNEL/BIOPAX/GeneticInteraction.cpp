#include<UNIPAX/KERNEL/BIOPAX/GeneticInteraction.h>
#include<set>
//Begin section for file GeneticInteraction.cpp
//TODO: Add definitions that you want preserved
//End section for file GeneticInteraction.cpp

UniPAX::GeneticInteraction::GeneticInteraction() : UniPAX::Interaction(), phenotype(0), interactionScore(0) {
    }

UniPAX::GeneticInteraction::GeneticInteraction(const GeneticInteraction& arg) : UniPAX::Interaction(arg) ,
	phenotype(arg.phenotype),
	interactionScore(arg.interactionScore)
{
    }

UniPAX::GeneticInteraction & UniPAX::GeneticInteraction::operator =(const GeneticInteraction & arg)  {
	UniPAX::Interaction::operator=(arg);
	phenotype = arg.phenotype;
	interactionScore = arg.interactionScore;
    phenotype = arg.phenotype;
	interactionScore = arg.interactionScore;

	return *this;
}

UniPAX::GeneticInteraction::~GeneticInteraction()  {
    }

bool UniPAX::GeneticInteraction::merge(GeneticInteraction& object)
{
	{
		std::set<UniPAX::ScorePtr> tmp(getInteractionScores().begin(), getInteractionScores().end());
		for (std::vector<UniPAX::ScorePtr>::iterator it = object.getInteractionScores().begin(); it != object.getInteractionScores().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getInteractionScores().assign(tmp.begin(), tmp.end());
	}
	{
		std::set<UniPAX::PhenotypeVocabularyPtr> tmp(getPhenotypes().begin(), getPhenotypes().end());
		for (std::vector<UniPAX::PhenotypeVocabularyPtr>::iterator it = object.getPhenotypes().begin(); it != object.getPhenotypes().end(); it++)
		{
			if (*it != 0)
			{
				tmp.insert(*it);
			}
		}
		getPhenotypes().assign(tmp.begin(), tmp.end());
	}
	return UniPAX::Interaction::merge(object);
}

bool UniPAX::GeneticInteraction::update(PersistenceManager& manager)
{
	{
		std::vector<boost::shared_ptr<UniPAX::Score> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::Score> >::iterator it;
		for (it = interactionScore.begin(); it != interactionScore.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<Score>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setInteractionScores(tmp_vec);
	}
	{
		std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> > tmp_vec;
		std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> >::iterator it;
		for (it = phenotype.begin(); it != phenotype.end(); it++)
		{
			if (manager.isMerged(*it))
				tmp_vec.push_back(boost::dynamic_pointer_cast<PhenotypeVocabulary>(manager.getMergedObject(*it)));
			else
				tmp_vec.push_back(*it);
		}
		setPhenotypes(tmp_vec);
	}

	return UniPAX::Interaction::update(manager);
}

const std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> > & UniPAX::GeneticInteraction::getPhenotypes() const {
	return phenotype;
}

std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> > & UniPAX::GeneticInteraction::getPhenotypes() {
	return phenotype;
}

void UniPAX::GeneticInteraction::setPhenotypes(std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> > _phenotypes) {
	phenotype = _phenotypes;
}

void UniPAX::GeneticInteraction::addPhenotype(boost::shared_ptr<UniPAX::PhenotypeVocabulary>  _phenotype) {
	phenotype.push_back(_phenotype);
}

const std::vector<boost::shared_ptr<UniPAX::Score> > & UniPAX::GeneticInteraction::getInteractionScores() const {
        return interactionScore;
}

std::vector<boost::shared_ptr<UniPAX::Score> > & UniPAX::GeneticInteraction::getInteractionScores() {
	return interactionScore;
}

void UniPAX::GeneticInteraction::setInteractionScores(std::vector<boost::shared_ptr<UniPAX::Score> > _interactionScores) {
	interactionScore = _interactionScores;
}

void UniPAX::GeneticInteraction::addInteractionScore(boost::shared_ptr<UniPAX::Score>  _interactionScore) {
	interactionScore.push_back(_interactionScore);
}

bool UniPAX::GeneticInteraction::setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager) {

	if (UniPAX::Interaction::setAttribute(attribute, value, manager))
		return true;

	if (boost::iequals(attribute,"interactionScore"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "GeneticInteraction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		interactionScore.push_back(boost::dynamic_pointer_cast<UniPAX::Score>(object));
		return true;
	}
	if (boost::iequals(attribute,"phenotype"))
	{
		// if sometimes set to NIL or empty string neglect
		if (value == "NIL" || value.empty())
			return true;

		boost::shared_ptr<UniPAX::UPBase> object = manager.getInstance(value,"");
		if (object == 0)
		{
			std::cerr << "GeneticInteraction::setAttribute - object not known (value = " << value << ")" << std::endl;
			return false;
		}

		phenotype.push_back(boost::dynamic_pointer_cast<UniPAX::PhenotypeVocabulary>(object));
		return true;
	}

	return false;

}

bool UniPAX::GeneticInteraction::getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager) {

	if (!UniPAX::Interaction::getAttribute(value, manager))
		return false;

	std::string tmp = "";
	{
		std::vector<boost::shared_ptr<UniPAX::Score> >::iterator it;
		for (it = interactionScore.begin(); it != interactionScore.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#interactionScore", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#interactionScore", tmp));

			}
		}
	}
	tmp.clear();
	{
		std::vector<boost::shared_ptr<UniPAX::PhenotypeVocabulary> >::iterator it;
		for (it = phenotype.begin(); it != phenotype.end(); it++)
		{
			if (*it == 0)
			{
//				value.push_back(std::pair<std::string,std::string>("#phenotype", "NIL"));
			}
			else
			{
				tmp.clear();
				if (!manager.getId(*it,tmp))
				{
					return false;
				}
				value.push_back(std::pair<std::string,std::string>("#phenotype", tmp));

			}
		}
	}

	return true;

}

//void UniPAX::GeneticInteraction::init (odb::callback_event e, odb::database& db) const
//{
//	UniPAX::Interaction::init(e,db);
//
//	return;
//}

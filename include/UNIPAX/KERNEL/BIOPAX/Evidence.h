#ifndef EVIDENCE_H
#define EVIDENCE_H
//Begin section for file Evidence.h
//TODO: Add definitions that you want preserved
//End section for file Evidence.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/EvidenceCodeVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/ExperimentalForm.h>
#include<UNIPAX/KERNEL/BIOPAX/Score.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

class EvidenceCodeVocabulary;
class ExperimentalForm;
class Score;
class Xref;

#pragma db object polymorphic
class UNIPAX_EXPORT Evidence : public UtilityClass {

protected:
	std::vector<UnipaxPtr<EvidenceCodeVocabulary>::type > evidenceCode;

	std::vector<UnipaxPtr<ExperimentalForm>::type > experimentalForm;

	std::vector<UnipaxPtr<Score>::type > confidence;

	// std::vector<unsigned long long> id_xref;
	//#pragma db transient
	std::vector<UnipaxPtr<Xref>::type > xref;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "Evidence";
	}

	static std::string type() {
		return std::string("Evidence");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idEvidence;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idEvidence;
	}

	Evidence();

	Evidence(const Evidence & arg);

	Evidence & operator =(const Evidence & arg);

	~Evidence();

	bool merge(Evidence& object);
	bool update(PersistenceManager& manager);


	//get evidenceCode
	const std::vector<UnipaxPtr<EvidenceCodeVocabulary>::type > & getEvidenceCodes() const;

	std::vector<UnipaxPtr<EvidenceCodeVocabulary>::type > & getEvidenceCodes();

	void setEvidenceCodes(std::vector<UnipaxPtr<EvidenceCodeVocabulary>::type > _evidenceCodes);

	void addEvidenceCode(UnipaxPtr<EvidenceCodeVocabulary>::type  _evidenceCode);


	//get experimentalForm
	const std::vector<UnipaxPtr<ExperimentalForm>::type > & getExperimentalForms() const;

	std::vector<UnipaxPtr<ExperimentalForm>::type > & getExperimentalForms();

	void setExperimentalForms(std::vector<UnipaxPtr<ExperimentalForm>::type > _experimentalForms);

	void addExperimentalForm(UnipaxPtr<ExperimentalForm>::type  _experimentalForm);


	//get confidence
	const std::vector<UnipaxPtr<Score>::type > & getConfidences() const;

	std::vector<UnipaxPtr<Score>::type > & getConfidences();

	void setConfidences(std::vector<UnipaxPtr<Score>::type > _confidences);

	void addConfidence(UnipaxPtr<Score>::type  _confidence);


	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;
	std::vector<UnipaxPtr<Xref>::type > & getXrefs();

	void addXref(UnipaxPtr<Xref>::type  _xref);

	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xrefs);


	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class Evidence

typedef UnipaxPtr<Evidence>::type EvidencePtr;

}//end namespace UniPAX

#endif

#ifndef BIOSOURCE_H
#define BIOSOURCE_H
//Begin section for file BioSource.h
//TODO: Add definitions that you want preserved
//End section for file BioSource.h
#include<UNIPAX/KERNEL/BIOPAX/UtilityClass.h>
#include<UNIPAX/KERNEL/BIOPAX/TissueVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/CellVocabulary.h>
#include<UNIPAX/KERNEL/BIOPAX/Xref.h>
#include<UNIPAX/COMMON/common.h>
#include<UNIPAX/KERNEL/ClassType.h>
#include<odb/core.hxx>
#include<vector>

namespace UniPAX {

#pragma db object polymorphic
class UNIPAX_EXPORT BioSource : public UtilityClass {

	//Begin section for UniPAX::BioSource
	//TODO: Add attributes that you want preserved
	//End section for UniPAX::BioSource

protected:

	UnipaxPtr<TissueVocabulary>::type tissue;

	std::vector<UnipaxPtr<CellVocabulary>::type > cellType;

	// std::vector<unsigned long long> id_xref;
	//#pragma db transient
	std::vector<UnipaxPtr<Xref>::type > xref;

	std::vector<std::string> name;

	std::string standardName;

	std::string displayName;

	friend class odb::access;
	//void init (odb::callback_event e, odb::database& db) const;

public:

	virtual std::string getType() {
		return "BioSource";
	}

	static std::string type() {
		return std::string("BioSource");
	}

	static UniPAX::ClassType::ID typeID() {
		return UniPAX::ClassType::idBioSource;
	}

	virtual UniPAX::ClassType::ID getTypeID() {
		return UniPAX::ClassType::idBioSource;
	}

	BioSource();

	BioSource(const BioSource & arg);

	BioSource & operator =(const BioSource & arg);

	~BioSource();

	bool merge(BioSource& object);
	bool update(PersistenceManager& manager);


	//get tissue
	const UnipaxPtr<TissueVocabulary>::type getTissue() const;

	UnipaxPtr<TissueVocabulary>::type getTissue();

	void setTissue(UnipaxPtr<TissueVocabulary>::type _tissue);

	//get cellType
	const std::vector<UnipaxPtr<CellVocabulary>::type > & getCellTypes() const;

	std::vector<UnipaxPtr<CellVocabulary>::type > & getCellTypes();

	void setCellTypes(std::vector<UnipaxPtr<CellVocabulary>::type > _cellTypes);

	void addCellType(UnipaxPtr<CellVocabulary>::type  _cellType);

	//get xref
	const std::vector<UnipaxPtr<Xref>::type > & getXrefs() const;

	std::vector<UnipaxPtr<Xref>::type > & getXrefs();

	void setXrefs(std::vector<UnipaxPtr<Xref>::type > _xref);

	void addXref(UnipaxPtr<Xref>::type  _xref);


	const std::vector<std::string> & getNames() const;

	std::vector<std::string> & getNames();

	void setNames(std::vector<std::string> _names);

	void addName(std::string _name);


	const std::string & getStandardName() const;

	std::string & getStandardName();

	void setStandardName(std::string _name);


	const std::string & getDisplayName() const;

	std::string & getDisplayName();

	void setDisplayName(std::string _name);

	bool setAttribute(std::string& attribute, std::string& value, PersistenceManager& manager);
	bool getAttribute(std::vector<std::pair<std::string,std::string> >& value, PersistenceManager& manager);

private:
	typedef UtilityClass super;

};  //end class BioSource

typedef UnipaxPtr<BioSource>::type BioSourcePtr;

}//end namespace UniPAX

#endif

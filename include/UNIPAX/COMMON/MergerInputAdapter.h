#ifndef UNIPAX_MERGER_INPUT_ADAPTER_H
#define UNIPAX_MERGER_INPUT_ADAPTER_H

#include <UNIPAX/COMMON/PersistenceManager.h>
#include <UNIPAX/PERSISTENCE/DBManager.h>

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

/** \brief class for handling different input types to merge method. Is needed for UnipaxId generation for parsed data.
 */

namespace UniPAX
{

namespace MergerInput
{
enum InputType { NONE = 0, PERSISTENCE_MANAGER = 1, DB_MANAGER = 2} ;
}

class UNIPAX_EXPORT MergerInputAdapter
{
public:
	/**
	 * \brief Constructs an empty MergerInputAdapter
	 */
	MergerInputAdapter();

	typedef UnipaxId (*idGenFuncPtr)();
	/**
	 * \brief Constructs a MergerInputAdapter from an Persistence Manager (for merge on file data)
	 */
	MergerInputAdapter(UnipaxPtr<UniPAX::PersistenceManager>::type manager, idGenFuncPtr = NULL);

	/**
	 * \brief Constructs a MergerInputAdapter from an DBManager (for merge on DB data)
	 */
	MergerInputAdapter(UniPAX::DBManager manager, idGenFuncPtr = NULL);

	/**
	 * \brief Copy constructor
	 */
	MergerInputAdapter(const MergerInputAdapter &);

	/**
	 * \brief Assignment operator
	 */
	MergerInputAdapter & operator =(const MergerInputAdapter &);

	virtual ~MergerInputAdapter();

	/**
	 * \brief Get a pointer to the internal used id generator function
	 */
	idGenFuncPtr getIdGenFunction();

	/**
	 * \brief Set the internal used id generator function
	 */
	void setIdGenFunction(idGenFuncPtr ptr);

	/**
	 * \brief Add an instance of a UniPAX type to the Adapter
	 */
	template<class T>
	typename UnipaxPtr<T>::type createInstance(bool & created)
	{
		if (input_type != MergerInput::NONE && pointer_id.empty())
		{
			if (!fillPtrIdMap())
			{
				std::cerr << "MergerInputAdapter::getPtrIdMap: failed." << std::endl;
				created = false;
				return typename UnipaxPtr<T>::type();
			}
		}
		UnipaxId uid = (*nextId)();
		std::string new_id = boost::lexical_cast<std::string>(uid);
//		if (!pm->convertAttribute(uid, new_id)) // cannot be used for true conversion (is adding a #type tag)
//		{
//			std::cerr << "MergerInputAdapter::createInstance: Could not create a new id." << std::endl;
//			created = false;
//			return typename UnipaxPtr<T>::type();
//		}
		typename UnipaxPtr<T>::type ptr = pm->createInstance<T>(new_id, created);
		if (created)
		{
			ptr->setUnipaxId(uid);
			pointer_id.insert(std::pair<UniPAX::UPBasePtr, UnipaxId>(ptr, uid));
			if (input_type == MergerInput::PERSISTENCE_MANAGER)
			{
				pm->update(ptr);
			}
		}
		return ptr;
	}

	/**
	 * \brief Remove an instance of a UniPAX type from the Adapter
	 */
	bool removeInstance(UniPAX::UPBasePtr ptr);

	/**
	 * \brief Returns a map of pointer to id of all handled objects.
	 */
	std::map<UniPAX::UPBasePtr, UnipaxId> & getPtrIdMap();

	UnipaxPtr<UniPAX::PersistenceManager>::type & getPersistenceManager();

	/**
	 * \brief returns all objects of a type and if recursive all subtypes
	 */
	bool getObjectsByType(std::vector< boost::shared_ptr<UniPAX::UPBase> >& result, std::string type, bool recursive = false);

private:

	bool fillPtrIdMap();

	MergerInput::InputType input_type;
	UnipaxPtr<UniPAX::PersistenceManager>::type pm;
	UniPAX::DBManager dm;
	idGenFuncPtr nextId;
	std::map<UniPAX::UPBasePtr, UnipaxId> pointer_id;
};

}
#endif

#include <UNIPAX/IMPORT/BIOPAX/BIOPAXReader.h>
#include <UNIPAX/IMPORT/BIOPAX/BIOPAXWriter.h>
#ifdef ODB_MYSQL
#include <UNIPAX/PERSISTENCE/MYSQL/MySQLManager.h>
#elif defined ODB_ORACLE
#include <UNIPAX/PERSISTENCE/ORACLE/OracleManager.h>
#endif

#include <UNIPAX/KERNEL/all.h>
#include <UNIPAX/COMMON/MergerInputAdapter.h>

#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>
#include <map>

UnipaxId id = 0;

UnipaxId nextId()
{
	return id++;
}

bool mergeXrefs(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_xrefs1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_xrefs2, bool debug)
{
	// merge Xref objects:
	// UnificationXref objects are important to be merged first
	// for serving the identity mapping in data integration
	std::multimap<std::string, boost::shared_ptr<UniPAX::Xref> > remainder;
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::iterator it = all_xrefs2.begin(); it != all_xrefs2.end(); it++)
	{
		boost::shared_ptr<UniPAX::Xref> tmp = boost::dynamic_pointer_cast<UniPAX::Xref>(*it);
		if (tmp->getId().empty())
		{
			std::cerr << "Empty Id field in " << tmp->getType() << " object." << std::endl;
		}
		else
		{
			remainder.insert(std::pair<std::string, boost::shared_ptr<UniPAX::Xref> >(tmp->getId(), tmp));
		}
	}

	//std::list<boost::shared_ptr<UniPAX::UPBase> > remainder(all_xrefs2.begin(), all_xrefs2.end());
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it = all_xrefs1.begin(); it != all_xrefs1.end(); it++)
	{
		boost::shared_ptr<UniPAX::Xref> it_xref = boost::dynamic_pointer_cast<UniPAX::Xref>(*it);
		if (debug) std::cout << "Copying "<< it_xref->getType() << " object " << it_xref->getDb() << ":" << it_xref->getId() << " with unpaxId:" << it_xref->getUnipaxId() << std::endl;
		// make a copy
		boost::shared_ptr<UniPAX::UPBase> result = it_xref->dynamic_copy();
		result->setUnipaxId(nextId());
		if (debug) std::cout << "Setting unipaxId to " << result->getUnipaxId() << std::endl;
		// search for identical object in remainder
		std::multimap<std::string, boost::shared_ptr<UniPAX::Xref> >::iterator found = remainder.find(it_xref->getId());
		if (found != remainder.end())
		{
			boost::shared_ptr<UniPAX::Xref> del_xref = found->second;
			if (!it_xref->getDb().empty() && !del_xref->getDb().empty() && !it_xref->getId().empty() && !del_xref->getId().empty())
			{
				if (debug) std::cout << "Trying to merge " << it_xref->getType() << " objects." << std::endl;
				if (debug) std::cout << it_xref->getDb() << ":" << it_xref->getId() << " and " << del_xref->getDb() << ":" << del_xref->getId() << std::endl;
				if (!result->merge(*del_xref))
				{
					// some fields may have different values?
					if (debug) std::cout << "Adding two separate objects." << std::endl;
				}
				else
				{
					if (debug) std::cout << "Objects successfully merged." << std::endl;
					// remove identical object
					remainder.erase(found);
				}
				merged.collect(result);
				merged.addMerge(del_xref ,result);
				merged.addMerge(*it, result);

			}
		}
		else
		{
			merged.collect(result);
			merged.addMerge(*it ,result);
		}
		if (debug) std::cout << "Number of merged objects: " << merged.getInstanceCount() << std::endl;
		result->update(merged);
	}
	// add all remaining Xref objects from remainder
	for (std::multimap<std::string, boost::shared_ptr<UniPAX::Xref> >::const_iterator it = remainder.begin() ; it != remainder.end(); it++)
	{
		if (debug) std::cout << "Copying "<< it->second->getType() << " object " << it->second->getDb() << ":" << it->second->getId() << " with unpaxId:" << it->second->getUnipaxId() << std::endl;
		// make a copy
		boost::shared_ptr<UniPAX::UPBase> result = it->second->dynamic_copy();
		result->setUnipaxId(nextId());
		result->update(merged);
		if (debug) std::cout << "Setting unipaxId to " << result->getUnipaxId() << std::endl;
		merged.collect(result);
		merged.addMerge(it->second, result);
	}
	return true;
}

/*template<class T>
std::vector<UniPAX::XrefPtr> getXrefs(T instance)
{
	return instance->getXrefs();
}*/

template<class T>
bool mergeEntitiesByRef(UniPAX::KernelCollector& merged, const std::vector<boost::shared_ptr<UniPAX::UPBase> > source_vec1, const std::vector<boost::shared_ptr<UniPAX::UPBase> > source_vec2, bool debug)
{
	// follow the merged EntityRefs to see, if two objects may be equal.
	// fill a multimap with (merged EntityRef.UnipaxId -> referenced Entity from the second data source)
	std::multimap<UnipaxId, boost::shared_ptr<T> > eref_uid_source2_map;
	//std::multimap<UniPAX::EntityReferencePtr, boost::shared_ptr<T> > eref_uid_source2_map;
	std::set<boost::shared_ptr<T> > src2_remainder;
	for (std::vector<UniPAX::UPBasePtr>::const_iterator it = source_vec2.begin(); it != source_vec2.end(); ++it)
	{
		boost::shared_ptr<T> entity2 = boost::dynamic_pointer_cast<T>(*it);
		//entity2->update(merged);
		for (std::vector<UniPAX::EntityReferencePtr>::const_iterator er_it = entity2->getEntityReferences().begin(); er_it != entity2->getEntityReferences().end(); ++er_it)
		{
			if (merged.isMerged(*er_it))
			{
				//(*er_it)->update(merged); // maybe like this?
				//eref_uid_source2_map.insert(std::pair<UnipaxId, typename UnipaxPtr<T>::type>((*er_it)->getUnipaxId(), entity2));
				eref_uid_source2_map.insert(std::pair<UnipaxId, typename UnipaxPtr<T>::type>(merged.getMergedObject(*er_it)->getUnipaxId(), entity2));
				//eref_uid_source2_map.insert(std::pair<UniPAX::EntityReferencePtr, typename UnipaxPtr<T>::type>(merged.getMergedObject(*er_it), entity2));
				src2_remainder.insert(entity2);
			}
		}
	}
	//search for matches between Entity objects
	std::map<UnipaxId, UniPAX::UPBasePtr> refs_handled;
	for (std::vector<UniPAX::UPBasePtr>::const_iterator it = source_vec1.begin(); it != source_vec1.end(); ++it)
	{
		boost::shared_ptr<T> entity3 = boost::dynamic_pointer_cast<T>((*it)->dynamic_copy());
		entity3->setUnipaxId(nextId());
		entity3->update(merged);
		if (debug) std::cout << "Copying instance of type " << entity3->getType()
										<< ".\nSetting id to " << entity3->getUnipaxId() << "." << std::endl;
		bool found = false;
		if (debug) std::cout << "Searching for matching EntityReference:" << std::endl;
		std::vector<UniPAX::EntityReferencePtr>::const_iterator er_it = entity3->getEntityReferences().begin();
		while (!found && er_it != entity3->getEntityReferences().end())
		{
			std::map<UnipaxId, UniPAX::UPBasePtr>::iterator ref_found = refs_handled.find((*er_it)->getUnipaxId());
			if (ref_found != refs_handled.end()) // identical object has already been handled -> doublet in source_vec1
			{
				if (debug) std::cout << "Identical object has already been handled. Doublet in source_vec1." << std::endl;
				merged.addMerge(*it, ref_found->second); // dummy addMerge to set it as merged
				found = true;
				break;
			}
			else
			{
				refs_handled.insert(std::pair<UnipaxId, UniPAX::UPBasePtr>((*er_it)->getUnipaxId(), entity3));
			}
			typedef typename std::multimap<UnipaxId, boost::shared_ptr<T> >::iterator mapIter;
			std::pair<mapIter, mapIter>	range = eref_uid_source2_map.equal_range((*er_it)->getUnipaxId());
			if (range.first != range.second)
			{
				mapIter match = range.first;
				if (debug) std::cout << "Found matching EntityReference." << std::endl;
				found = true;
				boost::shared_ptr<T> entity2 = match->second;
				entity2->update(merged);

				if (entity3->merge(*entity2))
				{
					if (debug) std::cout << "Successfully merged." << std::endl;
					src2_remainder.erase(match->second);
					merged.collect(entity3);
					merged.addMerge(entity2, entity3);
					merged.addMerge(*it, entity3);
				}
				else
				{
					if (debug) std::cout << "Merge unsuccessful." << std::endl;
					return false;
				}
				// for doublets in source2
				match++;
				while (match != range.second)
				{
					if (debug) std::cout << "Identical object has already been handled. Doublet in source_vec2." << std::endl;
					entity2 = match->second;
					merged.addMerge(entity2, entity3);
					match++;
				}
			}
//			if (merged.isMerged(*er_it))
//			{
//				UnipaxId uid = merged.getMergedObject(*er_it)->getUnipaxId();
//				//UniPAX::EntityReferencePtr uid = merged.getMergedObject(*er_it);
//				//typename std::multimap<UniPAX::EntityReferencePtr, boost::shared_ptr<T> >::iterator match = eref_uid_source2_map.find(uid);
//				typename std::multimap<UnipaxId, boost::shared_ptr<T> >::iterator match = eref_uid_source2_map.find(uid);
//				if (match != eref_uid_source2_map.end())
//				{
//					if (debug) std::cout << "Found matching EntityReference." << std::endl;
//					found = true;
//					boost::shared_ptr<T> entity2 = match->second;
//					entity2->update(merged);
//					if (entity3->merge(*entity2))
//					{
//						if (debug) std::cout << "Successfully merged." << std::endl;
//						// remove merged objects from map
//						//eref_uid_source2_map.erase(match);
//						src2_remainder.erase(match->second);
//						entity3->update(merged);
//						merged.collect(entity3);
//						merged.addMerge(entity2, entity3);
//						merged.addMerge(*it, entity3);
//					}
//					else
//					{
//						if (debug) std::cout << "Merge unsuccessful." << std::endl;
//						return false;
//					}
//				}
//			}
			er_it++;
		}
		if (debug && !found) std::cout << "No match found."  << std::endl;
		if (!found)
		{
			// add remaining objects from source1
			//entity3->update(merged);
			merged.collect(entity3);
			merged.addMerge(*it, entity3);
		}
	}
	// add remaining objects from source2
	for (typename std::set<boost::shared_ptr<T> >::iterator it = src2_remainder.begin(); it != src2_remainder.end(); ++it)
	{
		if (debug) std::cout << "Copying remaining " << (*it)->getType() << " object." << std::endl;
		boost::shared_ptr<T> entity3 = boost::dynamic_pointer_cast<T>((*it)->dynamic_copy());
		entity3->setUnipaxId(nextId());
		entity3->update(merged);
		if (debug) std::cout << "Setting id to " << entity3->getUnipaxId() << "." << std::endl;
		merged.collect(entity3);
		merged.addMerge(*it, entity3);
	}
	return true;
}

template<class T>
bool mergeInstancesOf(UniPAX::KernelCollector& merged, const std::vector<boost::shared_ptr<UniPAX::UPBase> > source_vec1, const std::vector<boost::shared_ptr<UniPAX::UPBase> > source_vec2, bool debug)
{
	// fill a multimap with (UnificationXref.id -> T*) pairs from the second data source
	std::multimap<std::string, boost::shared_ptr<T> > uxrefid_source2_map;
	std::set<boost::shared_ptr<T> > src2_remainder;
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it = source_vec2.begin(); it != source_vec2.end(); ++it)
	{
		boost::shared_ptr<T> instance2 = boost::dynamic_pointer_cast<T>(*it);
		//for (std::vector<boost::shared_ptr<UniPAX::Xref> >::const_iterator xit = instance2->getXrefs().begin(); xit != instance2->getXrefs().end(); ++xit)
		for (std::vector<boost::shared_ptr<UniPAX::Xref> >::const_iterator xit = instance2->getXrefs().begin(); xit != instance2->getXrefs().end(); ++xit)
		{
			if ((*xit)->getType().compare("UnificationXref") == 0)
			{
				uxrefid_source2_map.insert(std::pair<std::string, boost::shared_ptr<T> >((*xit)->getId(), instance2));
				src2_remainder.insert(instance2);
			}
		}
	}
	// search for matches between T objects
	std::map<UnipaxId, UniPAX::UPBasePtr> uxrefs_handled;
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::const_iterator it = source_vec1.begin(); it != source_vec1.end(); it++)
	{
		boost::shared_ptr<T> instance3 = boost::dynamic_pointer_cast<T>((*it)->dynamic_copy());
		instance3->setUnipaxId(nextId());
		instance3->update(merged);
		if (debug) std::cout << "Copying instance of type " << instance3->getType()
										<< ".\nSetting id to " << instance3->getUnipaxId() << "." << std::endl;
		bool found = false;
		if (debug) std::cout << "Searching for matching UnificationXref:" << std::endl;
		std::vector<boost::shared_ptr<UniPAX::Xref> >::const_iterator xit = instance3->getXrefs().begin();
		while (!found && xit != instance3->getXrefs().end())
		{
			if ((*xit)->getType().compare("UnificationXref") == 0)
			{
				std::map<UnipaxId, UniPAX::UPBasePtr>::iterator xref_found = uxrefs_handled.find((*xit)->getUnipaxId());
				if (xref_found != uxrefs_handled.end()) // identical object has already been handled -> doublet in source_vec1
				{
					if (debug) std::cout << "Identical object has already been handled. Doublet in source_vec1." << std::endl;
					merged.addMerge(*it, xref_found->second); // dummy addMerge to set it as merged
					found = true;
					break;
				}
				else
				{
					uxrefs_handled.insert(std::pair<UnipaxId, UniPAX::UPBasePtr>((*xit)->getUnipaxId(), instance3));
				}
				typedef typename std::multimap<std::string, boost::shared_ptr<T> >::iterator mapIter;
				std::pair<mapIter, mapIter>	range = uxrefid_source2_map.equal_range((*xit)->getId());
				if (range.first != range.second)
				{
					mapIter match = range.first;
					if (debug) std::cout << "Found matching UnificationXref." << std::endl;
					found = true;
					boost::shared_ptr<T> instance2 = match->second;
					instance2->update(merged);

					if (instance3->merge(*instance2))
					{
						if (debug) std::cout << "Successfully merged." << std::endl;
						src2_remainder.erase(match->second);
						merged.collect(instance3);
						merged.addMerge(instance2, instance3);
						merged.addMerge(*it, instance3);
					}
					else
					{
						if (debug) std::cout << "Merge unsuccessful." << std::endl;
						return false;
					}
					// for doublets in source2
					match++;
					while (match != range.second)
					{
						if (debug) std::cout << "Identical object has already been handled. Doublet in source_vec2." << std::endl;
						instance2 = match->second;
						merged.addMerge(instance2, instance3);
						match++;
					}
				}
			}
			xit++;
		}
		if (debug && !found) std::cout << "No match found."  << std::endl;
		if (!found)
		{
			merged.collect(instance3);
			merged.addMerge(*it, instance3);
		}
	}
	// add remaining objects from source2
	for (typename std::set<boost::shared_ptr<T> >::iterator it = src2_remainder.begin(); it != src2_remainder.end(); ++it)
	{
		if (debug) std::cout << "Copying remaining " << (*it)->getType() << " object." << std::endl;
		boost::shared_ptr<T> instance3 = boost::dynamic_pointer_cast<T>((*it)->dynamic_copy());
		instance3->setUnipaxId(nextId());
		instance3->update(merged);
		if (debug) std::cout << "Setting id to " << instance3->getUnipaxId() << "." << std::endl;
		merged.collect(instance3);
		merged.addMerge((*it), instance3);
	}
	return true;
}

bool mergeBioSources(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_biosources1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_biosources2, bool debug)
{
	// fill a multimap with (UnificationXref.id -> BioSource*) pairs from the second data source
	std::multimap<std::string, boost::shared_ptr<UniPAX::BioSource> > uxrefid_biosource2_map;
	std::set<UniPAX::BioSourcePtr> src2_remainder;
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::iterator it = all_biosources2.begin(); it != all_biosources2.end(); it++)
	{
		boost::shared_ptr<UniPAX::BioSource> biosource2 = boost::dynamic_pointer_cast<UniPAX::BioSource>(*it);
		for (std::vector<boost::shared_ptr<UniPAX::Xref> >::const_iterator xit = biosource2->getXrefs().begin(); xit != biosource2->getXrefs().end(); ++xit)
		{
			if ((*xit)->getType().compare("UnificationXref") == 0)
			{
				uxrefid_biosource2_map.insert(std::pair<std::string, boost::shared_ptr<UniPAX::BioSource> >((*xit)->getId(), biosource2));
				src2_remainder.insert(biosource2);
			}
		}
	}
	// search for matches between Biosource objects
	for (std::vector<boost::shared_ptr<UniPAX::UPBase> >::iterator it = all_biosources1.begin(); it != all_biosources1.end(); it++)
	{
		boost::shared_ptr<UniPAX::BioSource> biosource3 = boost::dynamic_pointer_cast<UniPAX::BioSource>((*it)->dynamic_copy());
		biosource3->setUnipaxId(nextId());
		biosource3->update(merged);
		if (debug) std::cout << "Copying BioSource object with displayName: " << biosource3->getDisplayName() << ".\nSetting id to " << biosource3->getUnipaxId() << "." << std::endl;
		bool found = false;
		std::vector<boost::shared_ptr<UniPAX::Xref> >::const_iterator xit = biosource3->getXrefs().begin();
		if (debug) std::cout << "Searching for matching UnificationXref:" << std::endl;
		while (!found && xit != biosource3->getXrefs().end())
		{
			if ((*xit)->getType().compare("UnificationXref") == 0)
			{
				std::multimap<std::string, boost::shared_ptr<UniPAX::BioSource> >::iterator match = uxrefid_biosource2_map.find((*xit)->getId());
				if (match != uxrefid_biosource2_map.end())
				{
					if (debug) std::cout << "Found matching UnificationXref." << std::endl;
					found = true;
					boost::shared_ptr<UniPAX::BioSource> biosource2 = match->second;
					biosource2->update(merged);
					if (biosource3->merge(*biosource2))
					{
						if (debug) std::cout << "Successfully merged." << std::endl;
						// remove merged objects
						//uxrefid_biosource2_map.erase(match);
						src2_remainder.erase(match->second);
						merged.collect(biosource3);
						merged.addMerge(biosource2, biosource3);
						merged.addMerge(*it, biosource3);
					}
					else
					{
						if (debug) std::cout << "Merge unsuccessful." << std::endl;
					}
				}
			}
			xit++;
		}
		if (debug && !found) std::cout << "No match found."  << std::endl;
		if (!found)
		{
			merged.collect(biosource3);
			merged.addMerge(*it, biosource3);
		}
	}
	// add remaining objects from source2
	for (std::set<UniPAX::BioSourcePtr>::const_iterator it = src2_remainder.begin(); it != src2_remainder.end(); ++it)
	{
		boost::shared_ptr<UniPAX::BioSource> biosource3 = boost::dynamic_pointer_cast<UniPAX::BioSource>((*it)->dynamic_copy());
		if (debug) std::cout << "Copying remaining BioSource object. Setting id to " << biosource3->getUnipaxId() << "." << std::endl;
		biosource3->setUnipaxId(nextId());
		biosource3->update(merged);
		merged.collect(biosource3);
		merged.addMerge(*it, biosource3);
	}
	return true;
}


//bool mergeControlledVocabularies(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_cvs1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_cvs2, bool debug)
//{
//	return mergeInstancesOf<UniPAX::ControlledVocabulary>(merged, all_cvs1, all_cvs2, debug);
//}
//
//bool mergeComplexes(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_entities1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_entities2, bool debug)
//{
//	return mergeInstancesOf<UniPAX::Complex>(merged, all_entities1, all_entities2, debug);
//}
//
//bool mergeEntityReferences(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_entity_refs1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_entity_refs2, bool debug)
//{
//	//if (!mergeInstancesOf<UniPAX::DnaReference>(merged, all_entity_refs1, all_entity_refs2, debug)
//	//		return false;
//	return mergeInstancesOf<UniPAX::EntityReference>(merged, all_entity_refs1, all_entity_refs2, debug);
//}
//
//bool mergeEvidences(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_evidences1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_evidences2, bool debug)
//{
//	return mergeInstancesOf<UniPAX::Evidence>(merged, all_evidences1, all_evidences2, debug);
//}
//
//bool mergeProvenances(UniPAX::KernelCollector& merged, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_provenances1, std::vector<boost::shared_ptr<UniPAX::UPBase> > all_provenances2, bool debug)
//{
//	return mergeInstancesOf<UniPAX::Provenance>(merged, all_provenances1, all_provenances2, debug);
//}


int main(int argC, char** argV)
{
	boost::program_options::options_description desc("Allowed options");
	bool debug = false;
	std::string input_file1, input_file2, output_file;
	std::string db_host, db_user, db_passw;
	std::string src1_db_name, src1_db_user, src1_db_passw;
	std::string src2_db_name, src2_db_user, src2_db_passw;
	std::string targetDb_name, targetDb_user, targetDb_passw;
	int db_port;
	desc.add_options()
								("help,h", "produce help message")
								("debug,d", "generate debug output")
								("db-host,H", boost::program_options::value< std::string >(&db_host)->default_value("localhost"), "host of the database server")
#ifdef ODB_MYSQL
								("src1-db-name,M", boost::program_options::value< std::string >(&src1_db_name), "name of the first UniPAX source database")
								("src2-db-name,N", boost::program_options::value< std::string >(&src2_db_name), "name of the second UniPAX source database")
								("target-db-name,T", boost::program_options::value< std::string >(&targetDb_name), "name of the UniPAX target database")
								("db-user,U", boost::program_options::value< std::string >(&db_user)->default_value("unipax"), "user name for the connection to the UniPAX database")
								("db-passw,p", boost::program_options::value< std::string >(&db_passw)->default_value("unipax"), "password of the UniPAX database")
								("db-port,P", boost::program_options::value< int >(&db_port)->default_value(3306), "port of the database server")
#elif defined ODB_ORACLE
								("src1-db-name,s1N", boost::program_options::value< std::string >(&src1_db_name), "SID of the first UniPAX source database")
								("src1-db-user,s1U", boost::program_options::value< std::string >(&src1_db_user)->default_value("unipax"), "user name of the first UniPAX source database")
								("src1-db-passw,s1P", boost::program_options::value< std::string >(&src1_db_passw)->default_value("unipax"), "password of the first UniPAX source database")
								("src2-db-name,s2N", boost::program_options::value< std::string >(&src2_db_name), "SID of the second UniPAX source database")
								("src2-db-user,s2U", boost::program_options::value< std::string >(&src2_db_user)->default_value("unipax"), "user name of the second UniPAX source database")
								("src2-db-passw,s2P", boost::program_options::value< std::string >(&src2_db_passw)->default_value("unipax"), "password of the second UniPAX source database")
								("target-db-name,tN", boost::program_options::value< std::string >(&targetDb_name), "name of the UniPAX target database")
								("target-db-user,tU", boost::program_options::value< std::string >(&targetDb_user)->default_value("unipax"), "user name of the UniPAX target database")
								("target-db-passw,tP", boost::program_options::value< std::string >(&targetDb_passw)->default_value("unipax"), "password of the UniPAX target database")
								("db-port,P", boost::program_options::value< int >(&db_port)->default_value(1521), "port of the database server")
#endif
								("input-file1,i", boost::program_options::value< std::string >(&input_file1), "first input file")
								("input-file2,j", boost::program_options::value< std::string >(&input_file2), "second input file")
								("file-output,o", boost::program_options::value< std::string >(&output_file), "use file-output instead of target database")
								;
	boost::program_options::positional_options_description pod;
	pod.add("output-file", -1); // for output
	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::command_line_parser(argC, argV).options(desc).positional(pod).run(), vm);
	boost::program_options::notify(vm);
	if (argC == 1 || vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}
	if (vm.count("debug"))
	{
		debug = true;
	}
	//		if (targetDb_name.empty() == output_file.empty())
	//		{
	//				std::cerr << "Please specify either at target database (-T name) or an outfile (-o name)." << std::endl;
	//				return 0;
	//		}
	//		if ((input_file1.empty() != input_file2.empty()) || (src1_db_name.empty() != src2_db_name.empty())
	//						|| (input_file1.empty() == src1_db_name.empty()))
	//		{
	//				std::cerr << "Please specify either input files (-i first -j second) or input databases (-M first -N second)." << std::endl;
	//				return 0;
	//		}
	//		if ((src1_db_name.empty() || !targetDb_name.empty()) && db_passw.empty())
	//		{
	//				std::cout << "Enter password for database access: ";
	//				std::cin >> db_passw;
	//		}
	UniPAX::MergerInputAdapter source1, source2;
	if (!src1_db_name.empty())
	{
		if (debug) std::cout << "input mode: db" << std::endl;
		// setup src DB connections
#ifdef ODB_MYSQL
		UniPAX::mysql::MySQLManager src1_db, src2_db;
		src1_db.setDBCredentials(db_user, db_passw, db_host, db_port, src1_db_name);
		source1 = UniPAX::MergerInputAdapter(src1_db);
		src2_db.setDBCredentials(db_user, db_passw, db_host, db_port, src2_db_name);
		source2 = UniPAX::MergerInputAdapter(src2_db);
#elif defined ODB_ORACLE
		UniPAX::oracle::OracleManager src1_db, src2_db;
		src1_db.setDBCredentials(src1_db_user, src1_db_passw, db_host, db_port, src1_db_name);
		source1 = UniPAX::MergerInputAdapter(src1_db);
		src2_db.setDBCredentials(src2_db_user, src2_db_passw, db_host, db_port, src2_db_name);
		source2 = UniPAX::MergerInputAdapter(src2_db);
#endif
	}
	else
	{
		if (debug) std::cout << "Input mode: file" << std::endl;
		// read infiles

		if (debug) std::cout << "Reading file " << input_file1 << std::endl;
		UniPAX::BIOPAXReader reader1(input_file1);
		reader1.setDebug(false);
		reader1.createObjectsOnly(true);
		if (!reader1.parse()) return 0;
		reader1.createObjectsOnly(false);
		if (!reader1.parse()) return 0;
		if (debug) std::cout << "done!" << std::endl;
		source1 = UniPAX::MergerInputAdapter(UnipaxPtr<UniPAX::PersistenceManager>::type(new UniPAX::PersistenceManager(reader1.getPersistenceManager())));

		if (debug) std::cout << "Reading file " << input_file2 << std::endl;
		UniPAX::BIOPAXReader reader2(input_file2);
		reader2.setDebug(false);
		reader2.createObjectsOnly(true);
		if (!reader2.parse()) return 0;
		reader2.createObjectsOnly(false);
		if (!reader2.parse()) return 0;
		if (debug) std::cout << "done!\n" << std::endl;
		source2 = UniPAX::MergerInputAdapter(UnipaxPtr<UniPAX::PersistenceManager>::type(new UniPAX::PersistenceManager(reader2.getPersistenceManager())));
	}
	source1.setIdGenFunction(&nextId);
	source2.setIdGenFunction(&nextId);
	UniPAX::KernelCollector result;
	std::vector<boost::shared_ptr<UniPAX::UPBase> > _first, _second;
	if (!(source1.getObjectsByType(_first, "Xref", true) && source2.getObjectsByType(_second, "Xref", true)))
	{
		return 0;
	}

	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Xref objects:" << std::endl;
	if (!mergeXrefs(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Xref objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	//result.updateAll();
	_first.clear();
	_second.clear();


	if (!(source1.getObjectsByType(_first, "BioSource", false) && source2.getObjectsByType(_second, "BioSource", false)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " BioSource objects: "<< std::endl;
	if (!mergeBioSources(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "BioSource objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Provenance", false) && source2.getObjectsByType(_second, "Provenance", false)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Provenance objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Provenance>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Provenance objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Evidence", false) && source2.getObjectsByType(_second, "Evidence", false)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Evidence objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Evidence>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Evidence objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "EntityReference", false) && source2.getObjectsByType(_second, "EntityReference", false)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " EntityReference objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::EntityReference>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "EntityReference objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	// Entity objects:
	if (!(source1.getObjectsByType(_first, "Gene", true) && source2.getObjectsByType(_second, "Gene", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Gene objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Gene>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Gene objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Dna", true) && source2.getObjectsByType(_second, "Dna", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Dna objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::Dna>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Dna objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "DnaRegion", true) && source2.getObjectsByType(_second, "DnaRegion", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " DnaRegion objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::DnaRegion>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "DnaRegion objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Protein", true) && source2.getObjectsByType(_second, "Protein", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Protein objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::Protein>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Protein objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Rna", true) && source2.getObjectsByType(_second, "Rna", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Rna objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::Rna>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Rna objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "RnaRegion", true) && source2.getObjectsByType(_second, "RnaRegion", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " RnaRegion objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::RnaRegion>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "RnaRegion objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "SmallMolecule", true) && source2.getObjectsByType(_second, "SmallMolecule", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " SmallMolecule objects: "<< std::endl;
	if (!mergeEntitiesByRef<UniPAX::SmallMolecule>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "SmallMolecule objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Complex", true) && source2.getObjectsByType(_second, "Complex", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Complex objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Complex>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Complex objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	// Add remaining UtilityClass objects...
	if (!(source1.getObjectsByType(_first, "UtilityClass", true) && source2.getObjectsByType(_second, "UtilityClass", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Adding " << _first.size() << " with " << _second.size() << " UtilityClass objects: "<< std::endl;
	for (std::vector<UniPAX::UPBasePtr>::iterator it = _first.begin(); it != _first.end(); ++it)
	{
		if (debug) std::cout << (*it)->getType() << " object found..." << std::endl;
		if (!result.isMerged(*it))
		{

			if (debug) std::cout << "... and not yet merged." << std::endl;

			//if (!(*it)->update(result)) return 0;
			if ((*it)->getTypeID() == UniPAX::ClassType::idStoichiometry)
			{
				UniPAX::StoichiometryPtr stoi = boost::dynamic_pointer_cast<UniPAX::Stoichiometry>(*it);
				if (debug) std::cout << "before copy " << (stoi->getPhysicalEntity() != 0) << std::endl;
				if (!stoi->update(result)) return 0;
				if (debug) std::cout << "before copy after update " << (stoi->getPhysicalEntity() != 0) << std::endl;
			}
			UniPAX::UPBasePtr object = (*it)->dynamic_copy();
			object->setUnipaxId(nextId());
			if (!object->update(result)) return 0;
			if (object->getTypeID() == UniPAX::ClassType::idStoichiometry)
			{
				UniPAX::StoichiometryPtr stoi = boost::dynamic_pointer_cast<UniPAX::Stoichiometry>(object);
				if (debug) std::cout << "after copy " << (stoi->getPhysicalEntity() != 0) << std::endl;
				if (!stoi->update(result)) return 0;
				if (debug) std::cout << "before copy after update " << (stoi->getPhysicalEntity() != 0) << std::endl;
			}
			if (!result.collect(object)) return 0;
			result.addMerge(*it, object);
		}
	}
	for (std::vector<UniPAX::UPBasePtr>::iterator it = _second.begin(); it != _second.end(); ++it)
	{
		if (debug) std::cout << (*it)->getType() << " object found..." << std::endl;
		if (!result.isMerged(*it))
		{
			if (debug) std::cout << "... and not yet merged." << std::endl;

			//if (!(*it)->update(result)) return 0;
			UniPAX::UPBasePtr object = (*it)->dynamic_copy();
			object->setUnipaxId(nextId());
			if (!object->update(result)) return 0;
			if (!result.collect(object)) return 0;
			result.addMerge(*it, object);
		}
	}

	if (debug) std::cout << "UtilityClass objects added.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();



	if (!(source1.getObjectsByType(_first, "Interaction", true) && source2.getObjectsByType(_second, "Interaction", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Interaction objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Interaction>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Interaction objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (!(source1.getObjectsByType(_first, "Pathway", true) && source2.getObjectsByType(_second, "Pathway", true)))
	{
		return 0;
	}
	if (debug) std::cout << "Merging " << _first.size() << " with " << _second.size() << " Pathway objects: "<< std::endl;
	if (!mergeInstancesOf<UniPAX::Pathway>(result, _first, _second, debug))
	{
		return 0;
	}
	if (debug) std::cout << "Pathway objects merged.\n" << std::endl;
	if (debug) std::cout << "Number of merged objects: " << result.getInstanceCount() << std::endl;
	_first.clear();
	_second.clear();

	if (debug) std::cout << result.isMerged(result.getInstance("175", "")) << std::endl;

	//result.updateAll();

	// \Entity objects


	/*if (debug) std::cout << "Merging BioSource objects:" << std::endl;
		  if (!mergeXrefs(result, _first, _second, debug))
		  {
		  return 0;
		  }
		  if (debug) std::cout << "Xref objects merged." << std::endl;*/

	//UniPAX::PersistenceManager target;
	/*UniPAX::mysql::MySQLManager targetDb;
		  if (!targetDb_name.empty())
		  {
		  targetDb.setDBCredentials(db_user, db_passw, db_host, db_port, targetDb_name);;
		  }*/

	// load all ids from dbs to merge
	/*std::vector<UnipaxId> ids1, ids2;
		  if (!src1_db.getIdsByType(ids1, "UPBase", true))
		  {
		  std::cerr << "Could not retrieve ids from database " << src1_db_name << ". Aborting merge." << std::endl;
		  return 0;
		  }
		  if (!src2_db.getIdsByType(ids2, "UPBase", true))
		  {
		  std::cerr << "Could not retrieve ids from database " << src2_db_name << ". Aborting merge." << std::endl;
		  return 0;
		  }
		  UniPAX::KernelCollector src1_manager, src2_manager;*/
	// merge UtilityClass subtypes

	/*{
		  std::vector<boost::shared_ptr<UniPAX::Xref> > all_xrefs1, all_xrefs2;
		  if (!src1_manager.getObjectsByType(all_xrefs1, "Xref", true))
		  {
		  std::cerr << "Could not retrieve Xref object pointers from database " << src1_db_name << ". Aborting merge." << std::endl;
		  return 0;
		  }
		  if (!src2_manager.getObjectsByType(all_xrefs2, "Xref", true))
		  {
		  std::cerr << "Could not retrieve Xref object pointers from database " << src2_db_name << ". Aborting merge." << std::endl;
		  return 0;
		  }
		  }
		// merge BioSource objects
		{
		std::vector<boost::shared_ptr<UniPAX::BioSource> > all_biosources1, all_biosources2;
		if (!src1_manager.getObjectsByType(all_biosources1, "BioSource", true))
		{
		std::cerr << "Could not retrieve BioSource object from database " << src1_db_name << ". Aborting merge." << std::endl;
		return 0;
		}
		if (!src1_manager.getObjectsByType(all_biosources2, "BioSource", true))
		{
		std::cerr << "Could not retrieve BioSource object from database " << src2_db_name << ". Aborting merge." << std::endl;
		return 0;
		}
		for (std::vector<boost::shared_ptr<UniPAX::BioSource> >::const_iterator it = all_biosources1.begin(); it != all_biosources1.end(); it++)
		{
		if ()
		}

		}*/
	/*for (std::vector<UnipaxId>::const_iterator it = ids1.begin(); it != ids1.end(); it++)
		  {

		  }*/
	UniPAX::BIOPAXWriter writer; // for output

	/*boost::shared_ptr<UniPAX::ProteinReference>  first = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(db.getObjectByID(705070265));
		  boost::shared_ptr<UniPAX::ProteinReference>  second = boost::dynamic_pointer_cast<UniPAX::ProteinReference>(db.getObjectByID(705076958));
		  boost::shared_ptr<UniPAX::BioSource>  first_org = boost::dynamic_pointer_cast<UniPAX::BioSource>(db.getObjectByID(16777233));
		  boost::shared_ptr<UniPAX::BioSource>  second_org = boost::dynamic_pointer_cast<UniPAX::BioSource>(db.getObjectByID(16777218));

		  manager.collect(first);
		  manager.collect(second);
		  writer.setPersistenceManager(manager);
		  writer.write(output_file);

		  UniPAX::KernelCollector manager2;
		// make a copy of first object
		std::cout << first_org.get()->getUnipaxId() << std::endl;
		UniPAX::BioSource tmp_org(*first_org);
		boost::shared_ptr<UniPAX::BioSource> third_org = boost::shared_ptr<UniPAX::BioSource>(&tmp_org);
		// merge second object into new object
		if (third_org->merge(*second_org))
		{
		manager2.collect(third_org);
		manager2.addMerge(second_org, third_org);
		}
		std::cout << "davor" << std::endl;
		first->update(manager2);
		std::cout << "mitte" << std::endl;
		second->update(manager2);
		std::cout << "danach" << std::endl;

		// make a copy of first object
		UniPAX::ProteinReference* tmp = new UniPAX::ProteinReference(*first);
		boost::shared_ptr<UniPAX::ProteinReference> third(tmp);
		// merge second object into new object
		if (third->merge(*second))
		{
		manager2.collect(third);
		manager2.addMerge(second, third);
		}

		//	UniPAX::MySQLManager db2;
		//	db2.setDBCredentials(db_user, db_passw, db_host, db_port, "unipax2");
		//	db2.persist(manager2);
		//	// assign new unipaxId by force
		//	db2.assignIds(manager2, true);*/
	writer.setDebug(false);
	if (true) std::cout << "Writing " << result.getInstanceCount() << " objects to file." << std::endl;
	writer.setPersistenceManager(result);
	writer.write(output_file);

	return 0;
}

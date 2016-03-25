#ifndef BRIDGEDBWRAPPER_H
#define BRIDGEDBWRAPPER_H

#include <UNIPAX/COMMON/common.h>
#include <string>
#include <vector>
#include <map>

namespace UniPAX
{

class UNIPAX_EXPORT BridgeDBWrapper
{
	public:

		BridgeDBWrapper();

		BridgeDBWrapper(std::string configFile);

		BridgeDBWrapper(const BridgeDBWrapper & rhv);

		BridgeDBWrapper & operator =(const BridgeDBWrapper & rhv);

		~BridgeDBWrapper();


		void parseConfigFile(std::string configFile);

		bool isMappingSupported(std::string source_id_system, std::string target_id_system);

		void mapIds(std::string src_system, std::vector<std::string> src_ids, std::string tgt_system, std::multimap<std::string, std::string> & id_mapping);

	protected:

		std::string executablePath;
		std::string mappingFilePath;
		std::string tmpFilePath;

		std::map<std::string, std::string> idSystems; // system names to codes map

}; // class BridgeDBWrapper

} // namespace UniPAX

#endif /* BRIDGEDBWRAPPER_H */

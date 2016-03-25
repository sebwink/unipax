#ifndef KERNEL_H_
#define KERNEL_H_

#include <UNIPAX/COMMON/common.h>
#include <UNIPAX/KERNEL/ClassType.h>

#include <string>
#include <map>
#include <set>
#include <vector>

namespace UniPAX
{

class UNIPAX_EXPORT Kernel
{

public:

	static bool isType(std::string type);

	static std::set<std::string> classes();

	static std::set<std::string> parents(std::string type, bool recursive = false);

	static std::set<std::string> children(std::string type, bool recursive = false);

	static std::vector<std::string> sorted_children(std::string type, bool recursive = false);

	static std::string shortType(std::string type);

	static ClassType::ID classType(std::string type);

	static std::string classType(ClassType::ID id, std::string default_value);

	static bool isClassType(std::string type);

	static bool isClassType(UniPAX::ClassType::ID id);

private:

	static std::set<std::string> _types;

	static std::map<std::string, ClassType::ID> _type_id;

	static std::map<ClassType::ID, std::string> _id_type;

	static std::map<std::string, std::vector<std::string> > _parents;

	static std::map<std::string, std::vector<std::string> > _children;

	static std::map<std::string, std::string> _shortType;

	static void children(std::string type, std::set<std::string> & v);

	static void children(std::string type, std::vector<std::string> & v);

	static void parents(std::string type, std::set<std::string> & v);

};

}



#endif /* KERNEL_H_ */

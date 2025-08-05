#ifndef LLM_PERMISSIONMODEL_HPP
#define LLM_PERMISSIONMODEL_HPP

#include "const/const_define.h"
#include "utility/reflection.hpp"

BEGIN_LLM_SPACE

struct permission_info {
	int id;
	int value;
	std::string remark;
	std::string create_at;
	std::string update_at;
};
REFLECTION(permission_info, 0, id, value, remark, create_at, update_at)

END_LLM_SPACE

#endif // !LLM_PERMISSIONMODEL_HPP

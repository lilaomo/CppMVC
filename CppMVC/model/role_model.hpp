#ifndef LLM_ROLEMODEL_HPP
#define LLM_ROLEMODEL_HPP

#include "const/const_define.h"
#include "utility/reflection.hpp"

BEGIN_LLM_SPACE

struct role_info {
	int id;
	std::array<char, 16> role_name;
	int permissions;
	std::string create_at;
	std::string update_at;
};
REFLECTION(role_info, 0, id, role_name, permissions, create_at, update_at)

END_LLM_SPACE

#endif // !LLM_ROLEMODEL_HPP

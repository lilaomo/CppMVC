#ifndef LLM_USERMODEL_HPP
#define LLM_USERMODEL_HPP

#include "const/const_define.h"
#include "utility/reflection.hpp"

BEGIN_LLM_SPACE

struct user_info {
	int id;
	std::array<char, 16> username;
	std::array<char, 16> password;
	char nickname[16];
	int role_id;
	std::string create_at;
	std::string update_at;
	std::string login_at;
};
REFLECTION(user_info, 0, id, username, password, nickname, role_id, create_at, update_at, login_at)


inline void init_user_info(user_info& user, const std::string& usn, const std::string& pwd, const std::string& nkn, int rid) {
	LLM reset_copy(user.username, usn);
	LLM reset_copy(user.password, pwd);
	LLM reset_copy(user.nickname, sizeof(user.nickname), nkn);
	user.role_id = rid;
	user.create_at = LLM get_current_time();
	user.update_at = LLM get_current_time();
}

END_LLM_SPACE

#endif // !LLM_USERMODEL_HPP

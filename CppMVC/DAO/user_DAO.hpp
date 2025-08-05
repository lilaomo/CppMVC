#ifndef LLM_USERDAO_HPP
#define LLM_USERDAO_HPP

#include "common_DAO.hpp"
#include "model/user_model.hpp"

BEGIN_LLM_SPACE

template<typename UserModel, 
	typename = CHECK_REFLECTION(UserModel), 
	typename = CHECK_CONTAINS(UserModel, user_info)>
class user_DAO : public detail::base_DAO<UserModel> {
	using user_m = UserModel;

public:
	user_DAO() {

	}

	~user_DAO() {

	}

	bool select_by_param(std::vector<user_m>& user, int id, const std::string& username, const std::string& nickname, int role_id) {
		std::string cond;
		if (id > 0)
			cond.append(std::format("and id = {}", id));
		if (!username.empty())
			cond.append(std::format("and username = '{}'", username));
		if (!nickname.empty())
			cond.append(std::format("and nickname = '{}'", nickname));
		if (role_id > 0)
			cond.append(std::format("and role_id = {}", role_id));
		return this->db_->select(user, cond);
	}

	bool select_by_id(user_m& user, int id) {
		std::vector<user_m> res;
		bool ret = this->db_->select(res, lilaomo::and_("id ="), id);
		if (ret && res.size() != 0)
			user = std::move(res[0]);
		return ret;
	}

	bool select_by_name(user_m& user, const std::string& username) {
		std::vector<user_m> res;
		bool ret = this->db_->select(res, lilaomo::and_("username ="), username);
		if (ret && res.size() != 0)
			user = std::move(res[0]);
		return ret;
	}

	bool select_all(std::vector<user_m>& user) {
		return this->db_->select(user);
	}

	int delete_by_id(int id) {
		return this->db_->func_delete<user_m>(lilaomo::and_("id ="), id);
	}

	int delete_by_name(const std::string& username) {
		return this->db_->func_delete<user_m>(lilaomo::and_("username ="), username);
	}
};

END_LLM_SPACE

#endif // !LLM_USERDAO_HPP

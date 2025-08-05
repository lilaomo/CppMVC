#ifndef LLM_USERSERVIMPL_HPP
#define LLM_USERSERVIMPL_HPP

#include "utility/model_utility.hpp"
#include "DAO/user_DAO.hpp"

BEGIN_LLM_SPACE_EX

class user_serv_impl {
public:
	user_serv_impl() {
		user_dao_.create_table(primary_key{ "id" }, autoincrement{ "id" });
	}
	~user_serv_impl() {}

	template<typename UserModel>
	serv_result login(const std::string& username, const std::string& password) {
		if (username.empty())
			return { serv_error::username_err, "username can not empty" };

		if constexpr (LLM is_user_info_v<UserModel>) {
			LLM user_info user;
			if (!user_dao_.select_by_name(user, username))
				return res_db_err();

			if (!LLM char_equal(user.password, password))
				return { serv_error::password_err, "password is not equal" };
			
			user.login_at = LLM get_current_time();
			user_dao_.update_one(user);
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

	template<typename UserModel>
	serv_result get_user(std::vector<UserModel>& user, int id) {
		if constexpr (LLM is_user_info_v<UserModel>) {
			if (!user_dao_.select_by_id(user, id))
				return res_db_err();
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

	template<typename UserModel>
	serv_result get_user(std::vector<UserModel>& user, int id, const std::string& username, const std::string& nickname, int role_id) {
		if constexpr (LLM is_user_info_v<UserModel>) {
			if (!user_dao_.select_by_param(user, id, username, nickname, role_id))
				return res_db_err();
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

	template<typename UserModel>
	serv_result update_user(const UserModel& user) {
		if constexpr (LLM is_user_info_v<UserModel>) {
			if (user.id < 1 || LLM char_empty(user.username) || LLM char_empty(user.password) || user.role_id < 1)
				return { serv_error::user_param_err, "id or username or password or role id can not empty error" };

			if (user_dao_.update_one(user) == -1)
				return res_db_err();
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

	template<typename UserModel>
	serv_result add_user(const UserModel& user) {
		if constexpr (LLM is_user_info_v<UserModel>) {
			if (LLM char_empty(user.username) || LLM char_empty(user.password) || user.role_id < 1)
				return { serv_error::user_param_err, "username or password or role id can not empty error" };

			if (user_dao_.insert_one<LLM AUTOINCREMENT>(user) == -1)
				return res_db_err();
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

	template<typename UserModel>
	serv_result delete_user(int id) {
		if (id < 1)
			return { serv_error::user_id_err, "user id can not less than 1" };

		if constexpr (LLM is_user_info_v<UserModel>) {
			if (!user_dao_.delete_by_id(id))
				return res_db_err();
		}
		else return res_model_err<UserModel>();
		return res_success();
	}

private:
	serv_result res_success() {
		return { serv_error::success, "success" };
	}

	template<typename UserNodel>
	serv_result res_model_err() {
		return { serv_error::model_not_support, std::format("not support this user model({}) now", typeid(UserNodel).name()) };
	}

	serv_result res_db_err() {
		return { serv_error::db_err, user_dao_.last_error() };
	}

private:
	user_DAO<user_info> user_dao_;
};

END_LLM_SPACE_EX

#endif // !LLM_USERSERVIMPL_HPP

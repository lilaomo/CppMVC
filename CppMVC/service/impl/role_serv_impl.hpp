#ifndef LLM_ROLESERVIMPL_HPP
#define LLM_ROLESERVIMPL_HPP

#include "DAO/role_DAO.hpp"

BEGIN_LLM_SPACE_EX

class role_serv_impl {
public:
	role_serv_impl() {
		role_dao_.create_table(primary_key{ "id" }, autoincrement{ "id" });
	}
	~role_serv_impl() {}

	template<typename RoleModel>
	serv_error get_role(int id, RoleModel& role, std::string& err) {
		if (id < 1) {
			err = "role id can not less than 1";
			return serv_error::role_id_err;
		}

		if constexpr (std::is_same_v<RoleModel, role_info>) {
			bool ret = role_dao_.select_by_id(role, id);
			if (!ret) {
				err = role_dao_.last_error();
				return serv_error::db_err;
			}
		}
		else return serv_error::model_not_support;
		return serv_error::success;
	}

private:
	role_DAO<role_info> role_dao_;
};

END_LLM_SPACE_EX

#endif // !LLM_ROLESERVIMPL_HPP
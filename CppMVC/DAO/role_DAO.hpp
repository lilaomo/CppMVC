#ifndef LLM_ROLEDAO_HPP
#define LLM_ROLEDAO_HPP

#include "common_DAO.hpp"
#include "model/role_model.hpp"

BEGIN_LLM_SPACE

template<typename RoleModel, 
	typename = CHECK_REFLECTION(RoleModel),
	typename = CHECK_CONTAINS(RoleModel, role_info)>
class role_DAO : public detail::base_DAO<RoleModel> {
	using role_m = RoleModel;

public:
	role_DAO() {

	}

	~role_DAO() {

	}

	template<typename... Args>
	bool create_table(Args&&... args) {
		return this->db_->create_table<role_m>(std::forward<Args>(args)...);
	}

	template<typename... Args>
	bool create_index(const std::string& index_name, Args&&... args) {
		return this->db_->create_index<role_m>(index_name, std::forward<Args>(args)...);
	}

	bool select_by_id(role_m& role, int id) {
		std::vector<role_m> res;
		bool ret = this->db_->select(res, lilaomo::and_("id ="), id);
		if (ret && res.size() != 0)
			role = std::move(res[0]);
		return ret;
	}

	bool select_by_permission(std::vector<role_m>& role, int permission) {
		return this->db_->select(role, lilaomo::and_("permissions ="), permission);
	}

	int delete_by_id(int id) {
		return this->db_->func_delete<role_m>(lilaomo::and_("id ="), id);
	}
};

END_LLM_SPACE

#endif // !LLM_ROLEDAO_HPP

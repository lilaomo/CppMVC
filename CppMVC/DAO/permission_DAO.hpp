#ifndef LLM_PERMISSIONDAO_HPP
#define LLM_PERMISSIONDAO_HPP

#include "common_DAO.hpp"
#include "model/permission_model.hpp"

BEGIN_LLM_SPACE

template<typename PermissionModel, 
	typename = CHECK_REFLECTION(PermissionModel),
	typename = CHECK_CONTAINS(PermissionModel, permission_info)>
class permission_DAO : public detail::base_DAO<PermissionModel> {
	using pers_m = PermissionModel;

public:
	permission_DAO() {

	}

	~permission_DAO() {

	}

	template<typename... Args>
	bool create_table(Args&&... args) {
		return this->db_->create_table<pers_m>(std::forward<Args>(args)...);
	}

	template<typename... Args>
	bool create_index(const std::string& index_name, Args&&... args) {
		return this->db_->create_index<pers_m>(index_name, std::forward<Args>(args)...);
	}

	bool select_by_id(pers_m& pers, int id) {
		std::vector<pers_m> res;
		bool ret = this->db_->select<pers_m>(res, lilaomo::and_("id ="), id);
		if (ret && res.size() != 0)
			pers = std::move(res[0]);
		return ret;
	}

	int delete_by_id(int id) {
		return this->db_->func_delete<pers_m>(lilaomo::and_("id ="), id);
	}
};

END_LLM_SPACE

#endif // !LLM_PERMISSIONDAO_HPP

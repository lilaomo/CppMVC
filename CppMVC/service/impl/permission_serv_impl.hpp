#ifndef LLM_PERMISSIOSERVIMPL_HPP
#define LLM_PERMISSIOSERVIMPL_HPP

#include "DAO/permission_DAO.hpp"

BEGIN_LLM_SPACE_EX

class permission_serv_impl {
public:
	permission_serv_impl() {
		perm_dao_.create_table(primary_key{ "id" }, autoincrement{ "id" });
	}
	~permission_serv_impl() {}

private:
	permission_DAO<permission_info> perm_dao_;
};

END_LLM_SPACE_EX

#endif // !LLM_PERMISSIOSERVIMPL_HPP
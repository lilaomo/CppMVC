#ifndef LLM_ROLESERVICE_HPP
#define LLM_ROLESERVICE_HPP

#include "const/const_define.h"
#include <memory>

BEGIN_LLM_SPACE

template<typename Impl>
class role_service {
public:
	using impl_type = Impl;
	using impl_ptr = std::unique_ptr<impl_type>;

	role_service() : impl_(std::make_unique<impl_type>()) {}
	~role_service() {}

	template<typename RoleModel>
	serv_error get_role(int id, RoleModel& role, std::string& err) {
		return  impl_->get_role<RoleModel>(id, role, err);
	}

private:
	impl_ptr impl_;
};

END_LLM_SPACE

#endif // !LLM_ROLESERV_HPP
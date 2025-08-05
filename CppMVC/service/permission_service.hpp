#ifndef LLM_PERMISSIONSERVICE_HPP
#define LLM_PERMISSIONSERVICE_HPP

#include "const/const_define.h"
#include <memory>

BEGIN_LLM_SPACE

template<typename Impl>
class permission_service {
public:
	using impl_type = Impl;
	using impl_ptr = std::unique_ptr<impl_type>;

	permission_service() : impl_(std::make_unique<impl_type>()) {}
	~permission_service() {}

private:
	impl_ptr impl_;
};

END_LLM_SPACE

#endif // !LLM_PERMISSIONSERV_HPP

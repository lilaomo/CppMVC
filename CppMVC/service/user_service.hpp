#ifndef LLM_USERSERVICE_HPP
#define LLM_USERSERVICE_HPP

#include "const/const_define.h"

#include <memory>

BEGIN_LLM_SPACE

template<typename Impl>
class user_service {
public:
	using impl_type = Impl;
	using impl_ptr = std::unique_ptr<impl_type>;

	user_service() : impl_(std::make_unique<impl_type>()) {}
	~user_service() {}

	template<typename UserModel, typename... Args>
	serv_result login(Args&&... args) {
		return impl_->login<UserModel>(std::forward<Args>(args)...);
	}

	template<typename... Args>
	serv_result get_user(Args&&... args) {
		return impl_->get_user(std::forward<Args>(args)...);
	}

	template<typename UserModel, typename... Args>
	serv_result update_user(Args&&... args) {
		return impl_->update_user(std::forward<Args>(args)...);
	}

	template<typename UserModel, typename... Args>
	serv_result add_user(Args&&... args) {
		return impl_->add_user(std::forward<Args>(args)...);
	}

	template<typename UserModel, typename... Args>
	serv_result delete_user(Args&&... args) {
		return impl_->delete_user<UserModel>(std::forward<Args>(args)...);
	}

private:
	impl_ptr impl_;
};

END_LLM_SPACE

#endif // !LLM_USERSERVICE_HPP

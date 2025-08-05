#ifndef LLM_PERMISSIONCTRLLER_H
#define LLM_PERMISSIONCTRLLER_H

#include "common_ctrller.hpp"
#include "service/permission_service.hpp"
#include "service/impl/permission_serv_impl.hpp"
#include "aspect/api_aspect.h"
#include "aspect/token_aspect.h"

BEGIN_LLM_SPACE

using permission_service_t = permission_service<detail::permission_serv_impl>;

class permission_ctrller : public common_ctrller<permission_ctrller, permission_service_t> {
	using base_type = common_ctrller<permission_ctrller, permission_service_t>;

public:
	permission_ctrller();
	~permission_ctrller();

	void login(cinatra::request& req, cinatra::response& res);
	void logout(cinatra::request& req, cinatra::response& res);
	void update_user(cinatra::request& req, cinatra::response& res);

	void get_all_user(cinatra::request& req, cinatra::response& res);
	void add_user(cinatra::request& req, cinatra::response& res);
	void delete_user(cinatra::request& req, cinatra::response& res);

public:
	static constexpr inline base_type::url_type url = { 
		{"/user/login", &permission_ctrller::login},
		{"/user/logout", &permission_ctrller::logout},
		{"/user/update", &permission_ctrller::update_user},
		{"/user/get_all", &permission_ctrller::get_all_user},
		{"/user/add", &permission_ctrller::add_user},
		{"/user/delete", &permission_ctrller::delete_user}
	};
	static inline base_type::aspect_type asp = { std::make_unique<api_aspect>(), std::make_unique<token_aspect>() };

};

END_LLM_SPACE

#endif // !LLM_PERMISSIONCTRLLER_H

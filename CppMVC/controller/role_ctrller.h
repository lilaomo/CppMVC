#ifndef LLM_ROLECTRLLER_H
#define LLM_ROLECTRLLER_H

#include "common_ctrller.hpp"
#include "service/role_service.hpp"
#include "service/impl/role_serv_impl.hpp"
#include "aspect/api_aspect.h"
#include "aspect/token_aspect.h"

BEGIN_LLM_SPACE

using role_service_t = role_service<detail::role_serv_impl>;

class role_ctrller : public common_ctrller<role_ctrller, role_service_t> {
	using base_type = common_ctrller<role_ctrller, role_service_t>;

public:
	role_ctrller();
	~role_ctrller();

	void login(cinatra::request& req, cinatra::response& res);
	void logout(cinatra::request& req, cinatra::response& res);
	void update_user(cinatra::request& req, cinatra::response& res);

	void get_all_user(cinatra::request& req, cinatra::response& res);
	void add_user(cinatra::request& req, cinatra::response& res);
	void delete_user(cinatra::request& req, cinatra::response& res);

public:
	static constexpr inline base_type::url_type url = { 
		{"/user/login", &role_ctrller::login},
		{"/user/logout", &role_ctrller::logout},
		{"/user/update", &role_ctrller::update_user},
		{"/user/get_all", &role_ctrller::get_all_user},
		{"/user/add", &role_ctrller::add_user},
		{"/user/delete", &role_ctrller::delete_user}
	};
	static inline base_type::aspect_type asp = { std::make_unique<api_aspect>(), std::make_unique<token_aspect>() };

};

END_LLM_SPACE

#endif // !LLM_ROLECTRLLER_H

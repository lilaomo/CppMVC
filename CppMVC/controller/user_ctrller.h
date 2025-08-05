#ifndef LLM_USERCTRLLER_H
#define LLM_USERCTRLLER_H

#include "common_ctrller.hpp"
#include "service/user_service.hpp"
#include "service/impl/user_serv_impl.hpp"
#include "aspect/api_aspect.h"
#include "aspect/token_aspect.h"

BEGIN_LLM_SPACE

using user_service_t = user_service<detail::user_serv_impl>;

class user_ctrller : public common_ctrller<user_ctrller, user_service_t> {
	using base_type = common_ctrller<user_ctrller, user_service_t>;

public:
	user_ctrller();
	~user_ctrller();

	void login(cinatra::request& req, cinatra::response& res);
	void logout(cinatra::request& req, cinatra::response& res);
	void update_user(cinatra::request& req, cinatra::response& res);

	void get_user(cinatra::request& req, cinatra::response& res);
	void add_user(cinatra::request& req, cinatra::response& res);
	void delete_user(cinatra::request& req, cinatra::response& res);

public:
	static constexpr inline base_type::url_type url = { 
		{"/user/login", &user_ctrller::login}, 
		{"/user/logout", &user_ctrller::logout},
		{"/user/update", &user_ctrller::update_user},
		{"/user/get", &user_ctrller::get_user},
		{"/user/add", &user_ctrller::add_user},
		{"/user/delete", &user_ctrller::delete_user}
	};
	static inline base_type::aspect_type asp = { std::make_unique<api_aspect>(), std::make_unique<token_aspect>() };

};

END_LLM_SPACE

#endif // !LLM_USERCTRLLER_H

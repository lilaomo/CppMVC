#include "controller/user_ctrller.h"

lilaomo::user_ctrller::user_ctrller() : common_ctrller<user_ctrller, user_service_t>("user_ctrller"sv) {

}

lilaomo::user_ctrller::~user_ctrller() {

}



void lilaomo::user_ctrller::login(cinatra::request& req, cinatra::response& res) {
	auto&& [ret, req_json] = pre_handle_json(req, res);
	if (!ret)
		return;

	auto&& [errcode, err] = this->serv_->login<LLM user_info>(req_json.value("username", ""), req_json.value("password", ""));

	nlohmann::json&& res_json = comm_res_json(errcode, std::move(err));
	set_response_json(res, res_json.dump());
}



void lilaomo::user_ctrller::logout(cinatra::request& req, cinatra::response& res) {
	if (!pre_handle(req, res))
		return;
	nlohmann::json&& res_json = comm_res_json(serv_error::success, "logout success");
	set_response_json(res, res_json.dump());
}



void lilaomo::user_ctrller::update_user(cinatra::request& req, cinatra::response& res) {
	auto&& [ret, req_json] = pre_handle_json(req, res);
	if (!ret)
		return;

	LLM user_info user = LLM obj_from_json<LLM user_info>(req_json);
	auto&& [errcode, err] = this->serv_->update_user<LLM user_info>(user);

	nlohmann::json&& res_json = comm_res_json(errcode, std::move(err));
	set_response_json(res, res_json.dump());
}



void lilaomo::user_ctrller::get_user(cinatra::request& req, cinatra::response& res) {
	auto&& [ret, req_json] = pre_handle_json(req, res);
	if (!ret)
		return;

	std::vector<LLM user_info> user;
	auto&& [errcode, err] = this->serv_->get_user(user, req_json.value("id", -1), req_json.value("username", ""), 
		req_json.value("nickname", ""), req_json.value("role_id", -1));

	nlohmann::json&& res_json = comm_res_json(errcode, std::move(err));
	res_json["data"] = LLM obj_to_json(user);
	set_response_json(res, res_json.dump());
}



void lilaomo::user_ctrller::add_user(cinatra::request & req, cinatra::response & res) {
	auto&& [ret, req_json] = pre_handle_json(req, res);
	if (!ret)
		return;

	LLM user_info user = LLM obj_from_json<LLM user_info>(req_json);
	auto&& [errcode, err] = this->serv_->add_user<LLM user_info>(user);

	nlohmann::json&& res_json = comm_res_json(errcode, std::move(err));
	set_response_json(res, res_json.dump());
}



void lilaomo::user_ctrller::delete_user(cinatra::request& req, cinatra::response& res) {
	auto&& [ret, req_json] = pre_handle_json(req, res);
	if (!ret)
		return;

	int32_t id = req_json["id"].is_null() ? -1 : req_json["id"].get<int32_t>();
	auto&& [errcode, err] = this->serv_->delete_user<user_info>(id);

	nlohmann::json&& res_json = comm_res_json(errcode, std::move(err));
	set_response_json(res, res_json.dump());
}
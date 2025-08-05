#ifndef LLM_COMMONCTRLLER_H
#define LLM_COMMONCTRLLER_H

#undef TRACE
#define ASIO_STANDALONE

#include "utility/llm_utility.hpp"
#include "aspect/base_aspect.h"

#include "third_part/cinatra/http_server.hpp"
#include "third_part/nlohmann/json.hpp"

BEGIN_LLM_SPACE

template<typename Child, typename Service>
class common_ctrller {
public:
	using child_type = Child;
	using service_type = Service;

	using serv_ptr = std::unique_ptr<service_type>;
	using func_type = void(Child::*)(cinatra::request&, cinatra::response&);
	using url_type = std::pair<std::string_view, func_type>[];
	using aspect_ptr = std::unique_ptr<lilaomo::base_aspect>;
	using aspect_type = aspect_ptr[];
	using pre_json_type = std::pair<bool, nlohmann::json>;

	common_ctrller(std::string_view ctrll_name) : serv_(std::make_unique<service_type>()), ctrll_name_(ctrll_name) {}
	virtual ~common_ctrller() {};

	inline static constexpr std::size_t get_url_count() {
		return sizeof(child_type::url) / sizeof(child_type::url[0]);
	}

	inline static constexpr std::size_t get_aspect_count() {
		return sizeof(child_type::asp) / sizeof(child_type::asp[0]);
	}

	template<std::size_t I>
	std::pair<std::string_view, unsigned int*> get_register() {
		constexpr auto item = child_type::url[I];
		return std::make_pair(item.first, LLM to_int_ptr(item.second));
	}

	decltype(auto) get_aspect_tuple() {
		return make_aspect_tuple(std::make_index_sequence<get_aspect_count()>{});
	}

	std::string_view get_ctrller_name() const noexcept {
		return ctrll_name_;
	}

protected:
	bool pre_handle(const cinatra::request& req, cinatra::response& res) const {
		res.add_header("Access-Control-Allow-Origin", "*");
		res.add_header("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
		res.add_header("Access-Control-Allow-Credentials", "true");
		res.add_header("Access-Control-Allow-Headers", "X-Token, lang, authorization");
		res.add_header("Vary", "Origin");

		if (req.get_method() == "OPTIONS") {
			res.set_status_and_content(cinatra::status_type::ok);
			return false;
		}
		return true;
	}

	pre_json_type pre_handle_json(const cinatra::request& req, cinatra::response& res) const {
		if (!pre_handle(req, res))
			return { false, {} };

		nlohmann::json req_json;
		std::string body(req.body());
		if (!body.empty()) {
			req_json = nlohmann::json::parse(body, nullptr, false);
			if (req_json.is_discarded()) {
				res.set_status_and_content(cinatra::status_type::bad_request, "parse json failed");
				return { false, std::move(req_json) };
			}
		}
		return { true, std::move(req_json) };
	}

	bool pre_handle_file(const cinatra::request& req, cinatra::response& res) const {
		if (!pre_handle(req, res))
			return false;
		return req.get_content_type() == cinatra::content_type::octet_stream || req.get_content_type() == cinatra::content_type::multipart;
	}

	nlohmann::json comm_res_json(serv_error err_code, std::string&& err_info) {
		nlohmann::json res_json;
		res_json["err_code"] = err_code;
		res_json["err_info"] = std::move(err_info);
		res_json["time"] = LLM get_current_time();
		return res_json;
	}

	void set_response_json(cinatra::response& res, std::string&& str_res) const {
		res.set_status_and_content(cinatra::status_type::ok, std::move(str_res), cinatra::req_content_type::json);
	}

private:
	template<std::size_t... N>
	decltype(auto) make_aspect_tuple(const std::index_sequence<N...>&) {
		return std::make_tuple(child_type::asp[N].get()...);
	}

protected:
	serv_ptr serv_;
	std::string_view ctrll_name_;
};

END_LLM_SPACE

#endif // !LLM_COMMONCTRLLER_H

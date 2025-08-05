#ifndef LLM_TOKENASPECT_H
#define LLM_TOKENASPECT_H

#include "aspect/base_aspect.h"

BEGIN_LLM_SPACE

struct token_aspect : public base_aspect {
	bool before(cinatra::request& req, cinatra::response& res) {
		auto token = req.get_header_value("token");
		LLMLOG_D("token check, url: {}, token: {}", req.get_url(), token);
		if (!check_token(req.get_url(), token)) {
			LLMLOG_E("token check failed, token: {}", token);
			res.set_status_and_content(cinatra::status_type::bad_request, "token check failed");
			return false;
		}
		LLMLOG_D("token check success.");
		return true;
	}

	bool after(cinatra::request& req, cinatra::response& res) {
		if (req.get_url() == "/user/login")
			res.add_header("token", "test");
		return true;
	}

	bool check_token(const std::string_view& url, const std::string_view& token) {
		if (url == "/user/login")
			return true;

		if (token.empty())
			return false;
		return true;
	}
};

END_LLM_SPACE

#endif // !LLM_TOKENASPECT_H

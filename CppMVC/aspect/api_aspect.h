#ifndef LLM_APIASPECT_H
#define LLM_APIASPECT_H

#include "aspect/base_aspect.h"

BEGIN_LLM_SPACE

struct api_aspect : public base_aspect {
	bool before(cinatra::request& req, cinatra::response& res) {
		auto&& begin_time = std::chrono::steady_clock::now();
		req.set_aspect_data("btime", std::move(begin_time));
		LLMLOG_I("start url: {}", req.get_url());
		return true;
	}

	bool after(cinatra::request& req, cinatra::response& res) {
		auto&& begin_time = req.get_aspect_data<std::chrono::steady_clock::time_point>("btime");
		std::chrono::duration<double> spc_time = std::chrono::steady_clock::now() - begin_time;
		LLMLOG_I("end url: {}, total cost: {}s", req.get_url(), spc_time.count());
		return true;
	}
};

END_LLM_SPACE

#endif // !LLM_APIASPECT_H

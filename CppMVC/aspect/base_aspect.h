#ifndef LLM_BASEASPECT_H
#define LLM_BASEASPECT_H

#include "const/const_define.h"
#include "logger/logger.hpp"

#include "third_part/cinatra/request.hpp"
#include "third_part/cinatra/response.hpp"

BEGIN_LLM_SPACE

struct base_aspect {
	virtual ~base_aspect() {}
	virtual bool before(cinatra::request& req, cinatra::response& res) = 0;
	virtual bool after(cinatra::request& req, cinatra::response& res) = 0;
};

END_LLM_SPACE

#endif // !LLM_BASEASPECT_H

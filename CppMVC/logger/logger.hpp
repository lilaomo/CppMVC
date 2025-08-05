#ifndef LLM_LOGGER_HPP
#define LLM_LOGGER_HPP

#include "config/cfg.hpp"
#include "utility/llm_utility.hpp"

#include "third_part/spdlog/spdlog.h"
#include "third_part/spdlog/sinks/daily_file_sink.h"

#define LLM_PRE_LOG "{} {}# "
#define LLM_FILENAME lilaomo::get_name_from_path(__FILE__)

#define LLMLOG(lvl, fmt, ...) lilaomo::loged<lvl>(fmt, __VA_ARGS__)
#define LLMLOG_T(fmt, ...) lilaomo::loged<lilaomo::log_level::level_trace>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_D(fmt, ...) lilaomo::loged<lilaomo::log_level::level_debug>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_I(fmt, ...) lilaomo::loged<lilaomo::log_level::level_info>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_W(fmt, ...) lilaomo::loged<lilaomo::log_level::level_warn>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_E(fmt, ...) lilaomo::loged<lilaomo::log_level::level_error>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_C(fmt, ...) lilaomo::loged<lilaomo::log_level::level_critical>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)
#define LLMLOG_O(fmt, ...) lilaomo::loged<lilaomo::log_level::level_off>(LLM_PRE_LOG fmt, LLM_FILENAME, __LINE__, __VA_ARGS__)

BEGIN_LLM_SPACE

namespace detail {

template<typename... Args>
using llm_format_t = typename spdlog::format_string_t<Args...>;

}

template<log_t LogType = log_t::multi_thrd>
class logger : noncopyable {
	using sink_type = std::conditional_t<LogType == log_t::multi_thrd, spdlog::sinks::daily_file_sink_mt, spdlog::sinks::daily_file_sink_st>;
	using sink_ptr = std::shared_ptr<sink_type>;
	using log_ptr = std::shared_ptr<spdlog::logger>;

public:
	static logger<LogType>* instance() {
		static logger<LogType> log;
		return &log;
	}

	void init(int hh, int mm, log_level lvl, std::size_t flush_time) {
		init_sink(hh, mm, lvl);
		init_log();
		spdlog::register_logger(logger_);
		spdlog::flush_every(std::chrono::seconds(flush_time));
	}

	template<log_level Lvl, typename... Args>
	void log(const detail::llm_format_t<Args...>& fmt, Args&&... args) {
		logger_->log(spdlog::level::level_enum(Lvl), fmt, std::forward<Args>(args)...);
	}

private:
	logger() {
	}

	~logger() {
	}

	void init_sink(int hh, int mm, log_level lvl) {
		normal_sink_ = std::make_shared<sink_type>("logs/llm_info.log", hh, mm);
		error_sink_ = std::make_shared<sink_type>("logs/llm_error.log", hh, mm);
		normal_sink_->set_level(spdlog::level::level_enum(lvl));
		error_sink_->set_level(spdlog::level::err);

		sink_vec_.push_back(normal_sink_);
		sink_vec_.push_back(error_sink_);
	}

	void init_log() {
		logger_ = std::make_shared<spdlog::logger>("lilaomo_log", std::begin(sink_vec_), std::end(sink_vec_));
		logger_->set_pattern("[%l] [%Y-%m-%d %H:%M:%S,%e] [thread id: %t] - %v");
		logger_->flush_on(spdlog::level::err);
	}

private:
	log_ptr logger_;
	sink_ptr normal_sink_;
	sink_ptr error_sink_;
	std::vector<spdlog::sink_ptr> sink_vec_;
};


template<log_level Lvl, typename... Args>
void loged(detail::llm_format_t<Args...> fmt, Args&&... args) {
	auto logger = lilaomo::logger<>::instance();
	logger->log<Lvl>(fmt, std::forward<Args>(args)...);
}

END_LLM_SPACE

#endif // !LLM_LOGGER_HPP

#ifndef LLM_SERVER_HPP
#define LLM_SERVER_HPP

#include "controller/user_ctrller.h"
#include "aspect/api_aspect.h"

#ifdef SSL_SERV
#define CINATRA_ENABLE_SSL
#endif // SSL_SERV

BEGIN_LLM_SPACE

struct ssl_serv {};
struct non_serv {};

template<typename ServType, typename U = std::conditional_t<std::is_same_v<ServType, non_serv>, cinatra::NonSSL, cinatra::SSL>>
class server {
	using serv_type = ServType;
	using cinatra_type = U;
	using serv_ptr = std::unique_ptr<cinatra::http_server_proxy<cinatra_type>>;

	using user_ctrller_t = common_ctrller<user_ctrller, user_service_t>;

public:
	explicit server(std::size_t thrd_cnt)
		: serv_(std::make_unique<cinatra::http_server_proxy<cinatra_type>>(thrd_cnt))
		, user_ctrl_(std::make_unique<user_ctrller>())
		, run_flag_(false)
		, thrd_cnt_(thrd_cnt)
	{
		register_url<user_ctrller_t::get_url_count(), user_ctrller_t::get_aspect_count()>(user_ctrl_.get());
	}

	~server() {
		stop();
	}

	bool start(const std::string& ip, const std::string& port, long keep_alive_timeout) {
		LLMLOG_D("start function ================================= in");
		if (run_flag_) {
			LLMLOG_E("server has been started.");
			return true;
		}

		LLMLOG_D("go to function init...");
		if (!init(ip, port, keep_alive_timeout)) {
			LLMLOG_E("init server failed.");
			return false;
		}

		LLMLOG_D("run...");
		serv_->run();
		run_flag_ = true;
		LLMLOG_D("start function ================================= out");
		return true;
	}

	void restart(const std::string& ip, const std::string& port) {
		LLMLOG_D("restart function ================================= in");
		stop();
		serv_.reset(new cinatra::http_server_proxy<cinatra_type>(thrd_cnt_));
		return start(ip, port);
	}

	void stop() {
		LLMLOG_D("stop function ================================= in");
		if (run_flag_) {
			LLMLOG_D("stop...");
			serv_->stop();
			run_flag_ = false;
		}
		LLMLOG_D("stop function ================================= out");
	}

private:
	bool init(const std::string& ip, const std::string& port, long keep_alive_timeout) {
		LLMLOG_D("init function ================================= in");
		if constexpr (std::is_same_v<serv_type, ssl_serv>)
			serv_->set_ssl_conf({ "server.crt", "server.key" });

		LLMLOG_D("listen port...");
		if (!serv_->listen(ip, port)) {
			LLMLOG_E("init function, listen port failed");
			return false;
		}

		serv_->set_static_dir("./www");
		serv_->set_keep_alive_timeout(keep_alive_timeout);
		LLMLOG_D("keep alive timeout {}s", keep_alive_timeout);
		LLMLOG_D("init function ================================= out");
		return true;
	}

	template<std::size_t UrlCnt, std::size_t AspCnt, typename Ctrller>
	void register_url(Ctrller ctrller) {
		LLMLOG_D("register {} url...", ctrller->get_ctrller_name());
		register_url<UrlCnt>(ctrller, std::make_index_sequence<AspCnt>{});
	}

	template<std::size_t UrlCnt, typename Ctrller, std::size_t... N>
	void register_url(Ctrller ctrller, const std::index_sequence<N...>&) {
		auto aspect_tuple = ctrller->get_aspect_tuple();
		register_url_impl(ctrller, std::make_index_sequence<UrlCnt>{}, std::get<N>(aspect_tuple)...);
	}

	template<typename Ctrller, std::size_t... N, typename... Args>
	void register_url_impl(Ctrller ctrller, const std::index_sequence<N...>&, Args&&... args) {
		register_url_impl2<N...>(ctrller, std::forward<Args>(args)...);
	}

	template<std::size_t I, std::size_t... N, typename Ctrller, typename... Args>
	void register_url_impl2(Ctrller ctrller, Args&&... args) {
		using ObjType = typename std::remove_pointer<std::decay_t<Ctrller>>::type;
		using FuncType = void(ObjType::*)(cinatra::request&, cinatra::response&);
		auto u = ctrller->get_register<I>();
		FuncType func = LLM from_int_ptr<FuncType>(u.second);
		serv_->set_http_handler<cinatra::OPTIONS, cinatra::GET, cinatra::POST>
			(u.first, func, ctrller, args...);
		register_url_impl2<N...>(ctrller, std::forward<Args>(args)...);
	}

	template<typename Ctrller, typename... Args>
	void register_url_impl2(Ctrller ctrller, Args&&... args) {}

private:
	serv_ptr serv_;
	std::unique_ptr<user_ctrller> user_ctrl_;

	std::atomic_bool run_flag_;
	std::size_t thrd_cnt_;
};

#ifdef SSL_SERV
template<typename... Args>
decltype(auto) make_ssl_serv(Args&&... args) {
	return std::make_unique<server<ssl_serv>>(std::forward<Args>(args)...);
}

using ssl_server = std::unique_ptr<server<ssl_serv>>;
#endif // !SSL_SERV

template<typename... Args>
decltype(auto) make_nonssl_serv(Args&&... args) {
	return std::make_unique<server<non_serv>>(std::forward<Args>(args)...);
}

using nonssl_server = std::unique_ptr<server<non_serv>>;

END_LLM_SPACE

#endif // !LLM_SERVER_HPP

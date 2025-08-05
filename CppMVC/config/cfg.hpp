#ifndef LLM_CFG_HPP
#define LLM_CFG_HPP

#include "const/const_define.h"
#include "utility/llm_utility.hpp"

BEGIN_LLM_SPACE

namespace detail {

struct log_config {
	int hh;
	int mm;
	log_level lvl;
	std::size_t sec;

	void set(int h, int m, log_level l, std::size_t s) {
		hh = h;
		mm = m;
		lvl = l;
		sec = s;
	}
};


struct serv_config {
	std::string ip;
	std::string port;
	long keep_alive_timeout;

	void set(std::string&& i, std::string&& p, long time) {
		ip = std::move(i);
		port = std::move(p);
		keep_alive_timeout = time;
	}
};

struct db_config {
	std::string str_db;

	struct db_mysql {
		std::string ip;
		uint32_t port;
		std::string user;
		std::string pwd;
		std::string db;
	} mysql_db;

	struct db_sqlite {
		std::string file_path;
	} sqlite_db;

	void set(std::string&& ip, uint32_t port, std::string&& user, std::string&& pwd, std::string&& db) {
		mysql_db.ip = std::move(ip);
		mysql_db.port = port;
		mysql_db.user = std::move(user);
		mysql_db.pwd = std::move(pwd);
		mysql_db.db = std::move(db);
		str_db = "mysql";
	}

	void set(std::string&& file_path) {
		sqlite_db.file_path = std::move(file_path);
		str_db = "sqlite";
	}
};

}


class configure {
public:
	configure() {}
	~configure() {}

	template<database_t DB>
	bool load_config() {
		std::string&& cfg_path = std::format("{}\\system.json", get_current_path());
		std::ifstream ifs(cfg_path, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) {
			err_ = std::format("can not open file, path: {}", cfg_path);
			return false;
		}

		try {
			auto&& cfg = nlohmann::json::parse(ifs);
			log_cfg_.set(cfg["log"]["hour"].get<int>(), cfg["log"]["min"].get<int>(),
				log_level(cfg["log"]["level"].get<int>()), cfg["log"]["flush_sec"].get<std::size_t>());
			serv_cfg_.set(cfg["server"]["ip"].get<std::string>(), cfg["server"]["port"].get<std::string>(), 
				cfg["server"]["keep_alive_timeout"].get<long>());

			if constexpr (DB == database_t::mysql) {
				db_cfg_.set(cfg["database"]["mysql"]["ip"].get<std::string>(), cfg["database"]["mysql"]["port"].get<uint32_t>(),
					cfg["database"]["mysql"]["user"].get<std::string>(), cfg["database"]["mysql"]["pwd"].get<std::string>(),
					cfg["database"]["mysql"]["db"].get<std::string>());
			}
			else if constexpr (DB == database_t::sqlite) {
				db_cfg_.set(cfg["database"]["sqlite"]["path"].get<std::string>());
			}
			return true;
		}
		catch (const std::exception& e) {
			err_ = e.what();
			return false;
		}
	}

	std::string error() const noexcept {
		return err_;
	}

	const detail::log_config& log_cfg() const noexcept {
		return log_cfg_;
	}

	const detail::serv_config& serv_cfg() const noexcept {
		return serv_cfg_;
	}

	const detail::db_config& db_cfg() const noexcept {
		return db_cfg_;
	}

private:
	detail::log_config log_cfg_;
	detail::serv_config serv_cfg_;
	detail::db_config db_cfg_;
	std::string err_;
};

END_LLM_SPACE

#endif // !LLM_CFG_HPP

#ifndef LLM_COMMONDAO_HPP
#define LLM_COMMONDAO_HPP

#include "utility/llm_utility.hpp"
#include "config/cfg.hpp"
#include "logger/logger.hpp"
#include "sqlite/sqlite_handler.h"
#include "mysql/mysql_handler.h"

BEGIN_LLM_SPACE

namespace detail {

inline static constexpr database_t use_db = database_t::sqlite;

template<database_t DB>
struct db_members {
	static constexpr decltype(auto) get_db_type() {
		if constexpr (DB == database_t::mysql)
			return mysql_handler();
		else
			return sqlite_handler();
	}
};

using db_type = decltype(db_members<use_db>::get_db_type());


template<typename DB>
class db_ctrller : noncopyable {
	using database = DB;
	using db_t = std::unique_ptr<database>;

public:
	static db_ctrller<database>* instance() {
		static db_ctrller<database> db;
		return &db;
	}

	template<typename... Args>
	bool connect(Args&&... args) {
		return db_proxy_->connect(std::forward<Args>(args)...);
	}

	void disconnect() {
		db_proxy_->disconnect();
	}

	template<typename T, typename... Args>
	bool create_table(Args&&... args) {
		return db_proxy_->create_table<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	bool create_index(Args&&... args) {
		return db_proxy_->create_index<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename... Args>
	bool select(T&& res, Args&&... args) {
		return db_proxy_->select(std::forward<T>(res), std::forward<Args>(args)...);
	}

	template<int Auto, typename T>
	int insert(T&& t) {
		return db_proxy_->insert<Auto>(std::forward<T>(t));
	}

	template<typename T>
	int update(T&& t) {
		return db_proxy_->update(std::forward<T>(t));
	}

	template<typename T, typename... Args>
	int func_delete(Args&&... args) {
		return db_proxy_->func_delete<T>(std::forward<Args>(args)...);
	}

	std::string last_error() const noexcept {
		return db_proxy_->last_error();
	}

private:
	db_ctrller() : db_proxy_(std::make_unique<database>()) {

	}

	~db_ctrller() {

	}

private:
	db_t db_proxy_;
};

}


inline decltype(auto) db_factory() {
	return detail::db_ctrller<detail::db_type>::instance();
}


namespace detail {

template<typename Model>
class base_DAO {
	using model_t = Model;

public:
	base_DAO() : db_(db_factory()) {}
	~base_DAO() = default;

	std::string last_error()const noexcept {
		return db_->last_error();
	}

	template<typename... Args>
	bool create_table(Args&&... args) {
		return db_->create_table<model_t>(std::forward<Args>(args)...);
	}

	template<typename... Args>
	bool create_index(const std::string& index_name, Args&&... args) {
		return db_->create_index<model_t>(index_name, std::forward<Args>(args)...);
	}

	template<int Auto, typename T>
	CHECK_TYPE_SAME(model_t, T, int) insert_one(T&& t) {
		return db_->insert<Auto>(std::forward<T>(t));
	}

	template<int Auto, typename T>
	IS_VEC_LIST(model_t, T, int) insert_list(T&& t) {
		return db_->insert<Auto>(std::forward<T>(t));
	}

	template<typename T>
	CHECK_TYPE_SAME(model_t, T, int) update_one(T&& t) {
		return db_->update(std::forward<T>(t));
	}

	template<typename T>
	IS_VEC_LIST(model_t, T, int) update_list(T&& t) {
		return db_->update(std::forward<T>(t));
	}

protected:
	db_ctrller<db_type>* db_;
};

}

END_LLM_SPACE

#endif // !LLM_COMMONDAO_HPP

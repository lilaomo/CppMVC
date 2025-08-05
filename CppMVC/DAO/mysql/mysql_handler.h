#ifndef LLM_MYSQLHANDLER_H
#define LLM_MYSQLHANDLER_H

#include "utility/db_utility.hpp"

#include "mysql/mysql.h"
#pragma comment(lib, "libmysql.lib")

BEGIN_LLM_SPACE_EX

class mysql_handler {
	struct res_raii {
		res_raii(MYSQL_RES* res) : res_(res) {}

		~res_raii() {
			if (res_) {
				mysql_free_result(res_);
				res_ = nullptr;
			}
		}

		MYSQL_RES*& get() noexcept {
			return res_;
		}

		MYSQL_RES* res_;
	};

	struct stmt_raii {
		stmt_raii(MYSQL_STMT* stmt) : stmt_(stmt) {}

		~stmt_raii() {
			if (stmt_ != nullptr) {
				mysql_stmt_close(stmt_);
				stmt_ = nullptr;
			}
		}

		MYSQL_STMT*& get() noexcept {
			return stmt_;
		}

		MYSQL_STMT* stmt_;
	};

public:
	mysql_handler();
	~mysql_handler();

	bool connect(const std::string& user, const std::string& pwd, const std::string& db, 
		const std::string& ip, uint32_t port, uint32_t timeout = 0);
	void disconnect();

	template<typename T, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	bool create_table(Args&&... args) {
		std::string&& sql = get_create_table_sql<DB_MYSQL, T>(std::forward<Args>(args)...);
		sql.insert(sql.size() - 1, "ENGINE=InnoDB DEFAULT CHARSET=utf8");
		if (mysql_query(db_, sql.c_str()) != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}
		return true;
	}

	template<typename T, typename IndexType, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	bool create_index(Args&&... args) {
		std::string&& sql = get_create_index_sql<DB_MYSQL, T, IndexType>(std::forward<Args>(args)...);
		if (mysql_query(db_, sql.c_str()) != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}
		return true;
	}

	template<typename T, typename U = typename std::decay_t<T>::value_type, 
		typename = decltype(std::declval<std::decay_t<T>>().push_back(std::declval<U>())), typename... Args>
	bool select(T&& res, Args&&... args) {
		std::string&& sql = get_select_sql<U>(std::forward<Args>(args)...);
		if (mysql_real_query(db_, sql.c_str(), static_cast<unsigned long>(sql.size())) != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}

		res_raii my_res(mysql_store_result(db_));
		if (!my_res.get()) {
			last_err_ = mysql_error(db_);
			return false;
		}

		MYSQL_ROW row = {0};
		while (row = mysql_fetch_row(my_res.get())) {
			U t = { 0 };
			LLM_DTL for_each<U>([&t, &row, this](auto& item, auto i) {
				get_value(t.*item, row[decltype(i)::value]);
			});
			res.push_back(std::move(t));
		}
		return true;
	}

	template<int Auto, typename T,
		bool Batch = is_vector<std::decay_t<T>>::value || is_list<std::decay_t<T>>::value>
	int insert(T&& t) {
		std::string sql;
		if constexpr (Batch) {
			using U = typename std::decay_t<T>::value_type;
			static_assert(is_reflection<U>::value, "vector::value_type is not reflection");
			sql = get_insert_sql<U>(true);
		}
		else {
			using U = std::decay_t<T>;
			static_assert(is_reflection<U>::value, "type is not reflection");
			sql = get_insert_sql<U>(true);
		}
		return insert_impl<Auto, Batch>(sql, std::forward<T>(t));
	}

	template<typename T,
		bool Batch = is_vector<std::decay_t<T>>::value || is_list<std::decay_t<T>>::value>
	int update(T&& t) {
		std::string sql;
		if constexpr (Batch) {
			using U = typename std::decay_t<T>::value_type;
			static_assert(is_reflection<U>::value, "vector::value_type is not reflection");
			sql = get_insert_sql<U>(false);
		}
		else {
			using U = std::decay_t<T>;
			static_assert(is_reflection<U>::value, "type is not reflection");
			sql = get_insert_sql<U>(false);
		}
		return insert_impl<NONAUTOINCREMENT, Batch>(sql, std::forward<T>(t));
	}

	template<typename T, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	int func_delete(Args... args) {
		std::string&& sql = get_delete_sql<T>(std::forward<Args>(args)...);
		if (mysql_query(db_, sql.c_str()) != 0) {
			last_err_ = mysql_error(db_);
			return -1;
		}
		return static_cast<int>(mysql_affected_rows(db_));
	}

	bool begin() {
		if (mysql_query(db_, "BEGIN") != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}
		return true;
	}

	bool commit() {
		if (mysql_query(db_, "COMMIT") != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}
		return true;
	}

	bool rollback() {
		if (mysql_query(db_, "ROLLBACK") != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}
		return true;
	}

	inline std::string last_error() const noexcept {
		return last_err_;
	}

private:
	template<int Auto, bool Batch, typename T>
	int insert_impl(const std::string& sql, T&& t) {
		stmt_raii stmt(mysql_stmt_init(db_));
		if (!stmt.get() || mysql_stmt_prepare(stmt.get(), sql.c_str(), static_cast<unsigned long>(sql.size())) != 0) {
			last_err_ = mysql_error(db_);
			return -1;
		}
		
		int eff_row = 0;
		if constexpr (Batch) {
			if (!begin())
				return -1;
			for (auto& i : t) {
				if (!exec_insert<Auto>(i, stmt.get())) {
					rollback();
					return -1;
				}
			}
			eff_row = commit() ? static_cast<int>(t.size()) : -1;
		}
		if constexpr (!Batch) {
			if (!exec_insert<Auto>(std::forward<T>(t), stmt.get()))
				return -1;
			eff_row = 1;
		}
		return eff_row;
	}

	template<int Auto, typename T, typename U = std::decay_t<T>>
	bool exec_insert(T&& t, MYSQL_STMT* stmt) {
		std::vector<MYSQL_BIND> bind_param;
		LLM_DTL for_each<U>([&t, &bind_param, this](auto& item, auto idx) {
			MYSQL_BIND param = {0};
			bind_param.push_back(std::move(param));

			constexpr std::size_t index = decltype(idx)::value;
			if constexpr (get_key_index<U>() == index && Auto == AUTOINCREMENT) {
				bind_param[index].buffer_type = MYSQL_TYPE_NULL;
				return;
			}
			bind_value(t.*item, bind_param[index]);
		});

		if (mysql_stmt_bind_param(stmt, &bind_param[0]) != 0 || mysql_stmt_execute(stmt) != 0) {
			last_err_ = mysql_error(db_);
			return false;
		}

		return mysql_stmt_affected_rows(stmt) != 0;
	}

	template<typename T, typename U = std::remove_reference_t<T>>
	void get_value(T&& value, char* data) {
		if constexpr (std::is_same_v<U, std::string>) {
			value = data ? data : "NULL";
		}
		else if constexpr (lilaomo::is_char_array_v<U>) {
			char* ptr = nullptr;
			if constexpr (std::is_array_v<U>)
				ptr = value;
			else
				ptr = value.data();

			if (ptr)
				data ? memcpy(ptr, data, strlen(data)) : memset(ptr, 0, sizeof(T));
		}
		else if constexpr (std::is_integral_v<U>) {
			if constexpr (std::is_same_v<U, int64_t>)
				value = std::atoll(data);
			else
				value = std::atoi(data);
		}
		else if constexpr (std::is_floating_point_v<U>) {
			value = std::strtod(data, nullptr);
		}
		else;
	}

	template<typename T, typename U = std::remove_const_t<std::remove_reference_t<T>>>
	void bind_value(T&& t, MYSQL_BIND& bind_param) {
		if constexpr (std::is_same_v<U, std::string>) {
			if (t != "NULL") {
				bind_param.buffer_type = MYSQL_TYPE_STRING;
				bind_param.buffer = (void*)t.data();
				bind_param.buffer_length = static_cast<unsigned long>(t.size());
			}
			else bind_param.buffer_type = MYSQL_TYPE_NULL;
		}
		else if constexpr (lilaomo::is_char_array_v<U>) {
			const char* ptr = nullptr;
			if constexpr (std::is_array_v<U>)
				ptr = t;
			else
				ptr = t.data();

			if (ptr && ptr[0] != '\0') {
				bind_param.buffer_type = MYSQL_TYPE_STRING;
				bind_param.buffer = (void*)ptr;
				bind_param.buffer_length = static_cast<unsigned long>(strlen(ptr));
			}
			else bind_param.buffer_type = MYSQL_TYPE_NULL;
		}
		else if constexpr (std::is_integral_v<U> || std::is_floating_point_v<U>) {
			bind_param.buffer_type = mysql_mun_type_map<U>();
			bind_param.buffer = (void*)&t;
			bind_param.buffer_length = sizeof(t);
		}
		else;
	}

	template<typename T>
	constexpr enum_field_types mysql_mun_type_map() {
		if constexpr (std::is_same_v<T, bool>) {
			return MYSQL_TYPE_BOOL;
		}
		else if constexpr (std::is_same_v<T, char>) {
			return MYSQL_TYPE_TINY;
		}
		else if constexpr (std::is_same_v<T, short>) {
			return MYSQL_TYPE_SHORT;
		}
		else if constexpr (std::is_same_v<T, int>) {
			return MYSQL_TYPE_LONG;
		}
		else if constexpr (std::is_same_v<T, int64_t>) {
			return MYSQL_TYPE_LONGLONG;
		}
		else if constexpr (std::is_same_v<T, float>) {
			return MYSQL_TYPE_FLOAT;
		}
		else if constexpr (std::is_same_v<T, double>) {
			return MYSQL_TYPE_DOUBLE;
		}
		else MYSQL_TYPE_LONG;
	}

private:
	MYSQL* db_;
	std::string last_err_;
};

END_LLM_SPACE_EX

#endif // !LLM_MYSQLHANDLER_H


#ifndef LLM_SQLITEHANDLER_H
#define LLM_SQLITEHANDLER_H

#include "utility/llm_utility.hpp"
#include "utility/db_utility.hpp"

#include "third_part/sqlite/sqlite3.h"
#pragma comment(lib, "sqlite.lib")

BEGIN_LLM_SPACE_EX

class sqlite_handler {
	struct stmt_raii {
		stmt_raii() : stmt_(nullptr) { }

		~stmt_raii() {
			if (stmt_ != nullptr) {
				sqlite3_finalize(stmt_);
				stmt_ = nullptr;
			}
		}

		sqlite3_stmt*& get() noexcept {
			return stmt_;
		}

		sqlite3_stmt* stmt_;
	};

public:
	sqlite_handler();
	~sqlite_handler();

	bool connect(const std::string& db_path);
	void disconnect();
	bool execute(const std::string& sql);

	template<typename T, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	bool create_table(Args&&... args) {
		std::string&& sql = get_create_table_sql<DB_SQLITE, T>(std::forward<Args>(args)...);
		if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
			last_err_ = sqlite3_errmsg(db_);
			return false;
		}
		return true;
	}

	template<typename T, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	bool create_index(Args&&... args) {
		std::string&& sql = get_create_index_sql<DB_SQLITE, T, void>(std::forward<Args>(args)...);
		if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
			last_err_ = sqlite3_errmsg(db_);
			return false;
		}
		return true;
	}

	template<typename T, typename U = typename std::decay_t<T>::value_type, 
		typename = decltype(std::declval<std::decay_t<T>>().push_back(std::declval<U>())), typename... Args>
	bool select(T&& res, Args&&... args) {
		std::string&& sql = get_select_sql<U>(std::forward<Args>(args)...);
		stmt_raii stmt;
		if (sqlite3_prepare_v2(db_, sql.c_str(), static_cast<int>(sql.size()), &stmt.get(), nullptr) != SQLITE_OK) {
			last_err_ = sqlite3_errmsg(db_);
			return false;
		}

		while (true) {
			if (sqlite3_step(stmt.get()) != SQLITE_ROW)
				break;

			U t = { 0 };
			LLM_DTL for_each<U>([&t, &stmt, this](auto& item, auto i) {
				get_value(t.*item, decltype(i)::value, stmt.get());
			});
			res.push_back(std::move(t));
		}
		return true;
	}

	template<int Auto, typename T, 
		bool Batch = is_vector<std::decay_t<T>>::value || is_list<std::decay_t<T>>::value>
	int insert(T&& t) {
		if constexpr (Batch) {
			using U = typename std::decay_t<T>::value_typel;
			static_assert(is_reflection<U>::value, "vector::value_type is not reflection");
			std::string&& sql = get_insert_sql<U>(true);
			if (!begin())
				return -1;
			for (auto& i : t) {
				if (!insert_impl<Auto>(sql, i)) {
					rollback();
					return -1;
				}
			}
			return commit() ? static_cast<int>(t.size()) : -1;
		}
		else {
			static_assert(is_reflection<std::decay_t<T>>::value, "type is not reflection");
			std::string&& sql = get_insert_sql<T>(true);
			return insert_impl<Auto>(sql, std::forward<T>(t)) ? 1 : -1;
		}
	}

	template<typename T, 
		bool Batch = is_vector<std::decay_t<T>>::value || is_list<std::decay_t<T>>::value>
	int update(T&& t) {
		if constexpr (Batch) {
			using U = typename std::decay_t<T>::value_typel;
			static_assert(is_reflection<U>::value, "vector::value_type is not reflection");
			std::string&& sql = get_insert_sql<U>(false);
			if (!begin())
				return -1;
			for (auto& i : t) {
				if (!insert_impl<NONAUTOINCREMENT>(sql, i)) {
					rollback();
					return -1;
				}
			}
			return commit() ? static_cast<int>(t.size()) : -1;
		}
		else {
			static_assert(is_reflection<std::decay_t<T>>::value, "type is not reflection");
			std::string&& sql = get_insert_sql<T>(false);
			return insert_impl<NONAUTOINCREMENT>(sql, std::forward<T>(t)) ? 1 : -1;
		}
	}

	template<typename T, typename = std::enable_if_t<is_reflection<T>::value>, typename... Args>
	int func_delete(Args... args) {
		int before_num = sqlite3_total_changes(db_);

		std::string&& sql = get_delete_sql<T>(std::forward<Args>(args)...);
		stmt_raii stmt;
		if (sqlite3_prepare_v2(db_, sql.c_str(), static_cast<int>(sql.size()), &stmt.get(), nullptr) != SQLITE_OK) {
			last_err_ = sqlite3_errmsg(db_);
			return 0;
		}
		if (sqlite3_step(stmt.get()) != SQLITE_DONE) {
			last_err_ = sqlite3_errmsg(db_);
			return 0;
		}

		int effect_row = sqlite3_total_changes(db_) - before_num;
		return effect_row;
	}

	bool begin() {
		return true;
	}

	bool commit() {
		return true;
	}

	bool rollback() {
		return true;
	}

	inline std::string last_error() const noexcept {
		return last_err_;
	}


private:
	template<int Auto, typename T, typename U = std::decay_t<T>>
	bool insert_impl(const std::string& sql, T&& t) {
		stmt_raii stmt;
		if (sqlite3_prepare_v2(db_, sql.c_str(), static_cast<int>(sql.size()), &stmt.get(), nullptr) != SQLITE_OK) {
			last_err_ = sqlite3_errmsg(db_);
			return false;
		}

		LLM_DTL for_each<U>([&t, &stmt, this](auto& item, auto i) {
			if constexpr (get_key_index<U>() == decltype(i)::value && Auto == AUTOINCREMENT) {
				sqlite3_bind_null(stmt.get(), static_cast<int>(decltype(i)::value + 1));
				return;
			}

			bind_value(t.*item, static_cast<int>(decltype(i)::value + 1), stmt.get());
		});

		if (sqlite3_step(stmt.get()) != SQLITE_DONE) {
			last_err_ = sqlite3_errmsg(db_);
			return false;
		}
		return true;
	}

	template<typename T, typename U = std::remove_reference_t<T>>
	void get_value(T&& value, int i, sqlite3_stmt* stmt) {
		if constexpr (std::is_same_v<U, std::string>) {
			const char* text = (const char*)sqlite3_column_text(stmt, i);
			value = text ? text : "NULL";
		}
		else if constexpr (lilaomo::is_char_array_v<U>) {
			char* ptr = nullptr;
			if constexpr (std::is_array_v<U>)
				ptr = value;
			else
				ptr = value.data();

			if (ptr) {
				const char* text = (const char*)sqlite3_column_text(stmt, i);
				text ? memcpy(ptr, text, sizeof(U)) : memset(ptr, 0, sizeof(U));
			}
		}
		else if constexpr (std::is_integral_v<U>) {
			if constexpr (std::is_same_v<U, int64_t>)
				value = sqlite3_column_int64(stmt, i);
			else 
				value = sqlite3_column_int(stmt, i);
		}
		else if constexpr (std::is_floating_point_v<U>) {
			value = sqlite3_column_double(stmt, i);
		}
		else;
	}

	template<typename T, typename U = std::remove_const_t<std::remove_reference_t<T>>>
	void bind_value(T&& value, int i, sqlite3_stmt* stmt) {
		if constexpr (std::is_same_v<U, std::string>) {
			value.compare("NULL") == 0 ? sqlite3_bind_null(stmt, i) : 
				sqlite3_bind_text(stmt, i, value.c_str(), static_cast<int>(value.size()), nullptr);
		}
		else if constexpr (lilaomo::is_char_array_v<U>) {
			const char* ptr = nullptr;
			if constexpr (std::is_array_v<U>)
				ptr = value;
			else
				ptr = value.data();

			(ptr && ptr[0] != '\0') ? sqlite3_bind_text(stmt, i, ptr, sizeof(U), nullptr) : sqlite3_bind_null(stmt, i);
		}
		else if constexpr (std::is_integral_v<U>) {
			if constexpr (std::is_same_v<U, int64_t>)
				sqlite3_bind_int64(stmt, i, value);
			else
				sqlite3_bind_int(stmt, i, value);
		}
		else if constexpr (std::is_floating_point_v<U>) {
			sqlite3_bind_double(stmt, i, value);
		}
		else;
	}

private:
	sqlite3* db_;
	std::string last_err_;
};

END_LLM_SPACE_EX

#endif // !LLM_SQLITEHANDLER_H


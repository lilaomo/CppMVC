#ifndef LLM_DBUTILITY_HPP
#define LLM_DBUTILITY_HPP

#include "const/const_define.h"
#include "llm_utility.hpp"

#include <string>
#include <array>
#include <vector>
#include <list>
#include <type_traits>

using namespace std::string_view_literals;

BEGIN_LLM_SPACE

namespace detail {
inline constexpr static int DB_MYSQL = 0;
inline constexpr static int DB_SQLITE = 1;
}

constexpr static int AUTOINCREMENT = std::true_type::value;
constexpr static int NONAUTOINCREMENT = std::false_type::value;


struct primary_key {
    std::string_view key;

    constexpr primary_key(const char* k) : key(k) {}

    template<int DB_TYPE>
    std::string get() const {
        if constexpr (DB_TYPE == detail::DB_MYSQL)
            return std::format("PRIMARY KEY(`{}`)", key);
        else if constexpr (DB_TYPE == detail::DB_SQLITE)
            return " PRIMARY KEY";
        else 
            return "";
    }
};

struct autoincrement {
    std::string_view key;

    constexpr autoincrement(const char* k) : key(k) {}

    template<int DB_TYPE>
    constexpr std::string_view get() const {
        if constexpr (DB_TYPE == detail::DB_MYSQL)
            return " AUTO_INCREMENT"sv;
        else if constexpr (DB_TYPE == detail::DB_SQLITE)
            return " AUTOINCREMENT"sv;
        else return ""sv;
    }
};

struct not_null {
    std::string_view key;

    constexpr not_null(const char* k) : key(k) {}

    template<int DB_TYPE>
    constexpr std::string_view get() const {
        return " NOT NULL"sv;
    }
};

template<typename T>
struct default_val {
    using value_type = T;

    std::string_view key;
    value_type val;

    constexpr default_val(const char* k, value_type v) : key(k), val(v) {}

    template<int DB_TYPE>
    std::string get() const {
        if constexpr (DB_TYPE == detail::DB_MYSQL) {
            if constexpr (std::is_same_v<value_type, int> || std::is_same_v<value_type, double>)
                return std::format(" DEFAULT {}", val);
            else 
                return std::format(" DEFAULT '{}'", val);
        }
        else return "";
    }
};
//default_val(const char*)->default_val<std::string>;

struct unique_index {};
struct normal_index {};
struct fulltext_index {};

struct or_ : public cmp_ {
    constexpr or_(const char* condition) : cmp_(condition, " or ") {}
};

struct and_ : public cmp_ {
    constexpr and_(const char* condition) : cmp_(condition, " and ") {}
};


namespace detail {

template<typename T>
struct type_container {};

template<int DB_TYPE>
constexpr auto type_to_name(type_container<bool>) noexcept {
    if constexpr (DB_TYPE == DB_MYSQL) {
        return "BOOLEAN"sv;
    }
    return "INTEGER"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<char>) noexcept {
    if constexpr (DB_TYPE == DB_MYSQL) {
        return "TINYINT"sv;
    }
    return "INTEGER"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<short>) noexcept {
    if constexpr (DB_TYPE == DB_MYSQL) {
        return "SMALLINT"sv;
    }
    return "INTEGER"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<int>) noexcept {
    return "INTEGER"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<float>) noexcept {
    return "FLOAT"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<double>) noexcept {
    return "DOUBLE"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<int64_t>) noexcept {
    if constexpr (DB_TYPE == DB_MYSQL) {
        return "BIGINT"sv;
    }
    return "INTEGER"sv;
}

template<int DB_TYPE>
constexpr auto type_to_name(type_container<std::string>) noexcept {
    return "TEXT"sv;
}

template<int DB_TYPE, std::size_t N>
constexpr auto type_to_name(type_container<char[N]>) noexcept {
    GET_VARCHAR_STR
}

template<int DB_TYPE, std::size_t N>
constexpr auto type_to_name(type_container<std::array<char, N>>) noexcept {
    GET_VARCHAR_STR
}

template<int DB_TYPE, typename T>
constexpr auto get_type_names() {
    constexpr auto SIZE = get_size<T>();
    std::array<std::string_view, SIZE> arr = {};
    LLM_DTL for_each<T>([&](auto&, auto i) {
        constexpr auto INDEX = decltype(i)::value;
        using M = Reflect_members<T>;
        using U = std::remove_reference_t<decltype(std::declval<T>().*(std::get<INDEX>(M::apply_impl())))>;
        arr[INDEX] = type_to_name<DB_TYPE>(type_container<U>{});
    });
    return arr;
}


//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
template<int DB_TYPE, typename... Args>
void get_key_condition_impl(std::string& end_cond, std::string& field_name, const std::string_view& key, const std::tuple<Args...>& tup) {}

template<int DB_TYPE, std::size_t I, std::size_t... N, typename... Args>
void get_key_condition_impl(std::string& end_cond, std::string& field_name, const std::string_view& key, const std::tuple<Args...>& tup) {
    const auto& item = std::get<I>(tup);
    if (key == item.key) {
        using T = std::decay_t<decltype(item)>;
        if constexpr (DB_TYPE == DB_MYSQL && std::is_same_v<T, primary_key>) {
            end_cond.append(item.get<DB_TYPE>());
        }
        else field_name.append(item.get<DB_TYPE>());
    }
    get_key_condition_impl<DB_TYPE, N...>(end_cond, field_name, key, tup);
}

template<int DB_TYPE, typename... Args, std::size_t... Idx>
void get_key_condition_impl(std::string& end_cond, std::string& field_name, const std::string_view& key, 
    const std::tuple<Args...>& tup, const std::index_sequence<Idx...>&) 
{
    get_key_condition_impl<DB_TYPE, Idx...>(end_cond, field_name, key, tup);
}

template<int DB_TYPE, typename... Args>
void get_key_condition(std::string&  end_cond, std::string& field_name, const std::string_view& key, Args&&... args) {
    get_key_condition_impl<DB_TYPE>(end_cond, field_name, key, std::make_tuple<Args...>(std::forward<Args>(args)...),
        std::make_index_sequence<std::tuple_size<std::tuple<Args...>>::value>{});
}



inline void get_where_sql(std::string& sql) { sql.append(";"); }

inline void get_where_sql(std::string& sql, const std::string& where_sql) { sql.append(where_sql).append(";"); }

template<typename T, typename... Args>
void get_where_sql(std::string& sql, cmp_&& condition, T&& value, Args&&... args) {
    using U = std::decay_t<T>;
    if constexpr (std::is_same_v<U, std::string> || lilaomo::is_char_array_v<U>) {
        if constexpr (std::is_array_v<U> || std::is_same_v<U, char*>)
            sql.append(condition.symbol).append(condition.condition).append(" '").append(value).append("'");
        else
            sql.append(condition.symbol).append(condition.condition).append(" '").append(value.data()).append("'");
        get_where_sql(sql, std::forward<Args>(args)...);
    }
    else if constexpr (std::is_integral_v<U> || std::is_floating_point_v<U>) {
        sql.append(condition.symbol).append(condition.condition).append(" ").append(std::to_string(value));
        get_where_sql(sql, std::forward<Args>(args)...);
    }
    else get_where_sql(sql);
}



inline void get_field_string(std::string& sql, const std::string& field) {
    sql.append(field);
}

template<typename... Args>
void get_field_string(std::string& sql, const std::string& field, Args&&... args) {
    sql.append(field).append(", ");
    get_field_string(sql, std::forward<Args>(args)...);
}


//-------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------//
template<typename T, typename... Args>
std::string get_select_sql(Args&&... args) {
    std::string sql{"select * from "};
    sql.append(get_name<T>()).append(" where 1 = 1 ");
    get_where_sql(sql, std::forward<Args>(args)...);
    return sql;
}

template <typename T>
std::string get_insert_sql(bool is_insert) {
    std::string sql = is_insert ? "insert into " : "replace into ";
    constexpr std::size_t SIZE = get_size<T>();
    auto name = get_name<T>();
    constexpr auto fields = get_fields<T>();

    sql.append(name).append("(").append(fields).append(") values(");
    for (std::size_t i = 0; i < SIZE; ++i) {
        sql += "?";
        sql += i < SIZE - 1 ? ", " : ");";
    }
    return sql;
}

template<typename T, typename... Args>
std::string get_delete_sql(Args&&... args) {
    std::string sql{"delete from "};
    sql.append(get_name<T>()).append(" where 1 = 1");

    get_where_sql(sql, std::forward<Args>(args)...);

    return sql;
}

template<int DB_TYPE, typename T, typename... Args>
std::string get_create_table_sql(Args&&... args) {
    std::string sql{"CREATE TABLE IF NOT EXISTS "};
    sql.append(get_name<T>()).append("(");

    constexpr auto type_name_arr = get_type_names<DB_TYPE, T>();
    constexpr auto fields = get_fields<T>();
    std::string end_cond;
    std::size_t slow = 0, fast = 0, index = 0;
    while (fast != std::string::npos) {
        fast = fields.find(',', slow);
        auto temp = fields.substr(slow, fast - slow);
        auto field_name = temp[0] == ' ' ? temp.substr(1) : temp;

        std::string field_cond;
        get_key_condition<DB_TYPE>(end_cond, field_cond, field_name, std::forward<Args>(args)...);
        sql.append(field_name).append(" ").append(type_name_arr[index]).append(field_cond).append(",");
        slow = fast + 1;
        ++index;
    }

    if constexpr (DB_TYPE == DB_MYSQL) {
        sql.append(end_cond);
    }
    else sql.erase(sql.size() - 1, 1);

    sql.append(");");
    return sql;
}

template<int DB_TYPE, typename T, typename IndexType, typename... Args>
std::string get_create_index_sql(const std::string& index_name, Args&&... args) {
    std::string sql;
    if constexpr (DB_TYPE == detail::DB_MYSQL) {
        if constexpr (std::is_same_v<IndexType, unique_index>)
            sql = "CREATE UNIQUE INDEX ";
        else if constexpr (std::is_same_v<IndexType, fulltext_index>)
            sql = "CREATE FULLTEXT INDEX ";
        else
            sql = "CREATE INDEX ";
    }
    else sql = "CREATE INDEX ";
    sql.append(index_name).append(" ON ").append(get_name<T>()).append("(");
    get_field_string(sql, std::forward<Args>(args)...);
    sql.append(");");
    return sql;
}

}  // namespace detail

END_LLM_SPACE  // namespace lilaomo

#endif // !LLM_DBUTILITY_HPP


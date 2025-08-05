#ifndef LLM_LLMUTILITY_HPP
#define LLM_LLMUTILITY_HPP

#include "const/const_define.h"
#include "reflection.hpp"

#include <type_traits>
#include <memory>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>

#include "third_part/nlohmann/json.hpp"

BEGIN_LLM_SPACE

//===============================================meta==================================================

template<typename T>
using Reflect_members = decltype(iguana_reflect_members(std::declval<T>()));

template<typename T, typename = void>
struct is_reflection : std::false_type {};

template<typename T>
struct is_reflection<T, std::enable_if_t<std::is_same<decltype(Reflect_members<T>::size()), std::size_t>::value>>
	: std::true_type {};

template<typename T>
inline constexpr bool is_reflection_v = is_reflection<T>::value;

template<template <typename...> class U, typename T>
struct is_template_instant_of : std::false_type {};

template<template <typename...> class U, typename... Args>
struct is_template_instant_of<U, U<Args...>> : std::true_type {};

template<typename T>
struct is_stdstring : is_template_instant_of<std::basic_string, T> {};

template<typename T>
struct is_tuple : is_template_instant_of<std::tuple, T> {};

template<typename T>
struct is_vector : is_template_instant_of<std::vector, T> {};

template<typename T>
struct is_list : is_template_instant_of<std::list, T> {};

template<typename T>
struct is_char_array : std::false_type {};

template<std::size_t N>
struct is_char_array<std::array<char, N>> : std::true_type {};

template<std::size_t N>
struct is_char_array<char[N]> : std::true_type {};

template<typename T>
inline constexpr bool is_char_array_v = is_char_array<T>::value;


template<typename... Ts>
struct contains {};

template<typename T>
struct contains<T> {
	static constexpr inline bool value = std::false_type::value;
};

template<typename T1, typename T2, typename... Ts>
struct contains<T1, T2, Ts...> {
	static constexpr inline bool value = std::is_same_v<T1, T2> ? std::true_type::value : contains<T1, Ts...>::value;
};



//===============================================object==================================================

class noncopyable {
protected:
	noncopyable() = default;
	~noncopyable() = default;

	noncopyable(const noncopyable&) = delete;
	noncopyable(noncopyable&&) = delete;

	noncopyable& operator=(const noncopyable&) = delete;
	noncopyable& operator=(noncopyable&&) = delete;
};


struct cmp_ {
	std::string_view condition;
	std::string_view symbol;

	constexpr cmp_(const char* c, const char* s) : condition(c), symbol(s) {}
};



//===============================================function==================================================

namespace detail {

template<typename T>
inline constexpr std::string_view get_name() {
    using M = Reflect_members<T>;
    return M::name();
}

template<typename T>
inline constexpr std::string_view get_fields() {
    using M = Reflect_members<T>;
    return M::fields();
}

template<typename T, typename std::size_t I>
inline constexpr std::string_view get_field() {
    using M = Reflect_members<T>;
    return std::get<I>(M::field_index());
}

template<typename T>
inline constexpr std::size_t get_size() {
    using M = Reflect_members<T>;
    return M::size();
}

template<typename T>
inline constexpr std::size_t get_key_index() {
    using M = Reflect_members<T>;
    return M::key_index();
}

template<typename... Args, typename F>
inline constexpr void get_mem_item(const std::tuple<Args...>& tup, F&& f) {}

template<std::size_t I, std::size_t... N, typename... Args, typename F>
inline constexpr void get_mem_item(const std::tuple<Args...>& tup, F&& f) {
    f(std::get<I>(tup), std::integral_constant<std::size_t, I>{});
    get_mem_item<N...>(tup, std::forward<F>(f));
}

template<typename... Args, typename F, std::size_t... Idx>
inline constexpr void for_each0(const std::tuple<Args...>& tup, F&& f, const std::index_sequence<Idx...>&) {
    get_mem_item<Idx...>(tup, std::forward<F>(f));
}

template<typename T, typename F>
inline constexpr void for_each(F&& f) {
    using M = Reflect_members<T>;
    for_each0(M::apply_impl(), std::forward<F>(f), std::make_index_sequence<M::size()>{});
}

}



template<typename T>
unsigned int* to_int_ptr(const T& t) {
	return reinterpret_cast<unsigned int*>(const_cast<T*>(&t));
}

template<typename T>
T from_int_ptr(unsigned int* ptr) {
	return *reinterpret_cast<T*>(ptr);
}


inline std::string get_current_path() {
	return std::filesystem::current_path().string();
}


inline std::string get_current_time() {
	auto&& now = std::chrono::system_clock::now();
	time_t now_t = std::chrono::system_clock::to_time_t(now);

	std::tm now_tm;
	localtime_s(&now_tm, &now_t);

	return std::format("{0}-{1}-{2} {3}:{4}:{5}", now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday, 
		now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec);
}


inline constexpr const char* get_name_from_path(const char* path) {
	std::string_view str(path);
	return str.substr(str.find_last_of('\\') + 1).data();
}


inline void reset_copy(void* dst, std::size_t max_size, const void* src, std::size_t size) {
	if (!dst)
		return;
	memset(dst, 0, max_size);

	if (!src)
		return;
	memcpy(dst, src, std::min(max_size - 1, size));
}

inline void reset_copy(void* dst, std::size_t max_size, const std::string& src) {
	if (!dst)
		return;
	memset(dst, 0, max_size);

	if (src.empty())
		return;
	memcpy(dst, src.c_str(), std::min(max_size - 1, src.size()));
}

template<std::size_t N>
void reset_copy(std::array<char, N>& dst, const void* src, std::size_t size) {
	memset(dst.data(), 0, N);
	if (!src)
		return;
	memcpy(dst.data(), src, std::min(N - 1, size));
}

template<std::size_t N>
void reset_copy(std::array<char, N>& dst, const std::string& src) {
	memset(dst.data(), 0, N);
	if (src.empty())
		return;
	memcpy(dst.data(), src.c_str(), std::min(N - 1, src.size()));
}


inline bool char_empty(const char* str) {
	return str ? str[0] == '\0' : true;
}

template<std::size_t N>
bool char_empty(const std::array<char, N>& str) {
	return str[0] == '\0';
}


inline bool char_equal(const char* str1, const char* str2) {
	if (!str1 || !str2)
		return false;
	return strcmp(str1, str2) == 0;
}

inline bool char_equal(const char* str1, const std::string& str2) {
	if (!str1)
		return false;
	return str2.compare(str1) == 0;
}

template<std::size_t N>
bool char_equal(std::array<char, N>& str1, const char* str2) {
	if (!str2)
		return false;
	return strcmp(str1.data(), str2) == 0;
}

template<std::size_t N>
bool char_equal(std::array<char, N>& str1, const std::string& str2) {
	return str2.compare(str1.data()) == 0;
}


inline void char_append(char* dst, std::size_t max_size, const char* str, std::size_t size) {
	std::size_t len = strlen(dst);
	memcpy(dst + len, str, std::min(max_size - len - 1, size));
}

inline void char_append(char* dst, std::size_t max_size, const std::string& str) {
	std::size_t len = strlen(dst);
	memcpy(dst + len, str.c_str(), std::min(max_size - len - 1, str.size()));
}

template<std::size_t N>
void char_append(std::array<char, N>& dst, const char* str, std::size_t size) {
	std::size_t len = strlen(dst.data());
	memcpy(&dst[len], str, std::min(N - len - 1, size));
}

template<std::size_t N>
void char_append(std::array<char, N>& dst, const std::string& str) {
	std::size_t len = strlen(dst.data());
	memcpy(&dst[len], str.c_str(), std::min(N - len - 1, str.size()));
}


template<typename Obj, typename = std::enable_if_t<is_reflection<std::decay_t<Obj>>::value>>
nlohmann::json obj_to_json(Obj&& obj) {
	nlohmann::json obj_json;
	obj_json["object_name"] = LLM_DTL get_name<Obj>();
	LLM_DTL for_each<Obj>([&obj, &obj_json](auto item, auto i) {
		constexpr std::string_view key_name = LLM_DTL get_field<Obj, decltype(i)::value>();
		obj_json[key_name] = obj.*item;
	});
	return obj_json;
}

template<typename Obj, typename = std::enable_if_t<is_reflection<std::decay_t<Obj>>::value>>
std::vector<nlohmann::json> obj_to_json(const std::vector<Obj>& vec) {
	std::vector<nlohmann::json> res;
	for (const auto& obj : vec) {
		nlohmann::json obj_json;
		obj_json["object_name"] = LLM_DTL get_name<Obj>();
		LLM_DTL for_each<Obj>([&obj, &obj_json](auto item, auto i) {
			constexpr std::string_view key_name = LLM_DTL get_field<Obj, decltype(i)::value>();
			obj_json[key_name] = obj.*item;
		});
		res.push_back(std::move(obj_json));
	}
	return res;
}

template<typename Obj, typename = std::enable_if_t<is_reflection<std::decay_t<Obj>>::value>>
Obj obj_from_json(const nlohmann::json& obj_json) {
	Obj obj = { 0 };
	if (obj_json.is_object()) {
		LLM_DTL for_each<Obj>([&obj, &obj_json](auto item, auto i) {
			constexpr std::string_view key_name = LLM_DTL get_field<Obj, decltype(i)::value>();
			using MemVarType = std::remove_reference_t<decltype(obj.*item)>;
			if constexpr (LLM is_char_array_v<MemVarType>) {
				std::string&& val = obj_json.value(key_name, std::string());
				if constexpr (std::is_array_v<MemVarType>)
					LLM reset_copy(obj.*item, sizeof(MemVarType), val);
				else
					LLM reset_copy(obj.*item, val);
			}
			else obj.*item = obj_json.value(key_name, MemVarType());
		});
	}
	return obj;
}

END_LLM_SPACE

#endif // !LLM_LLMUTILITY_HPP


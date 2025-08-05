#ifndef LLM_CONSTDEFINE_H_
#define LLM_CONSTDEFINE_H_

#include <cstdint>
#include <vector>
#include <string_view>

#define LLM_VERSION "v1.0.0.0"

#define BEGIN_LLM_SPACE namespace lilaomo {
#define END_LLM_SPACE }

#define BEGIN_LLM_SPACE_EX namespace lilaomo::detail {
#define END_LLM_SPACE_EX }

#define LLM lilaomo::
#define LLM_DTL lilaomo::detail::


#define IS_VEC_LIST(T1, T2, T) std::enable_if_t<(lilaomo::is_vector<std::decay_t<T2>>::value || \
												 lilaomo::is_list<std::decay_t<T2>>::value) && \
												 std::is_same_v<T1, typename std::decay_t<T2>::value_type>, T>
#define CHECK_TYPE_SAME(T1, T2, T) std::enable_if_t<std::is_same_v<T1, std::decay_t<T2>>, T>
#define CHECK_REFLECTION(T) std::enable_if_t<lilaomo::is_reflection<T>::value>
#define CHECK_CONTAINS(...) std::enable_if_t<lilaomo::contains<__VA_ARGS__>::value>


#define LTRACE lilaomo::log_level::level_trace
#define LDEBUG lilaomo::log_level::level_debug
#define LINFO lilaomo::log_level::level_info
#define LWARN lilaomo::log_level::level_warn
#define LERROR lilaomo::log_level::level_error
#define LCRITICAL lilaomo::log_level::level_critical
#define LOFF lilaomo::log_level::level_off


BEGIN_LLM_SPACE

enum class log_t : std::uint8_t {
	single_thrd,
	multi_thrd
};


enum class log_level : std::uint8_t {
	level_trace,
	level_debug,
	level_info,
	level_warn,
	level_error,
	level_critical,
	level_off
};


enum class database_t : std::uint8_t {
	mysql,
	sqlite
};


enum class serv_error : std::uint32_t {
	success,
	db_err,
	model_not_support,
	user_id_err,
	username_err,
	password_err,
	user_param_err,
	role_id_err,
	permission_id_err
};


using serv_result = std::pair<serv_error, std::string>;

END_LLM_SPACE

#endif // !LLM_CONSTDEFINE_H_

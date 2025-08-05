#ifndef LLM_MODELUTILITY_HPP
#define LLM_MODELUTILITY_HPP

#include "model/user_model.hpp"

#include <type_traits>

BEGIN_LLM_SPACE

template<typename UserModel>
inline constexpr bool is_user_info_v = std::is_same_v<UserModel, LLM user_info>;

END_LLM_SPACE

#endif // !LLM_MODELUTILITY_HPP


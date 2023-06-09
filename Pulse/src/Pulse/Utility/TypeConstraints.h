#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

namespace Pulse::Utility {

	template<typename T>
	concept IsCRTPConform = std::is_same_v<T, std::remove_cvref_t<decltype(std::declval<T>())>>;

	template<typename T>
	concept IsEmpty

} // namespace Pulse::Utility
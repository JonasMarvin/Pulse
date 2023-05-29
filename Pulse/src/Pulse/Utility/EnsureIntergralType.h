#pragma once

#include <type_traits>

namespace Pulse::Utility {

	template<typename Type>
	class EnsureIntergralType {
		static_assert(std::is_integral<Type>::value, "Type must be an integral type!");

	}; // class EnsureIntergralType

} // namespace Pulse::Utility
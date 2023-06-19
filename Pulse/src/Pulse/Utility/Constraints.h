#pragma once

#include <type_traits>
#include <utility>

namespace Pulse::Utility {

	template<typename Base, typename Derived>
    concept CRTPConform = std::is_base_of_v<Base, Derived> && std::is_same_v<Derived, std::remove_cvref_t<decltype(static_cast<Base*>(nullptr)->template _Self<Derived>())>>;

	template<typename T>
	concept Unsigned = std::is_unsigned_v<T>;

	template<typename T>
	concept Integral = std::is_integral_v<T>;

	template<typename T>
	concept UnsignedIntegral = Integral<T> && Unsigned<T>;

	template<typename T>
	concept NumericLimits = requires {
		std::numeric_limits<T>::min();
		std::numeric_limits<T>::max();
	};

	template<typename T>
	concept UnsignedIntegralWithNumericLimits = UnsignedIntegral<T> && NumericLimits<T>;

} // namespace Pulse::Utility
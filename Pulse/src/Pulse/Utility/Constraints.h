#pragma once

#include <type_traits>
#include <utility>

namespace Pulse::Utility {

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
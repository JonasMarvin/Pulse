// This file is used to define core functionality of the engine.
// E.g disabling specific warnings or defining macros.
#pragma once

#include <memory>
#include <type_traits>

// Asserts

#ifdef PLS_DEBUG
	#define PLS_ENABLE_ASSERTS
#endif // PLS_DEBUG

#ifdef PLS_ENABLE_ASSERTS
	#define PLS_ASSERT(x, ...) { if(!(x)) { PLS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PLS_CORE_ASSERT(x, ...) { if(!(x)) { PLS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PLS_ASSERT(x, ...)
	#define PLS_CORE_ASSERT(x, ...)
#endif

 // Macro to get a bit at a specific position
#define PLS_BIT(x) (1 << x)

// Types for managing the lifetime of objects
namespace Pulse {

	// Unique pointer system
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Reference counting system
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

} // namespace Pulse
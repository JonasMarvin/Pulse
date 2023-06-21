#pragma once

#include <type_traits>

// This disables the warning that is thrown when using STL classes in DLLs.
#pragma warning(disable : 4251)

// This is used to export from the Pulse DLL and import into other applications.
#ifdef PLS_PLATFORM_WINDOWS
	#ifdef PLS_BUILD_DLL
		#define PLS_API __declspec(dllexport)
	#else
		#define PLS_API __declspec(dllimport)
	#endif
#else
	#error Pulse only supports Windows!
#endif

#define PLS_BIT(x) (1 << x)

#define PLS_OPTIONAL_TEMPLATE_ARGUMENT(parameter) typename parameter = std::nullptr_t
#define PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(parameter) !std::is_same_v<parameter, std::nullptr_t>
#define PLS_DOES_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(parameter) template <typename T = parameter> requires (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(T))
#define PLS_DOES_NOT_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(parameter) template <typename T = parameter> requires (!PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(T))
#define PLS_DOES_REQUIRE_OPTIONAL_TEMPLATE_ARGUMENT(parameter) requires (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(parameter))
#define PLS_DOES_NOT_REQUIRE_OPTIONAL_TEMPLATE_ARGUMENT(parameter) requires (!PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(parameter))
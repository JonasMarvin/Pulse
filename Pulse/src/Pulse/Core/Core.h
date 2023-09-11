// This file is used to define core functionality of the engine.
// E.g disabling specific warnings or defining macros.
#pragma once

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

// Asserts

#ifdef PLS_ENABLE_ASSERTS
	#define PLS_ASSERT(x, ...) { if(!(x)) { PLS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PLS_CORE_ASSERT(x, ...) { if(!(x)) { PLS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PLS_ASSERT(x, ...)
	#define PLS_CORE_ASSERT(x, ...)
#endif

 // Macro to get a bit at a specific position
#define PLS_BIT(x) (1 << x)
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

#define BIT(x) (1 << x)

// Type for EventListener ID's and Event ID's.
typedef unsigned int EventID;
typedef unsigned int EventListenerID;
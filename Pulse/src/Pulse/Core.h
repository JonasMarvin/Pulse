#pragma once

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
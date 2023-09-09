#pragma once

// Pulse functionality
#include "Pulse/Log.h"
#include "Pulse/Events/Events.h"

// STL includes
#include <type_traits>
#include <memory>
#include <chrono>
#include <functional>

// Data structures
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

// Platform specific includes
#ifdef PLS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
#pragma once

// Pulse functionality
#include "Pulse/Core/Logging/Log.h"
#include "Pulse/Events/Events.h"

// STL includes
#include <type_traits>
#include <typeindex>
#include <memory>
#include <chrono>
#include <functional>
#include <cstdint>

// Data structures
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

// File system
#include <fstream>

// Platform specific includes
#ifdef PLS_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
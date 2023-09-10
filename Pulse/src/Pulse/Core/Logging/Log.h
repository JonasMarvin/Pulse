#pragma once

#include "Pulse/Core/Core.h"

#include "spdlog/spdlog.h"

namespace Pulse {

	// Class for logging
	class PLS_API Log {
	public:
		static void Init(); // Initialize the logger

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger_; } // Get the core logger
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger_; } // Get the client logger
	
	private:
		static std::shared_ptr<spdlog::logger> clientLogger_; // Client logger
		static std::shared_ptr<spdlog::logger> coreLogger_; // Core logger
	};

} // namespace Pulse

// Core log macros
#define PLS_CORE_TRACE(...)	::Pulse::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PLS_CORE_INFO(...)	::Pulse::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PLS_CORE_WARN(...)	::Pulse::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PLS_CORE_ERROR(...) ::Pulse::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define PLS_TRACE(...)		::Pulse::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PLS_INFO(...)		::Pulse::Log::GetClientLogger()->info(__VA_ARGS__)
#define PLS_WARN(...)		::Pulse::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PLS_ERROR(...)		::Pulse::Log::GetClientLogger()->error(__VA_ARGS__)
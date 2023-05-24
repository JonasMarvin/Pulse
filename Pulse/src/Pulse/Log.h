#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"

namespace Pulse {

	class PLS_API Log {
	public:

		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger_; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger_; }
	
	private:
		static std::shared_ptr<spdlog::logger> clientLogger_;
		static std::shared_ptr<spdlog::logger> coreLogger_;
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
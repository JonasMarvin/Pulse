#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Pulse {

	std::shared_ptr<spdlog::logger> Log::clientLogger_;
	std::shared_ptr<spdlog::logger> Log::coreLogger_;

	void Log::Init() {
		spdlog::set_pattern("%^[%T]%-8l| %-5n: %v%$");
		coreLogger_ = spdlog::stdout_color_mt("PULSE");
		coreLogger_->set_level(spdlog::level::trace);

		clientLogger_ = spdlog::stdout_color_mt("APP");
		clientLogger_->set_level(spdlog::level::trace);
	}
	
} // namespace Pulse
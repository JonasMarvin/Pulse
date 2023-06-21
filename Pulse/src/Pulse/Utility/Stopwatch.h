#pragma once

#include <chrono>

#include "Pulse/Core.h"
#include "Pulse/Log.h"

namespace Pulse::Utility {
	
	class PLS_API Stopwatch {
	public:
		using Clock = std::chrono::high_resolution_clock;
		
		Stopwatch();

		void Reset();
		void Pause();
		void Resume();

		template <typename Precision = std::chrono::milliseconds>
		double GetTime() const;

		template <typename Precision = std::chrono::milliseconds>
		void PrintTime(const char* message = nullptr) const;

	private:
		std::chrono::time_point<Clock> startTime_;
		std::chrono::time_point<Clock> lastPausedTime_;
		std::chrono::duration<double> totalPausedTime_;
		bool isPaused_;

	}; // class Stopwatch

} // namespace Pulse::Utility

#include "Pulse/Utility/Stopwatch.tpp"
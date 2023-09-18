#pragma once

#include <chrono>

#include "Pulse/Core/Core.h"
#include "Pulse/Core/Logging/Log.h"

namespace Pulse::Utility {
	
	// Class for measuring time using chrono
	class Stopwatch {
	public:
		using Clock = std::chrono::high_resolution_clock; // Using high resolution clock to measure time with nanosecond precision
		
		Stopwatch(); // Constructor

		void Reset(); // Reset the stopwatch
		void Pause(); // Pause the stopwatch
		void Resume(); // Resume the stopwatch

		template <typename Precision = std::chrono::milliseconds>
		double GetTime() const; // Get the time elapsed since the stopwatch was started in the specified precision as template parameter. Standard is milliseconds

		template <typename Precision = std::chrono::milliseconds>
		void PrintTime(const char* message = nullptr) const; // Print the time elapsed since the stopwatch was started in the specified precision as template parameter. Standard is milliseconds

	private:
		std::chrono::time_point<Clock> startTime_; // Time point when the stopwatch was started
		std::chrono::time_point<Clock> lastPausedTime_; // Time point when the stopwatch was last paused
		std::chrono::duration<double> totalPausedTime_; // Total time the stopwatch was paused
		bool isPaused_; // Flag to indicate if the stopwatch is paused

	}; // class Stopwatch

} // namespace Pulse::Utility

#include "Pulse/Utility/Stopwatch.tpp"
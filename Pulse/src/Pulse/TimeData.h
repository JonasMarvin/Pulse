#pragma once

#include "Pulse/Utility/Stopwatch.h"

namespace Pulse {

	// class to represent the time data of the application
	class TimeData {
	public:
		operator float() const; // Conversion operator to convert the time data to a float in seconds

		float GetDeltaTimeNanoSeconds() const; // Get the delta time in nano seconds
		float GetDeltaTimeMicroSeconds() const; // Get the delta time in micro seconds
		float GetDeltaTimeMilliSeconds() const; // Get the delta time in milli seconds
		float GetDeltaTimeSeconds() const; // Get the delta time in seconds
		float GetDeltaTimeMinutes() const; // Get the delta time in minutes

	private:
		Pulse::Utility::Stopwatch stopwatch_; // Stopwatch to measure the time between frames
		double deltaTime_ = 0.0; // Delta time between frames
		double lastFrameTime_ = 0.0; // Time of the last frame
		double currentFrameTime_ = 0.0; // Time of the current frame

		void Initialize(); // Initialize the time data
		void Update(); // Update the time data

		friend class Application; // To allow the application to access the private members of the time data

	}; // class TimeData

} // namespace Pulse
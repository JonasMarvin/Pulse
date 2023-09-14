#pragma once

#include <cstdint>

namespace Pulse::Input {

	// From glfw3.h
	// Represents a gamepad button
	enum class GamepadButtonCode : uint32_t {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LeftBumper = 4,
		RightBumper = 5,
		Back = 6,
		Start = 7,
		Guide = 8,
		LeftThumb = 9,
		RightThumb = 10,
		DpadUp = 11,
		DpadRight = 12,
		DpadDown = 13,
		DpadLeft = 14,
	};

	// From glfw3.h
	// Represents a gamepad axis
	enum class GamepadAxisCode : uint32_t {
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5,
	};

} // End of namespace Pulse::Input
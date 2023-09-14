#pragma once

#include <cstdint>

namespace Pulse::Input {

	// From glfw3.h
	// Represents the mouse buttons.
	enum class MouseCode : uint32_t {

		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,
		ButtonLast = Button8,
		ButtonLeft = Button1,
		ButtonRight = Button2,
		ButtonMiddle = Button3

	}; // End of enum class MouseCode : uint32_t

} // End of namespace Pulse::Input
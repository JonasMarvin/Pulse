#pragma once

#include <cstdint>

namespace Pulse::Input {

    // This enum class is based on GLFW's joystick codes and is used to identify a joystick
    enum class JoystickCode : uint32_t {
        Joystick1 = 0,
        Joystick2 = 1,
        Joystick3 = 2,
        Joystick4 = 3,
        Joystick5 = 4,
        Joystick6 = 5,
        Joystick7 = 6,
        Joystick8 = 7,
        Joystick9 = 8,
        Joystick10 = 9,
        Joystick11 = 10,
        Joystick12 = 11,
        Joystick13 = 12,
        Joystick14 = 13,
        Joystick15 = 14,
        Joystick16 = 15,
        JoystickLast = Joystick16,
    };

} // namespace Pulse::Input

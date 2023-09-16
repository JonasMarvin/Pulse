#pragma once

#include <cstdint>

namespace Pulse::Input {

    // This enum class is based on GLFW's action codes
    enum class InputAction : uint32_t {
        Released = 0,
        Pressed = 1,
        Repeated = 2
    };

} // namespace Pulse::Input
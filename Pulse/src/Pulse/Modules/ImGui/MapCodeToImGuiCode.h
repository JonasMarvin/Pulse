#pragma once

#include <imgui.h>

#include "Pulse/Modules/Input/KeyCodes.h"
#include "Pulse/Modules/Input/MouseCodes.h"
#include "Pulse/Modules/Input/GamepadCodes.h"

namespace Pulse::Input {

	class MapCodeToImGuiCode {
	public:
		static ImGuiKey MapKeyCodeToImGuiKey(KeyCode keyCode);
		static int MapMouseCodeToImGuiMouse(MouseCode mouseCode);
		static ImGuiKey MapGamepadButtonCodesToImGuiKey(GamepadButtonCode gamepadCode);
		static ImGuiKey MapGamepadAxisCodesToImGuiKey(GamepadAxisCode gamepadCode);

	}; // class MapCodeToImGuiCode

} // namespace Pulse::Input
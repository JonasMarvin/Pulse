// The purpose of this file is to allow convient inclusion of the Event system.
#pragma once

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

	namespace Window {
		
		extern std::shared_ptr<Pulse::Events::Event<int, int>> WindowResizeEvent; // Format: <int width, int height>.Gets triggered when the window is resized.
		extern std::shared_ptr<Pulse::Events::Event<>> WindowCloseEvent; // Format: <>.Gets triggered when the window is closed.
		
	} // namespace Window

	namespace Input {
	
		extern std::shared_ptr<Pulse::Events::Event<int, int, int, int>> KeyEvent; // Format: <int key, int scancode, int action, int mods>.Gets triggered when a key interaction takes place.
		extern std::shared_ptr<Pulse::Events::Event<int, int, int>> MouseEvent; // Format: <int button, int action, int mods>.Gets triggered when a mouse interaction takes place.
		extern std::shared_ptr<Pulse::Events::Event<double, double>> ScrollEvent; // Format: <double xOffset, double yOffset>.Gets triggered scrolling with a device takes place.
		extern std::shared_ptr<Pulse::Events::Event<double, double>> MouseMovedEvent; // Format: <double xPos, double yPos>.Gets triggered when the mouse moves.

	} // namespace Input

} // namespace Pulse::Events
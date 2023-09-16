// The purpose of this file is to allow convenient inclusion of the Event system.
#pragma once

#include "Pulse/Events/IEventListener.h"
#include "Pulse/Modules/Input/KeyCodes.h"
#include "Pulse/Modules/Input/MouseCodes.h"
#include "Pulse/Modules/Input/InputActions.h"

namespace Pulse::Events {

	namespace Window {

		inline std::shared_ptr<Pulse::Events::Event<int, int>> WindowResizeEvent = Pulse::Events::Event<int, int>::Create(); // Format: <int width, int height>.Gets triggered when the window is resized.
		inline std::shared_ptr<Pulse::Events::Event<>> WindowCloseEvent = Pulse::Events::Event<>::Create(); // Format: <>.Gets triggered when the window is closed.

	} // namespace Window

	namespace Input {

		inline std::shared_ptr<Pulse::Events::Event<Pulse::Input::KeyCode, Pulse::Input::InputAction>> KeyEvent = Pulse::Events::Event<Pulse::Input::KeyCode, Pulse::Input::InputAction>::Create(); // Format: <Pulse::Input::KeyCode keyCode, Pulse::Input::InputAction inputAction>.Gets triggered when a key interaction takes place.
		inline std::shared_ptr<Pulse::Events::Event<Pulse::Input::MouseCode, Pulse::Input::InputAction>> MouseEvent = Pulse::Events::Event<Pulse::Input::MouseCode, Pulse::Input::InputAction>::Create(); // Format: <Pulse::Input::MouseCode mouseCode, Pulse::Input::InputAction inputAction>.Gets triggered when a mouse interaction takes place.
		inline std::shared_ptr<Pulse::Events::Event<double, double>> ScrollEvent = Pulse::Events::Event<double, double>::Create(); // Format: <double xOffset, double yOffset>.Gets triggered scrolling with a device takes place.
		inline std::shared_ptr<Pulse::Events::Event<double, double>> MouseMovedEvent = Pulse::Events::Event<double, double>::Create(); // Format: <double xPos, double yPos>.Gets triggered when the mouse moves.
		inline std::shared_ptr<Pulse::Events::Event<unsigned int>> CharEvent = Pulse::Events::Event<unsigned int>::Create(); // Format: <unsigned int unicode codepoint>.Gets triggered when a character is entered.

	} // namespace Input

} // namespace Pulse::Events

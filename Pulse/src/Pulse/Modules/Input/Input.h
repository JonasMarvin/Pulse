#pragma once

#include "Pulse/Modules/IModule.h"
#include "Pulse/Modules/Input/KeyCodes.h"
#include "Pulse/Modules/Input/MouseCodes.h"
#include "Pulse/Modules/Input/GamepadCodes.h"
#include "Pulse/Modules/Input/JoystickCodes.h"

namespace Pulse::Modules {

	// interface class for input on different platforms
	class PLS_API Input : public IModule {
	public:
		void Initialize() override = 0; // Virtual function to handle initialization of the input.
		void Shutdown() override = 0; // Virtual function to handle shutdown of the input.

		// Functions for Keyboard
		virtual bool IsKeyPressed(const Pulse::Input::KeyCode key) = 0; // Virtual function to check if a key is pressed. Implemented by the platform specific input module.

		// Functions for Mouse
		virtual bool IsMouseButtonPressed(const Pulse::Input::MouseCode button) = 0; // Virtual function to check if a mouse button is pressed. Implemented by the platform specific input module.
		virtual float GetMouseX() = 0; // Virtual function to get the x position of the mouse. Implemented by the platform specific input module.
		virtual float GetMouseY() = 0; // Virtual function to get the y position of the mouse. Implemented by the platform specific input module.
		virtual std::pair<float, float> GetMousePosition() = 0; // Virtual function to get the position of the mouse. First value is x and second y. Implemented by the platform specific input module.

		// Functions for Gamepads
		virtual bool IsGamepadConnected(Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to check if a specific gamepad is connected. Implemented by the platform-specific input module.
		virtual bool IsGamepadButtonPressed(Pulse::Input::GamepadButtonCode button, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to check if a gamepad button is pressed. Implemented by the platform-specific input module.
		virtual bool GetGamepadRightAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the position of the right axis of the gamepad. First value is x and second y. Implemented by the platform-specific input module.
		virtual bool GetGamepadRightAxisX(float& x, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the x position of the right axis of the gamepad. Implemented by the platform-specific input module.
		virtual bool GetGamepadRightAxisY(float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the y position of the right axis of the gamepad. Implemented by the platform-specific input module.
		virtual bool GetGamepadLeftAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the position of the left axis of the gamepad. First value is x and second y. Implemented by the platform-specific input module.
		virtual bool GetGamepadLeftAxisX(float& x, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the x position of the left axis of the gamepad. Implemented by the platform-specific input module.
		virtual bool GetGamepadLeftAxisY(float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the y position of the left axis of the gamepad. Implemented by the platform-specific input module.
		virtual bool GetGamepadRightTrigger(float& value, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the right trigger of the gamepad. Implemented by the platform-specific input module.
		virtual bool GetGamepadLeftTrigger(float& value, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) = 0; // Virtual function to get the left trigger of the gamepad. Implemented by the platform-specific input module.

	protected:
		Input() = default; // Default constructor is protected to only allow module manager to create it.
		virtual ~Input() = default; // Default destructor is protected to only allow module manager to destroy it.

		friend class ModuleManager; // Module manager is a friend to allow it to create and destroy modules.
	}; // class Input

} // namespace Pulse::Modules
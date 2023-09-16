#pragma once

#include "Pulse/Modules/Input/Input.h"

#include <GLFW/glfw3.h>

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"

namespace Pulse::Modules::Windows {

	class PLS_API WindowsInput : public Input {
	public:
		void Initialize() override; // function to initialize the input module.
		void Update() override; // function to handle the update event of the input module.
		void Shutdown() override; // function to shutdown the module.

		// Functions for Keyboard
		bool IsKeyPressed(const Pulse::Input::KeyCode keyCode) override; // function to check if a key is pressed.

		// Functions for Mouse
		bool IsMouseButtonPressed(const Pulse::Input::MouseCode mouseCode) override; // function to check if a mouse button is pressed.
		float GetMouseX() override; // function to get the x position of the mouse.
		float GetMouseY() override; // function to get the y position of the mouse.
		std::pair<float, float> GetMousePosition() override; // function to get the position of the mouse. First value is x and second y.

		// Functions for Gamepad
		bool IsGamepadConnected(Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to check if a gamepad is connected.
		bool IsGamepadButtonPressed(Pulse::Input::GamepadButtonCode gamepadButtonCode, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to check if a gamepad button is pressed.
		bool GetGamepadRightAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the position of the right axis of the gamepad. First value is x and second y.
		bool GetGamepadRightAxisX(float& x, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the x position of the right axis of the gamepad.
		bool GetGamepadRightAxisY(float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the y position of the right axis of the gamepad.
		bool GetGamepadLeftAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the position of the left axis of the gamepad. First value is x and second y.
		bool GetGamepadLeftAxisX(float& x, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the x position of the left axis of the gamepad.
		bool GetGamepadLeftAxisY(float& y, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the y position of the left axis of the gamepad.
		bool GetGamepadRightTrigger(float& value, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the right trigger of the gamepad.
		bool GetGamepadLeftTrigger(float& value, Pulse::Input::JoystickCode joystickCode = Pulse::Input::JoystickCode::Joystick1) override; // Function to get the left trigger of the gamepad.

	private:
		WindowsInput() : gamepadStates_{} {}; // default constructor private to prevent instantiation.
		~WindowsInput() = default; // default destructor private to prevent instantiation

		GLFWwindow* window_ = nullptr; // pointer to the window.
		GLFWgamepadstate gamepadStates_[static_cast<uint32_t>(Pulse::Input::JoystickCode::JoystickLast)]; // state of the gamepads. update has do be done manually before a check

		friend class ModuleManager; // friend class to allow the module manager to instantiate and destroy the class.

	}; // class WindowsInput

} // namespace Pulse::Modules::Windows
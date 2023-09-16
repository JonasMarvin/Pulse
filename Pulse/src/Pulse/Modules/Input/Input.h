#pragma once

#include "Pulse/Modules/IModule.h"
#include "Pulse/Modules/Input/KeyCodes.h"
#include "Pulse/Modules/Input/MouseCodes.h"
#include "Pulse/Modules/Input/GamepadCodes.h"

namespace Pulse::Modules {

	// interface class for input on different platforms
	class PLS_API Input : public IModule {
	public:
		void Update() override = 0; // Virtual function to handle update of the input
		void Initialize() override = 0; // Virtual function to handle initialization of the input.
		void Shutdown() override = 0; // Virtual function to handle shutdown of the input.

		// Functions for Keyboard
		virtual bool IsKeyPressed(Pulse::Input::KeyCode key) = 0; // Virtual function to check if a key is pressed. Implemented by the platform specific input module.

		// Functions for Mouse
		virtual bool IsMouseButtonPressed(Pulse::Input::MouseCode button) = 0; // Virtual function to check if a mouse button is pressed. Implemented by the platform specific input module.
		virtual float GetMouseX() = 0; // Virtual function to get the x position of the mouse. Implemented by the platform specific input module.
		virtual float GetMouseY() = 0; // Virtual function to get the y position of the mouse. Implemented by the platform specific input module.
		
		// Functions for Gamepads
		virtual bool IsGamepadButtonPressed(Pulse::Input::GamepadButtonCode button) = 0; // Virtual function to check if a gamepad button is pressed. Implemented by the platform specific input module.
		virtual float GetGamepadRightAxisX() = 0; // Virtual function to get the x position of the right axis of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadRightAxisY() = 0; // Virtual function to get the y position of the right axis of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadLeftAxisX() = 0; // Virtual function to get the x position of the left axis of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadLeftAxisY() = 0; // Virtual function to get the y position of the left axis of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadRightTriggerXAxis() = 0; // Virtual function to get the right trigger of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadRightTriggerYAxis() = 0; // Virtual function to get the right trigger of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadLeftTriggerXAxis() = 0; // Virtual function to get the left trigger of the gamepad. Implemented by the platform specific input module.
		virtual float GetGamepadLeftTriggerYAxis() = 0; // Virtual function to get the left trigger of the gamepad. Implemented by the platform specific input module.
		
	protected:
		Input() = default; // Default constructor is protected to only allow module manager to create it.
		virtual ~Input() = default; // Default destructor is protected to only allow module manager to destroy it.

		friend class ModuleManager; // Module manager is a friend to allow it to create and destroy modules.
	}; // class Input

} // namespace Pulse::Modules
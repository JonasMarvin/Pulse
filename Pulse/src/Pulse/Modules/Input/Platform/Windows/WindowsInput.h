#pragma once

#include "Pulse/Modules/Input/Input.h"

#include <GLFW/glfw3.h>

namespace Pulse::Modules::Windows {

	class PLS_API WindowsInput : public Input {
	public:
		void Initialize() override; // function to initialize the input
		void Update() override; // function to handle the update event of the input
		void Shutdown() override; // function to shutdown the 

	private:
		WindowsInput() = default; // default constructor private to prevent instantiation
		~WindowsInput() = default; // default destructor private to prevent instantiation

		friend class ModuleManager; // friend class to allow the module manager to instantiate and destroy the class

	}; // class WindowsInput

} // namespace Pulse::Modules::Windows
#pragma once

#include "Pulse/Modules/Window/Window.h"

#include <GLFW/glfw3.h>

namespace Pulse::Modules::Windows {

	// Class for a Windows window
	// Its a module and should only be created and managed by the module manager
	class WindowsWindow : public Pulse::Modules::Window {
	public:
		void Initialize() override; // function to initialize the window
		void Update() override; // function to handle the update event of the window
		void Shutdown() override; // function to shutdown the window

		unsigned int GetWidth() const override; // function to get the width of the window
		unsigned int GetHeight() const override; // function to get the height of the window

		// Window attributes
		void SetVSync(bool enabled) override; // function to set the vsync of the window
		bool IsVSync() const override; // function to get the vsync of the window

	private:
		WindowsWindow() : window_(nullptr) {}; // default constructor private to prevent creation of the window outside of the module manager
		~WindowsWindow() = default; // default destructor private to prevent deletion of the window outside of the module manager

		GLFWwindow* window_ = nullptr; // pointer to the GLFW window

		struct WindowData { // struct to store the window data
			std::string title = ""; // title of the window
			unsigned int width = 500; // width of the window
			unsigned int height = 500; // height of the window
			bool vsync = false; // vsync of the window
		} data_; // window data

		friend class ModuleManager; // friend class to allow the module manager to create and manage the window

	}; // class WindowsWindow

} // namespace Pulse
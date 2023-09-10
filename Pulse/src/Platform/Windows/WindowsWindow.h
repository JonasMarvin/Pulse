#pragma once

#include "Pulse/Core/Window.h"

#include <GLFW/glfw3.h>

namespace Pulse {

	// Class for a Windows window
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& properties); // constructor taking in window properties
		virtual ~WindowsWindow(); // virtual destructor for inheritance reasons

		void OnUpdate() override; // function to handle the update event of the window

		unsigned int GetWidth() const override; // function to get the width of the window
		unsigned int GetHeight() const override; // function to get the height of the window

		// Window attributes
		void SetVSync(bool enabled) override; // function to set the vsync of the window
		bool IsVSync() const override; // function to get the vsync of the window

	private:
		GLFWwindow* window_; // pointer to the GLFW window

		struct WindowData { // struct to store the window data
			std::string title = ""; // title of the window
			unsigned int width = 0; // width of the window
			unsigned int height = 0; // height of the window
			bool vsync = false; // vsync of the window
		} data_; // window data

	}; // class WindowsWindow

} // namespace Pulse




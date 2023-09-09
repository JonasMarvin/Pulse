#pragma once

#include <string>

#include "Pulse/Core.h"
#include "Pulse/Events/Events.h"

namespace Pulse {

	// Window properties
	struct WindowProperties {
		std::string title; // Title of the window
		unsigned int width; // Width of the window in pixels
		unsigned int height; // Height of the window in pixels

		WindowProperties(const std::string& title = "Pulse Engine",
						unsigned int width = 1280,
						unsigned int height = 720)
			: title(title), width(width), height(height) {} // Constructor with default values
	};

	// Interface representing a desktop system based Window
	// Use the Create function to create a window because it has to be created on the heap.
	// This interface will be implemented by platform specific window classes.
	class PLS_API Window {
	public:
		virtual ~Window() {} // Virtual destructor to allow deletion of the derived class.

		virtual void OnUpdate() = 0; // Virtual function to handle update of the window.

		virtual unsigned int GetWidth() const = 0; // Virtual function to get the width of the window.
		virtual unsigned int GetHeight() const = 0; // Virtual function to get the height of the window.

		virtual void SetVSync(bool enabled) = 0; // Virtual function to set the vsync of the window.
		virtual bool IsVSync() const = 0; // Virtual function to get the vsync of the window.

		static Window* Create(const WindowProperties& properties = WindowProperties()); // Static function to create a window. Returns a pointer to the created window of the platform in use.
	};

} // namespace Pulse
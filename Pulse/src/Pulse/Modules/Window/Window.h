#pragma once

#include <string>

#include "Pulse/Core/Core.h"
#include "Pulse/Events/Events.h"
#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {

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
	// Its a module that has to be managed by the module manager. Dont create it directly and use the ModuleManager to create it.
	// This interface will be implemented by platform specific window classes.
	class PLS_API Window : IModule {
	public:
		void Update() override = 0; // Virtual function to handle update of the window.
		void Initialize() override = 0; // Virtual function to handle initialization of the window.
		void Shutdown() override = 0; // Virtual function to handle shutdown of the window.

		virtual unsigned int GetWidth() const = 0; // Virtual function to get the width of the window.
		virtual unsigned int GetHeight() const = 0; // Virtual function to get the height of the window.

		virtual void SetVSync(bool enabled) = 0; // Virtual function to set the vsync of the window.
		virtual bool IsVSync() const = 0; // Virtual function to get the vsync of the window.

	protected:
		Window() = default; // Default constructor protected so that it can only be created by the module manager.
		virtual ~Window() = default; // Default destructor protected so that it can only be deleted by the module manager.

		friend class ModuleManager; // The module manager is befriended with the module to allow it to call the Initialize, Update and Shutdown functions
	};

} // namespace Pulse::Modules
#pragma once

#include "Core.h"
#include "Window.h"

namespace Pulse
{
	// This is the base class for all Pulse applications.
	class PLS_API Application {
	public:
		Application(); // Constructor
		virtual ~Application(); // Virtual destructor for proper cleanup

		void Run(); // Main loop of the application

	private:
		std::unique_ptr<Window> window_; // Unique pointer to the window of the application
		bool isRunning_ = true; // Boolean to check if the application is running
	};

	Application* CreateApplication(); // To be defined in CLIENT

} // namespace Pulse
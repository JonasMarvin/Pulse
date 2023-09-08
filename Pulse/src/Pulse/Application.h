#pragma once

#include "Core.h"

namespace Pulse
{
	// This is the base class for all Pulse applications.
	class PLS_API Application {
	public:
		Application(); // Constructor
		virtual ~Application(); // Virtual destructor for proper cleanup

		void Run(); // Main loop of the application
	};

	Application* CreateApplication(); // To be defined in CLIENT

} // namespace Pulse
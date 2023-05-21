#pragma once

#include "Core.h"

namespace Pulse
{
	class PLS_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace Pulse
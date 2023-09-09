#include "pch.h"

#include <GLFW/glfw3.h>

#include "Application.h"

namespace Pulse {

	Application::Application() {
		window_ = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {

		while (true) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}

} // namespace Pulse
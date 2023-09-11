#include "pch.h"

#include "Pulse/Platform/Windows/WindowsWindow.h"

#include <glad/glad.h>

#include "Pulse/Events/Events.h"

// Define correspoding static events. Declaration is in Events.h
std::shared_ptr<Pulse::Events::Event<int, int>> Pulse::Events::Window::WindowResizeEvent = Pulse::Events::Event<int, int>::Create();
std::shared_ptr<Pulse::Events::Event<>> Pulse::Events::Window::WindowCloseEvent = Pulse::Events::Event<>::Create();
std::shared_ptr<Pulse::Events::Event<int, int, int, int>> Pulse::Events::Input::KeyEvent = Pulse::Events::Event<int, int, int, int>::Create();
std::shared_ptr<Pulse::Events::Event<int, int, int>> Pulse::Events::Input::MouseEvent = Pulse::Events::Event<int, int, int>::Create();
std::shared_ptr<Pulse::Events::Event<double, double>> Pulse::Events::Input::ScrollEvent = Pulse::Events::Event<double, double>::Create();
std::shared_ptr<Pulse::Events::Event<double, double>> Pulse::Events::Input::MouseMovedEvent = Pulse::Events::Event<double, double>::Create();

namespace Pulse::Modules::Windows {

	static bool isGLFWInitialized = false;

	void WindowsWindow::Initialize() {

		PLS_CORE_INFO("Creating window {0} ({1}, {2})", data_.title, data_.width, data_.height);
	
		if (!isGLFWInitialized) {
			int success = glfwInit();
			PLS_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback([](int error, const char* description) {
				PLS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});
			isGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)data_.width, (int)data_.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PLS_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.height = height;
			data.width = width;
			Pulse::Events::Window::WindowResizeEvent->Trigger(width, height);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			Pulse::Events::Window::WindowCloseEvent->Trigger();
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Pulse::Events::Input::KeyEvent->Trigger(key, scancode, action, mods);
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			Pulse::Events::Input::MouseEvent->Trigger(button, action, mods);
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset) {
			Pulse::Events::Input::ScrollEvent->Trigger(xOffset, yOffset);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) {
			Pulse::Events::Input::MouseMovedEvent->Trigger(xPos, yPos);
		});
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::Update() {
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	unsigned int WindowsWindow::GetWidth() const {
		return data_.width;
	}

	unsigned int WindowsWindow::GetHeight() const {
		return data_.height;
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		data_.vsync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return data_.vsync;
	}

} // namespace Pulse::Modules::Windows
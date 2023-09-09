#include "pch.h"

#include "WindowsWindow.h"
#include "Pulse/Log.h"
#include "Pulse/Events/Events.h"

namespace Pulse {

	static bool isGLFWInitialized = false;

	std::shared_ptr<Pulse::Events::Event<int, int>> Pulse::Events::Window::WindowResizeEvent = Pulse::Events::Event<int, int>::Create();
	std::shared_ptr<Pulse::Events::Event<>> Pulse::Events::Window::WindowCloseEvent = Pulse::Events::Event<>::Create();
	std::shared_ptr<Pulse::Events::Event<int, int, int, int>> Pulse::Events::Input::KeyEvent = Pulse::Events::Event<int, int, int, int>::Create();
	std::shared_ptr<Pulse::Events::Event<int, int, int>> Pulse::Events::Input::MouseEvent = Pulse::Events::Event<int, int, int>::Create();
	std::shared_ptr<Pulse::Events::Event<double, double>> Pulse::Events::Input::ScrollEvent = Pulse::Events::Event<double, double>::Create();
	std::shared_ptr<Pulse::Events::Event<double, double>> Pulse::Events::Input::MouseMovedEvent = Pulse::Events::Event<double, double>::Create();

	Window* Window::Create(const WindowProperties& properties) {
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) {
		data_.title = properties.title;
		data_.width = properties.width;
		data_.height = properties.height;

		PLS_CORE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);
	
		if (!isGLFWInitialized) {
			int success = glfwInit();
			PLS_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback([](int error, const char* description) {
				PLS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});
			isGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)properties.width, (int)properties.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
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

	WindowsWindow::~WindowsWindow() {
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::OnUpdate() {
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

} // namespace Pulse
#include "pch.h"

#include "WindowsWindow.h"
#include "Pulse/Log.h"

namespace Pulse {

	static bool isGLFWInitialized = false;

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
			isGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)properties.width, (int)properties.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);
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
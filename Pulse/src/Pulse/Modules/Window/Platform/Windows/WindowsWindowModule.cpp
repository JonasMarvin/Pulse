#include "pch.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindowModule.h"

#include "Pulse/Events/Events.h"
#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"

namespace Pulse::Modules::Windows {

	static bool isGLFWInitialized = false;

	void WindowsWindowModule::Initialize() {

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
		if (ModuleManager::GetInstance().HasModule<RendererModule>()) {
			ModuleManager::GetInstance().GetModule<RendererModule>()->SetContextWindow(window_);
		}

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
	}

	void WindowsWindowModule::Shutdown() {
		glfwDestroyWindow(window_);
		glfwTerminate();
	}

	void WindowsWindowModule::Update() {
		glfwPollEvents();
	}

	unsigned int WindowsWindowModule::GetWidth() const {
		return data_.width;
	}

	unsigned int WindowsWindowModule::GetHeight() const {
		return data_.height;
	}

	void WindowsWindowModule::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		data_.vsync = enabled;
	}

	bool WindowsWindowModule::IsVSync() const {
		return data_.vsync;
	}

	void* WindowsWindowModule::GetNativeWindow() const {
		return window_;
	}

} // namespace Pulse::Modules::Windows
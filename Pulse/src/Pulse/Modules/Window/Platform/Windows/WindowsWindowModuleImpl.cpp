#include "pch.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindowModuleImpl.h"

#include "Pulse/Events/Events.h"
#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"

namespace Pulse::Modules::Windows {

	static bool isGLFWInitialized = false;

	void WindowsWindowModuleImpl::Initialize() {

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
			Events::Window::WindowResizeEvent->Trigger(width, height);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window) {
			Events::Window::WindowCloseEvent->Trigger();
		});
	}

	void WindowsWindowModuleImpl::Shutdown() {
		glfwDestroyWindow(window_);
		glfwTerminate();
	}

	void WindowsWindowModuleImpl::Update() {
		glfwPollEvents();
	}

	unsigned int WindowsWindowModuleImpl::GetWidth() const {
		return data_.width;
	}

	unsigned int WindowsWindowModuleImpl::GetHeight() const {
		return data_.height;
	}

	void WindowsWindowModuleImpl::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		data_.vsync = enabled;
	}

	bool WindowsWindowModuleImpl::IsVSync() const {
		return data_.vsync;
	}

	void* WindowsWindowModuleImpl::GetNativeWindow() const {
		return window_;
	}

} // namespace Pulse::Modules::Windows
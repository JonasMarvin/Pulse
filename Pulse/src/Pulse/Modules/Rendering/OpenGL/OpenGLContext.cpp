#include "pch.h"

#include "Pulse/Modules/Rendering/OpenGL/OpenGLContext.h"
#include <glad/glad.h>

namespace Pulse::Modules::Rendering {

	OpenGLContext::OpenGLContext(void* window) : window_(static_cast<GLFWwindow*>(window)) {
		PLS_CORE_ASSERT(window_, "Window is null!");
	}

	void OpenGLContext::Initialize() {
		glfwMakeContextCurrent(window_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PLS_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(window_);
	}

} // namespace Pulse::Modules::Rendering
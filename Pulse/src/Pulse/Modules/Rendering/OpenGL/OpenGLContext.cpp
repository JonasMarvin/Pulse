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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		PLS_CORE_INFO("OpenGL Context initialized with GLFWwindow.");
		PLS_CORE_INFO("OpenGL info: Vendor: {0} | Renderer: {1} | Version {2}", (const char*)glGetString(GL_VENDOR), (const char*)glGetString(GL_RENDERER), (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(window_);
	}

} // namespace Pulse::Modules::Rendering
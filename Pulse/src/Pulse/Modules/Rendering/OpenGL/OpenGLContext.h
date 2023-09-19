#pragma once

#include "Pulse/Modules/Rendering/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Pulse::Modules::Rendering {

	// class to represent the OpenGL context. Gets created by the static Create function in GraphicsContext by the Renderer module
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(void* window); // Constructor to create the OpenGL context

		void Initialize() override; // function to initialize the OpenGL context
		void SwapBuffers() override; // function to swap the buffers of the OpenGL context

	private:
		GLFWwindow* window_;

	}; // class OpenGLContext

} // namespace Pulse::Modules::Rendering
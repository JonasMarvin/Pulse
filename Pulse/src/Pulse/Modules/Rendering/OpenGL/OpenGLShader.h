#pragma once

#include "Pulse/Modules/Rendering/Shader.h"

namespace Pulse::Modules::Rendering {

	// class to represent the OpenGL shader program
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource); // creating, compiling and linking the shader program
		~OpenGLShader(); // Destructor to destroy the shader program

		void Bind() const override; // Bind the shader program to OpenGL
		void Unbind() const override; // Unbind the shader program from OpenGL

	private:
		uint32_t rendererID_ = 0; // The ID of the shader program to be used by OpenGL
	}; // class OpenGLShader

} // namespace Pulse::Modules::Rendering
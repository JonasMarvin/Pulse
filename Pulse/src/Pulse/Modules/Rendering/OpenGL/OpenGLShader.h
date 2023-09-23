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

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override; // Upload a 4x4 matrix to the shader
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override; // Upload a 4 float vector to the shader

	private:
		uint32_t rendererID_ = 0; // The ID of the shader program to be used by OpenGL
	}; // class OpenGLShader

} // namespace Pulse::Modules::Rendering
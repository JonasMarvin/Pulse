#pragma once

#include "Pulse/Modules/Rendering/Shader.h"
#include <glm/glm.hpp>

namespace Pulse::Modules::Rendering {

	// class to represent the OpenGL shader program
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource); // creating, compiling and linking the shader program
		~OpenGLShader(); // Destructor to destroy the shader program

		void Bind() const override; // Bind the shader program to OpenGL
		void Unbind() const override; // Unbind the shader program from OpenGL

		void UploadUniformInt(const std::string& name, int value); // Upload an integer to the shader

		void UploadUniformFloat(const std::string& name, float value); // Upload a float to the shader
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values); // Upload a 2 float vector to the shader
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values); // Upload a 3 float vector to the shader
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values); // Upload a 4 float vector to the shader

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix); // Upload a 3x3 matrix to the shader
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix); // Upload a 4x4 matrix to the shader

		


	private:
		uint32_t rendererID_ = 0; // The ID of the shader program to be used by OpenGL
	}; // class OpenGLShader

} // namespace Pulse::Modules::Rendering
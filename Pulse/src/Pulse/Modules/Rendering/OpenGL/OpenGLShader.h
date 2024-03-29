#pragma once

#include "Pulse/Modules/Rendering/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum; // TODO: Remove this

namespace Pulse::Modules::Rendering {

	// class to represent the OpenGL shader program
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource); // creating, compiling and linking the shader program from strings
		OpenGLShader(const std::string& filepath); // creating, compiling and linking the shader program from a file
		OpenGLShader(const std::string& name, const std::string& filepath); // creating, compiling and linking the shader program from a file
		~OpenGLShader(); // Destructor to destroy the shader program

		void Bind() const override; // Bind the shader program to OpenGL
		void Unbind() const override; // Unbind the shader program from OpenGL
		const std::string& GetName() const override; // get the name of the shader

		void UploadUniformInt(const std::string& name, int value); // Upload an integer to the shader

		void UploadUniformFloat(const std::string& name, float value); // Upload a float to the shader
		void UploadUniformFloat2(const std::string& name, const glm::vec2& values); // Upload a 2 float vector to the shader
		void UploadUniformFloat3(const std::string& name, const glm::vec3& values); // Upload a 3 float vector to the shader
		void UploadUniformFloat4(const std::string& name, const glm::vec4& values); // Upload a 4 float vector to the shader

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix); // Upload a 3x3 matrix to the shader
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix); // Upload a 4x4 matrix to the shader

	private:
		std::string ReadFile(const std::string& filepath); // Read the shader source code from a file
		std::unordered_map<GLenum, std::string> ProcessShaderSource(const std::string& shaderSource); // Process the shader source code
		static GLenum ShaderTypeFromString(const std::string& type); // Get the shader type from a string

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources); // Compile the shader program

		uint32_t rendererID_ = 0; // The ID of the shader program to be used by OpenGL
		std::string name_; // The name of the shader program

	}; // class OpenGLShader

} // namespace Pulse::Modules::Rendering
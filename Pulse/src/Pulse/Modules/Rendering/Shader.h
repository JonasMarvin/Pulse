#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Pulse::Modules::Rendering {

	// interface class for shader programs. Implementation is API specific
	class Shader {
	public:
		virtual ~Shader() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the vertex buffer
		virtual void Unbind() const = 0; // unbind the vertex buffer

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0; // upload a 4x4 matrix to the shader
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) = 0; // upload a 4 float vector to the shader

		static std::shared_ptr<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource); // factory method to create vertex buffer of the current API
	}; // class Shader

} // namespace Pulse::Modules::Rendering
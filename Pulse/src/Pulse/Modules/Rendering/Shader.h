#pragma once

#include <string>

namespace Pulse::Modules::Rendering {

	// interface class for shader programs. Implementation is API specific
	class Shader {
	public:
		virtual ~Shader() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the vertex buffer
		virtual void Unbind() const = 0; // unbind the vertex buffer

		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource); // factory method to create vertex buffer of the current API
	}; // class Shader

} // namespace Pulse::Modules::Rendering
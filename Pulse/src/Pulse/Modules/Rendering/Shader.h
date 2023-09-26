#pragma once

#include <string>
#include <unordered_map>

namespace Pulse::Modules::Rendering {

	// interface class for shader programs. Implementation is API specific
	class Shader {
	public:
		virtual ~Shader() = default; // virtual destructor to ensure derived classes are destructed properly

		virtual void Bind() const = 0; // bind the shader
		virtual void Unbind() const = 0; // unbind the shader

		virtual const std::string& GetName() const = 0; // get the name of the shader

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource); // factory method to create a shader of the current API
		static Ref<Shader> Create(const std::string& filepath); // factory method to create a shader of the current API
		static Ref<Shader> Create(const std::string& name, const std::string& filepath); // factory method to create a shader of the current API

	}; // class Shader

	// class to represent a library of shaders
	class ShaderLibrary {
	public:
		void Add(const std::string& name, const Ref<Shader>& shader); // add a existing shader to the library with a specific name
		void Add(const Ref<Shader>& shader); // add a existing shader to the library
		
		Ref<Shader> Load(const std::string& name, const std::string& filepath); // load a shader from a file with a specific name
		Ref<Shader> Load(const std::string& filepath); // load a shader from a file
		
		Ref<Shader> Get(const std::string& name); // get a shader from the library

		bool Exists(const std::string& name) const; // check if a shader exists in the library
	private:
		std::unordered_map<std::string, Ref<Shader>> shaders_; // map of shaders in the library

	}; // class ShaderLibrary

} // namespace Pulse::Modules::Rendering
#include "pch.h"

#include "Shader.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLShader.h"

namespace Pulse::Modules::Rendering {

	// Shader implementation:
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Shader!");	return nullptr;
			case RendererAPI::Type::OpenGL:																							return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Shader!");	return nullptr;
			case RendererAPI::Type::OpenGL:																							return CreateRef<OpenGLShader>(filepath);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
		case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Shader!");	return nullptr;
		case RendererAPI::Type::OpenGL:																							return CreateRef<OpenGLShader>(filepath, name);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

	// ShaderLibrary implementation:
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		if (Exists(name)) {
			PLS_CORE_WARN("Shader {0} already exists in the Shader Library! Adding to the Shader library failed.", name);
			return;
		}
		shaders_[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		const auto& name = shader->GetName();
		if (Exists(name)) {
			PLS_CORE_WARN("Shader {0} already exists in the Shader Library! Adding to the Shader library failed.", name);
			return;
		}
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		PLS_CORE_ASSERT(Exists(name), "Shader {0} does not exist in the Shader Library! Retrieving from the Shader library failed.", name);
		return shaders_[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return shaders_.find(name) != shaders_.end();
	}

} // namespace Pulse::Modules::Rendering
#include "pch.h"

#include "Shader.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLShader.h"

namespace Pulse::Modules::Rendering {

	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Shader!");	return nullptr;
			case RendererAPI::Type::OpenGL:																							return CreateRef<OpenGLShader>(vertexSource, fragmentSource);
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

} // namespace Pulse::Modules::Rendering
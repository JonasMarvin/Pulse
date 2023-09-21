#include "pch.h"

#include "Shader.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/Renderer.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLShader.h"

namespace Pulse::Modules::Rendering {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (ModuleManager::GetInstance().GetModule<Renderer>()->GetRendererAPI()) {
			case Renderer::API::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Shader!");	return nullptr;
			case Renderer::API::OpenGL:																							return new OpenGLShader(vertexSource, fragmentSource);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace Pulse::Modules::Rendering
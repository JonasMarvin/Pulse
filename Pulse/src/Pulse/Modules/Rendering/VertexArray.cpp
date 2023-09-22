#include "pch.h"

#include "VertexArray.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLVertexArray.h"

namespace Pulse::Modules::Rendering {

	std::shared_ptr<VertexArray> VertexArray::Create() {
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:	PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by VertexArray!");	return nullptr;
			case RendererAPI::Type::OpenGL:																							return std::make_shared<OpenGLVertexArray>();
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace Pulse::Modules::Rendering
#include "pch.h"

#include "VertexArray.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/Renderer.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLVertexArray.h"

namespace Pulse::Modules::Rendering {

	VertexArray* VertexArray::Create() {
		switch (ModuleManager::GetInstance().GetModule<Renderer>()->GetRendererAPI()) {
			case Renderer::API::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by VertexArray!");	return nullptr;
			case Renderer::API::OpenGL:																								return new OpenGLVertexArray();
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace Pulse::Modules::Rendering
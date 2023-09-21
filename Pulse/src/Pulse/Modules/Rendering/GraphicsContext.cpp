#include "pch.h"

#include "Pulse/Modules/Rendering/GraphicsContext.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/Renderer.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLContext.h"

namespace Pulse::Modules::Rendering {

    GraphicsContext* GraphicsContext::Create(void* window)
    {
		switch (ModuleManager::GetInstance().GetModule<Renderer>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");	return nullptr;
			case RendererAPI::Type::OpenGL:																					return new OpenGLContext(window);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
    }
} // namespace Pulse::Modules::Rendering
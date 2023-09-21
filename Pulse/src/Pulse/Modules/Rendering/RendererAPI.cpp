#include "pch.h"

#include "Pulse/Modules/Rendering/RendererAPI.h"

#include "Pulse/Modules/Rendering/OpenGL/OpenGLRendererAPI.h"

namespace Pulse::Modules::Rendering {
	
	RendererAPI* RendererAPI::Create(RendererAPI::Type api) {
		switch (api) {
			case RendererAPI::Type::None:		PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");	return nullptr;
			case RendererAPI::Type::OpenGL:																					return new OpenGLRendererAPI();
		}
		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace Pulse::Modules::Rendering
#include "pch.h"

#include "Texture.h"

#include "Pulse/Modules/Rendering/RendererAPI.h"
#include "Pulse/Modules/Rendering/OpenGL/OpenGLTexture.h"
#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Modules/Rendering/RendererModule.h"

namespace Pulse::Modules::Rendering {

	// Texture2D implementation:
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (ModuleManager::GetInstance().GetModule<RendererModule>()->GetRendererAPIType()) {
			case RendererAPI::Type::None:	PLS_CORE_ASSERT(false, "RendererAPI::None is currently not supported by Texture 2D!");	return nullptr;
			case RendererAPI::Type::OpenGL:																							return CreateRef<OpenGLTexture2D>(path);
		}

		PLS_CORE_ASSERT(false, "Unknown renderer API!");
		return nullptr;
	}

} // namespace  Pulse::Modules::Rendering
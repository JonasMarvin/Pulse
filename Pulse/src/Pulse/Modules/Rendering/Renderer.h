#pragma once

#include "Pulse/Modules/IUpdatableModule.h"
#include "Pulse/Modules/Rendering/GraphicsContext.h"

// Class for rendering to a graphics api
// Used to abstract the different graphics api's to be easy to use
// Should only be created and managed by the module manager
namespace Pulse::Modules::Rendering {

	class Renderer : public IUpdatableModule {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		}; // enum class API

		void Initialize() override; // function to initialize the renderer
		void Update() override; // function to handle the update event of the renderer
		void Shutdown() override; // function to shutdown the renderer

		void SetContextWindow(void* window); // function to set the context window of the renderer
		API GetRendererAPI() const; // function to get the set api of the renderer

	private:
		API rendererAPI_ = API::OpenGL; // the api of the renderer

		GraphicsContext* graphicsContext_ = nullptr; // pointer to the graphics context

		Renderer() = default;
		~Renderer() = default;

		friend class ModuleManager;
	}; // class Renderer

} // namespace Pulse::Modules::Rendering
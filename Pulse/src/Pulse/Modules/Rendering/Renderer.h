#pragma once

#include "Pulse/Modules/IUpdatableModule.h"
#include "Pulse/Modules/Rendering/GraphicsContext.h"
#include "Pulse/Modules/Rendering/VertexArray.h"
#include "Pulse/Modules/Rendering/RendererAPI.h"

// Class for rendering to a graphics api
// Used to abstract the different graphics api's to be easy to use
// Should only be created and managed by the module manager
namespace Pulse::Modules {

	class Renderer : public IUpdatableModule {
	public:
		void Initialize() override; // function to initialize the renderer
		void Update() override; // function to handle the update event of the renderer
		void Shutdown() override; // function to shutdown the renderer

		void BeginScene(); // function to begin the frame
		void Submit(const std::shared_ptr<Rendering::VertexArray>& vertexArray);
		void EndScene(); // function to end the frame

		void SetContextWindow(void* window); // function to set the context window of the renderer

		const Rendering::RendererAPI::Type GetRendererAPIType() const; // function to get the set api of the renderer

		const Rendering::RendererAPI& GetRendererAPI() const; // function to get the renderer api

	private:
		Rendering::RendererAPI* rendererAPI_ = nullptr; // pointer to the renderer api

		Rendering::GraphicsContext* graphicsContext_ = nullptr; // pointer to the graphics context
		
		Renderer() = default;
		~Renderer() = default;

		friend class ModuleManager;
	}; // class Renderer

} // namespace Pulse::Modules::Rendering
#pragma once

#include "Pulse/Modules/IUpdatableModule.h"
#include "Pulse/Modules/Rendering/GraphicsContext.h"
#include "Pulse/Modules/Rendering/Buffer.h"
#include "Pulse/Modules/Rendering/Shader.h"
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
		void EndScene(); // function to end the frame

		void SetContextWindow(void* window); // function to set the context window of the renderer

		Rendering::RendererAPI::API GetRendererAPI() const; // function to get the set api of the renderer

	private:
		Rendering::RendererAPI::API rendererAPI_ = Rendering::RendererAPI::API::OpenGL; // the api of the renderer TODO: changable

		Rendering::GraphicsContext* graphicsContext_ = nullptr; // pointer to the graphics context
		std::shared_ptr<Rendering::Shader> shader_ = nullptr; // pointer to the shader
		std::shared_ptr<Rendering::VertexArray> vertexArray_ = nullptr; // vertex array object
		std::shared_ptr<Rendering::VertexBuffer> vertexBuffer_ = nullptr; // pointer to the vertex buffer
		std::shared_ptr<Rendering::IndexBuffer> indexBuffer_ = nullptr; // pointer to the index buffer
		
		std::shared_ptr<Rendering::VertexArray> squareVertexArray_ = nullptr; // vertex array object
		std::shared_ptr<Rendering::Shader> squareShader_ = nullptr; // pointer to the shader

		Renderer() = default;
		~Renderer() = default;

		friend class ModuleManager;
	}; // class Renderer

} // namespace Pulse::Modules::Rendering
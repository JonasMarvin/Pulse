#pragma once

#include "Pulse/Modules/IUpdatableModule.h"
#include "Pulse/Modules/Rendering/GraphicsContext.h"
#include "Pulse/Modules/Rendering/Buffer.h"
#include "Pulse/Modules/Rendering/Shader.h"
#include "Pulse/Modules/Rendering/VertexArray.h"

// Class for rendering to a graphics api
// Used to abstract the different graphics api's to be easy to use
// Should only be created and managed by the module manager
namespace Pulse::Modules {

	class Renderer : public IUpdatableModule {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		}; // enum class API

		void Initialize() override; // function to initialize the renderer
		void Update() override; // function to handle the update event of the renderer
		void Shutdown() override; // function to shutdown the renderer

		void BeginFrame(); // function to begin the frame
		void EndFrame(); // function to end the frame

		void SetContextWindow(void* window); // function to set the context window of the renderer

		API GetRendererAPI() const; // function to get the set api of the renderer

	private:
		API rendererAPI_ = API::OpenGL; // the api of the renderer TODO: changable

		Rendering::GraphicsContext* graphicsContext_ = nullptr; // pointer to the graphics context
		Rendering::Shader* shader_ = nullptr; // pointer to the shader
		Rendering::VertexArray* vertexArray_ = nullptr; // vertex array object
		Rendering::VertexBuffer* vertexBuffer_ = nullptr; // pointer to the vertex buffer
		Rendering::IndexBuffer* indexBuffer_ = nullptr; // pointer to the index buffer
		
		Rendering::VertexArray* squareVertexArray_ = nullptr; // vertex array object
		Rendering::Shader* squareShader_ = nullptr; // pointer to the shader

		Renderer() = default;
		~Renderer() = default;

		friend class ModuleManager;
	}; // class Renderer

} // namespace Pulse::Modules::Rendering
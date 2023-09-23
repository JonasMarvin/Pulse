#pragma once

#include "Pulse/Modules/IUpdatableModule.h"
#include "Pulse/Modules/Rendering/GraphicsContext.h"
#include "Pulse/Modules/Rendering/VertexArray.h"
#include "Pulse/Modules/Rendering/RendererAPI.h"
#include "Pulse/Modules/Rendering/Shader.h"

// Class for rendering to a graphics api
// Used to abstract the different graphics api's to be easy to use
// Should only be created and managed by the module manager
namespace Pulse::Modules {

	class RendererModule : public IUpdatableModule {
	public:
		void Initialize() override; // function to initialize the renderer
		void Update() override; // function to handle the update event of the renderer
		void Shutdown() override; // function to shutdown the renderer

		void SetViewProjectionMatrixReference(const glm::mat4* viewProjectionMatrix); // function to set the view projection matrix of the renderer to point to the given matrix. Used by the camera module
		void ResetViewProjectionMatrixReference(); // function to reset the view projection matrix of the renderer to point to the default matrix. Used by the camera module

		void BeginScene(); // function to begin the frame
		void Submit(const std::shared_ptr<Rendering::Shader> shader, const std::shared_ptr<Rendering::VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f)); // function to submit a object to get rendered
		void EndScene(); // function to end the frame

		void SetContextWindow(void* window); // function to set the context window of the renderer

		const Rendering::RendererAPI::Type GetRendererAPIType() const; // function to get the set api of the renderer

		const Rendering::RendererAPI& GetRendererAPI() const; // function to get the renderer api

	private:
		Rendering::RendererAPI* rendererAPI_ = nullptr; // pointer to the renderer api
		Rendering::GraphicsContext* graphicsContext_ = nullptr; // pointer to the graphics context
		
		const glm::mat4* viewProjectionMatrix_ = nullptr; // pointer to the view projection matrix
		const glm::mat4 defaultViewProjectionMatrix_ = glm::mat4(1.0f); // default view projection matrix

		RendererModule() = default; // default constructor private to prevent creation of the renderer outside of the module manager
		~RendererModule() = default; // default destructor private to prevent deletion of the renderer outside of the module manager

		friend class ModuleManager; // friend class to allow the module manager to create and manage the renderer
	}; // class Renderer

} // namespace Pulse::Modules::Rendering
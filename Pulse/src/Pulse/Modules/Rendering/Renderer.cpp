#include "pch.h"

#include "Pulse/Modules/Rendering/Renderer.h"

namespace Pulse::Modules {

	void Renderer::Initialize() {
		rendererAPI_ = Rendering::RendererAPI::Create(Rendering::RendererAPI::Type::OpenGL);
	}

	void Renderer::Update() {
		// TODO: Implement command queue and execute commands here or start a thread for it
	}

	void Renderer::Shutdown() {
		delete(graphicsContext_);
		graphicsContext_ = nullptr;
	}

	void Renderer::SetViewProjectionMatrixReference(const glm::mat4* viewProjectionMatrix) {
		viewProjectionMatrix_ = viewProjectionMatrix;
	}

	void Renderer::ResetViewProjectionMatrixReference() {
		viewProjectionMatrix_ = &defaultViewProjectionMatrix_;
	}

	void Renderer::BeginScene() {
		rendererAPI_->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		rendererAPI_->Clear();
	}

	void Renderer::Submit(const std::shared_ptr<Rendering::Shader> shader, const std::shared_ptr<Rendering::VertexArray>& vertexArray) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", *viewProjectionMatrix_);
		vertexArray->Bind();
		rendererAPI_->DrawIndexed(vertexArray);
	}

	void Renderer::EndScene() {
		graphicsContext_->SwapBuffers();
	}

	void Renderer::SetContextWindow(void* window) {
		graphicsContext_ = Rendering::GraphicsContext::Create(window);
		graphicsContext_->Initialize();
	}

	const Rendering::RendererAPI::Type Renderer::GetRendererAPIType() const {
		return rendererAPI_->GetAPIType();
	}

	const Rendering::RendererAPI& Renderer::GetRendererAPI() const{
		return *rendererAPI_;
	}
} // namespace Pulse::Modules::Rendering
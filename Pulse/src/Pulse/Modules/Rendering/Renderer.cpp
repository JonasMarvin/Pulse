#include "pch.h"

#include "Pulse/Modules/Rendering/Renderer.h"

#include "Pulse/Modules/Rendering/Shader.h"

namespace Pulse::Modules {

	void Renderer::Initialize() {
		rendererAPI_ = Rendering::RendererAPI::Create(Rendering::RendererAPI::Type::OpenGL);
	}

	void Renderer::Update() {
		
	}

	void Renderer::Shutdown() {
		delete(graphicsContext_);
		graphicsContext_ = nullptr;
	}

	void Renderer::BeginScene() {
		rendererAPI_->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		rendererAPI_->Clear();
	}

	void Renderer::Submit(const std::shared_ptr<Rendering::VertexArray>& vertexArray) {
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
#include "pch.h"

#include "Pulse/Modules/Rendering/RendererModule.h"

#include "Pulse/Modules/Rendering/OpenGL/OpenGLShader.h"

namespace Pulse::Modules {

	void RendererModule::Initialize() {
		rendererAPI_ = Rendering::RendererAPI::Create(Rendering::RendererAPI::Type::OpenGL);
	}

	void RendererModule::Update() {
		// TODO: Implement command queue and execute commands here or start a thread for it
	}

	void RendererModule::Shutdown() {
		delete(graphicsContext_);
		graphicsContext_ = nullptr;
	}

	void RendererModule::SetViewProjectionMatrixReference(const glm::mat4* viewProjectionMatrix) {
		viewProjectionMatrix_ = viewProjectionMatrix;
	}

	void RendererModule::ResetViewProjectionMatrixReference() {
		viewProjectionMatrix_ = &defaultViewProjectionMatrix_;
	}

	void RendererModule::BeginScene() {
		rendererAPI_->SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		rendererAPI_->Clear();
	}

	void RendererModule::Submit(const Ref<Rendering::Shader> shader, const Ref<Rendering::VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		std::static_pointer_cast<Rendering::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", *viewProjectionMatrix_);
		std::static_pointer_cast<Rendering::OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		rendererAPI_->DrawIndexed(vertexArray);
	}

	void RendererModule::EndScene() {
		graphicsContext_->SwapBuffers();
	}

	void RendererModule::SetContextWindow(void* window) {
		graphicsContext_ = Rendering::GraphicsContext::Create(window);
		graphicsContext_->Initialize();
	}

	const Rendering::RendererAPI::Type RendererModule::GetRendererAPIType() const {
		return rendererAPI_->GetAPIType();
	}

	const Rendering::RendererAPI& RendererModule::GetRendererAPI() const{
		return *rendererAPI_;
	}
} // namespace Pulse::Modules::Rendering
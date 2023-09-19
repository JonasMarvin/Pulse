#include "pch.h"

#include "Renderer.h"

namespace Pulse::Modules::Rendering {

	void Renderer::Initialize() {

	}

	void Renderer::Update() {
		graphicsContext_->SwapBuffers();
	}

	void Renderer::Shutdown() {
		delete graphicsContext_;
		graphicsContext_ = nullptr;
	}

	void Renderer::SetContextWindow(void* window) {
		graphicsContext_ = GraphicsContext::Create(window);
		graphicsContext_->Initialize();
	}

	Renderer::API Renderer::GetRendererAPI() const
	{
		return rendererAPI_;
	}
} // namespace Pulse::Modules::Rendering
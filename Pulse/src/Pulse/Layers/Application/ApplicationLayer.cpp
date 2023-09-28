#include "pch.h"

#include "Pulse/Layers/Application/ApplicationLayer.h"
#include "Pulse/Core/Engine.h"

namespace Pulse::Layers {
		
	ApplicationLayer::ApplicationEventListener::ApplicationEventListener() {
		AddListener(Events::Window::WindowCloseEvent ,&ApplicationEventListener::OnWindowClose);
	}

	void ApplicationLayer::ApplicationEventListener::OnWindowClose() {
		Engine::Stop(); // TODO: Maybe not the right place to call this? Or Add a virtual function application layer for this to be called on window close? Or does it belong in the engine?
	}

	void ApplicationLayer::OnAttach() {
		applicationEventListener_ = Events::IEventListener<ApplicationEventListener>::Create();
	}

	void ApplicationLayer::OnDetach() {
		applicationEventListener_ = nullptr;
	}

} // namespace Pulse::Layers
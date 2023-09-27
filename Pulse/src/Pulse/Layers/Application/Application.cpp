#include "pch.h"

#include "Pulse/Layers/Application/Application.h"
#include "Pulse/Core/Engine.h"

namespace Pulse::Layers {
		
	Application::ApplicationEventListener::ApplicationEventListener() {
		AddListener(Events::Window::WindowCloseEvent ,&ApplicationEventListener::OnWindowClose);
	}

	void Application::ApplicationEventListener::OnWindowClose() {
		Engine::Stop(); // TODO: Maybe not the right place to call this? Or Add a virtual function application layer for this to be called on window close? Or does it belong in the engine?
	}

	void Application::OnAttach() {
		applicationEventListener_ = Events::IEventListener<ApplicationEventListener>::Create();
	}

	void Application::OnDetach() {
		applicationEventListener_ = nullptr;
	}

} // namespace Pulse::Layers
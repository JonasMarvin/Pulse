#include "pch.h"

#include <glad/glad.h>

#include "Application.h"

#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"
#include "Pulse/Modules/Input/Platform/Windows/WindowsInput.h"
#include "Pulse/Modules/ImGui/ImGuiModule.h"
#include "Pulse/Modules/Rendering/Renderer.h"

namespace Pulse {
		
	Application::ApplicationEventListener::ApplicationEventListener(Application& application)
		: parentApplication_(application) {
		AddListener(Events::Window::WindowCloseEvent ,&ApplicationEventListener::OnWindowClose);
	}

	void Application::ApplicationEventListener::OnWindowClose() {
		parentApplication_.isRunning_ = false;
		PLS_CORE_INFO("Window closed");
	}

	Application::Application() :
		moduleManager_(Pulse::Modules::ModuleManager::GetInstance()),
		applicationEventListener_(Events::IEventListener<ApplicationEventListener>::Create(*this)) {
		
		// Registering core modules
		moduleManager_.RegisterModule<Pulse::Modules::Rendering::Renderer>();
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsWindow>();
		moduleManager_.RegisterModule<Pulse::Modules::Windows::WindowsInput>();
		moduleManager_.RegisterModule<Pulse::Modules::ImGuiModule>();

		glGenVertexArrays(1, &vertexArray_);
		glBindVertexArray(vertexArray_);

		glGenBuffers(1, &vertexBuffer_);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application() {
		isRunning_ = false;
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		while (isRunning_) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray_);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.UpdateModules();
		}
	}

} // namespace Pulse
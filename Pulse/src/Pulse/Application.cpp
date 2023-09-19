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

		std::string vertexSource = R"(
			#version 430 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;			

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		shader_ = std::make_unique<Modules::Rendering::OpenGLShader>(vertexSource, fragmentSource);
	}

	Application::~Application() {
		isRunning_ = false;
		moduleManager_.ShutdownModules();
	}

	void Application::Run() {
		while (isRunning_) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			shader_->Bind();
			glBindVertexArray(vertexArray_);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			moduleManager_.GetModule<Modules::ImGuiModule>()->BeginFrame();
			moduleManager_.RenderAllToImGui();
			moduleManager_.GetModule<Modules::ImGuiModule>()->EndFrame();
			moduleManager_.UpdateModules();
		}
	}

} // namespace Pulse
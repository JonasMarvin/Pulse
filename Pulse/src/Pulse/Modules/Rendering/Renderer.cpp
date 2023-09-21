#include "pch.h"

#include "Renderer.h"

#include <glad/glad.h>
#include "Pulse/Modules/Rendering/OpenGL/OpenGLBuffer.h"

namespace Pulse::Modules {

	void Renderer::Initialize() {
	}

	void Renderer::Update() {
		shader_->Bind();
		vertexArray_->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer_->GetCount(), GL_UNSIGNED_INT, nullptr);
		squareShader_->Bind();
		squareVertexArray_->Bind();
		glDrawElements(GL_TRIANGLES, squareVertexArray_->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Shutdown() {
		delete graphicsContext_;
		graphicsContext_ = nullptr;
		delete vertexBuffer_;
		vertexBuffer_ = nullptr;
		delete indexBuffer_;
		indexBuffer_ = nullptr;
		delete shader_;
		shader_ = nullptr;
		delete vertexArray_;
		vertexArray_ = nullptr;
	}

	void Renderer::BeginFrame() {
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::EndFrame() {
		graphicsContext_->SwapBuffers();
	}

	void Renderer::SetContextWindow(void* window) {
		graphicsContext_ = Rendering::GraphicsContext::Create(window);
		graphicsContext_->Initialize();

		vertexArray_ = Rendering::VertexArray::Create();

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		vertexBuffer_ = Rendering::VertexBuffer::Create(vertices, sizeof(vertices));

		Rendering::BufferLayout layout = {
			{ Rendering::ShaderDataType::Float3, "a_Position" }
		};
		vertexBuffer_->SetLayout(layout);
		vertexArray_->AddVertexBuffer(vertexBuffer_);

		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer_ = Rendering::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		vertexArray_->SetIndexBuffer(indexBuffer_);

		squareVertexArray_ = Rendering::VertexArray::Create();
		
		float squareVertices[3 * 4] = {
			-0.2f, -0.2f, 0.0f,
			 0.2f, -0.2f, 0.0f,
			 0.2f,  0.2f, 0.0f,
			-0.2f,  0.2, 0.0f
		};

		Rendering::VertexBuffer* squareVB = Rendering::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Rendering::ShaderDataType::Float3, "a_Position" }
		});
		squareVertexArray_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Rendering::IndexBuffer* squareIB = Rendering::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		squareVertexArray_->SetIndexBuffer(squareIB);

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

		std::string vertexSource2 = R"(
			#version 430 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;			

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource2 = R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(0.8, 0.2, 0.3, 1.0);
			}
		)";

		shader_ = Modules::Rendering::Shader::Create(vertexSource, fragmentSource);
		squareShader_ = Modules::Rendering::Shader::Create(vertexSource2, fragmentSource2);
	}

	Renderer::API Renderer::GetRendererAPI() const {
		return rendererAPI_;
	}
} // namespace Pulse::Modules::Rendering
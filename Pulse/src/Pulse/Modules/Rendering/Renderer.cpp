#include "pch.h"

#include "Renderer.h"

#include <glad/glad.h>
#include "Pulse/Modules/Rendering/OpenGL/OpenGLBuffer.h"

namespace Pulse::Modules::Rendering {

	void Renderer::Initialize() {
	}

	void Renderer::Update() {
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		shader_->Bind();
		glBindVertexArray(vertexArray_);
		glDrawElements(GL_TRIANGLES, indexBuffer_->GetCount(), GL_UNSIGNED_INT, nullptr);
		graphicsContext_->SwapBuffers();
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
	}

	void Renderer::SetContextWindow(void* window) {
		graphicsContext_ = GraphicsContext::Create(window);
		graphicsContext_->Initialize();

		glCreateVertexArrays(1, &vertexArray_);
		glBindVertexArray(vertexArray_);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		vertexBuffer_ = VertexBuffer::Create(vertices, sizeof(vertices));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		uint32_t index = 0;
		for (auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		

		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer_ = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

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

		shader_ = Modules::Rendering::Shader::Create(vertexSource, fragmentSource);
	}

	Renderer::API Renderer::GetRendererAPI() const {
		return rendererAPI_;
	}
} // namespace Pulse::Modules::Rendering
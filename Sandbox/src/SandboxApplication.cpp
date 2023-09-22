#include <Pulse.h>

using namespace Pulse::Modules;

class Sandbox : public Pulse::Application {
public:
	Sandbox() {

		renderer_ = ModuleManager::GetInstance().GetModule<Pulse::Modules::RendererModule>();
		//input_ = ModuleManager::GetInstance().GetModule<Pulse::Modules::Windows::WindowsInputModule>();

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
			-0.2f,  0.2f, 0.0f
		};

		std::shared_ptr<Rendering::VertexBuffer> squareVB = Rendering::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Rendering::ShaderDataType::Float3, "a_Position" }
			});
		squareVertexArray_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Rendering::IndexBuffer> squareIB = Rendering::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		squareVertexArray_->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 430 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection vec4(a_Position, 1.0);
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

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 2.0);
			}
		)";

		std::string fragmentSource2 = R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			void main() {
				color = vec4(0.8, 0.2, 0.3, 1.0);
			}
		)";

		shader_ = Pulse::Modules::Rendering::Shader::Create(vertexSource, fragmentSource);
		squareShader_ = Pulse::Modules::Rendering::Shader::Create(vertexSource2, fragmentSource2);
	}

	void OnUpdate() override {
		//if (input_->IsKeyPressed(Pulse::Input::KeyCode::Left)) {
			
		//}
	}

	void OnRender() override {
		renderer_->Submit(shader_, vertexArray_);
		renderer_->Submit(squareShader_, squareVertexArray_);
	}

	~Sandbox() {

	}

private:
	//Windows::WindowsInputModule* input_ = nullptr; // input module
	RendererModule* renderer_ = nullptr; // renderer module

	std::shared_ptr<Pulse::Modules::Rendering::Shader> shader_ = nullptr; // pointer to the shader
	std::shared_ptr<Pulse::Modules::Rendering::VertexArray> vertexArray_ = nullptr; // vertex array object
	std::shared_ptr<Pulse::Modules::Rendering::VertexBuffer> vertexBuffer_ = nullptr; // pointer to the vertex buffer
	std::shared_ptr<Pulse::Modules::Rendering::IndexBuffer> indexBuffer_ = nullptr; // pointer to the index buffer

	std::shared_ptr<Pulse::Modules::Rendering::VertexArray> squareVertexArray_ = nullptr; // vertex array object
	std::shared_ptr<Pulse::Modules::Rendering::Shader> squareShader_ = nullptr; // pointer to the shader
};

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}
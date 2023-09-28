#include <Pulse.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Pulse::Modules;

class Sandbox : public Pulse::Layers::ApplicationLayer {
public:
	Sandbox() {

		renderer_ = ModuleManager::GetInstance().GetModule<Pulse::Modules::RendererModule>();
		input_ = ModuleManager::GetInstance().GetModule<Pulse::Modules::InputModule>();
		camera_ = ModuleManager::GetInstance().GetModule<Pulse::Modules::CameraModule>();

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

		float squareVertices[5 * 4] = {
			-0.2f, -0.2f, 0.0f, 0.0f, 0.0f,
			 0.2f, -0.2f, 0.0f, 1.0f, 0.0f,
			 0.2f,  0.2f, 0.0f, 1.0f, 1.0f,
			-0.2f,  0.2f, 0.0f ,0.0f, 1.0f
		};

		Pulse::Ref<Rendering::VertexBuffer> squareVB = Rendering::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Rendering::ShaderDataType::Float3, "a_Position" },
			{ Rendering::ShaderDataType::Float2, "a_TexCoord" }
			});
		squareVertexArray_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Pulse::Ref<Rendering::IndexBuffer> squareIB = Rendering::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		squareVertexArray_->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 430 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		shaderLibrary_.Add(Pulse::Modules::Rendering::OpenGLShader::Create("VertexPosColor", vertexSource, fragmentSource));
		auto textureShader = shaderLibrary_.Load("assets/shaders/Texture.glsl");

		texture_ = Pulse::Modules::Rendering::Texture2D::Create("assets/textures/Test.png");
		textureAlphaChannel_ = Pulse::Modules::Rendering::Texture2D::Create("assets/textures/TestAlpha.png");

		std::static_pointer_cast<Pulse::Modules::Rendering::OpenGLShader>(textureShader)->Bind();
		std::static_pointer_cast<Pulse::Modules::Rendering::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void Update(const Pulse::TimeData& timeData) override {
		// Print FPS:
		if (input_->IsKeyPressed(Pulse::Input::KeyCode::F)) {
			PLS_INFO("FPS: {0}", 1.0f / timeData);
		}

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::L)) {
			squarePosition_.x += squareMoveSpeed * timeData; // Use the updated right vector
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::J)) {
			squarePosition_.x -= squareMoveSpeed * timeData; // Use the updated right vector
		}

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::K)) {
			squarePosition_.y -= squareMoveSpeed * timeData; // Use the updated right vector
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::I)) {
			squarePosition_.y += squareMoveSpeed * timeData; // Use the updated right vector
		}
	}

	void Render(const Pulse::TimeData& timeData) override {
		auto vertexPosColorShader = shaderLibrary_.Get("VertexPosColor");
		renderer_->Submit(vertexPosColorShader, vertexArray_);

		auto textureShader = shaderLibrary_.Get("Texture");
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.11f, y * 0.11f, 0.0f)) * scale;
				texture_->Bind();
				renderer_->Submit(textureShader, squareVertexArray_, glm::translate(glm::mat4(1.0f), squarePosition_) * transform);
				textureAlphaChannel_->Bind();
				renderer_->Submit(textureShader, squareVertexArray_, glm::translate(glm::mat4(1.0f), squarePosition_) * transform);
			}
		}
	}

	void RenderImGui(const Pulse::TimeData& timeData) override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor_));
		ImGui::End();
	}

	~Sandbox() {

	}

private:
	InputModule* input_ = nullptr; // input module
	RendererModule* renderer_ = nullptr; // renderer module
	CameraModule * camera_ = nullptr; // renderer module

	float squareMoveSpeed = 5; // rotation speed of the camera

	glm::vec3 squarePosition_ = glm::vec3(0.0f); // position of the square
	glm::vec3 squareColor_ = glm::vec3(1.0f, 0.0f, 0.0f); // color of the square
	Pulse::Modules::Rendering::ShaderLibrary shaderLibrary_; // shader library

	Pulse::Ref<Pulse::Modules::Rendering::VertexArray> vertexArray_ = nullptr; // vertex array object
	Pulse::Ref<Pulse::Modules::Rendering::VertexBuffer> vertexBuffer_ = nullptr; // pointer to the vertex buffer
	Pulse::Ref<Pulse::Modules::Rendering::IndexBuffer> indexBuffer_ = nullptr; // pointer to the index buffer
	Pulse::Ref<Pulse::Modules::Rendering::Texture2D> texture_ = nullptr; // pointer to the texture
	Pulse::Ref<Pulse::Modules::Rendering::Texture2D> textureAlphaChannel_ = nullptr; // pointer to the texture

	Pulse::Ref<Pulse::Modules::Rendering::VertexArray> squareVertexArray_ = nullptr; // vertex array object
};

Pulse::Layers::ApplicationLayer* Pulse::Layers::CreateApplication() {
	return new Sandbox();
}
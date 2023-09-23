#include <Pulse.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Pulse::Modules;

class Sandbox : public Pulse::Application {
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

		std::string vertexSource2 = R"(
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

		std::string fragmentSource2 = R"(
			#version 430 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0);
			}
		)";

		shader_ = Pulse::Modules::Rendering::Shader::Create(vertexSource, fragmentSource);
		squareShader_ = Pulse::Modules::Rendering::Shader::Create(vertexSource2, fragmentSource2);
	}

	void OnUpdate(const Pulse::TimeData& timeData) override {
		// Print FPS:
		if (input_->IsKeyPressed(Pulse::Input::KeyCode::F)) {
			PLS_INFO("FPS: {0}", 1.0f / timeData);
		}
		// Toggle Perspective and Orthographic:
		if (input_->IsKeyPressed(Pulse::Input::KeyCode::P)) {
			camera_->SetType(Pulse::Modules::CameraModule::Type::Perspective);
		}
		if (input_->IsKeyPressed(Pulse::Input::KeyCode::O)) {
			camera_->SetType(Pulse::Modules::CameraModule::Type::Orthographic);
		}

		// Movement
		glm::vec3 translation = camera_->GetPosition();

		glm::vec3 right = camera_->GetRight();
		glm::vec3 up = camera_->GetUp();
		glm::vec3 front = camera_->GetFront();

		glm::vec3 movement;
		if (input_->IsKeyPressed(Pulse::Input::KeyCode::D)) {
			movement = right * (cameraSpeed_ * timeData); // Use the updated right vector
			translation += movement;
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::A)) {
			movement = right * (cameraSpeed_ * timeData); // Use the updated right vector
			translation -= movement;
		}

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::S)) {
			movement = front * (cameraSpeed_ * timeData); // Use the updated front vector
			translation -= movement;
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::W)) {
			movement = front * (cameraSpeed_ * timeData); // Use the updated front vector
			translation += movement;
		}

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::Q)) {
			movement = up * (cameraSpeed_ * timeData); // Use the updated up vector
			translation -= movement;
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::E)) {
			movement = up * (cameraSpeed_ * timeData); // Use the updated up vector
			translation += movement;
		}

		camera_->SetPosition(translation);
		glm::quat currentRotation = camera_->GetRotation();

		glm::quat rotationChangeY = glm::quat(1, 0, 0, 0); // Identity quaternion for Y-axis
		glm::quat rotationChangeX = glm::quat(1, 0, 0, 0); // Identity quaternion for X-axis

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::Left)) {
			rotationChangeY = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::Right)) {
			rotationChangeY = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
		}

		if (input_->IsKeyPressed(Pulse::Input::KeyCode::Up)) {
			rotationChangeX = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
		}

		else if (input_->IsKeyPressed(Pulse::Input::KeyCode::Down)) {
			rotationChangeX = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
		}

		currentRotation = rotationChangeY * currentRotation * rotationChangeX;
		camera_->SetRotation(currentRotation);

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

	void OnRender() override {
		renderer_->Submit(shader_, vertexArray_);
		std::static_pointer_cast<Pulse::Modules::Rendering::OpenGLShader>(squareShader_)->Bind();
		std::static_pointer_cast<Pulse::Modules::Rendering::OpenGLShader>(squareShader_)->UploadUniformFloat3("u_Color", squareColor_);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.11f, y * 0.11f, 0.0f)) * scale;
				renderer_->Submit(squareShader_, squareVertexArray_, glm::translate(glm::mat4(1.0f), squarePosition_) * transform);
			}
		}
	}

	void OnImGuiRender() override {
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

	float cameraSpeed_ = 0.5f; // speed of the camera
	float cameraRotationSpeed_ = 100; // rotation speed of the camera

	float squareMoveSpeed = 5; // rotation speed of the camera

	glm::vec3 squarePosition_ = glm::vec3(0.0f); // position of the square
	glm::vec3 squareColor_ = glm::vec3(1.0f, 0.0f, 0.0f); // color of the square

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
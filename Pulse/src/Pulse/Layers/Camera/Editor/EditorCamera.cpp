#include "pch.h"

#include "Pulse/Layers/Camera/Editor/EditorCamera.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Layers/Camera/CameraLayer.h"
#include "Pulse/Layers/LayerManager.h"

namespace Pulse::Layers::Camera::Editor {

	EditorCamera::EditorCamera() {
		orthographicCameraData_ = new OrthographicCameraData(glm::vec3(0.0f, 0.0f, orthographicZPosition_));
		isometricCameraData_ = new IsometricCameraData(glm::vec3(0.0f,0.0f, orthographicZPosition_));
		perspectiveCameraData_ = new PerspectiveCameraData(glm::vec3(0.0f, 0.0f, orthographicZPosition_));
		activeCameraType_ = Type::Perspective;

		inputModule_ = Modules::ModuleManager::GetInstance().GetModule<Modules::InputModule>();
		cameraLayer_ = LayerManager::GetInstance().GetLayer<CameraLayer>();
	}

	EditorCamera::~EditorCamera() {
		delete isometricCameraData_;
		isometricCameraData_ = nullptr;
		delete orthographicCameraData_;
		orthographicCameraData_ = nullptr;
		delete perspectiveCameraData_;
		perspectiveCameraData_ = nullptr;
	}

	const CameraData& EditorCamera::GetCameraData() const {
		if (activeCameraType_ == Type::Perspective) {
			return *perspectiveCameraData_;
		}
		else if (activeCameraType_ == Type::Isometric){
			return *isometricCameraData_;
		}
		else {
			return *orthographicCameraData_;
		}
	}

	void EditorCamera::Update(const TimeData& timeData) {
		// Switch between perspective, orthographic and isometric camera fluently:
		if (inputModule_->IsKeyPressed(Input::KeyCode::Keypad1) && activeCameraType_ != Type::Perspective) {
			if (activeCameraType_ == Type::Isometric) {
				perspectiveCameraData_->SetPosition(isometricCameraData_->GetPosition());
				perspectiveCameraData_->SetRotation(isometricCameraData_->GetRotation());
			}
			else {
				perspectiveCameraData_->SetPosition(glm::vec3(orthographicCameraData_->GetPosition().x, orthographicCameraData_->GetPosition().y, perspectiveCameraData_->GetPosition().z));
			}
			activeCameraType_ = Type::Perspective;
			cameraLayer_->ActualizeCamera();
		}
		else if (inputModule_->IsKeyPressed(Input::KeyCode::Keypad3) && activeCameraType_ != Type::Isometric) {
			if (activeCameraType_ == Type::Perspective) {
				isometricCameraData_->SetPosition(perspectiveCameraData_->GetPosition());
				isometricCameraData_->SetRotation(perspectiveCameraData_->GetRotation());
			}
			else {
				isometricCameraData_->SetPosition(glm::vec3(orthographicCameraData_->GetPosition().x, orthographicCameraData_->GetPosition().y, isometricCameraData_->GetPosition().z));
			}
			
			float camera_width = perspectiveCameraData_->GetAspectRatio();
			isometricCameraData_->SetLeft(-camera_width);
			isometricCameraData_->SetRight(camera_width);

			activeCameraType_ = Type::Isometric;
			cameraLayer_->ActualizeCamera();
		}
		else if (inputModule_->IsKeyPressed(Input::KeyCode::Keypad5) && activeCameraType_ != Type::Orthographic) {
			if (activeCameraType_ == Type::Perspective) {
				isometricCameraData_->SetPosition(perspectiveCameraData_->GetPosition());
				isometricCameraData_->SetRotation(perspectiveCameraData_->GetRotation());
			}
			else {
				perspectiveCameraData_->SetPosition(isometricCameraData_->GetPosition());
				perspectiveCameraData_->SetRotation(isometricCameraData_->GetRotation());
			}
			orthographicCameraData_->SetPosition(glm::vec3(perspectiveCameraData_->GetPosition().x, perspectiveCameraData_->GetPosition().y, orthographicCameraData_->GetPosition().z));
			orthographicCameraData_->SetZRotation(0.0f);

			float camera_width = perspectiveCameraData_->GetAspectRatio();
			orthographicCameraData_->SetLeft(-camera_width);
			orthographicCameraData_->SetRight(camera_width);

			activeCameraType_ = Type::Orthographic;
			cameraLayer_->ActualizeCamera();
		}

		// Logic for the perspective camera:
		if (activeCameraType_ == Type::Perspective) {
			// Move the camera:
			glm::vec3 translation = perspectiveCameraData_->GetPosition();
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad6)) {
				translation += perspectiveCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad4)) {
				translation -= perspectiveCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad2)) {
				translation -= perspectiveCameraData_->GetFrontVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad8)) {
				translation += perspectiveCameraData_->GetFrontVec() * (cameraSpeed_ * timeData);
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadDivide)) {
				translation -= perspectiveCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadMultiply)) {
				translation += perspectiveCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			perspectiveCameraData_->SetPosition(translation);

			// Rotate the camera:
			glm::quat currentRotation = perspectiveCameraData_->GetRotation();
			glm::quat rotationChangeY = glm::quat(1, 0, 0, 0);
			glm::quat rotationChangeX = glm::quat(1, 0, 0, 0);
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Left)) {
				rotationChangeY = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Right)) {
				rotationChangeY = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Up)) {
				rotationChangeX = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Down)) {
				rotationChangeX = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
			}
			currentRotation = rotationChangeY * currentRotation * rotationChangeX;
			perspectiveCameraData_->SetRotation(currentRotation);

			// Set FOV:
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad0)) {
				perspectiveCameraData_->SetFieldOfView(perspectiveCameraData_->GetFieldOfView() - (cameraScrollSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadDecimal)) {
				perspectiveCameraData_->SetFieldOfView(perspectiveCameraData_->GetFieldOfView() + (cameraScrollSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadEnter)) {
				perspectiveCameraData_->SetFieldOfView(45.0f);
			}
		}
		// Logic for the isometric camera:
		else if (activeCameraType_ == Type::Isometric) {
			glm::vec3 translation = isometricCameraData_->GetPosition();
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad6)) {
				translation += isometricCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad4)) {
				translation -= isometricCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad2)) {
				translation -= isometricCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad8)) {
				translation += isometricCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			isometricCameraData_->SetPosition(translation);

			// Rotate the camera:
			glm::quat currentRotation = isometricCameraData_->GetRotation();
			glm::quat rotationChangeY = glm::quat(1, 0, 0, 0);
			glm::quat rotationChangeX = glm::quat(1, 0, 0, 0);
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Left)) {
				rotationChangeY = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Right)) {
				rotationChangeY = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(0, 1, 0));
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Up)) {
				rotationChangeX = glm::angleAxis(glm::radians(cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Down)) {
				rotationChangeX = glm::angleAxis(glm::radians(-cameraRotationSpeed_ * timeData), glm::vec3(1, 0, 0));
			}
			currentRotation = rotationChangeY * currentRotation * rotationChangeX;
			isometricCameraData_->SetRotation(currentRotation);

			// Set ZoomLevel:
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad0)) {
				isometricCameraData_->SetZoomLevel(isometricCameraData_->GetZoomLevel() / (1.0f + cameraZoomSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadDecimal)) {
				isometricCameraData_->SetZoomLevel(isometricCameraData_->GetZoomLevel() * (1.0f + cameraZoomSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadEnter)) {
				isometricCameraData_->SetZoomLevel(1.0f);
			}
		}
		// Logic for the orthographic camera:
		else {
			// Move the camera:
			glm::vec3 translation = orthographicCameraData_->GetPosition();
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad6)) {
				translation += orthographicCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad4)) {
				translation -= orthographicCameraData_->GetRightVec() * (cameraSpeed_ * timeData);
			}

			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad2)) {
				translation -= orthographicCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Keypad8)) {
				translation += orthographicCameraData_->GetUpVec() * (cameraSpeed_ * timeData);
			}
			orthographicCameraData_->SetPosition(translation);

			// Rotate the camera:
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Left)) {
				orthographicCameraData_->SetZRotation(orthographicCameraData_->GetZRotation() + (cameraRotationSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Right)) {
				orthographicCameraData_->SetZRotation(orthographicCameraData_->GetZRotation() - (cameraRotationSpeed_ * timeData));
			}

			// Set ZoomLevel:
			if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Down)) {
				orthographicCameraData_->SetZoomLevel(orthographicCameraData_->GetZoomLevel() / (1.0f + cameraZoomSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::Up)) {
				orthographicCameraData_->SetZoomLevel(orthographicCameraData_->GetZoomLevel() * (1.0f + cameraZoomSpeed_ * timeData));
			}
			else if (inputModule_->IsKeyPressed(Pulse::Input::KeyCode::KeypadEnter)) {
				orthographicCameraData_->SetZoomLevel(1.0f);
			}
		}
	}

} // namespace Pulse::Layers::Camera::Editor
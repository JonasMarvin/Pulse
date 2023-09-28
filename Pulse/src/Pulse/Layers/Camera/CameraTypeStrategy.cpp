#include "pch.h"

#include "Pulse/Layers/Camera/CameraTypeStrategy.h"

namespace Pulse::Layers::Camera {

	// Perspective camera type strategy implementation:
	void PerspectiveCameraTypeStrategy::CalculateProjectionMatrix() {
		cameraData_.projectionMatrix_ = glm::perspective(glm::radians(cameraData_.fieldOfView_), cameraData_.aspectRatio_, cameraData_.nearPlane_, cameraData_.farPlane_);
	}

	void PerspectiveCameraTypeStrategy::CalculateViewMatrix() {
		cameraData_.viewMatrix_ = glm::lookAt(cameraData_.position_, cameraData_.position_ + cameraData_.frontVec_, cameraData_.upVec_);
	}

	// Orthographic camera type strategy implementation:
	void OrthographicCameraTypeStrategy::CalculateProjectionMatrix() {
		cameraData_.projectionMatrix_ = glm::ortho(cameraData_.left_ / cameraData_.zoomLevel_, cameraData_.right_ / cameraData_.zoomLevel_, cameraData_.bottom_ / cameraData_.zoomLevel_, cameraData_.top_ / cameraData_.zoomLevel_, cameraData_.nearPlane_, cameraData_.farPlane_);
	}

	void OrthographicCameraTypeStrategy::CalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), cameraData_.position_) * glm::rotate(glm::mat4(1.0f), glm::radians(cameraData_.zRotation_), glm::vec3(0.0f, 0.0f, 1.0f));
		cameraData_.viewMatrix_ = glm::inverse(transform);
	}

	// Isometric camera type strategy implementation:
	void IsometricCameraTypeStrategy::CalculateProjectionMatrix() {
		cameraData_.projectionMatrix_ = glm::ortho(cameraData_.left_ / cameraData_.zoomLevel_, cameraData_.right_ / cameraData_.zoomLevel_, cameraData_.bottom_ / cameraData_.zoomLevel_, cameraData_.top_ / cameraData_.zoomLevel_, cameraData_.nearPlane_, cameraData_.farPlane_);
	}

	void IsometricCameraTypeStrategy::CalculateViewMatrix() {
		cameraData_.viewMatrix_ = glm::lookAt(cameraData_.position_, cameraData_.position_ + cameraData_.frontVec_, cameraData_.upVec_);
	}

} // namespace Pulse::Modules::Camera
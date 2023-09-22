#include "pch.h"

#include "Pulse/Modules/Camera/CameraTypeStrategy.h"

#include "Pulse/Modules/Camera/CameraModule.h"

namespace Pulse::Modules::Camera {

	// Perspective camera type strategy implementation:
	void PerspectiveCameraTypeStrategy::CalculateProjectionMatrix() {
		camera_.projectionMatrix_ = glm::perspective(glm::radians(camera_.fieldOfView_), camera_.aspectRatio_, camera_.nearPlane_, camera_.farPlane_);
	}

	// Orthographic camera type strategy implementation:
	void OrthographicCameraTypeStrategy::CalculateProjectionMatrix() {
		float halfHeight = 1.0f / camera_.zoomLevel_;
		float halfWidth = halfHeight * camera_.aspectRatio_;
		camera_.projectionMatrix_ = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, camera_.nearPlane_, camera_.farPlane_);
	}

} // namespace Pulse::Modules::Camera
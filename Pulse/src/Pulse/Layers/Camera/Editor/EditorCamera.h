#pragma once

#include "Pulse/Layers/Camera/ICamera.h"
#include "Pulse/Modules/Input/InputModule.h"

namespace Pulse::Layers {

	class CameraLayer; // forward declaration of the camera layer class to avoid circular dependencies

} // namespace Pulse::Layers

namespace Pulse::Layers::Camera::Editor {

	// Editor camera class that supports isometric, perspective and orthographic cameras
	// Gets used by the camera layer and is updated every frame
	class EditorCamera : public ICamera {
	public:
		EditorCamera(); // constructor that sets the camera data with default values
		virtual ~EditorCamera(); // virtual destructor to allow proper cleanup of derived classes. Deletes CameraData pointers

		const CameraData& GetCameraData() const override; // function to get the active camera data

		void Update(const TimeData& timeData) override; // function to update the camera every frame

	private:
		IsometricCameraData* isometricCameraData_; // camera data of the isometric camera
		OrthographicCameraData* orthographicCameraData_; // camera data of the orthographic camera
		PerspectiveCameraData* perspectiveCameraData_; // camera data of the perspective camera
		Type activeCameraType_ = Type::Perspective; // type of the active camera

		const float cameraSpeed_ = 1.0f; // speed of the camera
		const float cameraRotationSpeed_ = 100; // rotation speed of the camera
		const float cameraScrollSpeed_ = 20.0f; // scroll speed of the camera
		const float cameraZoomSpeed_ = 1.0f; // zoom speed of the camera
		const float orthographicZPosition_ = 1.0f; // z position of the orthographic camera. Will also be used to initialize the isometric camera and perspective camera to make them look the same at the start

		Modules::InputModule* inputModule_ = nullptr; // pointer to the input module for faster acess
		CameraLayer* cameraLayer_ = nullptr; // pointer to the camera layer for faster acess

	}; // class EditorCamera

} // namespace Pulse::Layers::Camera::Editor
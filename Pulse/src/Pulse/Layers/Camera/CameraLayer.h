#pragma once

#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

#include "Pulse/Layers/IUpdatableLayer.h"
#include "Pulse/Layers/Camera/ICamera.h"
#include "Pulse/Modules/Camera/CameraModule.h"
#include "Pulse/Modules/Input/InputModule.h"

namespace Pulse::Layers {

	// This layer is used to handle different cameras in the scene by processing them to the camera module
	// and updating them respectively.
	// If your camera has multiple camera data make sure to always call ActualizeCamera() afterwards to update the camera data in the renderer module.
	class CameraLayer : public IUpdatableLayer {
	public:
		virtual ~CameraLayer() = default; // default virtual destructor for proper cleanup

		void OnAttach() override; // called when the layer is attached to the layer manager
		void OnDetach() override; // called when the layer is detached from the layer manager

		void Update(const TimeData& timeData) override; // called every frame to update the layer

		void ActualizeCamera(); // function to update the camera data in the renderer module
		void AddCamera(std::string name, Scope<Camera::ICamera> cameraData); // function to add a camera to the camera layer. By passing the cameraData here ownership of the cameraData is passed to the camera layer
		void SetActiveCamera(const std::string& name); // function to set the active camera
		void RemoveCamera(const std::string& name); // function to remove a camera from the camera layer.

		bool CameraExists(const std::string& name) const; // function to check if a camera exists in the camera layer

	private:
		std::unordered_map<std::string, Scope<Camera::ICamera>> cameraDataMap_; // map to store the camera data
		std::string activeCameraName_ = ""; // string to store the name of the active camera

		Modules::InputModule* inputModule_ = nullptr; // pointer to the input module for faster acess

	}; // class CameraLayer

} // namespace Pulse::Layers
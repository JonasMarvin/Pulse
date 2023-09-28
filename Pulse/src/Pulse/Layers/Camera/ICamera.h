#pragma once

#include "Pulse/Layers/Camera/CameraData.h"
#include "Pulse/Core/TimeData.h"

namespace Pulse::Layers::Camera {

	// Pure virtual class for cameras.
	// They need to be added to the camera layer to work.
	// Update function is called every frame to allow the camera to update itself every frame.
	// Camera data needs to be stored as Scope<CameraData> to allow for easy ownership transfer.
	class ICamera {
	public:
		virtual ~ICamera() = default; // default virtual destructor to allow proper cleanup of derived classes

		virtual const CameraData& GetCameraData() const = 0; // virtual function to get the camera data
		virtual void Update(const TimeData& timeData) = 0; // virtual function to update the camera every frame
		
	}; // class CameraBase

} // namespace Pulse
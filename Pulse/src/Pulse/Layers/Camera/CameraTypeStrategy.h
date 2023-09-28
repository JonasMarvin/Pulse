#pragma once

#include "Pulse/Layers/Camera/CameraData.h"

namespace Pulse::Layers::Camera {

	// Interface for camera type strategies
	// Gets used by the camera layer to calculate the projection matrix and the view matrix
	class ICameraTypeStrategy {
	public:
		virtual ~ICameraTypeStrategy() = default; // virtual destructor to allow proper cleanup of derived classes
		virtual void CalculateProjectionMatrix() = 0; // function to calculate the projection matrix
		virtual void CalculateViewMatrix() = 0; // function to calculate the view matrix

	}; // class ICameraTypeStrategy

	// class for calculating the projection matrix for the perspective camera type
	class PerspectiveCameraTypeStrategy : public ICameraTypeStrategy {
	public:
		PerspectiveCameraTypeStrategy(PerspectiveCameraData& cameraData) : cameraData_(cameraData) {}; // constructor to set the cameraData reference
		void CalculateProjectionMatrix() override; // function to calculate the projection matrix
		void CalculateViewMatrix() override; // function to calculate the view matrix

	private:
		PerspectiveCameraData& cameraData_; // reference to the cameraData to allow the strategy to access the data faster.

	}; // class PerspectiveCameraTypeStrategy

	// class for calculating the projection matrix for the orthographic camera type
	class OrthographicCameraTypeStrategy : public ICameraTypeStrategy {
	public:
		OrthographicCameraTypeStrategy(OrthographicCameraData& cameraData) : cameraData_(cameraData) {}; // constructor to set the cameraData reference
		void CalculateProjectionMatrix() override; // function to calculate the projection matrix
		void CalculateViewMatrix() override; // function to calculate the view matrix

	private:
		OrthographicCameraData& cameraData_; // reference to the cameraData to allow the strategy to access the data faster.

	}; // class OrthographicCameraTypeStrategy

	// class for calculating the projection matrix for the isometric camera type
	class IsometricCameraTypeStrategy : public ICameraTypeStrategy {
	public:
		IsometricCameraTypeStrategy(IsometricCameraData& cameraData) : cameraData_(cameraData) {}; // constructor to set the cameraData reference
		void CalculateProjectionMatrix() override; // function to calculate the projection matrix
		void CalculateViewMatrix() override; // function to calculate the view matrix

	private:
		IsometricCameraData& cameraData_; // reference to the cameraData to allow the strategy to access the data faster.

	}; // class IsometricCameraTypeStrategy

} // namespace Pulse::Layers::Camera
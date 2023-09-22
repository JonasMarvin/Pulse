#pragma once

namespace Pulse::Modules {

	class CameraModule; // forward declaration of the camera class

	namespace Camera{ 

		// Interface for camera type strategies
		// Gets used by the camera module to calculate the projection matrix
		class ICameraTypeStrategy {
		public:
			virtual ~ICameraTypeStrategy() = default; // virtual destructor to allow proper cleanup of derived classes

			virtual void CalculateProjectionMatrix() = 0; // function to calculate the projection matrix
		}; // class ICameraTypeStrategy

		// class for calculating the projection matrix for the perspective camera type
		class PerspectiveCameraTypeStrategy : public ICameraTypeStrategy {
		public:
			PerspectiveCameraTypeStrategy(CameraModule& camera) : camera_(camera) {}; // constructor to set the camera reference
			void CalculateProjectionMatrix() override; // function to calculate the projection matrix
		private:
			CameraModule& camera_; // reference to the camera module to allow the strategy to access the camera module
		}; // class PerspectiveCameraTypeStrategy

		// class for calculating the projection matrix for the orthographic camera type
		class OrthographicCameraTypeStrategy : public ICameraTypeStrategy {
		public:
			OrthographicCameraTypeStrategy(CameraModule& camera) : camera_(camera) {}; // constructor to set the camera reference
			void CalculateProjectionMatrix() override; // function to calculate the projection matrix
		private:
			CameraModule& camera_; // reference to the camera module to allow the strategy to access the camera module
		}; // class OrthographicCameraTypeStrategy

	} // namespace Camera
} // namespace Pulse::Modules
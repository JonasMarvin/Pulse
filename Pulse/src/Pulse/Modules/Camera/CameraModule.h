#pragma once

#include "Pulse/Modules/IModule.h"

#include <glm/gtc/quaternion.hpp>

#include "Pulse/Modules/Rendering/RendererModule.h"
#include "Pulse/Modules/Camera/CameraTypeStrategy.h"

namespace Pulse::Modules {

	// Class to represent camera logic. Each Setter will set all corresponding values and update the view matrix.
	// There is no need to set all values individually.
	// E.g SetPosition will set the position and update the view matrix / SetUp will set the up, front and right vector and update the view matrix.
	class CameraModule : public IModule {
	public:
		// Type of the camera
		enum class Type {
			None = 0,
			Orthographic,
			Perspective
		}; // enum Type

		void Initialize() override; // function to initialize the camera module
		void Shutdown() override; // function to shutdown the camera module

		// Setters
		void SetPosition(const glm::vec3& position); // function to set the position of the camera
		void SetRotation(const glm::quat& rotation); // function to set the rotation of the camera

		void SetFieldOfView(float fieldOfView); // function to set the field of view of the camera
		void SetAspectRatio(float aspectRatio); // function to set the aspect ratio of the camera
		void SetNearPlane(float nearPlane); // function to set the near plane of the camera
		void SetFarPlane(float farPlane); // function to set the far plane of the camera
		void SetZoomLevel(float zoomLevel); // function to set the zoom level of the camera

		void SetType(Type type); // function to set the type of the camera

		// Getters
		const glm::vec3& GetPosition() const; // function to get the position of the camera
		const glm::quat& GetRotation() const; // function to get the rotation of the camera

		const glm::mat4& GetViewProjectionMatrix() const; // function to get the view projection matrix of the camera

		float GetFieldOfView() const; // function to get the field of view of the camera
		float GetAspectRatio() const; // function to get the aspect ratio of the camera
		float GetNearPlane() const; // function to get the near plane of the camera
		float GetFarPlane() const; // function to get the far plane of the camera
		float GetZoomLevel() const; // function to get the zoom level of the camera

		Type GetType() const; // function to get the type of the camera

	private:
		glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f); // position of the camera
		glm::quat rotation_ = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // rotation of the camera

		glm::mat4 viewMatrix_ = glm::mat4(1.0f); // view matrix of the camera
		glm::mat4 projectionMatrix_ = glm::mat4(1.0f); // projection matrix of the camera
		glm::mat4 viewProjectionMatrix_ = glm::mat4(1.0f); // view projection matrix of the camera

		float fieldOfView_ = 45.0f; // field of view of the camera in degree
		float aspectRatio_ = 1.0f; // aspect ratio of the camera
		float nearPlane_ = 0.1f; // near plane of the camera
		float farPlane_ = 100.0f; // far plane of the camera
		float zoomLevel_ = 1.0f; // zoom level of the camera
		
		Type type_ = Type::None; // type of the camera
		Camera::ICameraTypeStrategy *cameraTypeStrategy_ = nullptr; // pointer to the camera type strategy to allow the camera module to calculate the projection matrix

		RendererModule* renderer_ = nullptr; // pointer to the renderer module to allow the camera module to access the renderer module faster

		void CalculateViewMatrix(); // function to calculate the view matrix of the camera
		void CalculateProjectionMatrix(); // function to calculate the projection matrix of the camera
		void CalculateViewProjectionMatrix(); // function to calculate the projection matrix of the camera

		CameraModule() = default; // default constructor private to prevent creation of the camera module outside of the module manager
		~CameraModule() = default; // default destructor private to prevent deletion of the camera module outside of the module manager

		friend class Camera::OrthographicCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module
		friend class Camera::PerspectiveCameraTypeStrategy; // friend class to allow the camera type strategies to access the camera module for faster access to the camera module
		friend class ModuleManager; // friend class to allow the module manager to create and manage the camera module
	}; // class Camera

} // namespace Pulse::Modules
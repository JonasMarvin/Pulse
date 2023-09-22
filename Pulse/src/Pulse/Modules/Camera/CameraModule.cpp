#include "pch.h"

#include "Pulse/Modules/Camera/CameraModule.h"

#include <glm/glm.hpp>

#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Modules {

	void CameraModule::Initialize() {
		renderer_ = ModuleManager::GetInstance().GetModule<RendererModule>();
		renderer_->SetViewProjectionMatrixReference(&viewProjectionMatrix_);
		SetType(Type::Orthographic); // TODO: Make this configurable
	}

	void CameraModule::Shutdown() {
		renderer_->ResetViewProjectionMatrixReference();
		delete(cameraTypeStrategy_);
		cameraTypeStrategy_ = nullptr;
	}

	// Setters:
	void CameraModule::SetPosition(const glm::vec3& position) {
		position_ = position;
		CalculateViewMatrix();
	}

	void CameraModule::SetRotation(const glm::quat& rotation) {
		rotation_ = rotation;
		CalculateViewMatrix();
	}

	void CameraModule::SetFieldOfView(float fieldOfView) {
		fieldOfView_ = fieldOfView;
		CalculateProjectionMatrix();
	}

	void CameraModule::SetAspectRatio(float aspectRatio) {
		aspectRatio_ = aspectRatio;
		CalculateProjectionMatrix();
	}

	void CameraModule::SetNearPlane(float nearPlane) {
		nearPlane_ = nearPlane;
		CalculateProjectionMatrix();
	}

	void CameraModule::SetFarPlane(float farPlane) {
		farPlane_ = farPlane;
		CalculateProjectionMatrix();
	}

	void CameraModule::SetZoomLevel(float zoomLevel) {
		zoomLevel_ = zoomLevel;
		CalculateProjectionMatrix();
	}

	void CameraModule::SetType(Type type) {
		if (type == type_) return;

		type_ = type;
		delete(cameraTypeStrategy_);
		switch (type_) {
			case Type::None:
				renderer_->ResetViewProjectionMatrixReference();
				delete(cameraTypeStrategy_);
				cameraTypeStrategy_ = nullptr;
				break;
			case Type::Perspective:
				cameraTypeStrategy_ = new Camera::PerspectiveCameraTypeStrategy(*this);
				break;
			case Type::Orthographic:
				cameraTypeStrategy_ = new Camera::OrthographicCameraTypeStrategy(*this);
				break;
		}
		CalculateProjectionMatrix();
	}

	// Getters:
	const glm::vec3& CameraModule::GetPosition() const {
		return position_;
	}

	const glm::quat& CameraModule::GetRotation() const {
		return rotation_;
	}

	const glm::vec3& CameraModule::GetUp() const {
		return up_;
	}

	const glm::vec3& CameraModule::GetFront() const {
		return front_;
	}

	const glm::vec3& CameraModule::GetRight() const {
		return right_;
	}

	float CameraModule::GetFieldOfView() const {
		return fieldOfView_;
	}

	float CameraModule::GetAspectRatio() const {
		return aspectRatio_;
	}

	float CameraModule::GetNearPlane() const {
		return nearPlane_;
	}

	float CameraModule::GetFarPlane() const {
		return farPlane_;
	}

	float CameraModule::GetZoomLevel() const {
		return zoomLevel_;
	}

	const glm::mat4& CameraModule::GetViewProjectionMatrix() const {
		return viewProjectionMatrix_;
	}

	CameraModule::Type CameraModule::GetType() const {
		return type_;
	}

	void CameraModule::CalculateViewMatrix() {
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), position_);
		glm::mat4 rotation = glm::mat4_cast(rotation_);
		up_ = glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
		front_ = glm::normalize(glm::vec3(rotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
		right_ = glm::normalize(glm::vec3(rotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
		viewMatrix_ = translation * rotation;
		viewMatrix_ = glm::inverse(viewMatrix_);
		CalculateViewProjectionMatrix();
	}

	void CameraModule::CalculateProjectionMatrix() {
		if (cameraTypeStrategy_ != nullptr) {
			cameraTypeStrategy_->CalculateProjectionMatrix();
			CalculateViewProjectionMatrix();
			return;
		}
		PLS_CORE_ASSERT(false, "The Type of the camera module has to be set before the ProjectionMatrix can be calculated!");
	}

	void CameraModule::CalculateViewProjectionMatrix() {
		viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
	}

} // namespace Pulse::Modules
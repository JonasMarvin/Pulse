#include "pch.h"

#include "Pulse/Modules/Camera/Camera.h"

#include <glm/glm.hpp>

#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Modules {

	void Camera::Initialize() {
		renderer_ = ModuleManager::GetInstance().GetModule<Renderer>();
		renderer_->SetViewProjectionMatrixReference(&viewProjectionMatrix_);
	}

	void Camera::Shutdown() {
		renderer_->ResetViewProjectionMatrixReference();
	}

	// Setters:
	void Camera::SetPosition(const glm::vec3& position) {

	}

	void Camera::SetRotation(const glm::vec3& rotation) {

	}

	void Camera::SetUp(const glm::vec3& up) {

	}

	void Camera::SetFront(const glm::vec3& front) {

	}

	void Camera::SetRight(const glm::vec3& right) {

	}

	void Camera::SetViewMatrix(const glm::mat4& viewMatrix) {

	}

	void Camera::SetProjectionMatrix(const glm::mat4& projectionMatrix) {

	}

	void Camera::SetFieldOfView(float fieldOfView) {

	}

	void Camera::SetAspectRatio(float aspectRatio) {

	}

	void Camera::SetNearPlane(float nearPlane) {

	}

	void Camera::SetFarPlane(float farPlane) {

	}

	void Camera::SetZoomLevel(float zoomLevel) {

	}

	void Camera::SetType(Type type) {

	}

	// Getters:
	const glm::vec3& Camera::GetPosition() const {
		return position_;
	}

	const glm::vec3& Camera::GetRotation() const {
		return rotation_;
	}

	const glm::vec3& Camera::GetUp() const {
		return up_;
	}

	const glm::vec3& Camera::GetFront() const {
		return front_;
	}

	const glm::vec3& Camera::GetRight() const {
		return right_;
	}

	const glm::mat4& Camera::GetViewMatrix() const {
		return viewMatrix_;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const {
		return projectionMatrix_;
	}

	float Camera::GetFieldOfView() const {
		return fieldOfView_;
	}

	float Camera::GetAspectRatio() const {
		return aspectRatio_;
	}

	float Camera::GetNearPlane() const {
		return nearPlane_;
	}

	float Camera::GetFarPlane() const {
		return farPlane_;
	}

	float Camera::GetZoomLevel() const {
		return zoomLevel_;
	}

	const glm::mat4 Camera::GetViewProjectionMatrix() const {
		return viewProjectionMatrix_;
	}

	Camera::Type Camera::GetType() const {
		return type_;
	}

} // namespace Pulse::Modules
#include "pch.h"

#include "Pulse/Layers/Camera/CameraData.h"

#include "Pulse/Layers/Camera/CameraTypeStrategy.h"

namespace Pulse::Layers::Camera {

	// Camera base implementation:
	CameraData::CameraData(Type cameraType, ICameraTypeStrategy* iCameraTypeStrategy, float nearPlane, float farPlane, const glm::vec3& position)
		: cameraType_(cameraType), iCameraTypeStrategy_(iCameraTypeStrategy), nearPlane_(nearPlane), farPlane_(farPlane), position_(position) {}

	CameraData::~CameraData() {
		delete(iCameraTypeStrategy_);
		iCameraTypeStrategy_ = nullptr;
	}

	Type CameraData::GetCameraType() const {
		return Type();
	}

	float CameraData::GetNearPlane() const {
		return nearPlane_;
	}

	float CameraData::GetFarPlane() const {
		return farPlane_;
	}

	const glm::vec3& CameraData::GetPosition() const {
		return position_;
	}

	const glm::mat4& CameraData::GetViewMatrix() const {
		return viewMatrix_;
	}

	const glm::mat4& CameraData::GetProjectionMatrix() const {
		return projectionMatrix_;
	}

	const glm::mat4& CameraData::GetViewProjectionMatrix() const {
		return viewProjectionMatrix_;
	}

	void CameraData::SetNearPlane(float value) {
		nearPlane_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void CameraData::SetFarPlane(float value) {
		farPlane_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void CameraData::SetPosition(const glm::vec3& value) {
		position_ = value;
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void CameraData::RecalculateViewMatrix() {
		iCameraTypeStrategy_->CalculateViewMatrix();
	}

	void CameraData::RecalculateProjectionMatrix() {
		iCameraTypeStrategy_->CalculateProjectionMatrix();
	}

	void CameraData::RecalculateViewProjectionMatrix() {
		viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
	}

	// Perspective Camera implementation:
	PerspectiveCameraData::PerspectiveCameraData(const glm::vec3& position, const glm::quat& rotation,
		float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
		: CameraData(Type::Perspective, new PerspectiveCameraTypeStrategy(*this), nearPlane, farPlane, position),
		fieldOfView_(fieldOfView), aspectRatio_(aspectRatio), rotation_(rotation)
	{
		RecalculateProjectionMatrix();
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	float PerspectiveCameraData::GetFieldOfView() const {
		return fieldOfView_;
	}

	float PerspectiveCameraData::GetAspectRatio() const {
		return aspectRatio_;
	}

	const glm::vec3& PerspectiveCameraData::GetFrontVec() const {
		return frontVec_;
	}

	const glm::vec3& PerspectiveCameraData::GetUpVec() const {
		return upVec_;
	}

	const glm::vec3& PerspectiveCameraData::GetRightVec() const {
		return rightVec_;
	}

	const glm::quat& PerspectiveCameraData::GetRotation() const {
		return rotation_;
	}

	void PerspectiveCameraData::SetFieldOfView(float value) {
		// Avoid invalid field of view values leading to matrix inversion:
		if (value < minFieldOfView_ || value > maxFieldOfView_) {
			return;
		}
		fieldOfView_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void PerspectiveCameraData::SetAspectRatio(float value) {
		aspectRatio_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void PerspectiveCameraData::SetFrontVec(const glm::vec3& value) {
		frontVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(frontVec_, upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void PerspectiveCameraData::SetUpVec(const glm::vec3& value) {
		upVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(frontVec_, upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void PerspectiveCameraData::SetRightVec(const glm::vec3& value) {
		rightVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(glm::cross(upVec_, rightVec_), upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void PerspectiveCameraData::SetRotation(const glm::quat& value) {
		rotation_ = value;
		upVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
		frontVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
		rightVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	// Orthographic Camera implementation:
	OrthographicCameraData::OrthographicCameraData(const glm::vec3& position, float zRotation, float left, float right, float bottom, float top,
		float nearPlane, float farPlane, float zoomLevel)
		: CameraData(Type::Orthographic, new OrthographicCameraTypeStrategy(*this), nearPlane, farPlane, position),
		zoomLevel_(zoomLevel), left_(left), right_(right), bottom_(bottom), top_(top), zRotation_(zRotation)
	{
		RecalculateProjectionMatrix();
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	float OrthographicCameraData::GetLeft() const {
		return left_;
	}

	float OrthographicCameraData::GetRight() const {
		return right_;
	}

	float OrthographicCameraData::GetBottom() const {
		return bottom_;
	}

	float OrthographicCameraData::GetTop() const {
		return top_;
	}

	const glm::vec3& OrthographicCameraData::GetUpVec() const {
		return upVec_;
	}

	const glm::vec3& OrthographicCameraData::GetRightVec() const {
		return rightVec_;
	}

	float OrthographicCameraData::GetZRotation() const {
		return zRotation_;
	}

	float OrthographicCameraData::GetZoomLevel() const {
		return zoomLevel_;
	}

	void OrthographicCameraData::SetLeft(float value) {
		left_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetRight(float value) {
		right_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetBottom(float value) {
		bottom_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetTop(float value) {
		top_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetUpVec(const glm::vec3& value) {
		upVec_ = glm::normalize(value);
		zRotation_ = glm::degrees(atan2f(-upVec_.x, upVec_.y));
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetRightVec(const glm::vec3& value) {
		rightVec_ = glm::normalize(value);
		zRotation_ = glm::degrees(atan2f(rightVec_.y, rightVec_.x));
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetZRotation(float value) {
		zRotation_ = value;
		float radians = glm::radians(zRotation_);
		upVec_ = glm::normalize(glm::vec3(-sinf(radians), cosf(radians), 0.0f));
		rightVec_ = glm::normalize(glm::vec3(cosf(radians), sinf(radians), 0.0f));
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCameraData::SetZoomLevel(float value) {
		if (value < minZoomLevel_ || value > maxZoomLevel_) {
			return;
		}
		zoomLevel_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	// Isometric Camera implementation:
	IsometricCameraData::IsometricCameraData(const glm::vec3& position, const glm::quat& rotation,
		float left, float right, float bottom, float top,
		float nearPlane, float farPlane, float zoomLevel)
		: CameraData(Type::Isometric, new IsometricCameraTypeStrategy(*this), nearPlane, farPlane, position),
		zoomLevel_(zoomLevel), left_(left), right_(right), bottom_(bottom), top_(top), rotation_(rotation)
	{
		RecalculateProjectionMatrix();
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	float IsometricCameraData::GetLeft() const {
		return left_;
	}

	float IsometricCameraData::GetRight() const {
		return right_;
	}

	float IsometricCameraData::GetBottom() const {
		return bottom_;
	}

	float IsometricCameraData::GetTop() const {
		return top_;
	}

	const glm::vec3& IsometricCameraData::GetFrontVec() const {
		return frontVec_;
	}

	const glm::vec3& IsometricCameraData::GetUpVec() const {
		return upVec_;
	}

	const glm::vec3& IsometricCameraData::GetRightVec() const {
		return rightVec_;
	}

	const glm::quat& IsometricCameraData::GetRotation() const {
		return rotation_;
	}

	float IsometricCameraData::GetZoomLevel() const {
		return zoomLevel_;
	}

	void IsometricCameraData::SetLeft(float value) {
		left_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetRight(float value) {
		right_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetBottom(float value) {
		bottom_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetTop(float value) {
		top_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetUpVec(const glm::vec3& value) {
		upVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(frontVec_, upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetFrontVec(const glm::vec3& value) {
		frontVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(frontVec_, upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetRightVec(const glm::vec3& value) {
		rightVec_ = glm::normalize(value);
		rotation_ = glm::quatLookAt(glm::cross(upVec_, rightVec_), upVec_);
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetRotation(const glm::quat& value) {
		rotation_ = value;
		upVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
		frontVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
		rightVec_ = glm::normalize(glm::vec3(rotation_ * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
		RecalculateViewMatrix();
		RecalculateViewProjectionMatrix();
	}

	void IsometricCameraData::SetZoomLevel(float value) {
		if (value < 0.001f || 0.001f > maxZoomLevel_) {
			return;
		}
		PLS_CORE_INFO("Zoom level: {0}", value);
		zoomLevel_ = value;
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

} // namespace Pulse::Layers::Camera
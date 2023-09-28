#include "pch.h"

#include "Pulse/Layers/Camera/CameraLayer.h"

#include "Pulse/Layers/Camera/Editor/EditorCamera.h"
#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Layers {

	void CameraLayer::OnAttach() {
		inputModule_ = Modules::ModuleManager::GetInstance().GetModule<Modules::InputModule>();
		AddCamera("EditorCamera", CreateScope<Camera::Editor::EditorCamera>());
		SetActiveCamera("EditorCamera");
	}

	void CameraLayer::OnDetach() {
		Modules::ModuleManager::GetInstance().GetModule<Modules::CameraModule>()->ResetViewProjectionMatrixReference();
	}

	void CameraLayer::Update(const TimeData& timeData) {
		if (activeCameraName_ != "") {
			cameraDataMap_[activeCameraName_]->Update(timeData);
		}
	}

	void CameraLayer::ActualizeCamera() {
		if (cameraDataMap_.size() > 0) {
			Modules::ModuleManager::GetInstance().GetModule<Modules::CameraModule>()->SetViewProjectionMatrixReference(&cameraDataMap_[activeCameraName_]->GetCameraData().GetViewProjectionMatrix());
			return;
		}
		PLS_CORE_WARN("No camera found!");
	}

	void CameraLayer::AddCamera(std::string name, Scope<Camera::ICamera> cameraData) {
		cameraDataMap_[name] = std::move(cameraData);
		PLS_CORE_INFO("Camera with name {0} added to the camera layer!", name);
	}

	void CameraLayer::SetActiveCamera(const std::string& name) {
		if (CameraExists(name)) {
			if (activeCameraName_ == name) {
				return;
			}
			activeCameraName_ = name;
			ActualizeCamera();
			PLS_CORE_INFO("Camera with name {0} is now active!", name);
			return;
		}
		PLS_CORE_WARN("Camera with name {0} does not exist!", name);
	}

	void CameraLayer::RemoveCamera(const std::string& name) {
		if (!CameraExists(name)) {
			PLS_CORE_WARN("Camera with name {0} does not exist!", name);
			return;
		}
		cameraDataMap_.erase(name);
		if (activeCameraName_ == name) {
			if (cameraDataMap_.size() > 0) {
				SetActiveCamera(cameraDataMap_.begin()->first);
				PLS_CORE_WARN("Active camera with name {0} removed! New active camera is {1}", name, activeCameraName_);
				return;
			}
			PLS_CORE_ERROR("Active camera with name {0} removed! No other Camera found.", name);
			return;
		}
		
	}

	bool CameraLayer::CameraExists(const std::string& name) const {
		return cameraDataMap_.find(name) != cameraDataMap_.end();
	}

}; // namespace Pulse::Layers
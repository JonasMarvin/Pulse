#include "pch.h"

#include "Pulse/Modules/Camera/CameraModule.h"

#include "Pulse/Modules/ModuleManager.h"

namespace Pulse::Modules {

	void CameraModule::Initialize() {
		renderer_ = ModuleManager::GetInstance().GetModule<RendererModule>();
		renderer_->SetViewProjectionMatrixReference(&defaultViewProjectionMatrix_);
	}

	void CameraModule::Shutdown() {
		renderer_->ResetViewProjectionMatrixReference();
		ResetViewProjectionMatrixReference();
	}

	void CameraModule::SetViewProjectionMatrixReference(const glm::mat4* viewProjectionMatrix) {
		viewProjectionMatrix_ = viewProjectionMatrix;
		renderer_->SetViewProjectionMatrixReference(viewProjectionMatrix_);
	}

	void CameraModule::ResetViewProjectionMatrixReference() {
		viewProjectionMatrix_ = nullptr;
		renderer_->ResetViewProjectionMatrixReference();
	}

} // namespace Pulse::Modules
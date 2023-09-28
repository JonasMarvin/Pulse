#pragma once

#include "Pulse/Modules/IModule.h"

#include <glm/glm.hpp>

#include "Pulse/Modules/Rendering/RendererModule.h"

namespace Pulse::Modules {

	// class to build a connection between cameras and the renderer.
	// Right now its not doing much, but it will be used to allow complex camera setups in the future.
	// Its just connecting the active camera view projection matrix to the renderer.
	class CameraModule : public IModule {
	public:
		void Initialize() override; // function to initialize the camera module
		void Shutdown() override; // function to shutdown the camera module

		void SetViewProjectionMatrixReference(const glm::mat4* viewProjectionMatrix);
		void ResetViewProjectionMatrixReference();

	private:
		RendererModule* renderer_ = nullptr; // pointer to the renderer module to allow the camera module to access the renderer module faster
		const glm::mat4* viewProjectionMatrix_ = nullptr; // pointer to the view projection matrix to allow the camera module to access the view projection matrix faster
		const glm::mat4 defaultViewProjectionMatrix_ = glm::mat4(1.0f); // default view projection matrix to allow the camera module to reset the view projection matrix to the default matrix

		CameraModule() = default; // default constructor private to prevent creation of the camera module outside of the module manager
		~CameraModule() = default; // default destructor private to prevent deletion of the camera module outside of the module manager
		
		friend class ModuleManager; // friend class to allow the module manager to create and manage the camera module
	}; // class CameraModule

} // namespace Pulse::Modules
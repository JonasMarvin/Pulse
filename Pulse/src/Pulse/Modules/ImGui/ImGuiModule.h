#pragma once

#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {

	class PLS_API ImGuiModule : public IModule {
	public:
		void Initialize() override; // function to initialize the module
		void Shutdown() override; // function to shutdown the module
		void Update() override; // function to update the module

	private:
		ImGuiModule() = default; // private constructor to prevent creation of the module outside of the module manager
		~ImGuiModule() = default; // private destructor to prevent deletion of the module outside of the module manager

		float time_ = 0.0f; // time since the module was last updated

		friend class ModuleManager; // friend class to allow the module manager to create and manage the window
	}; // class ImGui

} // namespace Pulse::Modules
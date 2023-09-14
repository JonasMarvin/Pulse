#pragma once

#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {

	class PLS_API Input : public IModule {
	public:
		void Update() override = 0; // Virtual function to handle update of the input
		void Initialize() override = 0; // Virtual function to handle initialization of the input.
		void Shutdown() override = 0; // Virtual function to handle shutdown of the input.

	protected:
		Input() = default; // Default constructor is protected to only allow module manager to create it.
		virtual ~Input() = default; // Default destructor is protected to only allow module manager to destroy it.

		friend class ModuleManager; // Module manager is a friend to allow it to create and destroy modules.
	}; // class Input

} // namespace Pulse::Modules
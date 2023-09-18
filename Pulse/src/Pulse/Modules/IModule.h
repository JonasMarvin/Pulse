#pragma once

#include "Pulse/Core/Core.h"

namespace Pulse::Modules {
	
	// Base Interface for modules that can be registered with the module manager.
	// You can use the constructor and destructor in derived classes. Use Initialize and Shutdown preferably.
	// Addtionally the actual module class should have the constructor and destructor private and befriended with the module manager to prevent direct instantiation.
	class IModule {
	public:
		IModule(const IModule&) = delete; // Copy constructor deleted as we don't want to copy modules
		IModule& operator=(const IModule&) = delete; // Copy assignment operator deleted as we don't want to copy modules
		IModule(IModule&&) = delete; // Move constructor deleted as we don't want to move modules
		IModule& operator=(IModule&&) = delete; // Move assignment operator deleted as we don't want to move modules

		virtual void Initialize() = 0; // Pure virtual function gets called by the module manager when the module is registered
		virtual void Shutdown() = 0; // Pure virtual function gets called by the module manager when the module is unregistered
	
	protected:
		IModule() = default; // Default constructor is protected as modules should only be created by the module manager
		virtual ~IModule() = default; // Default destructor is protected as modules should only be destroyed by the module manager

		friend class ModuleManager; // The module manager is befriended with the module to allow it to call the Initialize, Update and Shutdown functions
	}; // class IModule

} // namespace Pulse::Modules
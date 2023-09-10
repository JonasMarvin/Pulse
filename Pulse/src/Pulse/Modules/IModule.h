#pragma once

namespace Pulse::Modules {
	
	// Interface for modules that can be registered with the module manager.
	// You can use the constructor in dervied classes but its recommended to use the overriden Initialize function instead.
	class IModule {
	public:
		IModule(const IModule&) = delete; // Copy constructor deleted as we don't want to copy modules
		IModule& operator=(const IModule&) = delete; // Copy assignment operator deleted as we don't want to copy modules
		IModule(IModule&&) = delete; // Move constructor deleted as we don't want to move modules
		IModule& operator=(IModule&&) = delete; // Move assignment operator deleted as we don't want to move modules

		virtual void Initialize() = 0; // Pure virtual function gets called by the module manager when the module is registered
		virtual void Update() = 0; // Pure virtual function gets called by the module manager every frame
		virtual void Shutdown() = 0; // Pure virtual function gets called by the module manager when the module is unregistered
	
	private:
		IModule() = default; // Default constructor is private as modules should only be created by the module manager
		virtual ~IModule() = default; // Default destructor is private as modules should only be destroyed by the module manager

		friend class ModuleManager; // Module manager is a friend class so it can call the private constructor and destructor

	}; // class IModule

} // namespace Pulse::Modules
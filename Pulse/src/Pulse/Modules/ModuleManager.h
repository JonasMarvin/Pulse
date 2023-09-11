#pragma once

#include <memory>
#include <vector>
#include <typeindex>

#include "Pulse/Modules/IModule.h"
#include "Pulse/Core/Logging/Log.h"

namespace Pulse::Modules {

	// Singleton class that manages all modules as pointers
	// Setup happens in Application.
	class ModuleManager {
	public:
		ModuleManager(const ModuleManager&) = delete; // Delete copy constructor because singleton
		ModuleManager(ModuleManager&&) = delete; // Delete move constructor because singleton
		ModuleManager& operator=(const ModuleManager&) = delete; // Delete copy assignment operator because singleton
		ModuleManager& operator=(ModuleManager&&) = delete; // Delete move assignment operator because singleton

		static ModuleManager& GetInstance(); // Singleton instance getter

		// Registers a module to the module manager and initializes it by calling the modules Initialize() function
		template <typename T>
		void RegisterModule();

		// Returns a module of type T if it exists, otherwise returns nullptr
		template <typename T>
		T* GetModule();

		// Updates all modules by calling the modules Update() function. Gets called in Application::Run()
		void UpdateModules();

		// Shuts down a module of type T by calling the modules Shutdown() function and removes it from the module manager
		template <typename T>
		void UnregisterModule();

		// Shuts down all modules by calling the modules Shutdown() function and removes them from the module manager. Gets called before the Application shuts down
		void ShutdownModules();

	private:
		ModuleManager(); // Private constructor for singleton
		~ModuleManager() = default; // Private destructor for singleton

		std::vector<IModule*> modules_; // Vector of active modules safed as pointers
		std::unordered_map<std::type_index, IModule*> modulesMap_; // Map of active modules safed as pointers
	}; // class ModuleManager

} // namespace Pulse::Modules

#include "Pulse/Modules/ModuleManager.tpp"
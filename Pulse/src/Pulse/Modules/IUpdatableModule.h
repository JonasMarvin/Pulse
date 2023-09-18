#pragma once

#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {
    
    // Interface for modules that need to be updated every frame
    class PLS_API IUpdatableModule : public virtual IModule {
    public:
        IUpdatableModule(const IUpdatableModule&) = delete; // Copy constructor deleted as we don't want to copy modules
        IUpdatableModule& operator=(const IUpdatableModule&) = delete;  // Copy assignment operator deleted as we don't want to copy modules
        IUpdatableModule(IUpdatableModule&&) = delete; // Move constructor deleted as we don't want to move modules
        IUpdatableModule& operator=(IUpdatableModule&&) = delete; // Move assignment operator deleted as we don't want to move modules

        virtual void Update() = 0;  // Pure virtual function gets called by the module manager every frame after rendering

    protected:
        IUpdatableModule() = default; // Default constructor is protected as modules should only be created by the module manager
        virtual ~IUpdatableModule() = default; // Default destructor is protected as modules should only be destroyed by the module manager

        friend class ModuleManager; // The module manager is befriended with the module to allow it to call the Initialize, Update and Shutdown functions
    }; // class IUpdatableModule

} // namespace Pulse::Modules
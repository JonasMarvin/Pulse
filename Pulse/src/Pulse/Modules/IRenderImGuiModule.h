#pragma once

#include "Pulse/Modules/IModule.h"

namespace Pulse::Modules {

    // Interface for modules that need to be renderered with ImGui every frame
    class IRenderImGuiModule : public virtual IModule {
    public:
        IRenderImGuiModule(const IRenderImGuiModule&) = delete; // Copy constructor deleted as we don't want to copy modules
        IRenderImGuiModule& operator=(const IRenderImGuiModule&) = delete; // Copy assignment operator deleted as we don't want to copy modules
        IRenderImGuiModule(IRenderImGuiModule&&) = delete; // Move constructor deleted as we don't want to move modules
        IRenderImGuiModule& operator=(IRenderImGuiModule&&) = delete; // Move assignment operator deleted as we don't want to move modules

        virtual void RenderImGui() = 0;  // Pure virtual function gets called by the module manager every frame after rendering

    protected:
        IRenderImGuiModule() = default; // Default constructor is protected as modules should only be created by the module manager
        virtual ~IRenderImGuiModule() = default; // Default destructor is protected as modules should only be destroyed by the module manager

        friend class ModuleManager; // The module manager is befriended with the module to allow it to call the Initialize, Update and Shutdown functions
    }; // class IUpdatableModule

} // namespace Pulse::Modules
#pragma once

#include <string>

#include "Pulse/Modules/IUpdatableModule.h"

namespace Pulse::Modules {

	// Interface representing a desktop system based Window
	// Its a module that has to be managed by the module manager. Dont create it directly and use the ModuleManager to create it.
	// This interface will be implemented by platform specific window classes.
	class WindowModule : public IUpdatableModule {
	public:
		virtual unsigned int GetWidth() const = 0; // Virtual function to get the width of the window.
		virtual unsigned int GetHeight() const = 0; // Virtual function to get the height of the window.

		virtual void SetVSync(bool enabled) = 0; // Virtual function to set the vsync of the window.
		virtual bool IsVSync() const = 0; // Virtual function to get the vsync of the window.
		virtual void* GetNativeWindow() const = 0; // Virtual function to get the native window of the window.

	protected:
		WindowModule() = default; // Default constructor protected so that it can only be created by the module manager.
		virtual ~WindowModule() = default; // Default destructor protected so that it can only be deleted by the module manager.

		friend class ModuleManager; // The module manager is befriended with the module to allow it to call the Initialize, Update and Shutdown functions
	};

} // namespace Pulse::Modules
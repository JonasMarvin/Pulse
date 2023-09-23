#pragma once

#include "Pulse/Modules/Window/WindowModule.h"

#include <GLFW/glfw3.h>

namespace Pulse::Modules::Windows {

	// Class for a Windows window
	// Its a module and should only be created and managed by the module manager
	class WindowsWindowModuleImpl : public WindowModule {
	public:
		void Initialize() override; // function to initialize the window
		void Update() override; // function to handle the update event of the window
		void Shutdown() override; // function to shutdown the window

		unsigned int GetWidth() const override; // function to get the width of the window
		unsigned int GetHeight() const override; // function to get the height of the window

		// Window attributes
		void SetVSync(bool enabled) override; // function to set the vsync of the window
		bool IsVSync() const override; // function to get the vsync of the window

		void* GetNativeWindow() const override; // function to get the native window

	private:
		WindowsWindowModuleImpl() : window_(nullptr) {}; // default constructor private to prevent creation of the window outside of the module manager
		~WindowsWindowModuleImpl() = default; // default destructor private to prevent deletion of the window outside of the module manager

		GLFWwindow* window_ = nullptr; // pointer to the GLFW window

		struct WindowData { // struct to store the window data
			std::string title = "Pulse"; // title of the window
			unsigned int width = 1920; // width of the window
			unsigned int height = 1080; // height of the window
			bool vsync = false; // vsync of the window
			WindowData()
				: title("Pulse"), width(1920), height(1080), vsync(false) {} // default constructor
		} data_; // window data

		friend class ModuleManager; // friend class to allow the module manager to create and manage the window

	}; // class WindowsWindowModuleImpl

} // namespace Pulse
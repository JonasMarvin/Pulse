#pragma once

#include "Pulse/Modules/IModule.h"
#include "Pulse/Modules/ImGui/OpenGL/ImGuiOpenGLRenderer.h"
#include "Pulse/Modules/Window/Platform/Windows/WindowsWindow.h"
#include "Pulse/Events/Events.h"

namespace Pulse::Modules {

	// class to manage the imgui functionality
	class PLS_API ImGuiModule : public IModule {
	public:
		// This class is used by ImGuiModule to listen to events with a proper lifetime management
		class PLS_API ImGuiModuleEventListener : public Pulse::Events::IEventListener<ImGuiModuleEventListener> {
		public:
			ImGuiModuleEventListener(ImGuiModule& parent, ImGuiIO& imGuiIO); // Constructor to add the event listener to the events
			~ImGuiModuleEventListener() override = default; // Destructor to remove the event listener from the events

			void OnMouseMoved(double xOffset, double yOffset);
			void OnMouseScrolled(double xOffset, double yOffset);
			void OnMouseButton(int button, int action, int mods);
			void OnKey(int key, int scancode, int action, int mods);
			void OnChar(unsigned int character);
			void OnWindowResize(int width, int height);
		private:
			ImGuiModule& parent_; // reference to the parent 
			ImGuiIO& imGuiIO_; // reference to the ImGui IO object to allow faster access to the ImGui IO object
		}; // class ImGuiModuleEventListener

		void Initialize() override; // function to initialize the module
		void Shutdown() override; // function to shutdown the module
		void Update() override; // function to update the module

	private:
		ImGuiModule() : window_(nullptr), imGuiIO_(nullptr) {}// private constructor to prevent creation of the module outside of the module manager
		~ImGuiModule() = default; // private destructor to prevent deletion of the module outside of the module manager

		std::shared_ptr<ImGuiModuleEventListener> imGuiModuleEventListener_; // pointer to the event listener
		Pulse::Modules::Windows::WindowsWindow* window_; // pointer to the window object
		ImGuiIO* imGuiIO_; // pointer to the ImGui IO object to allow faster access to the ImGui IO object
		float time_ = 0.0f; // time since the module was last updated

		friend class ModuleManager; // friend class to allow the module manager to create and manage the window
	}; // class ImGui

} // namespace Pulse::Modules
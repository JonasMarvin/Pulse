#pragma once

#include "Pulse/Core/Core.h"
#include "Pulse/Core/Window.h"
#include "Pulse/Events/Events.h"
#include "Pulse/Modules/ModuleManager.h"

namespace Pulse
{
	// This is the base class for all Pulse applications.
	class PLS_API Application {
	public:
		// This internal class is used by Application to allow proper lifetime managements by listeners of the application. Dont use this at all except in the application class it is not meant to be used outside of it.
		class PLS_API ApplicationEventListener : public Events::IEventListener<ApplicationEventListener> {
		public:
			ApplicationEventListener(Application& application); // Constructor to add the event listeners to the events.
			virtual ~ApplicationEventListener() override = default; // Virtual destructor to allow deletion of the derived class.
			void OnWindowClose(); // Function to be called when the window is closed.

		private:
			Application& parentApplication_; // Reference to the parent application to be able to access the private members of the application.
		};

		Application(); // Constructor
		virtual ~Application(); // Virtual destructor for proper cleanup

		void Run(); // Main loop of the application

	private:
		std::shared_ptr<ApplicationEventListener> applicationEventListener_; // Shared pointer to the application event listener to allow lifetime management of the application by the event system
		Pulse::Modules::ModuleManager& moduleManager_; // Module manager to manage all the modules of the application
		std::unique_ptr<Window> window_; // Unique pointer to the window of the application
		bool isRunning_ = true; // Boolean to check if the application is running
	};

	Application* CreateApplication(); // To be defined in CLIENT

} // namespace Pulse
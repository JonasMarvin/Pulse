#pragma once

#include "Pulse/Core/Core.h"
#include "Pulse/Events/Events.h"
#include "Pulse/Layers/IImGuiRenderableLayer.h"
#include "Pulse/Layers/IRenderableLayer.h"
#include "Pulse/Layers/IUpdatableLayer.h"

namespace Pulse::Layers {

	// This is the base class for all Pulse applications and a layer. Can not be used as a layer directly due to pure virtual functions. Use the CLIENT class instead.
	class Application : public IUpdatableLayer, public IRenderableLayer, public IImGuiRenderableLayer{
	public:
		Application() = default; // Default constructor
		virtual ~Application() = default; // default virtual destructor for proper cleanup

		void OnAttach() final override; // Attach function. Final override to prevent overriding in CLIENT. Use the constructor for initialization logic instead.
		void OnDetach() final override; // Detach function. Final override to prevent overriding in CLIENT. Use the destructor for cleanup logic instead.

		virtual void Update(const TimeData& timeData) override = 0; // Update function to be defined in CLIENT. Gets called in the main loop of the application automatically before updating and rendering.
		virtual void Render(const TimeData& timeData) override = 0; // Render function to be defined in CLIENT. Gets called in the main loop of the application automatically before rendering and after beginning the scene and after update.
		virtual void RenderImGui(const TimeData& timeData) override = 0; // ImGui render function to be defined in CLIENT. Gets called in the main loop of the application automatically after rendering and before ending the scene.

	private:
		// This class is used by Application to allow proper lifetime managements by listeners of the application. Dont use this at all except in the application class it is not meant to be used outside of it.
		class ApplicationEventListener : public Events::IEventListener<ApplicationEventListener> {
		public:
			ApplicationEventListener(); // Constructor to add the event listeners to the events.
			~ApplicationEventListener() override = default; // Destructor to remove the event listeners from the events.

			void OnWindowClose(); // Function to be called when the window is closed.
		};

		std::shared_ptr<ApplicationEventListener> applicationEventListener_; // Shared pointer to the application event listener to allow lifetime management of the application by the event system

	}; // class Application

	Application* CreateApplication(); // Defined in the CLIENT

} // namespace Pulse
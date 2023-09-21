#pragma once

namespace Pulse::Modules::Rendering {
	
	// Interface class for the graphics context
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default; // Virtual destructor for proper cleanup

		virtual void Initialize() = 0; // Virtual function to initialize the graphics context
		virtual void SwapBuffers() = 0; // Virtual function to swap the buffers of the graphics context

		static GraphicsContext* Create(void* window); // Static function to create a graphics context based on the renderer api and the window passed
	};
}
#pragma once

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Layers/LayerManager.h"
#include "Pulse/Core/TimeData.h"

namespace Pulse {

	// Class that controls the engine initialization, loop and shutdown.
	// It is the main class of the engine and gets called by main.
	class Engine {
	public :
		static void Initialize(); // Initialize the engine by setting up the modules and layers.
		static void Run(); // Run the engine by calling according layer and module functions each frame.
		static void Shutdown(); // Shutdown the engine by shutting down the modules and layers.

		static void Stop(); // Stop the engine by setting the isRunning flag to false.

	private:
		static Modules::ModuleManager* moduleManager_; // Reference to the module manager singleton.
		static Layers::LayerManager* layerManager_; // Reference to the layer manager singleton.
		static bool isRunning_; // Flag that indicates if the engine is running.
		static TimeData timeData_; // Time between the last and the current frame.

	}; // class Engine

} // namespace Pulse
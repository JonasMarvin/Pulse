#pragma once

#include "Pulse/Core/Engine.h"

#ifdef PLS_PLATFORM_WINDOWS

	// This is the entry point for the engine.
	int main(int argc, char** argv) {
		Pulse::Engine::Initialize();
		Pulse::Engine::Run();
		Pulse::Engine::Shutdown();
	}

#endif
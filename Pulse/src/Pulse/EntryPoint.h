#pragma once

#ifdef PLS_PLATFORM_WINDOWS

extern Pulse::Application* Pulse::CreateApplication(); // This is defined in Sandbox/src/SandboxApplication.cpp

// This is the entry point for the engine.
int main(int argc, char** argv) {

	Pulse::Log::Init();
	PLS_CORE_INFO("Initialized Log");

	auto* application = Pulse::CreateApplication();
	application->Run();
	PLS_CORE_INFO("Closing application");
	delete application;
}

#endif
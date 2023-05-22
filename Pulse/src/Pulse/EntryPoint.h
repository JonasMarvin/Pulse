#pragma once

#ifdef PLS_PLATFORM_WINDOWS

extern Pulse::Application* Pulse::CreateApplication();

int main(int argc, char** argv) {
	
	Pulse::Log::Init();
	PLS_CORE_WARN("Initialized Log");
	int a = 5;
	PLS_ERROR("Hello! Var={0}", a);

	auto* application = Pulse::CreateApplication();
	application->Run();
	delete application;
}

#endif
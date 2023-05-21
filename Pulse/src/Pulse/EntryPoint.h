#pragma once

#ifdef PLS_PLATFORM_WINDOWS

extern Pulse::Application* Pulse::CreateApplication();

int main(int argc, char** argv) {
	auto* application = Pulse::CreateApplication();
	application->Run();
	delete application;
}

#endif
#include <Pulse.h>

static void TestFunction(int test) {
	PLS_INFO("Test function called");
}

class Player : public Pulse::Events::IEventListener<Player> {

	public:
		

		void OnTestEvent() {
			PLS_INFO("Test function called");
	}
		~Player() {
			PLS_ERROR("Player destroyed");
		}

};

class Sandbox : public Pulse::Application {
public:
	Sandbox() {
		int tmpEventCount = 1000000;
		int eventListenerCount = 100;
		int eventListenerCallCount = 1;

		Pulse::Utility::Stopwatch stopwatch;

		// for (int i = 0; i <= tmpEventCount; ++i) {
			//Pulse::Events::Event<> emptyEvent;
		//}
		stopwatch.PrintTime<std::chrono::seconds>("Empty event creation time: ");
		
		stopwatch.Reset();
		//for (int i = 0; i <= tmpEventCount; ++i) {
			//Pulse::Events::Event<int, bool, int, float, long long> tmpEvent;
		//}
		stopwatch.PrintTime<std::chrono::seconds>("Five arguments event creation time: ");

		// Pulse::Events::UnsafeEvent<> testEvent;
		stopwatch.Reset();
		// auto player = std::make_shared<Player>();
		
		
		stopwatch.PrintTime<std::chrono::seconds>("Listener creation time: ");
	}

	~Sandbox() {

	}
};

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}

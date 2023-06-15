#include <Pulse.h>

#include <memory>
#include <chrono>


class Player : public Pulse::Events::IEventListener<Player> {
public:
	void ChangeHealth(int health , float test, int health2, float test2) {
		
	}

	void ChangeKarsten(int health) {
	}

private:
	int health_ = 0;
};

class Player2 : public Pulse::Events::IEventListener<Player2> {
public:
	void ChangeHealth(int health ,float test, int health2, float test2) {
	}

	void ChangeKarsten(int health) {
	}

private:
	int health_ = 0;
};

 void TestFunction(int health, float test, int health2, float test2) {

}

 class Sandbox : public Pulse::Application {
 public:
	 Sandbox() {
		 auto Hit = Pulse::Events::CreatePulseEvent<int>();
		 auto player = std::make_shared<Player>();
		 auto Hit2 = Pulse::Events::CreatePulseEvent<int>();
		 auto Hit3 = Pulse::Events::CreatePulseEvent<int, float,int, float>();
		 auto Hit4 = Pulse::Events::CreatePulseEvent<int, const std::string&>();
		 auto startAddingEvents = std::chrono::high_resolution_clock::now();
		 for (int i = 0; i < 1000; ++i) {
			 auto Hit22 = Pulse::Events::CreatePulseEvent<int>();
		 }
		 // Calculate elapsed time for adding and removing events
		 auto endAddingRemovingvents = std::chrono::high_resolution_clock::now();
		 auto durationAddingRemovingEvents = std::chrono::duration_cast<std::chrono::milliseconds>(endAddingRemovingvents - startAddingEvents).count();
		 PLS_TRACE("event adding and removing time: {0} milliseconds", durationAddingRemovingEvents);
		 // Measure time for adding listeners
		 auto startAddingListeners = std::chrono::high_resolution_clock::now();
		 // Add listeners
		 for (int i = 0; i < 10000; ++i) {
			 EventListenerID listener1 = player->AddListener(Hit3, &Player::ChangeHealth, false); 
		 }
		 // Calculate elapsed time for adding listeners
		 auto endAddingListeners = std::chrono::high_resolution_clock::now();
		 auto durationAddingListeners = std::chrono::duration_cast<std::chrono::milliseconds>(endAddingListeners - startAddingListeners).count();
		 PLS_TRACE("Listener adding time: {0} milliseconds", durationAddingListeners);

		 // Measure time for triggering events
		 auto startTriggeringEvents = std::chrono::high_resolution_clock::now();

		 // Trigger events multiple times
		 for (int i = 0; i < 1000; ++i) {
			 Hit3->Trigger(1, 1.0f, 1, 1.0f);
		 }

		 // Calculate elapsed time for triggering events
		 auto endTriggeringEvents = std::chrono::high_resolution_clock::now();
		 auto durationTriggeringEvents = std::chrono::duration_cast<std::chrono::milliseconds>(endTriggeringEvents - startTriggeringEvents).count();
		 PLS_TRACE("Event triggering time: {0} milliseconds", durationTriggeringEvents);

		 player->Cleanup();
	 }

	 ~Sandbox() {
		 
	 }
 };

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}
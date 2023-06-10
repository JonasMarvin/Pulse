#include <Pulse.h>

#include <memory>
#include <chrono>


class Player : public Pulse::Events::IEventListener<Player> {
public:
	void ChangeHealth(int health = 1) {
	}

	void ChangeKarsten(int health) {
	}

private:
	int health_ = 0;
};

class Player2 : public Pulse::Events::IEventListener<Player2> {
public:
	void ChangeHealth(int health = 1) {
	}

	void ChangeKarsten(int health) {
	}

private:
	int health_ = 0;
};

 void TestFunction(int health, float test) {
	 static int a = 0;
	 a += health;
}

 class Sandbox : public Pulse::Application {
 public:
	 Sandbox() {
		 Pulse::Events::Event<int> Hit{};
		 std::shared_ptr<Player> player = std::make_shared<Player>();
		 Pulse::Events::Event<int> Hit2{};
		 Pulse::Events::Event<int, float> Hit3{};
		 Pulse::Events::Event<int, const std::string&> Hit4{};

		 // Measure time for adding listeners
		 auto startAddingListeners = std::chrono::high_resolution_clock::now();

		 // Add listeners
		 for (int i = 0; i < 1000000; ++i) {
			 EventListenerID listener1 = player->AddListener(Hit, &Player::ChangeHealth);
		 }
		 // Calculate elapsed time for adding listeners
		 auto endAddingListeners = std::chrono::high_resolution_clock::now();
		 auto durationAddingListeners = std::chrono::duration_cast<std::chrono::milliseconds>(endAddingListeners - startAddingListeners).count();
		 PLS_TRACE("Listener adding time: {0} milliseconds", durationAddingListeners);

		 // Measure time for triggering events
		 auto startTriggeringEvents = std::chrono::high_resolution_clock::now();

		 // Trigger events multiple times
		 for (int i = 0; i < 1; ++i) {
			 Hit.Trigger(1);
		 }

		 // Calculate elapsed time for triggering events
		 auto endTriggeringEvents = std::chrono::high_resolution_clock::now();
		 auto durationTriggeringEvents = std::chrono::duration_cast<std::chrono::milliseconds>(endTriggeringEvents - startTriggeringEvents).count();
		 PLS_TRACE("Event triggering time: {0} milliseconds", durationTriggeringEvents);


		 EventListenerID listener3 = player->AddListener(Hit, &Player::ChangeHealth);
		 EventListenerID listener4 = player->AddListener(Hit, &Player::ChangeKarsten);

		 // Trigger event again
		 Hit.Trigger(100);

		 EventListenerID listener5 = player->AddListener(Hit2, &Player::ChangeHealth);
		 EventListenerID listener6 = player->AddListener(Hit2, &Player::ChangeKarsten);

		 // Print the total time taken for both adding listeners and triggering events
		 auto totalTime = durationAddingListeners + durationTriggeringEvents;
		 PLS_TRACE("Total time: {0} milliseconds", totalTime);
	 }

	 ~Sandbox() {
	 }
 };

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}
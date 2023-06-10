#include <Pulse.h>

#include <memory>

class Player : public Pulse::Events::IEventListener<Player> {
public:
	void ChangeHealth(int health = 1) {
		health_ += health;
		PLS_TRACE(health_);
	}

	void ChangeKarsten(int health) {
		health_ += health;
		PLS_TRACE(health_);
	}

private:
	int health_ = 0;
};

class Player2 : public Pulse::Events::IEventListener<Player2> {
public:
	void ChangeHealth(int health = 1) {
		health_ += health;
		PLS_TRACE(health_);
	}

	void ChangeKarsten(int health) {
		health_ += health;
		PLS_TRACE(health_);
	}

private:
	int health_ = 0;
};

class Sandbox : public Pulse::Application {
	public:
		Sandbox() {
			
			Pulse::Events::Event<int> Hit{};
			std::shared_ptr<Player> player = std::make_shared<Player>();
			Pulse::Events::Event<int> Hit2{};
			
			// Add listeners
			EventListenerID listener1 = player->AddListener(Hit, &Player::ChangeHealth);
			EventListenerID listener2 = player->AddListener(Hit, &Player::ChangeKarsten);
			EventListenerID listener8 = player->AddListener(Hit, &Player::ChangeHealth);
			EventListenerID listener7 = player->AddListener(Hit, &Player::ChangeKarsten);
			Hit.Trigger(1);

			player->RemoveListener(listener1);
			player->RemoveListener(listener2);
			player->RemoveListener(listener8);
			player->RemoveListener(listener7);

			Hit.Trigger(10);

			EventListenerID listener3 = player->AddListener(Hit, &Player::ChangeHealth);
			EventListenerID listener4 = player->AddListener(Hit, &Player::ChangeKarsten);

			Hit.Trigger(100);

			EventListenerID listener5 = player->AddListener(Hit2, &Player::ChangeHealth);
			EventListenerID listener6 = player->AddListener(Hit2, &Player::ChangeKarsten);
		}
		~Sandbox() {

		}
};

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}
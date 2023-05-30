#include <Pulse.h>

class Player : public Pulse::Modules::Events::IEventListener<Player> {
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

class Player2 : public Pulse::Modules::Events::IEventListener<Player2> {
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
			Player player{};
			Pulse::Modules::Events::IEvent<int> Hit{};

			// Add listeners
			uint64_t listener1 = player.AddListener(Hit, &Player::ChangeHealth);
			uint64_t listener2 = player.AddListener(Hit, &Player::ChangeKarsten);

			Hit.Trigger(1);

			// Remove listeners
			player.RemoveListener(listener1);
			player.RemoveListener(listener2);

			Hit.Trigger(10);

			uint64_t listener3 = player.AddListener(Hit, &Player::ChangeHealth);
			uint64_t listener4 = player.AddListener(Hit, &Player::ChangeKarsten);

			Hit.Trigger(100);

			Pulse::Modules::Events::IEvent<int> Hit2{};

			uint64_t listener5 = player.AddListener(Hit2, &Player::ChangeHealth);
			uint64_t listener6 = player.AddListener(Hit2, &Player::ChangeKarsten);
		}
		~Sandbox() {
		}
};

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}
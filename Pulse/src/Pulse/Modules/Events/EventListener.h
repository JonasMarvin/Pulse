#pragma once

#include "Pulse/Utility/IDManager.h"

namespace Pulse::Modules::Events {

	template <typename... Args>
	class EventListenerBase {
	public:
		inline EventListenerBase() : eventListenerID_(eventIDManager_.GenerateID()){ }
		virtual inline ~EventListenerBase() {
			eventIDManager_.FreeID(eventListenerID_);
		}

		virtual inline void Invoke(Args... args) = 0;

		inline uint32_t GetEventListenerID() const {
			return eventListenerID_;
		}

	private:
		uint32_t eventListenerID_;
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};
	};

	template <typename T, typename... Args>
	class EventListener : public EventListenerBase<Args...> {
	public:
		typedef void(T::* Callback)(Args...);

		EventListener() = delete;
		inline EventListener(T* objectInstance, const Callback callback)
			: objectInstance_(objectInstance), callback_(callback) { }
		inline ~EventListener() override = default;

		inline void Invoke(Args... args) override {
			(objectInstance_->*callback_)(args...);
		}

	private:
		T* objectInstance_;
		Callback callback_;

	}; // class EventListener

} // namespace Pulse::Modules::Events
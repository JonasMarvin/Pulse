#pragma once

#include "Pulse/Utility/IDManager.h"

#include <memory>

namespace Pulse::Events {

	template <typename... Args>
	class EventListenerBase {
	public:
		EventListenerBase() : eventListenerID_(eventIDManager_.GenerateID()) { }
		virtual ~EventListenerBase() {
			eventIDManager_.FreeID(eventListenerID_);
		}

		virtual void Invoke(Args... args) = 0;
		
		uint32_t GetEventListenerID() const {
			return eventListenerID_;
		}

	protected:
		uint32_t eventListenerID_;

	private:
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class EventListenerBase

	template <typename T, typename... Args>
	class EventListener : public EventListenerBase<Args...> {
	public:
		typedef void(T::* Callback)(Args...);

		EventListener(T* objectInstance, const Callback callback)
			: objectInstance_(objectInstance), callback_(callback) { }

		void Invoke(Args... args) override {
			(objectInstance_->*callback_)(args...);
		}

	private:
		T* objectInstance_;
		Callback callback_;

	}; // class EventListener

} // namespace Pulse::Events
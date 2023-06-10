#pragma once

#include "Pulse/Utility/IDManager.h"

#include <memory>
#include <functional>

namespace Pulse::Events {

	template <typename... Args>
	class EventListenerBase {
	public:
		EventListenerBase() : eventListenerID_(eventIDManager_.GenerateID()) { }
		virtual ~EventListenerBase() {
			eventIDManager_.FreeID(eventListenerID_);
		}

		virtual void Invoke(Args&&... args) = 0;
		
		uint32_t GetEventListenerID() const {
			return eventListenerID_;
		}

	protected:
		uint32_t eventListenerID_;

	private:
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class EventListenerBase

	template <typename T, typename... Args>
	class EventListenerMember : public EventListenerBase<Args...> {
	public:
		typedef void(T::* Callback)(Args...);

		EventListenerMember(T* objectInstance, const Callback callback)
			: objectInstance_(objectInstance), callback_(callback) { }

		void Invoke(Args&&... args) override {
			(objectInstance_->*callback_)(std::forward<Args>(args)...);
		}

	private:
		T* objectInstance_;
		Callback callback_;

	}; // class EventListenerMember

	template <typename... Args>
	class EventListenerNoMember : public EventListenerBase<Args...> {
	public:
		typedef std::function<void(Args...)> Callback;

		EventListenerNoMember(const Callback& callback)
			: callback_(callback) {}

		void Invoke(Args... args) override {
			callback_(std::forward<Args>(args)...);
		}

	private:
		Callback callback_;

	}; // class EventListenerNoMember

} // namespace Pulse::Events
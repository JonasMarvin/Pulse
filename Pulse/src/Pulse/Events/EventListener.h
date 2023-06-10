#pragma once

#include "Pulse/Utility/IDManager.h"
#include "Pulse/Log.h"

#include <memory>

namespace Pulse::Events {

	class IEventListenerBase;

	class PLS_API OnEventRemovalHandler {
	public:
		inline OnEventRemovalHandler(std::shared_ptr<IEventListenerBase> iEventListenerBase)
			: iEventListenerBase_(iEventListenerBase) { }
		void RemoveEventFromConnectedIEventListener(uint32_t eventID_);

	protected:
		std::weak_ptr<IEventListenerBase> iEventListenerBase_;
	}; // class OnEventRemovalHandler

	template <typename... Args>
	class EventListenerBase : public OnEventRemovalHandler {
	public:
		EventListenerBase(std::shared_ptr<IEventListenerBase> iEventListenerBase)
			: OnEventRemovalHandler(iEventListenerBase), eventListenerID_(eventIDManager_.GenerateID()) { }
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

		EventListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, T* objectInstance, const Callback callback)
			: EventListenerBase<Args...>(iEventListenerBase), objectInstance_(objectInstance), callback_(callback) { }

		void Invoke(Args... args) override {
			(objectInstance_->*callback_)(args...);
		}

	private:
		T* objectInstance_;
		Callback callback_;

	}; // class EventListener

} // namespace Pulse::Events
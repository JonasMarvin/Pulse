#pragma once

#include "Pulse/Utility/IDManager.h"

#include <memory>
#include <functional>

namespace Pulse::Events {

	template <typename... Args>
	class EventListenerBase {
	public:
		EventListenerBase(bool isThreadSafe) : isThreadSafe_(isThreadSafe), eventListenerID_(eventIDManager_.GenerateID()) { }
		virtual ~EventListenerBase() {
			eventIDManager_.FreeID(eventListenerID_);
		}

		virtual void Invoke(Args... args) = 0;
		
		uint32_t GetEventListenerID() const {
			return eventListenerID_;
		}

		bool IsThreadSafe() const {
			return isThreadSafe_;
		}

		void SetEnqeuedInThread(bool isEnqeuedInThread) {
			isEnqeuedInThread_ = isEnqeuedInThread;
		}

		bool IsEnqeuedInThread() const {
			return isEnqeuedInThread_;
		}

	protected:
		uint32_t eventListenerID_;

	private:
		bool isThreadSafe_ = false;
		bool isEnqeuedInThread_ = false;
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class EventListenerBase

	template <typename T, typename... Args>
	class EventListenerMember : public EventListenerBase<Args...> {
	public:
		typedef void(T::* Callback)(Args...);

		EventListenerMember(T* objectInstance, const Callback callback, bool isThreadSafe)
			: EventListenerBase<Args...>(isThreadSafe), objectInstance_(objectInstance), callback_(callback) { }

		void Invoke(Args... args) override {
			(objectInstance_->*callback_)(std::move(args)...);
		}

	private:
		T* objectInstance_;
		Callback callback_;

	}; // class EventListenerMember

	template <typename... Args>
	class EventListenerNoMember : public EventListenerBase<Args...> {
	public:
		typedef std::function<void(Args...)> Callback;

		EventListenerNoMember(const Callback& callback, bool isThreadSafe)
			: EventListenerBase<Args...>(isThreadSafe), callback_(callback) {}

		void Invoke(Args... args) override {
			callback_(std::move(args)...);
		}

	private:
		Callback callback_;

	}; // class EventListenerNoMember

} // namespace Pulse::Events
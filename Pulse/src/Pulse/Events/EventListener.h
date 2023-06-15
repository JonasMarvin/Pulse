#pragma once

#include <memory>
#include <functional>

#include "Pulse/Utility/IDManager.h"

namespace Pulse::Events {

	template <typename... Args>
	class EventListener {
	public:

		virtual ~EventListener();

		virtual void Invoke(Args... args) = 0;
		
		uint32_t GetEventListenerID() const;

		bool IsThreadSafe() const;
		void _SetEnqeuedInThread(bool isEnqeuedInThread);
		bool IsEnqeuedInThread() const;

	protected:
		EventListener(bool isThreadSafe) : isThreadSafe_(isThreadSafe), eventListenerID_(eventIDManager_.GenerateID()) { }

		uint32_t eventListenerID_;

	private:
		bool isThreadSafe_ = false;
		bool isEnqeuedInThread_ = false;
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class EventListenerBase

	namespace Internal{

		template <typename T, typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			typedef void(T::* Callback)(Args...);

			EventListenerMember(T* objectInstance, const Callback callback, bool isThreadSafe)
				: EventListener<Args...>(isThreadSafe), objectInstance_(objectInstance), callback_(callback) { }

			void Invoke(Args... args) override;

		private:
			T* objectInstance_;
			Callback callback_;

		}; // class EventListenerMember

		template <typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			typedef std::function<void(Args...)> Callback;

			EventListenerNoMember(const Callback& callback, bool isThreadSafe)
				: EventListener<Args...>(isThreadSafe), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			Callback callback_;

		}; // class EventListenerNoMember

	} // namespace Internal

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
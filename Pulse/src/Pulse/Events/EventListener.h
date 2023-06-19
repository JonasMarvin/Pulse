#pragma once

#include <memory>
#include <functional>

#include "Pulse/Core.h"

namespace Pulse::Events {

	namespace Internal {
		
		class IEventListenerBase;
		class EventBase;

		class PLS_API EventListenerBase : public std::enable_shared_from_this<EventListenerBase> {
		public:
			virtual ~EventListenerBase() = default;

			void _RemoveFromIEventListenerBase();
			void _RemoveFromEventBase();

			void _SetEnqeuedInThread(const bool& enqueued);
			bool IsEnqeuedInThread() const;

		protected:
			EventListenerBase(std::weak_ptr<IEventListenerBase>&& iEventListenerBase, std::weak_ptr<EventBase>&& eventBase)
				: iEventListenerBase_(std::move(iEventListenerBase)), eventBase_(std::move(eventBase)) {}
	
			std::weak_ptr<IEventListenerBase> iEventListenerBase_;
			std::weak_ptr<EventBase> eventBase_;
			bool isEnqeuedInThread_ = false;

		}; // class EventListenerBase

	} // namespace Internal

	template <typename... Args>
	class EventListener : public Internal::EventListenerBase{
	public:
		virtual ~EventListener() override = default;

		virtual void Invoke(Args... args) = 0;

	protected:
		EventListener(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event)
			: Internal::EventListenerBase(std::move(iEventListenerBase), std::move(event)) {}
	}; // class EventListenerBase

	namespace Internal{

		template <typename T, typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			typedef void(T::* Callback)(Args...);

			virtual ~EventListenerMember() override = default;

			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event,
				T* objectInstance, Callback callback)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event)), objectInstance_(objectInstance), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			T* objectInstance_;
			Callback callback_;

		}; // class EventListenerMember

		template <typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			typedef std::function<void(Args...)> Callback;

			virtual ~EventListenerNoMember() override = default;

			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event,
				Callback&& callback)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event)), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			Callback callback_;

		}; // class EventListenerNoMember

	} // namespace Internal

	// Unsafe system:

	template<typename... Args>
	class UnsafeEventListener {
	public:
		virtual ~UnsafeEventListener() = default;

		virtual void Invoke(Args... args) = 0;

		void _SetEnqeuedInThread(const bool& enqueued);
		bool IsEnqeuedInThread() const;

	protected:
		UnsafeEventListener() = default;

	private:
		bool isEnqeuedInThread_ = false;

	} // class UnsafeEventListener

	template <typename T, typename... Args>
		class UnsafeEventListenerMember : public UnsafeEventListener<Args...> {
		public:
			typedef void(T::* Callback)(Args...);

			virtual ~UnsafeEventListenerMember() override = default;

			UnsafeEventListenerMember(T* objectInstance, Callback callback)
				: objectInstance_(objectInstance), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			T* objectInstance_;
			Callback callback_;

		}; // class UnsafeEventListenerMember

		template <typename... Args>
		class UnsafeEventListenerNoMember : public UnsafeEventListener<Args...> {
		public:
			typedef std::function<void(Args...)> Callback;

			virtual ~UnsafeEventListenerNoMember() override = default;

			UnsafeEventListenerNoMember(Callback callback)
				: callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			Callback callback_;

		}; // class UnsafeEventListenerNoMember

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
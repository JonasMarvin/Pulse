#pragma once

#include <memory>
#include <functional>
#include <thread>

#include "Pulse/Core.h"

namespace Pulse::Events {

	namespace Internal {
		
		class IEventListenerBase;
		class EventBase;

		class PLS_API EventListenerBase : public std::enable_shared_from_this<EventListenerBase> {
		public:
			void _RemoveFromIEventListenerBase();
			void _RemoveFromEventBase();

			void _SetEnqueuedInThread(bool enqueued);
			bool IsEnqeuedInThread() const noexcept;
			bool IsThreadsafe() const noexcept;

		protected:
			EventListenerBase(std::weak_ptr<IEventListenerBase>&& iEventListenerBase, std::weak_ptr<EventBase>&& eventBase, bool isThreadsafe)
				: iEventListenerBase_(std::move(iEventListenerBase)), eventBase_(std::move(eventBase)), isThreadsafe_(isThreadsafe)  {}
	
			EventListenerBase() = delete;

			virtual ~EventListenerBase() = default;
			
			std::weak_ptr<IEventListenerBase> iEventListenerBase_;
			std::weak_ptr<EventBase> eventBase_;
			bool isEnqueuedInThread_ = false;
			bool isThreadsafe_ = false;

		}; // class EventListenerBase

	} // namespace Internal

	template <typename... Args>
	class EventListener : public Internal::EventListenerBase{
	public:
		virtual ~EventListener() override = default;

		virtual void Invoke(Args... args) = 0;

	protected:
		EventListener(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, bool isThreadsafe)
			: Internal::EventListenerBase(std::move(iEventListenerBase), std::move(event), isThreadsafe) {}

	private:
		EventListener() = delete;
	}; // class EventListenerBase

	namespace Internal{

		template <typename T, typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			using Callback = void(T::*)(Args...);

			virtual ~EventListenerMember() override = default;

			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, T* objectInstance, Callback&& callback, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {}

			void Invoke(Args... args) override;

		private:
			EventListenerMember() = delete;

			T* objectInstance_;
			Callback callback_;

		}; // class EventListenerMember

		template <typename Callable, typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			virtual ~EventListenerNoMember() override = default;

			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, Callable&& callback, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), callback_(std::forward<Callable>(callback)) {}

			void Invoke(Args... args) override;

		private:
			EventListenerNoMember() = default;

			Callable callback_;

		}; // class EventListenerNoMember

	} // namespace Internal

	// Unsafe system:

	template<typename... Args>
	class UnsafeEventListener {
	public:
		virtual ~UnsafeEventListener();

		virtual void Invoke(Args... args) = 0;

		void _SetEnqeuedInThread(bool enqueued);
		bool IsEnqeuedInThread() const noexcept;
		bool IsThreadsafe() const noexcept;

	protected:
		UnsafeEventListener(bool isThreadsafe) : isThreadsafe_(isThreadsafe) {};

	private:
		UnsafeEventListener() = delete;

		bool isEnqeuedInThread_ = false;
		bool isThreadsafe_ = false;

	}; // class UnsafeEventListener

	template <typename T, typename... Args>
		class UnsafeEventListenerMember : public UnsafeEventListener<Args...> {
		public:
			using Callback = void(T::*)(Args...);

			virtual ~UnsafeEventListenerMember() override = default;

			UnsafeEventListenerMember(T* objectInstance, Callback&& callback, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {}

			void Invoke(Args... args) override;

		private:
			UnsafeEventListenerMember() = delete;

			T* objectInstance_;
			Callback callback_;

		}; // class UnsafeEventListenerMember

		template <typename Callable, typename... Args>
		class UnsafeEventListenerNoMember : public UnsafeEventListener<Args...> {
		public:
			virtual ~UnsafeEventListenerNoMember() override = default;

			UnsafeEventListenerNoMember(Callable&& callback, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), callback_(std::forward<Callable>(callback)) {}

			void Invoke(Args... args) override;

		private:
			UnsafeEventListenerNoMember() = delete;

			Callable callback_;

		}; // class UnsafeEventListenerNoMember

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
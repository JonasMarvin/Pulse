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

		template <typename T, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			using Callback = void(T::*)(Args...);

			virtual ~EventListenerMember() override = default;

			PLS_DOES_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, T* objectInstance, Callback&& callback, Condition&& condition, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)), condition_(std::forward<Condition>(condition)) {}

			PLS_DOES_NOT_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, T* objectInstance, Callback&& callback, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {}

			void Invoke(Args... args) override;

		private:
			EventListenerMember() = delete;

			T* objectInstance_;
			Callback callback_;
			Condition condition_;

		}; // class EventListenerMember

		template <typename Callable, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			virtual ~EventListenerNoMember() override = default;

			PLS_DOES_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, Callable&& callback, Condition&& condition, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), callback_(std::forward<Callable>(callback)), condition_(std::forward<Condition>(condition)) {}

			PLS_DOES_NOT_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, Callable&& callback, bool isThreadsafe)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), callback_(std::forward<Callable>(callback)) {}

			void Invoke(Args... args) override;

		private:
			EventListenerNoMember() = default;

			Callable callback_;
			Condition condition_;

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

	template <typename T, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
		class UnsafeEventListenerMember : public UnsafeEventListener<Args...> {
		public:
			using Callback = void(T::*)(Args...);

			virtual ~UnsafeEventListenerMember() override = default;

			PLS_DOES_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			UnsafeEventListenerMember(T* objectInstance, Callback&& callback, Condition&& condition, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)), condition_(std::forward<Condition>(condition)) {}

			PLS_DOES_NOT_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			UnsafeEventListenerMember(T* objectInstance, Callback&& callback, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {}

			void Invoke(Args... args) override;

		private:
			UnsafeEventListenerMember() = delete;

			T* objectInstance_;
			Callback callback_;
			Condition condition_;

		}; // class UnsafeEventListenerMember

		template <typename Callable, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
		class UnsafeEventListenerNoMember : public UnsafeEventListener<Args...> {
		public:
			virtual ~UnsafeEventListenerNoMember() override = default;

			PLS_DOES_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			UnsafeEventListenerNoMember(Callable&& callback, Condition&& condition, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), callback_(std::forward<Callable>(callback)), condition_(std::forward<Condition>(condition)) {}

			PLS_DOES_NOT_REQUIRE_OPTIONAL_CLASS_TEMPLATE_ARGUMENT(Condition)
			UnsafeEventListenerNoMember(Callable&& callback, bool isThreadsafe = false)
				: UnsafeEventListener<Args...>(isThreadsafe), callback_(std::forward<Callable>(callback)) {}

			void Invoke(Args... args) override;

		private:
			UnsafeEventListenerNoMember() = delete;

			Callable callback_;
			Condition condition_;

		}; // class UnsafeEventListenerNoMember

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
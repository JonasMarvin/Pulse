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
			virtual ~EventListenerBase() noexcept = default;

			void _RemoveFromIEventListenerBase();
			void _RemoveFromEventBase();

			void _SetEnqeuedInThread(const bool& enqueued) noexcept;
			bool IsEnqeuedInThread() const noexcept;
			bool IsThreadsafe() const noexcept;

		protected:
			EventListenerBase(std::weak_ptr<IEventListenerBase>&& iEventListenerBase, std::weak_ptr<EventBase>&& eventBase, const bool& isThreadsafe) noexcept
				: iEventListenerBase_(std::move(iEventListenerBase)), eventBase_(std::move(eventBase)), isThreadsafe_(isThreadsafe)  {}
	
			std::weak_ptr<IEventListenerBase> iEventListenerBase_;
			std::weak_ptr<EventBase> eventBase_;
			bool isEnqeuedInThread_ = false;
			bool isThreadsafe_ = false;

		}; // class EventListenerBase

	} // namespace Internal

	template <typename... Args>
	class EventListener : public Internal::EventListenerBase{
	public:
		virtual ~EventListener() noexcept override = default;

		virtual void Invoke(Args... args) = 0;

	protected:
		EventListener(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, const bool& isThreadsafe) noexcept
			: Internal::EventListenerBase(std::move(iEventListenerBase), std::move(event), isThreadsafe) {}
	}; // class EventListenerBase

	namespace Internal{

		template <typename T, typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			typedef void(T::* Callback)(Args...);

			virtual ~EventListenerMember() noexcept override = default;

			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event,
				T* objectInstance, Callback callback, const bool& isThreadsafe) noexcept
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), objectInstance_(objectInstance), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			T* objectInstance_;
			Callback callback_;

		}; // class EventListenerMember

		template <typename Callable, typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			virtual ~EventListenerNoMember() noexcept override = default;

			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event,
				Callable&& callback, const bool& isThreadsafe) noexcept
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event), isThreadsafe), callback_(std::forward<Callable>(callback)) {}

			void Invoke(Args... args) override;

		private:
			Callable callback_;

		}; // class EventListenerNoMember

	} // namespace Internal

	// Unsafe system:

	template<typename... Args>
	class UnsafeEventListener {
	public:
		virtual ~UnsafeEventListener() noexcept;

		virtual void Invoke(Args... args) = 0;

		void _SetEnqeuedInThread(const bool& enqueued) noexcept;
		bool IsEnqeuedInThread() const noexcept;
		bool IsThreadsafe() const noexcept;

	protected:
		UnsafeEventListener(const bool& isThreadsafe) noexcept : isThreadsafe_(isThreadsafe) {};

	private:
		bool isEnqeuedInThread_ = false;
		bool isThreadsafe_ = false;

	}; // class UnsafeEventListener

	template <typename T, typename... Args>
		class UnsafeEventListenerMember : public UnsafeEventListener<Args...> {
		public:
			typedef void(T::* Callback)(Args...);

			virtual ~UnsafeEventListenerMember() noexcept override = default;

			UnsafeEventListenerMember(T* objectInstance, Callback callback, const bool& isThreadsafe = false) noexcept
				: UnsafeEventListener<Args...>(isThreadsafe), objectInstance_(objectInstance), callback_(callback) {}

			void Invoke(Args... args) override;

		private:
			T* objectInstance_;
			Callback callback_;

		}; // class UnsafeEventListenerMember

	template <typename Callable, typename... Args>
	class UnsafeEventListenerNoMember : public UnsafeEventListener<Args...> {
	public:
		virtual ~UnsafeEventListenerNoMember() noexcept override = default;

		UnsafeEventListenerNoMember(Callable&& callback, const bool& isThreadsafe = false) noexcept
			: UnsafeEventListener<Args...>(isThreadsafe), callback_(std::forward<Callable>(callback)) {}

		void Invoke(Args... args) override;

	private:
		Callable callback_;

	}; // class UnsafeEventListenerNoMember

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
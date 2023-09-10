#pragma once

#include <memory>
#include <functional>

#include "Pulse/Core/Core.h"

namespace Pulse::Events {

	namespace Internal {

		class IEventListenerBase; // Forward declaration to avoid circular dependency
		class EventBase; // Forward declaration to avoid circular dependency

		// Internal Base class for the EventListener class to connect the Events to the IEventListeners and vice versa to be able to remove the EventListener from the Event and the IEventListener without having to know each other.
		class PLS_API EventListenerBase : public std::enable_shared_from_this<EventListenerBase> {
		public:
			void _RemoveFromIEventListenerBase(); // Internal usage only. Removes the EventListener from the IEventListenerBase.
			void _RemoveFromEventBase(); // Internal usage only. Removes the EventListener from the EventBase.

		protected:
			EventListenerBase(std::weak_ptr<IEventListenerBase>&& iEventListenerBase, std::weak_ptr<EventBase>&& eventBase)
				: iEventListenerBase_(std::move(iEventListenerBase)), eventBase_(std::move(eventBase)) {} // Protected constructor to avoid direct instantiation of the base class.

			EventListenerBase() = delete; // Delete default constructor to avoid direct instantiation of the base class.

			virtual ~EventListenerBase() = default; // Protected destructor to avoid deletion of the base class.

			std::weak_ptr<IEventListenerBase> iEventListenerBase_; // Weak pointer to the IEventListenerBase to be able to remove the EventListener from the IEventListenerBase. Weak pointer to avoid circular dependency.
			std::weak_ptr<EventBase> eventBase_; // Weak pointer to the EventBase to be able to remove the EventListener from the EventBase. Weak pointer to avoid circular dependency.

		}; // class EventListenerBase

	} // namespace Internal

	// Base class for the EventListener class to allow Triggering of the event listeners without knowing the Parameter types of the event.
	// Do not try to manage the lifetime of this class directly. Use the IEventListener class and Event class instead.
	// Direct Invoke calls are allowed but not recommended as they have no purpose.
	template <typename... Args>
	class EventListener : public Internal::EventListenerBase {
	public:
		virtual ~EventListener() override = default; // Virtual destructor to allow deletion of the derived class.

		virtual void Invoke(Args... args) = 0; // Virtual function to allow Triggering of the event listeners without knowing the Parameter types of the event.

	protected:
		EventListener(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event)
			: Internal::EventListenerBase(std::move(iEventListenerBase), std::move(event)) {} // Protected constructor to avoid direct instantiation of the base class.

	private:
		EventListener() = delete; // Delete default constructor to avoid direct instantiation of the base class.

	}; // class EventListenerBase

	namespace Internal {

		// Internal class to save the object instance and the callback function of a member function event listener.
		// Do not try to manage the lifetime of this class directly. Use the IEventListener class and Event class instead.
		template <typename T, typename... Args>
		class EventListenerMember : public EventListener<Args...> {
		public:
			using Callback = void(T::*)(Args...); // Type alias for the callback function.

			virtual ~EventListenerMember() override = default; // Virtual destructor to allow deletion of the derived class.

			EventListenerMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, T* objectInstance, Callback&& callback)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event)), objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {} // Constructor to save the object instance and the callback function of the event listener.

			void Invoke(Args... args) override; // Override of the virtual function to implement the Invoke function and allow invoking of the event listener.

		private:
			EventListenerMember() = delete; // Delete default constructor to avoid direct instantiation of the base class.

			T* objectInstance_; // Pointer to the object instance of the event listener.
			Callback callback_; // Callback function of the event listener.

		}; // class EventListenerMember

		// Internal class to save the callback function of a non-member function event listener.
		// Do not try to manage the lifetime of this class directly. Use the IEventListener class and Event class instead.
		template <typename Callable, typename... Args>
		class EventListenerNoMember : public EventListener<Args...> {
		public:
			virtual ~EventListenerNoMember() override = default; // Virtual destructor to allow deletion of the derived class.

			EventListenerNoMember(std::weak_ptr<Internal::IEventListenerBase>&& iEventListenerBase, std::weak_ptr<Internal::EventBase>&& event, Callable&& callback)
				: EventListener<Args...>(std::move(iEventListenerBase), std::move(event)), callback_(std::forward<Callable>(callback)) {} // Constructor to save the callback function of the event listener.

			void Invoke(Args... args) override; // Override of the virtual function to implement the Invoke function and allow invoking of the event listener.

		private:
			EventListenerNoMember() = default; // Delete default constructor to avoid direct instantiation of the base class.

			Callable callback_; // Callback function of the event listener.

		}; // class EventListenerNoMember

	} // namespace Internal

	// Unsafe system for events. This system does not use shared_ptrs and is therefore not memory safe.
	// Its completely independent from the safe system. So unsafe event listeners can not be added to safe events and vice versa.
	// It's not using IEventListeners but rather UnsafeEventListenerMember and UnsafeEventListenerNoMember directly.
	// This system is not recommended to use but is provided for performance reasons because it does not use shared_ptrs and the removal of listeners is not using a vtable.
	// Also it allocates less memory than the safe system.
	// The Triggering of the eventlisteners is still using a vtable and is therefore not faster than the safe system.
	// Allows any number and type of arguments as template parameters.
	// The event listeners need to have the same number and type of arguments to be able to listen to the event.
	namespace Internal {

		// Internal base class for the UnsafeEventListener class to allow Triggering of the event listeners without knowing the Parameter types of the event.
		// Use UnsafeEventListenerMember or UnsafeEventListenerNoMember to create an unsafe event listener.
		template<typename... Args>
		class UnsafeEventListener {
		public:
			virtual void Invoke(Args... args) = 0; // Virtual function to allow Triggering of the event listeners without knowing the Parameter types of the event.

		protected:
			virtual ~UnsafeEventListener() = default; // Virtual destructor to allow deletion of the derived class and the base classes.
			UnsafeEventListener() = default; // Default constructor to allow instantiation of the base class in the derived classes.

		}; // class UnsafeEventListener

	} // namespace Internal

	// Use this class to create an unsafe event listener for a member function.
	// You are responsible for the lifetime of the object instance and the lifetime of the event listener and the lifetime of the event.
	// Has to be allocated on the heap.
	template <typename T, typename... Args>
	class UnsafeEventListenerMember : public Internal::UnsafeEventListener<Args...> {
	public:
		using Callback = void(T::*)(Args...); // Type alias for the callback function.

		virtual ~UnsafeEventListenerMember() override = default; // Virtual destructor to allow deletion of the derived class.

		UnsafeEventListenerMember(T* objectInstance, Callback&& callback)
			: objectInstance_(objectInstance), callback_(std::forward<Callback>(callback)) {} // Constructor to save the object instance and the callback function of the event listener.

		void Invoke(Args... args) override; // Override of the virtual function to implement the Invoke function and allow invoking of the event listener.

	private:
		UnsafeEventListenerMember() = delete; // Delete default constructor to avoid avoid non parameter instantiation of this class.

		T* objectInstance_; // Pointer to the object instance of the event listener.
		Callback callback_; // Callback function of the event listener.

	}; // class UnsafeEventListenerMember

	// Use this class to create an unsafe event listener for a non-member function.
	// You are responsible for the lifetime of the event listener and the lifetime of the event.
	// Has to be allocated on the heap.
	// !If you use this you have to spefically state the template types as type deduction fails here sometimes!

	template <typename Callable, typename... Args>
	class UnsafeEventListenerNoMember : public Internal::UnsafeEventListener<Args...> {
	public:
		virtual ~UnsafeEventListenerNoMember() override = default; // Virtual destructor to allow deletion of the derived class.

		UnsafeEventListenerNoMember(Callable&& callback)
			: callback_(std::forward<Callable>(callback)) {} // Constructor to save the callback function of the event listener.

		void Invoke(Args... args) override; // Override of the virtual function to implement the Invoke function and allow invoking of the event listener.

	private:
		UnsafeEventListenerNoMember() = delete; // Delete default constructor to avoid non parameter instantiation of this class.

		Callable callback_; // Callback function of the event listener.

	}; // class UnsafeEventListenerNoMember

} // namespace Pulse::Events

#include "Pulse/Events/EventListener.tpp"
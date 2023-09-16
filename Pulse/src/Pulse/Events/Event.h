#pragma once

#include <memory>
#include <unordered_set>
#include <tuple>

#include "EventListener.h"

namespace Pulse::Events{
	
	namespace Internal {

		// Pure virtual base class for providing a virtual function allowing removal of event listeners without knowing the Parameter types of the event.
		class PLS_API EventBase {
		public:
			virtual void _RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) = 0; // Pure virtual function to allow removal of event listeners without knowing the Parameter types of the event.

		protected:
			EventBase() = default; // Protected constructor to prevent instantiation of this class.
			~EventBase() = default; // Protected destructor to prevent deletion of this class.

		}; // class EventBase
		
	} // namespace Internal

	// Events need to be instantiated with the Create() function to ensure that the Event is created using a shared_ptr.
	// Alternatively, the Event can be instantiated with std::make_shared<Pulse::Events::Event<Args...>>().
	// Allows any number and type of arguments as template parameters.
	// The event listeners need to have the same number and type of arguments to be able to listen to the event.
	// If an event gets deleted all event listeners of this event will be removed automatically.
	template <typename... Args>
	class Event : public Internal::EventBase {
	public:
		Event() = default; // Default constructor to allow instantiation of this class. Do not use this constructor to instantiate this class directly.
		~Event(); // Destructor to remove all event listeners from the event.

		static std::shared_ptr<Event<Args...>> Create(); // Function to create an Event using a shared_ptr.

		void _AddListener(const std::shared_ptr<EventListener<Args...>>& eventListener); // Internal function to add an event listener to the event. Dont use this function directly but use the AddListener function of an IEventListener instead.
		void _RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) override; // Internal function to remove an event listener from the event. Dont use this function directly but use the RemoveListener function of an IEventListener instead.
		void RemoveAllListeners(); // Function to remove all event listeners from the event.

		void Trigger(Args... args); // Function to trigger the event and call all event listeners.

	private:
		std::unordered_set<std::shared_ptr<EventListener<Args...>>> eventListeners_; // Unordered set of event listeners.

	}; // class Event

	// Unsafe system for events. This system does not use shared_ptrs and is therefore not memory safe.
	// Its completely independent from the safe system. So unsafe event listeners can not be added to safe events and vice versa.
	// It's not using IEventListeners but rather UnsafeEventListenerMember and UnsafeEventListenerNoMember directly.
	// This system is not recommended to use but is provided for performance reasons because it does not use shared_ptrs and the removal of listeners is not using a vtable.
	// Also it allocates less memory than the safe system.
	// The Triggering of the eventlisteners is still using a vtable and is therefore not faster than the safe system.
	// Allows any number and type of arguments as template parameters.
	// The event listeners need to have the same number and type of arguments to be able to listen to the event.
	template <typename... Args>
	class UnsafeEvent {
	public:
		void AddListener(Internal::UnsafeEventListener<Args...>* eventListener); // Function to add an event listener to the event. Accepts UnsafeEventListenerMember and UnsafeEventListenerNoMember as argument.
		void RemoveListener(Internal::UnsafeEventListener<Args...>* eventListener); // Function to remove an event listener from the event. Accepts UnsafeEventListenerMember and UnsafeEventListenerNoMember as argument.

		void Trigger(Args... args); // Function to trigger the event and call all event listeners.

	private:
		std::unordered_set<Internal::UnsafeEventListener<Args...>*> eventListeners_; // Unordered set of event listeners.

	}; // class UnsafeEvent

} // namespace Pulse::Events

#include "Pulse/Events/Event.tpp"
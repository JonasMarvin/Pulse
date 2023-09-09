#pragma once

#include <unordered_set>
#include <memory>
#include <type_traits>

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

    namespace Internal {

        // Internal class to allow EventListeners to be removed without having to know the EventListener template parameters in the events
        // Not to be used directly
        class PLS_API IEventListenerBase : public std::enable_shared_from_this<IEventListenerBase> {
        public:
            void _RemoveListenerFromUnorderedSet(const std::shared_ptr<EventListenerBase>& eventListener); // Internal usage only. Removes the EventListener from the IEventListenerBase.

        protected:
            virtual ~IEventListenerBase() = default; // Protected destructor to avoid deletion of the base class.
            IEventListenerBase() = default; // Protected constructor to avoid direct instantiation of the base class.

            std::unordered_set<std::shared_ptr<EventListenerBase>> eventListeners_; // Unordered set of event listeners.

        }; // class IEventListenerBase

    } // namespace Internal

    // This class need to be inherited from to be able to add funcions of the class as event listeners to events.
    // If you want to use a non member function as event listener use a inerhiting class to add the function to allow lifetime management.
    // Otherwise use the unsafe system.
    // If a inerhiting classes instance gets deleted all event listeners of this instance will be removed from the events automatically.
    // This uses the CRTP pattern and is used like this: class NAME ... : public Pulse::Events::IEventListener<NAME>
    // If you want to use the eventsystem the derived class has to be allocated using a shared_ptr.
    // The derived class has to be allocated using std::make_shared<NAME>() or NAME::Create() to ensure that the derived class is created using a shared_ptr.
    // Otherwise the lifetime management of the derived class will not work.
    template<typename Derived>
    class IEventListener : public Internal::IEventListenerBase {
    public:
        static std::shared_ptr<Derived> Create() { // Function to create an IEventListener using a shared_ptr.
            return std::make_shared<Derived>();
        }

        IEventListener(const IEventListener&) = delete; // Delete copy constructor to avoid copying of the base class.
        IEventListener& operator=(const IEventListener&) = delete; // Delete copy assignment operator to avoid copying of the base class.

        template <typename Callable, typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback); // Function to add an event listener to the event. Accepts any callable object as callback. Returns a weak_ptr to the event listener to be able to remove the event listener from the event manually. The Listeners should not use move semantics to alter the passed parameters state as this would break other Listeners that get called later on event Triggering.

        template <typename... Args>
        void RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener); // Function to remove an event listener from the event. Accepts a weak_ptr to the event listener.

    protected:
        IEventListener() = default; // Protected constructor to avoid direct instantiation of the base class.
        virtual ~IEventListener() override; // Virtual destructor to allow deletion of the derived class.

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"

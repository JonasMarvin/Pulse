#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

    class PLS_API IEventListenerBase {
    public:
        inline virtual ~IEventListenerBase() {
            for (auto& eventIterator : eventPointers_) {
                eventIterator.second->RemoveListener(eventIterator.first);
			}
        }

        void RemoveListener(uint32_t eventListenerID);
        void OnEventRemoval(uint32_t eventID);

    protected:
        std::unordered_map<uint32_t, std::unordered_set<uint32_t>> eventToListeners_;
        std::unordered_map<uint32_t, EventBase*> eventPointers_;
        std::unordered_map<uint32_t, uint32_t> listenersAndEvents_;

    }; // class IEventListenerBase

    template<Pulse::Utility::CRTPConform Derived>
    class IEventListener : public IEventListenerBase {
    public:

        template <typename... Args>
        uint32_t AddListener(Event<Args...>& Event, void(Derived::* callback)(Args...)) {
            uint32_t eventListenerID = Event.AddListener(std::make_unique<EventListener<Derived, Args...>>(this, static_cast<Derived*>(this), callback));
            uint32_t eventID = Event.GetEventID();
            EventBase* eventPointer = &Event;

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = eventPointer;
            listenersAndEvents_[eventListenerID] = eventID;

            PLS_CORE_INFO("Listener {0} succesfully added to the event", eventListenerID);

#ifdef PLS_DEBUG
            PLS_CORE_INFO("Listener {0} succesfully added to the event {1}.", eventListenerID, eventID);
#endif // PLS_DEBUG

            return eventListenerID;
        }

    }; // class IEventListener

} // namespace Pulse::Events

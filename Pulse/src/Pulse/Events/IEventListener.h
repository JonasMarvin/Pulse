#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

    class PLS_API IEventListenerBase {
    public:
        
        void RemoveListener(EventListenerID eventListenerID);
        void OnEventRemoval(EventID eventID);

        virtual std::shared_ptr<IEventListenerBase> get_shared_from_this() = 0;

    protected:
        std::unordered_map<EventID, std::unordered_set<EventListenerID>> eventToListeners_;
        std::unordered_map<EventID, EventBase*> eventPointers_;
        std::unordered_map<EventListenerID, EventID> listenersAndEvents_;

    }; // class IEventListenerBase

    template<Pulse::Utility::CRTPConform Derived>
    class IEventListener : public IEventListenerBase, public std::enable_shared_from_this<Derived> {
    public:

        virtual ~IEventListener() {
            auto self_shared_ptr = this->get_shared_from_this();
            if (self_shared_ptr) {
                for (auto& eventIterator : eventPointers_) {
                    eventIterator.second->RemoveListener(self_shared_ptr, eventIterator.first);
                }
            }
        }

        template <typename... Args>
        EventListenerID AddListener(Event<Args...>& Event, void(Derived::* callback)(Args...)) {
            EventListenerID eventListenerID = Event.AddListener(get_shared_from_this(),std::make_unique<EventListenerMember<Derived, Args...>>(static_cast<Derived*>(this), callback));
            EventID eventID = Event.GetEventID();
            EventBase* eventPointer = &Event;

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = eventPointer;
            listenersAndEvents_[eventListenerID] = eventID;

            return eventListenerID;
        }

        template <typename... Args>
        EventListenerID AddListener(Event<Args...>& event, void(*callback)(Args...)) {
            EventListenerID eventListenerID = event.AddListener(get_shared_from_this(), std::make_unique<EventListenerNoMember<Args...>>(callback));
            EventID eventID = event.GetEventID();
            EventBase* eventPointer = &event;

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = eventPointer;
            listenersAndEvents_[eventListenerID] = eventID;

            return eventListenerID;
        }

        template <typename... Args, typename Functor>
        EventListenerID AddListener(Event<Args...>& event, Functor&& callback) {
            EventListenerID eventListenerID = event.AddListener(get_shared_from_this(), std::make_unique<EventListenerNoMember<Args...>>(std::forward<Functor>(callback)));
            EventID eventID = event.GetEventID();
            EventBase* eventPointer = &event;

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = eventPointer;
            listenersAndEvents_[eventListenerID] = eventID;

            return eventListenerID;
        }

        virtual std::shared_ptr<IEventListenerBase> get_shared_from_this() override {
            try {
                return std::static_pointer_cast<IEventListenerBase>(std::enable_shared_from_this<Derived>::shared_from_this());
            }
            catch (...) {
                return nullptr;
            }
        }

    }; // class IEventListener

} // namespace Pulse::Events

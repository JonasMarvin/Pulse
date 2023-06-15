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

        inline bool IsClean() const { return isClean_; }

    protected:
        std::unordered_map<EventID, std::unordered_set<EventListenerID>> eventToListeners_;
        std::unordered_map<EventID, std::shared_ptr<Internal::EventBase>> eventPointers_;
        std::unordered_map<EventListenerID, EventID> listenersAndEvents_;
        bool isClean_ = false;
    }; // class IEventListenerBase

    template<Pulse::Utility::CRTPConform Derived>
    class IEventListener : public IEventListenerBase, public std::enable_shared_from_this<Derived> {
    public:

        virtual ~IEventListener() {
			if (!isClean_) {
#pragma warning(push)
#pragma warning(disable: 4297)
                throw std::runtime_error("IEventListener is not clean. Please call Cleanup() before destroying the object."); // TODO: automate this in a parent script that is like MonoBehaviour in Unity
#pragma warning(pop)
            }
		}

        void Cleanup() {
            auto self_shared_ptr = this->get_shared_from_this();
            if (self_shared_ptr) {
                for (auto& eventIterator : eventPointers_) {
                    eventIterator.second->_RemoveListener(self_shared_ptr, eventIterator.first);
                }
            }
            isClean_ = true;
        }

        template <typename... Args>
        EventListenerID AddListener((std::shared_ptr<Internal::Event<Args...>> event, void(Derived::* callback)(Args...), bool isThreadsafe = false) {
            EventListenerID eventListenerID = event->_AddListener(get_shared_from_this(),std::make_shared<EventListenerMember<Derived, Args...>>(static_cast<Derived*>(this), callback, isThreadsafe));
            EventID eventID = event->_GetEventID();

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = event;
            listenersAndEvents_[eventListenerID] = eventID;

            return eventListenerID;
        }

        template <typename... Args>
        EventListenerID AddListener(std::shared_ptr<Internal::Event<Args...>> event, void(*callback)(Args...), bool isThreadsafe = false) {
            EventListenerID eventListenerID = event.AddListener(get_shared_from_this(), std::make_shared<EventListenerNoMember<Args...>>(callback, isThreadsafe));
            EventID eventID = event->_GetEventID();

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = event;
            listenersAndEvents_[eventListenerID] = eventID;

            return eventListenerID;
        }

        template <typename... Args, typename Functor>
        EventListenerID AddListener((std::shared_ptr<Internal::Event<Args...>> event, Functor&& callback, bool isThreadsafe = false) {
            EventListenerID eventListenerID = event.AddListener(get_shared_from_this(), std::make_shared<EventListenerNoMember<Args...>>(std::forward<Functor>(callback, isThreadsafe)));
            EventID eventID = event->_GetEventID();

            eventToListeners_[eventID].insert(eventListenerID);
            eventPointers_[eventID] = event;
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

    private:
        std::weak_ptr<Derived> selfWeakPointer_;

    }; // class IEventListener

} // namespace Pulse::Events

#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

    namespace Internal {
        
        class PLS_API IEventListenerBase {
        public:
            void _RemoveListener(EventListenerID eventListenerID);
            void _OnEventRemoval(std::weak_ptr<EventBase> eventID);

        protected:
            IEventListenerBase() = default;
            std::unordered_map<std::weak_ptr<EventBase>, EventListenerID, std::owner_less<std::weak_ptr<EventBase>>> eventToListeners_;
            std::unordered_map<EventListenerID, std::weak_ptr<EventBase>> listenersAndEvents_;

        }; // class IEventListenerBase

    } // namespace Internal
    

    template<Pulse::Utility::CRTPConform Derived>
    class IEventListener : public Internal::IEventListenerBase, public std::enable_shared_from_this<Derived> {
    public:
        virtual ~IEventListener();

        void _Cleanup();

        template <typename... Args>
        EventListenerID AddListener(std::shared_ptr<Event<Args...>> event, void(Derived::* callback)(Args...), bool isThreadsafe = false);

        template <typename... Args>
        EventListenerID AddListener(std::shared_ptr<Event<Args...>> event, void(*callback)(Args...), bool isThreadsafe = false);

        template <typename Functor, typename... Args>
        EventListenerID AddListener(std::shared_ptr<Event<Args...>> event, Functor&& callback, bool isThreadsafe = false);

        std::shared_ptr<Internal::IEventListenerBase> _get_shared_from_this() override;
    
    protected:
        IEventListener() = default;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
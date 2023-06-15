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
            void _OnEventRemoval(EventID eventID);

            virtual std::shared_ptr<IEventListenerBase> _get_shared_from_this() = 0;

        protected:
            IEventListenerBase() = default;

            bool IsClean() const;

            std::unordered_map<EventID, std::unordered_set<EventListenerID>> eventToListeners_;
            std::unordered_map<EventID, std::shared_ptr<Internal::EventBase>> eventPointers_;
            std::unordered_map<EventListenerID, EventID> listenersAndEvents_;
            bool isClean_ = false;

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

        virtual std::shared_ptr<Internal::IEventListenerBase> _get_shared_from_this() override;
    
    protected:
        IEventListener() = default;

    private:
        std::weak_ptr<Derived> selfWeakPointer_;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
#pragma once

#include <unordered_set>
#include <memory>

#include "Pulse/Events/Event.h"
#include "Pulse/Utility/Constraints.h"

namespace Pulse::Events {

    namespace Internal {

        class PLS_API IEventListenerBase : public std::enable_shared_from_this<IEventListenerBase> {
        public:
            virtual ~IEventListenerBase() = default;

            void _RemoveListenerFromUnorderedSet(const std::shared_ptr<EventListenerBase>& eventListener);
        protected:
            IEventListenerBase() = default;
            
            std::unordered_set<std::shared_ptr<EventListenerBase>> eventListeners_;

        }; // class IEventListenerBase

    } // namespace Internal

    template<Pulse::Utility::CRTPConform Derived>
    class IEventListener : public Internal::IEventListenerBase {
    public:
        ~IEventListener() override;

        template <typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, void(Derived::*callback)(Args...), bool isThreadsafe = false);

        template <typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, void(*callback)(Args...), bool isThreadsafe = false);

        template <typename Functor, typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Functor&& callback, bool isThreadsafe = false);
    
        template <typename... Args>
        void RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener);

    protected:
        IEventListener() = default;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
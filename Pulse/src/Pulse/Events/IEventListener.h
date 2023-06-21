#pragma once

#include <unordered_set>
#include <memory>
#include <type_traits>

#include "Pulse/Events/Event.h"

namespace Pulse::Events {

    namespace Internal {

        class PLS_API IEventListenerBase : public std::enable_shared_from_this<IEventListenerBase> {
        public:
            void _RemoveListenerFromUnorderedSet(const std::shared_ptr<EventListenerBase>& eventListener);

        protected:
            virtual ~IEventListenerBase() = default;
            IEventListenerBase() = default;

            std::unordered_set<std::shared_ptr<EventListenerBase>> eventListeners_;

        }; // class IEventListenerBase

    } // namespace Internal

    template<typename Derived>
    class IEventListener : public Internal::IEventListenerBase {
    public:
        template <typename Callable, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
        PLS_DOES_REQUIRE_OPTIONAL_TEMPLATE_ARGUMENT(Condition)
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback, Condition&& condition, bool isThreadsafe = false);
    
        template <typename Callable, PLS_OPTIONAL_TEMPLATE_ARGUMENT(Condition), typename... Args>
        PLS_DOES_NOT_REQUIRE_OPTIONAL_TEMPLATE_ARGUMENT(Condition)
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback, bool isThreadsafe = false);

        template <typename... Args>
        void RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener);

    protected:
        virtual ~IEventListener() override;
        IEventListener() = default;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
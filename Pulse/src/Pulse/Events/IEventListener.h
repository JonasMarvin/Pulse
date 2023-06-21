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
            IEventListenerBase();

            std::unordered_set<std::shared_ptr<EventListenerBase>> eventListeners_;

        }; // class IEventListenerBase

    } // namespace Internal

    template<typename Derived>
    class IEventListener : public Internal::IEventListenerBase {
    public:
        static std::shared_ptr<Derived> Create() {
            return std::make_shared<Derived>();
        }

        IEventListener(const IEventListener&) = delete;
        IEventListener& operator=(const IEventListener&) = delete;

        template <typename Callable, typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback, bool isThreadsafe = false);

        template <typename... Args>
        void RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener);

    protected:
        IEventListener() = default;
        virtual ~IEventListener() override;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
#pragma once

#include <unordered_set>
#include <memory>
#include <type_traits>

#include "Pulse/Events/Event.h"
#include "Pulse/Utility/Constraints.h"

namespace Pulse::Events {

    namespace Internal {

        class PLS_API IEventListenerBase : public std::enable_shared_from_this<IEventListenerBase> {
        public:
            virtual ~IEventListenerBase() noexcept = default;

            void _RemoveListenerFromUnorderedSet(const std::shared_ptr<EventListenerBase>& eventListener);

            template <typename Derived>
            Derived* _Self() noexcept;

        protected:
            IEventListenerBase() noexcept = default;

            std::unordered_set<std::shared_ptr<EventListenerBase>> eventListeners_;

        }; // class IEventListenerBase

    } // namespace Internal

    template<Derived>
    requires Pulse::Utility::CRTPConform<Internal::IEventListenerBase, Derived>
    class IEventListener : public Internal::IEventListenerBase {
    public:
        ~IEventListener() noexcept override;

        template <typename Callable, typename... Args>
        std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback, bool isThreadsafe = false);
    
        template <typename... Args>
        void RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener);

    protected:
        IEventListener() noexcept = default;

    }; // class IEventListener

} // namespace Pulse::Events

#include "Pulse/Events/IEventListener.tpp"
namespace Pulse::Events {

    template<typename Derived>
    IEventListener<Derived>::~IEventListener() {
        for (const auto& eventListener : eventListeners_) {
            eventListener->_RemoveFromEventBase();
        }
    }

    template<typename Derived>
    template <typename Callable, typename... Args>
    std::weak_ptr<EventListener<Args...>> IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback) {
        std::weak_ptr<Internal::IEventListenerBase> weakThis = this->weak_from_this();
        std::weak_ptr<Internal::EventBase> weakEventBase = event;
        std::shared_ptr<EventListener<Args...>> newEventListener;

        if constexpr (std::is_member_function_pointer_v<std::decay_t<Callable>>) {
            auto memberCallback = static_cast<decltype(callback)>(callback);
            newEventListener = std::make_shared<Internal::EventListenerMember<Derived, Args...>>(std::move(weakThis), std::move(weakEventBase), static_cast<Derived*>(this), std::forward<Callable>(memberCallback));
        }
        else {
            newEventListener = std::make_shared<Internal::EventListenerNoMember<std::decay_t<Callable>, Args...>>(std::move(weakThis), std::move(weakEventBase), std::forward<Callable>(callback));
        }

        event->_AddListener(newEventListener);
        eventListeners_.emplace(newEventListener);
        return std::weak_ptr<EventListener<Args...>>(newEventListener);
    }

    template<typename Derived>
    template <typename... Args>
    void IEventListener<Derived>::RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener) {
		auto sharedEventListener = eventListener.lock();
        if (sharedEventListener) {
            if (eventListeners_.find(sharedEventListener) != eventListeners_.end()) {
                sharedEventListener->_RemoveFromEventBase();
                eventListeners_.erase(sharedEventListener);
            }
		}
	}

} // namespace Pulse::Events
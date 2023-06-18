namespace Pulse::Events {

    template<Pulse::Utility::CRTPConform Derived>
    IEventListener<Derived>::~IEventListener() {
        for (const auto& eventListener : eventListeners_) {
			eventListener->_RemoveFromEventBase();
		}
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename... Args>
    std::weak_ptr<EventListener<Args...>> IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>>& event, void(Derived::* callback)(Args...), bool isThreadsafe) {
        std::weak_ptr<Internal::IEventListenerBase> weakThis = this->weak_from_this();
        std::weak_ptr<Internal::EventBase> weakEventBase = event;
        auto newEventListener = std::make_shared<Internal::EventListenerMember<Derived, Args...>>(std::move(weakThis), std::move(weakEventBase), static_cast<Derived*>(this), callback);  
        event->_AddListener(newEventListener, isThreadsafe);
        eventListeners_.emplace(newEventListener);
        return std::weak_ptr<EventListener<Args...>>(newEventListener);
    }

    template<Pulse::Utility::CRTPConform Derived>
    template<typename... Args>
    std::weak_ptr<EventListener<Args...>> IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>>& event, void (*callback)(Args...), bool isThreadsafe) {
        std::weak_ptr<Internal::IEventListenerBase> weakThis = this->weak_from_this();
        std::weak_ptr<Internal::EventBase> weakEventBase = event;
        auto newEventListener = std::make_shared<Internal::EventListenerNoMember<Args...>>(std::move(weakThis), std::move(weakEventBase), callback);
        event->_AddListener(newEventListener, isThreadsafe);
        eventListeners_.emplace(newEventListener);
        return std::weak_ptr<EventListener<Args...>>(newEventListener);
    }

    template <Pulse::Utility::CRTPConform Derived>
    template<typename Functor, typename... Args>
    std::weak_ptr<EventListener<Args...>> IEventListener<Derived>::AddListener(std::shared_ptr<Event<Args...>>& event, Functor&& callback, bool isThreadsafe) {
        std::weak_ptr<Internal::IEventListenerBase> weakThis = this->weak_from_this();
        std::weak_ptr<Internal::EventBase> weakEventBase = event;
        auto newEventListener = std::make_shared<Internal::EventListenerNoMember<Args...>>(std::move(weakThis), std::move(weakEventBase), std::forward<Functor>(callback));
        event->_AddListener(newEventListener, isThreadsafe);
        eventListeners_.emplace(newEventListener);
        return std::weak_ptr<EventListener<Args...>>(newEventListener);
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename... Args>
    void IEventListener<Derived>::RemoveListener(const std::weak_ptr<EventListener<Args...>>& eventListener) {
		auto sharedEventListener = eventListener.lock();
        if (sharedEventListener) {
			sharedEventListener->_RemoveFromEventBase();
			eventListeners_.erase(sharedEventListener);
		}
	}

} // namespace Pulse::Events
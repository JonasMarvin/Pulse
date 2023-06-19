namespace Pulse::Events {

    template<Pulse::Utility::CRTPConform Derived>
    IEventListener<Derived>::~IEventListener() {
        for (const auto& eventListener : eventListeners_) {
			eventListener->_RemoveFromEventBase();
		}
    }

    template <Pulse::Utility::CRTPConform Derived>
    template <typename Callable, typename... Args>
    std::weak_ptr<EventListener<Args...>> AddListener(std::shared_ptr<Event<Args...>>& event, Callable&& callback, bool isThreadsafe = false){
        std::weak_ptr<Internal::IEventListenerBase> weakThis = this->weak_from_this();
        std::weak_ptr<Internal::EventBase> weakEventBase = event;
        std::shared_ptr<Internal::EventListenerBase> newEventListener;

        if(constexpr(std::is_member_function_pointer_v<std::decay_t<Callable>>)){
            auto memberCallback = static_cast<decltype(Derived::callback)*>(callback);
            newEventListener = std::make_shared<Internal::EventListenerMember<Derived, Args...>>(std::move(weakThis), std::move(weakEventBase), static_cast<Derived*>(this), memberCallback, isThreadsafe);  
        }
        else{
            newEventListener = std::make_shared<Internal::EventListenerNoMember<std::decay_t<Callable>, Args...>>(std::move(weakThis), std::move(weakEventBase), std::forward<Callable>(callback), isThreadsafe);
        }

        event->_AddListener(newEventListener);
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
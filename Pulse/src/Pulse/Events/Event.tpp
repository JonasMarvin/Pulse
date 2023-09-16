namespace Pulse::Events{

    // Definition of the Create function
    template <typename... Args>
    std::shared_ptr<Event<Args...>> Event<Args...>::Create() {
        return std::make_shared<Event<Args...>>();
    }

    template<typename... Args>
    Event<Args...>::~Event() {
		for (const auto& eventListener : eventListeners_) {
			eventListener->_RemoveFromIEventListenerBase();
		}
	}

    template<typename... Args>
	void Event<Args...>::_AddListener(const std::shared_ptr<EventListener<Args...>>& eventListener) {
		eventListeners_.emplace(eventListener);
	}

    template<typename... Args>
	void Event<Args...>::_RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) {
        auto toBeRemovedEventListener = std::static_pointer_cast<EventListener<Args...>>(eventListener);
        eventListeners_.erase(toBeRemovedEventListener);
	}

    template<typename... Args>
    void Event<Args...>::RemoveAllListeners() {
        for (const auto& eventListener : eventListeners_) {
			eventListener->_RemoveFromIEventListenerBase();
		}
		eventListeners_.clear();
	}

    template<typename... Args>
    void Event<Args...>::Trigger(Args... args) {

        auto argsTupleForSt = std::make_tuple(std::forward<Args>(args)...);
        for (const auto& eventListener : eventListeners_) {
            std::apply(
                [eventListener](auto&&... args) {
                    eventListener->Invoke(std::forward<decltype(args)>(args)...);
                },
                argsTupleForSt
            );
        }
    }

    template<typename... Args>
	void UnsafeEvent<Args...>::AddListener(Internal::UnsafeEventListener<Args...>* eventListener){
        if(!eventListener){
            return;
        }
        eventListeners_.emplace(eventListener);
    }
	
    template<typename... Args>
    void UnsafeEvent<Args...>::RemoveListener(Internal::UnsafeEventListener<Args...>* eventListener){
        if(!eventListener){
            return;
        }
        eventListeners_.erase(eventListener);
    }

    template<typename... Args>
	void UnsafeEvent<Args...>::Trigger(Args... args){
        auto argsTupleForSt = std::make_tuple(std::forward<Args>(args)...);
        for (const auto& eventListener : eventListeners_) {
            std::apply(
                [eventListener](auto&&... args) {
                    eventListener->Invoke(std::forward<decltype(args)>(args)...);
                },
                argsTupleForSt
            );
        }
    }

} // namespace Pulse::Events
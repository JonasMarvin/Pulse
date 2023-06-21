#include <iostream>

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
        for (const auto& eventListener : multithreadedEventListeners_) {
			eventListener->_RemoveFromIEventListenerBase();
		}
        std::cout << "Destructor called" << std::endl;
	}

    template<typename... Args>
	void Event<Args...>::_AddListener(const std::shared_ptr<EventListener<Args...>>& eventListener) {
		eventListener->IsThreadsafe() ? multithreadedEventListeners_.emplace(eventListener) : eventListeners_.emplace(eventListener);
	}

    template<typename... Args>
	void Event<Args...>::_RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) {
        auto toBeRemovedEventListener = std::static_pointer_cast<EventListener<Args...>>(eventListener);
        if(toBeRemovedEventListener->IsThreadsafe()){
            multithreadedEventListeners_.erase(toBeRemovedEventListener);
        }
        else{
            eventListeners_.erase(toBeRemovedEventListener);
        }
	}

    template<typename... Args>
    void Event<Args...>::Trigger(Args... args) {
        if (!multithreadedEventListeners_.empty()) {
            auto argsTupleForMt = std::make_tuple(args...);
            std::apply(
                [this](auto&&... args) {
                    listenerPool_.Enqueue<Args...>(multithreadedEventListeners_, std::forward<decltype(args)>(args)...);
                },
                argsTupleForMt
            );
        }

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

    // Unsafe system:

    template<typename... Args>
	void UnsafeEvent<Args...>::AddListener(UnsafeEventListener<Args...>* eventListener){
        if(!eventListener){
            return;
        }
        
        eventListener->IsThreadsafe() ? multithreadedEventListeners_.emplace(eventListener) : eventListeners_.emplace(eventListener);
    }
	
    template<typename... Args>
    void UnsafeEvent<Args...>::RemoveListener(UnsafeEventListener<Args...>* eventListener){
        if(!eventListener){
            return;
        }

        if(eventListener->IsThreadsafe()){
            multithreadedEventListeners_.erase(eventListener);
        }
        else{
            eventListeners_.erase(eventListener);
        }
    }

    template<typename... Args>
	void UnsafeEvent<Args...>::Trigger(Args... args){
        if (!multithreadedEventListeners_.empty()) {
            auto argsTupleForMt = std::make_tuple(args...);
            std::apply(
                [this](auto&&... args) {
                    listenerPool_.Enqueue<Args...>(multithreadedEventListeners_, std::forward<decltype(args)>(args)...);
                },
                argsTupleForMt
            );
        }

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
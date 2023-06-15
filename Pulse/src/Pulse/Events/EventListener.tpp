namespace Pulse::Events {

    template <typename... Args>
	EventListener<Args...>::~EventListener() {
		eventIDManager_.FreeID(eventListenerID_);
	}
		
    template <typename... Args>
	uint32_t EventListener<Args...>::GetEventListenerID() const {
		return eventListenerID_;
	}

    template <typename... Args>
	bool EventListener<Args...>::IsThreadSafe() const {
		return isThreadSafe_;
	}

    template <typename... Args>
	void EventListener<Args...>::_SetEnqeuedInThread(bool isEnqeuedInThread) {
		isEnqeuedInThread_ = isEnqeuedInThread;
	}

    template <typename... Args>
	bool EventListener<Args...>::IsEnqeuedInThread() const {
		return isEnqeuedInThread_;
	}

	namespace Internal{

        template <typename T, typename... Args>
		void EventListenerMember<T, Args...>::Invoke(Args... args) {
			(objectInstance_->*callback_)(std::move(args)...);
		}
		
        template <typename... Args>
		void EventListenerNoMember<Args...>::Invoke(Args... args) {
			callback_(std::move(args)...);
		}

	} // namespace Internal

} // namespace Pulse::Events
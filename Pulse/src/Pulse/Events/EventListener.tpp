namespace Pulse::Events {

	namespace Internal{

        template <typename T, typename... Args>
		void EventListenerMember<T, Args...>::Invoke(Args... args) {
			(objectInstance_->*callback_)(std::forward<Args>(args)...);
		}
		
        template <typename Callable, typename... Args>
		void EventListenerNoMember<Args...>::Invoke(Args... args) {
			callback_(std::forward<Args>(args)...);
		}

	} // namespace Internal

	// Unsafe system:

	template <typename T, typename... Args>
	void UnsafeEventListenerMember<T, Args...>::Invoke(Args... args) {
		(objectInstance_->*callback_)(std::forward<Args>(args)...);
	}
		
    template <typename Callable, typename... Args>
	void UnsafeEventListenerNoMember<Args...>::Invoke(Args... args) {
		callback_(std::forward<Args>(args)...);
	}

	template<typename... Args>
	void UnsafeEventListener<Args...>::_SetEnqeuedInThread(const bool& enqueued) {
		isEnqeuedInThread_ = enqueued;
	}

	template<typename... Args>
	bool UnsafeEventListener<Args...>::IsEnqeuedInThread() const {
		return isEnqeuedInThread_;
	}

	template<typename... Args>
	bool UnsafeEventListener<Args...>::IsThreadsafe() const {
		return isThreadsafe_;
	}

	template<typename... Args>
	UnsafeEventListener<Args...>::~UnsafeEventListener(){
		if (IsEnqeuedInThread()) {
			while (IsEnqeuedInThread()) {
				std::this_thread::yield();
			}
		}
	}

} // namespace Pulse::Events
namespace Pulse::Events {

	namespace Internal{

        template <typename T, typename... Args>
		void EventListenerMember<T, Args...>::Invoke(Args... args) {
			(objectInstance_->*callback_)(std::forward<Args>(args)...);
		}
		
        template <typename Callable, typename... Args>
		void EventListenerNoMember<Callable, Args...>::Invoke(Args... args) {
			callback_(std::forward<Args>(args)...);
		}

	} // namespace Internal

	// Unsafe system:

	template <typename T, typename... Args>
	void UnsafeEventListenerMember<T, Args...>::Invoke(Args... args) {
		(objectInstance_->*callback_)(std::forward<Args>(args)...);
	}
		
    template <typename Callable, typename... Args>
	void UnsafeEventListenerNoMember<Callable, Args...>::Invoke(Args... args) {
		callback_(std::forward<Args>(args)...);
	}

	template<typename... Args>
	void UnsafeEventListener<Args...>::_SetEnqeuedInThread(const bool& enqueued) noexcept {
		isEnqeuedInThread_ = enqueued;
	}

	template<typename... Args>
	bool UnsafeEventListener<Args...>::IsEnqeuedInThread() const noexcept {
		return isEnqeuedInThread_;
	}

	template<typename... Args>
	bool UnsafeEventListener<Args...>::IsThreadsafe() const noexcept {
		return isThreadsafe_;
	}

	template<typename... Args>
	UnsafeEventListener<Args...>::~UnsafeEventListener() noexcept {
		if (IsEnqeuedInThread()) {
			while (IsEnqeuedInThread()) {
				std::this_thread::yield();
			}
		}
	}

} // namespace Pulse::Events
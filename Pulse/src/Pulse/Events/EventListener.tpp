namespace Pulse::Events {

	namespace Internal{

        template <typename T, typename Condition, typename... Args>
		void EventListenerMember<T, Condition, Args...>::Invoke(Args... args) {
			if constexpr (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(Condition)) {
				if (!condition_(std::forward<Args>(args)...)) {
					return;
				}
			}
			(objectInstance_->*callback_)(std::forward<Args>(args)...);
		}
		
        template <typename Callable, typename Condition, typename... Args>
		void EventListenerNoMember<Callable, Condition, Args...>::Invoke(Args... args) {
			if constexpr (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(Condition)) {
				if (!condition_(std::forward<Args>(args)...)) {
					return;
				}
			}
			callback_(std::forward<Args>(args)...);
		}

	} // namespace Internal

	// Unsafe system:

	template <typename T, typename Condition, typename... Args>
	void UnsafeEventListenerMember<T, Condition, Args...>::Invoke(Args... args) {
		if constexpr (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(Condition)) {
			if (!condition_(std::forward<Args>(args)...)) {
				return;
			}
		}
		(objectInstance_->*callback_)(std::forward<Args>(args)...);
	}
		
    template <typename Callable, typename Condition, typename... Args>
	void UnsafeEventListenerNoMember<Callable, Condition, Args...>::Invoke(Args... args) {
		if constexpr (PLS_OPTIONAL_TEMPLATE_ARGUMENT_EXISTS(Condition)) {
			if (!condition_(std::forward<Args>(args)...)) {
				return;
			}
		}
		callback_(std::forward<Args>(args)...);
	}

	template<typename... Args>
	void UnsafeEventListener<Args...>::_SetEnqeuedInThread(bool enqueued) {
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
	UnsafeEventListener<Args...>::~UnsafeEventListener() {
		if (IsEnqeuedInThread()) {
			while (IsEnqeuedInThread()) {
				std::this_thread::yield();
			}
		}
	}

} // namespace Pulse::Events
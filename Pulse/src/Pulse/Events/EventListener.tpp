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

	template <typename T, typename... Args>
	void UnsafeEventListenerMember<T, Args...>::Invoke(Args... args) {
		(objectInstance_->*callback_)(std::forward<Args>(args)...);
	}
		
    template <typename Callable, typename... Args>
	void UnsafeEventListenerNoMember<Callable, Args...>::Invoke(Args... args) {
		callback_(std::forward<Args>(args)...);
	}

} // namespace Pulse::Events
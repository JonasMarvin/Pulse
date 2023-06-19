namespace Pulse::Events {

	namespace Internal{

        template <typename T, typename... Args>
		void EventListenerMember<T, Args...>::Invoke(Args... args) {
			(objectInstance_->*callback_)(std::forward<Args>(args)...);
		}
		
        template <typename... Args>
		void EventListenerNoMember<Args...>::Invoke(Args... args) {
			callback_(std::forward<Args>(args)...);
		}

	} // namespace Internal

	// Unsafe system:

	template <typename T, typename... Args>
	void UnsafeEventListenerMember<T, Args...>::Invoke(Args... args) {
		(objectInstance_->*callback_)(std::forward<Args>(args)...);
	}
		
    template <typename... Args>
	void UnsafeEventListenerNoMember<Args...>::Invoke(Args... args) {
		callback_(std::forward<Args>(args)...);
	}

} // namespace Pulse::Events
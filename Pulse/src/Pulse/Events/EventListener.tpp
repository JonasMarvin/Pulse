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

} // namespace Pulse::Events
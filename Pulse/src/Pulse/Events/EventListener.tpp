#include <utility>

namespace Pulse::Events {

    template <typename... Args>
	EventListenerBase<Args...>::~EventListenerBase() {
		eventIDManager_.FreeID(eventListenerID_);
	}
		
    template <typename... Args>
	uint32_t EventListenerBase<Args...>::GetEventListenerID() const {
		return eventListenerID_;
	}

    template <typename... Args>
	bool EventListenerBase<Args...>::IsThreadSafe() const {
		return isThreadSafe_;
	}

    template <typename... Args>
	void EventListenerBase<Args...>::_SetEnqeuedInThread(bool isEnqeuedInThread) {
		isEnqeuedInThread_ = isEnqeuedInThread;
	}

    template <typename... Args>
	bool EventListenerBase<Args...>::IsEnqeuedInThread() const {
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
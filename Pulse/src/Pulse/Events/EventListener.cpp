#include "Pulse/Events/EventListener.h"

#include <thread>

#include "Pulse/Events/Event.h"
#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events::Internal {
	
	void EventListenerBase::_RemoveFromIEventListenerBase() {
		auto lockedIEventListenerBase_ = iEventListenerBase_.lock();
		if (lockedIEventListenerBase_) {
			if (this->IsEnqeuedInThread()) {
				while (this->IsEnqeuedInThread()) {
					std::this_thread::yield();
				}
			}
			lockedIEventListenerBase_->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

	void EventListenerBase::_RemoveFromEventBase() {
		auto lockedEventBase_ = eventBase_.lock();
		if (lockedEventBase_) {
			if (this->IsEnqeuedInThread()) {
				while (this->IsEnqeuedInThread()) {
					std::this_thread::yield();
				}
			}
			lockedEventBase_->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

	void EventListenerBase::_SetEnqeuedInThread(const bool& enqueued) {
		isEnqeuedInThread_ = enqueued;
	}

	bool EventListenerBase::IsEnqeuedInThread() const {
		return isEnqeuedInThread_;
	}

} // namespace Pulse::Events::Internal
#include "Pulse/Events/EventListener.h"

#include <thread>
#include <iostream>

#include "Pulse/Events/Event.h"
#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events::Internal {
	
	void EventListenerBase::_RemoveFromIEventListenerBase() {
		if (auto lockedIEventListenerBase = iEventListenerBase_.lock()) {
			if (IsEnqeuedInThread()) {
				while (IsEnqeuedInThread()) {
					std::this_thread::yield();
				}
			}
			std::cout << "Removing from IEventListenerBase" << std::endl;
			lockedIEventListenerBase->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

	void EventListenerBase::_RemoveFromEventBase() {
		if (auto lockedEventBase = eventBase_.lock()) {
			if (IsEnqeuedInThread()) {
				while (IsEnqeuedInThread()) {
					std::this_thread::yield();
				}
			}
			std::cout << "Removing from EventBase" << std::endl;
			lockedEventBase->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

	void EventListenerBase::_SetEnqueuedInThread(bool enqueued) {
		isEnqueuedInThread_ = enqueued;
	}

	bool EventListenerBase::IsEnqeuedInThread() const noexcept {
		return isEnqueuedInThread_;
	}

	bool EventListenerBase::IsThreadsafe() const noexcept {
		return isThreadsafe_;
	}

} // namespace Pulse::Events::Internal
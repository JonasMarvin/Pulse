#include "Pulse/Events/EventListener.h"

#include "Pulse/Events/Event.h"
#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events::Internal {
	
	void EventListenerBase::_RemoveFromIEventListenerBase() {
		if (auto lockedIEventListenerBase = iEventListenerBase_.lock()) {
			lockedIEventListenerBase->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

	void EventListenerBase::_RemoveFromEventBase() {
		if (auto lockedEventBase = eventBase_.lock()) {
			lockedEventBase->_RemoveListenerFromUnorderedSet(shared_from_this());
		}
	}

} // namespace Pulse::Events::Internal
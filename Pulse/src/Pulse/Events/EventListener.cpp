#include "Pulse/Events/EventListener.h"

#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events {

	void OnEventRemovalHandler::RemoveEventFromConnectedIEventListener(uint32_t eventID_) {
		if (auto iEventListenerBase = iEventListenerBase_.lock()) {
			iEventListenerBase->OnEventRemoval(eventID_);
		}
	}

} // namespace Pulse::Events
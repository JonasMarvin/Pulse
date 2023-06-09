#include "Pulse/Events/EventListener.h"

#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events {

	void OnEventRemovalHandler::RemoveEventFromConnectedIEventListener(uint32_t eventID_) {
		iEventListenerBase_->OnEventRemoval(eventID_);
	}

} // namespace Pulse::Events
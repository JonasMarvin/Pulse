#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events::Internal {

    void IEventListenerBase::_RemoveListenerFromUnorderedSet(const std::shared_ptr<EventListenerBase>& eventListener) {
        eventListeners_.erase(eventListener);
    }

} // namespace Pulse::Events::Internal
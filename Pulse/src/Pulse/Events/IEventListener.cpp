#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events {

    void IEventListenerBase::RemoveListener(EventListenerID eventListenerID) {
        auto iterator = listenersAndEvents_.find(eventListenerID);
        if (iterator != listenersAndEvents_.end()) {
            EventID eventID = iterator->second;
            listenersAndEvents_.erase(iterator);
            eventToListeners_[eventID].erase(eventListenerID);
            eventPointers_[eventID]->RemoveListener(get_shared_from_this(), eventListenerID);
            if (eventToListeners_[eventID].empty()) {
                eventPointers_.erase(eventID);
                eventToListeners_.erase(eventID);
            }
        }
    }

    void IEventListenerBase::OnEventRemoval(EventID eventID) {
        auto listenersIterator = eventToListeners_.find(eventID);
        if (listenersIterator != eventToListeners_.end()) {
            for (EventListenerID listenerID : listenersIterator->second) {
                listenersAndEvents_.erase(listenerID);
            }
            eventPointers_.erase(eventID);
            eventToListeners_.erase(listenersIterator);
        }
    }

} // namespace Pulse::Events
#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events {

    void IEventListenerBase::RemoveListener(uint32_t eventListenerID) {
        auto iterator = listenersAndEvents_.find(eventListenerID);
        if (iterator != listenersAndEvents_.end()) {
            uint32_t eventID = iterator->second;
            listenersAndEvents_.erase(iterator);
            eventToListeners_[eventID].erase(eventListenerID);
            eventPointers_[eventID]->RemoveListener(eventListenerID);
            if (eventToListeners_[eventID].empty()) {
                eventPointers_.erase(eventID);
                eventToListeners_.erase(eventID);
#ifdef PLS_DEBUG
                PLS_CORE_INFO("Event {1} succesfully removed from an IEventListener after the last listener {0} got removed.", eventListenerID, eventID);
                return;
#endif // PLS_DEBUG
            }
#ifdef PLS_DEBUG
            PLS_CORE_INFO("Listener {0} succesfully removed from event {1}.", eventListenerID, eventID);
#endif // PLS_DEBUG
        }
#ifdef PLS_DEBUG
        else {
            PLS_CORE_WARN("Tried to remove listener {0} from an IEventListener although it does not exist! Maybe it got deleted because the corresponding event got deleted.", eventListenerID);
        }
#endif // PLS_DEBUG
    }

    void IEventListenerBase::OnEventRemoval(uint32_t eventID) {

        auto listenersIterator = eventToListeners_.find(eventID);
        if (listenersIterator != eventToListeners_.end()) {
#ifdef PLS_DEBUG
            if (!eventToListeners_[eventID].empty()) {
                PLS_CORE_WARN("Removing event {0} from an IEventListener altough it still has listeners!", eventID);
            }
#endif // PLS_DEBUG
            for (uint32_t listenerID : listenersIterator->second) {
                listenersAndEvents_.erase(listenerID);
            }
            eventPointers_.erase(eventID);
            eventToListeners_.erase(listenersIterator);
#ifdef PLS_DEBUG
            PLS_CORE_INFO("Event {0} succesfully removed from an IEventListener.", eventID);
#endif // PLS_DEBUG
        }
#ifdef PLS_DEBUG
        else {
            PLS_CORE_WARN("Event {0} was already removed from an IEventListener.", eventID);
        }
#endif // PLS_DEBUG
    }

} // namespace Pulse::Events
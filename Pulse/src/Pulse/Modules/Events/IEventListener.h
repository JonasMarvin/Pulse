#pragma once

#include <vector>
#include <unordered_set>

#include "Pulse/Modules/Events/IEvent.h"
#include "Pulse/Utility/TypeConstraints.h"

namespace Pulse::Modules::Events {

    template<IsCRTPConform Derived>
    class IEventListener {
    public:
        // Declarations
        IEventListener() = default;
        inline virtual ~IEventListener();

        template <typename... Args>
        uint64_t AddListener(IEvent<Args...>& iEvent, void(Derived::* callback)(Args...));

        inline bool RemoveListener(uint64_t completeEventListenerID);

        inline virtual ~IEventListener() {
            // Remove in this classes declared Listeners from all Events
        }

        // Implementations
        template <typename... Args>
        uint64_t AddListener(IEvent<Args...>& iEvent, void(Derived::* callback)(Args...)) {
            uint32_t eventListenerID = iEvent.AddListener(std::make_unique<EventListener<Derived, Args...>>(static_cast<Derived*>(this), callback));
            uint32_t eventID = iEvent.GetEventID();
            uint64_t completeID = static_cast<uint64_t>(eventID) << 32 | eventListenerID;
            PLS_INFO(eventListenerID);
            PLS_INFO(eventID);
            PLS_INFO(completeID);
            completeEventListenerIDs_.insert(completeID);

            // TODO: Add to manager

            return completeID;
        }

        inline bool RemoveListener(uint64_t completeEventListenerID) {

            if (completeEventListenerIDs_.find(completeEventListenerID) != completeEventListenerIDs_.end()) {
                completeEventListenerIDs_.erase(completeEventListenerID);

                uint32_t eventID = static_cast<uint32_t>(completeEventListenerID >> 32);
                uint32_t listenerID = static_cast<uint32_t>(completeEventListenerID);
                PLS_INFO(completeEventListenerID);
                PLS_INFO(eventID);
                PLS_INFO(listenerID);
                // TODO: Remove from manager

                return true;
            }

            return false;
        }

    private:
        std::unordered_set<uint64_t> completeEventListenerIDs_;
    }; // class EventListener

} // namespace Pulse::Modules::Events

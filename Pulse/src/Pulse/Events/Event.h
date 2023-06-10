#pragma once

#include <unordered_map>
#include <memory>

#include "Pulse/Events/EventListener.h"

namespace Pulse::Events{

	class PLS_API EventBase {
	public:
		inline EventBase() : eventID_(eventIDManager_.GenerateID()) {}
		virtual inline ~EventBase() {
			eventIDManager_.FreeID(eventID_);
		};
		
		inline uint32_t GetEventID() const { 
			return eventID_;
		}

		virtual inline void RemoveListener(uint32_t eventListenerID) = 0;

	protected:
		uint32_t eventID_;

	private:
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class EventBase

	template <typename... Args>
	class Event : public EventBase{
	public:
		Event() {
#ifdef PLS_DEBUG
			PLS_CORE_INFO("Event {0} created.", eventID_);
#endif // PLS_DEBUG
		}

		virtual inline ~Event() {
			for(auto& eventListenerBase : eventListeners_) {
				eventListenerBase.second->RemoveEventFromConnectedIEventListener(eventID_);
			}
		}

		inline uint32_t AddListener(std::unique_ptr<EventListenerBase<Args...>> eventListener) {
			uint32_t newEventListenerID = eventListener->GetEventListenerID();
			eventListeners_[newEventListenerID] = std::move(eventListener);
			return newEventListenerID;
		}

		inline void RemoveListener(uint32_t eventListenerID) override {
			auto iterator = eventListeners_.find(eventListenerID);

			if (iterator != eventListeners_.end()) {
				eventListeners_.erase(iterator);
			}
#ifdef PLS_DEBUG
			else {
				PLS_CORE_WARN("Tried to remove non existing Listener {0} from event {1}!", eventListenerID, eventID_);
			}
#endif // PLS_DEBUG
		}

		inline void Trigger(Args... args) {
			for (auto& eventListener : eventListeners_) {
				eventListener.second->Invoke(args...);
			}
		}

	private:
		std::unordered_map<uint32_t, std::unique_ptr<EventListenerBase<Args...>>> eventListeners_;

	}; // class Event

} // namespace Pulse::Events
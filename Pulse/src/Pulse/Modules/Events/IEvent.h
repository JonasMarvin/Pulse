#pragma once

#include <unordered_map>
#include <memory>

#include "Pulse/Modules/Events/EventListener.h"

namespace Pulse::Modules::Events{

	template <typename... Args>
	class IEvent {
	public:
		inline IEvent() : eventID_(eventIDManager_.GenerateID()) {}
		virtual inline ~IEvent() {
			eventIDManager_.FreeID(eventID_);
		}

		inline uint32_t AddListener(std::unique_ptr<EventListenerBase<Args...>> eventListener) {
			uint32_t newEventListenerID = eventListener->GetEventListenerID();
			eventListeners_[newEventListenerID] = std::move(eventListener);
			return newEventListenerID;
		}

		inline bool RemoveListener(uint32_t eventListenerID) {
			auto iterator = eventListeners_.find(eventListenerID);
			if (iterator != eventListeners_.end()) {
				eventListeners_.erase(iterator);
				return true;
			}
			return false;
		}

		inline void Trigger(Args... args) {
			for (auto& eventListener : eventListeners_) {
				eventListener.second->Invoke(args...);
			}
		}

		inline uint32_t GetEventID() {
			return eventID_;
		}

	private:
		std::unordered_map<uint32_t, std::unique_ptr<EventListenerBase<Args...>>> eventListeners_;
		uint32_t eventID_;
		static inline Pulse::Utility::IDManager<uint32_t> eventIDManager_{};

	}; // class IEvent

} // namespace Pulse::Modules::Events
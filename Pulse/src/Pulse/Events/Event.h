#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "Pulse/Events/EventListener.h"
#include "Pulse/Core.h"

namespace Pulse::Events{

	class IEventListenerBase;

	class PLS_API EventBase {
	public:
		using ListenerCount = uint32_t;
		inline EventBase() : eventID_(eventIDManager_.GenerateID()) {}
		inline virtual ~EventBase() {
			eventIDManager_.FreeID(eventID_);
		};
		
		inline EventID GetEventID() const {
			return eventID_;
		}

		void RemoveEventFromConnectedIEventListeners();

		virtual void RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) = 0;
		void IncrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase);
		void DecrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase);

		struct WeakPtrHasher {
			std::size_t operator()(const std::weak_ptr<IEventListenerBase>& wp) const;
		};

		struct WeakPtrEqual {
			bool operator()(const std::weak_ptr<IEventListenerBase>& wp1, const std::weak_ptr<IEventListenerBase>& wp2) const;
		};

	protected:
		EventID eventID_;
		std::unordered_map<std::weak_ptr<IEventListenerBase>, ListenerCount, WeakPtrHasher, WeakPtrEqual> listeningIEventListeners_;

	private:
		static inline Pulse::Utility::IDManager<EventID> eventIDManager_{};

	}; // class EventBase

	template <typename... Args>
	class Event : public EventBase{
	public:
		virtual ~Event() {
			RemoveEventFromConnectedIEventListeners();
		}

		EventListenerID AddListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, std::unique_ptr<EventListenerBase<Args...>> eventListener) {
			IncrementListenerCount(iEventListenerBase);

			EventListenerID newEventListenerID = eventListener->GetEventListenerID();
			eventListeners_.emplace_back(newEventListenerID, std::move(eventListener));
			return newEventListenerID;
		}

		void RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) override {
			DecrementListenerCount(iEventListenerBase);

			auto eventListenerIterator = std::find_if(eventListeners_.begin(), eventListeners_.end(),
				[&](const auto& pair) { return pair.first == eventListenerID; });

			if (eventListenerIterator != eventListeners_.end()) {
				std::iter_swap(eventListenerIterator, eventListeners_.end() - 1);
				eventListeners_.pop_back();
			}
		}

		void Trigger(const Args&... args) {
			for (auto& [eventListenerID, eventListener] : eventListeners_) {
				if (eventListener->IsThreadSafe()) {

				}
				else {
					eventListener->Invoke(args...);
				}
			}
		}


	private:
		std::vector<std::pair<EventListenerID, std::unique_ptr<EventListenerBase<Args...>>>> eventListeners_;

	}; // class Event

} // namespace Pulse::Events
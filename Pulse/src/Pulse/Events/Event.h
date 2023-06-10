#pragma once

#include <unordered_map>
#include <memory>

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
			eventListeners_[newEventListenerID] = std::move(eventListener);
			return newEventListenerID;
		}

		void RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) override {
			DecrementListenerCount(iEventListenerBase);

			auto eventListenerIterator = eventListeners_.find(eventListenerID);
			if (eventListenerIterator != eventListeners_.end()) {
				eventListeners_.erase(eventListenerIterator);
			}
		}

		void Trigger(Args... args) {
			for (auto& eventListener : eventListeners_) {
				eventListener.second->Invoke(std::forward<Args>(args)...);
			}
		}

	private:
		std::unordered_map<EventListenerID, std::unique_ptr<EventListenerBase<Args...>>> eventListeners_;

	}; // class Event

} // namespace Pulse::Events
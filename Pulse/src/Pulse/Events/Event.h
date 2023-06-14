#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <utility>

#include "Pulse/Events/ListenerPool.h"
#include "Pulse/Core.h"

namespace Pulse::Events{

	class IEventListenerBase;

	template <typename... Args>
	std::unique_ptr<IEvent<Args...>> CreateEvent();

	template <typename... Args>
	class IEvent{
	public:
		virtual ~IEvent() = default;
		virtual void Trigger(Args... args) = 0;

	protected:
		IEvent() = default;

	} // class IEvent

	namespace Internal{

		class PLS_API EventBase {
		public:
			using ListenerCount = uint32_t;

			EventBase();
			virtual ~EventBase();
		
			EventID GetEventID() const;

			virtual void RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) = 0;
		
		protected:
			struct WeakPtrHasher {
				std::size_t operator()(const std::weak_ptr<IEventListenerBase>& wp) const;
			};

			struct WeakPtrEqual {
				bool operator()(const std::weak_ptr<IEventListenerBase>& wp1, const std::weak_ptr<IEventListenerBase>& wp2) const;
			};

			void IncrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase);
			void DecrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase);

			void RemoveEventFromConnectedIEventListeners();

			EventID eventID_;
			std::unordered_map<std::weak_ptr<IEventListenerBase>, ListenerCount, WeakPtrHasher, WeakPtrEqual> listeningIEventListeners_;

		private:
			static inline Pulse::Utility::IDManager<EventID> eventIDManager_{};

		}; // class EventBase

		template <typename... Args>
		class Event : public EventBase, public IEvent {
		public:
			virtual ~Event();

			EventListenerID AddListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, std::shared_ptr<EventListenerBase<Args...>> eventListener);
			void RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) override;
			void Trigger(Args... args) override;

		private:
			std::vector<std::pair<EventListenerID, std::shared_ptr<EventListenerBase<Args...>>>> eventListeners_;
			ListenerPool listenerPool_;

		}; // class Event
	
	} // namespace Internal

} // namespace Pulse::Events

#include "Pulse/Events/Event.tpp"
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

	namespace Internal{

		class PLS_API EventBase {
		public:
			using ListenerCount = uint32_t;

			virtual ~EventBase();
		
			EventID _GetEventID() const;

			virtual void _RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) = 0;
		
		protected:
			EventBase();

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
	
	} // namespace Internal

	template <typename... Args>
	class Event : public Internal::EventBase {
	public:
		virtual ~Event();

		static std::shared_ptr<Event<Args...>> Create();

		EventListenerID _AddListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, std::shared_ptr<EventListenerBase<Args...>> eventListener);
		void _RemoveListener(std::shared_ptr<IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) override;
		void Trigger(Args... args);

	private:
		Event() = default;
		std::vector<std::pair<EventListenerID, std::shared_ptr<EventListenerBase<Args...>>>> eventListeners_;
		Internal::ListenerPool listenerPool_;

	}; // class Event

} // namespace Pulse::Events

#include "Pulse/Events/Event.tpp"
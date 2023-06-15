#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <utility>

#include "Pulse/Events/ListenerPool.h"
#include "Pulse/Core.h"

namespace Pulse::Events{

	namespace Internal{

		class IEventListenerBase;

		class PLS_API EventBase {
		public:
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
			std::unordered_map<std::weak_ptr<IEventListenerBase>, size_t, WeakPtrHasher, WeakPtrEqual> listeningIEventListeners_;

		private:
			static inline Pulse::Utility::IDManager<EventID> eventIDManager_{};

		}; // class EventBase
	
	} // namespace Internal

	template <typename... Args>
	class Event : public Internal::EventBase {
	public:
		virtual ~Event();

		static std::shared_ptr<Event<Args...>> Create();

		EventListenerID _AddListener(std::shared_ptr<Internal::IEventListenerBase> iEventListenerBase, std::shared_ptr<EventListener<Args...>> eventListener);
		void _RemoveListener(std::shared_ptr<Internal::IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) override;
		void Trigger(Args... args);

	private:
		Event() = default;
		std::vector<std::pair<EventListenerID, std::shared_ptr<EventListener<Args...>>>> eventListeners_;
		Internal::ListenerPool listenerPool_;

	}; // class Event

	template <typename... Args>
	static std::shared_ptr<Event<Args...>> CreatePulseEvent();

} // namespace Pulse::Events

#include "Pulse/Events/Event.tpp"
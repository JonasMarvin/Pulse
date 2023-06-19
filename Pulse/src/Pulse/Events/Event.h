#pragma once

#include <memory>
#include <unordered_set>
#include <tuple>
#include <stdexcept>

#include "Pulse/Events/ListenerPool.h"

namespace Pulse::Events{

	namespace Internal {
		class PLS_API EventBase {
		public:
			virtual ~EventBase() = default;
			virtual void _RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) = 0;

		protected:
			EventBase() noexcept = default;

		}; // class EventBase
	} // namespace Internal

	template <typename... Args>
	class Event : public Internal::EventBase {
	public:
		Event() noexcept = default;
		~Event() override;

		static std::shared_ptr<Event<Args...>> Create();

		void _AddListener(const std::shared_ptr<EventListener<Args...>>& eventListener);
		void _RemoveListenerFromUnorderedSet(const std::shared_ptr<Internal::EventListenerBase>& eventListener) override;

		void Trigger(Args... args);

	private:
		std::unordered_set<std::shared_ptr<EventListener<Args...>>> eventListeners_;
		std::unordered_set<std::shared_ptr<EventListener<Args...>>> multithreadedEventListeners_;

		static inline Internal::ListenerPool listenerPool_{};

	}; // class Event

	// Unsafe system:

	template <typename... Args>
	class UnsafeEvent {
	public:
		UnsafeEvent() noexcept = default;
		~UnsafeEvent() noexcept = default;

		void AddListener(const UnsafeEventListener<Args...>* eventListener);
		void RemoveListener(const UnsafeEventListener<Args...>* eventListener);

		void Trigger(Args... args);

	private:
		std::unordered_set<UnsafeEventListener<Args...>*> eventListeners_;
		std::unordered_set<UnsafeEventListener<Args...>*> multithreadedEventListeners_;

		static inline Internal::ListenerPool listenerPool_{};

	}; // class UnsafeEvent

} // namespace Pulse::Events

#include "Pulse/Events/Event.tpp"
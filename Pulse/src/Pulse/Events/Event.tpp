#include <tuple>
#include <vector>
#include <memory>

namespace Pulse::Events{

    template<typename... Args>
    Event<Args...>::~Event() {
		RemoveEventFromConnectedIEventListeners();
	}

    template<typename... Args>
	EventListenerID Event<Args...>::_AddListener(std::shared_ptr<Internal::IEventListenerBase> iEventListenerBase, std::shared_ptr<EventListener<Args...>> eventListener) {
		IncrementListenerCount(iEventListenerBase);

		EventListenerID newEventListenerID = eventListener->GetEventListenerID();
		eventListeners_.emplace_back(newEventListenerID, eventListener);
		return newEventListenerID;
	}

    template<typename... Args>
	void Event<Args...>::_RemoveListener(std::shared_ptr<Internal::IEventListenerBase> iEventListenerBase, EventListenerID eventListenerID) {
		DecrementListenerCount(iEventListenerBase);

		auto eventListenerIterator = std::find_if(eventListeners_.begin(), eventListeners_.end(),
			[&](const auto& pair) { return pair.first == eventListenerID; });

		if (eventListenerIterator != eventListeners_.end()) {
			auto eventListener = eventListenerIterator->second;
				
			while (eventListener->IsEnqeuedInThread()) {
				std::this_thread::yield();
			}

			std::iter_swap(eventListenerIterator, eventListeners_.end() - 1);
			eventListeners_.pop_back();
		}
	}

    template<typename... Args>
	void Event<Args...>::Trigger(Args... args) {
		std::vector<std::shared_ptr<EventListener<Args...>>> batchedListeners;
		std::vector<std::tuple<Args...>> batchedArgs;

		for (auto& [eventListenerID, eventListener] : eventListeners_) {
			if (eventListener->IsThreadSafe()) {
					eventListener->_SetEnqeuedInThread(true);
					batchedListeners.push_back(eventListener);
					batchedArgs.push_back(std::make_tuple(args...));
			}
			else {
					eventListener->Invoke(args...);
			}
		}

			if (!batchedListeners.empty()) {
		listenerPool_.Enqueue(batchedListeners, batchedArgs);
		}
	}

	template <typename... Args>
	std::shared_ptr<Event<Args...>> Event<Args...>::Create() {
		auto deleter = [](Event<Args...>* pointer) { delete pointer; };
		return std::shared_ptr<Event<Args...>>(new Event<Args...>, deleter);
	}

	template <typename... Args>
	static std::shared_ptr<Event<Args...>> CreatePulseEvent() {
		return Event<Args...>::Create();
	}

} // namespace Pulse::Events
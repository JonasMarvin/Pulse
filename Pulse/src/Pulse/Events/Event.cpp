#include "Pulse/Events/Event.h"

#include "Pulse/Events/IEventListener.h"

namespace Pulse::Events {

	void EventBase::RemoveEventFromConnectedIEventListeners() {

		for (auto& [listener, id] : listeningIEventListeners_) {
			if (auto ptr = listener.lock()) {
				ptr->OnEventRemoval(eventID_);
			}
		}
	}

	void EventBase::IncrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase) {
		auto iterator = listeningIEventListeners_.find(iEventListenerBase);
		if (iterator != listeningIEventListeners_.end()) {
			iterator->second++;
		}
		else {
			listeningIEventListeners_[iEventListenerBase] = 1;
		}
	}

	void EventBase::DecrementListenerCount(const std::shared_ptr<IEventListenerBase>& iEventListenerBase) {
		auto listenerIterator = listeningIEventListeners_.find(iEventListenerBase);
		if (listenerIterator->second == 1) {
			listeningIEventListeners_.erase(listenerIterator);
		}
		else {
			listenerIterator->second--;
		}
	}

	std::size_t EventBase::WeakPtrHasher::operator()(const std::weak_ptr<IEventListenerBase>& wp) const {
		if (auto sp = wp.lock()) {
			return std::hash<std::shared_ptr<IEventListenerBase>>{}(sp);
		}
		else {
			return 0;
		}
	}

	bool EventBase::WeakPtrEqual::operator()(const std::weak_ptr<IEventListenerBase>& wp1, const std::weak_ptr<IEventListenerBase>& wp2) const {
		return wp1.lock() == wp2.lock();
	}

} // namespace Pulse::Events
#pragma once

#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <vector>
#include <tuple>

#include "Pulse/Events/EventListener.h"
#include "Pulse/Core.h"

namespace Pulse::Events::Internal {
	class PLS_API ListenerPool {
	public:
		ListenerPool(size_t threadCount = std::thread::hardware_concurrency());
		~ListenerPool();

        template <typename... Args>
        void Enqueue(std::vector<std::shared_ptr<EventListenerBase<Args...>>> eventListeners, std::vector<std::tuple<Args...>> argsList);
		
	private:
		std::vector<std::thread> threads_;
		std::queue<std::function<void()>> tasks_;
		std::condition_variable condition_;
		std::condition_variable conditionEmpty_;
		mutable std::mutex mutex_;
		size_t activeAndQueuedTasks_;
		bool isRunning_;

	}; // class ListenerPool

} // namespace Pulse::Events::Internal

#include "Pulse/Events/ListenerPool.tpp"
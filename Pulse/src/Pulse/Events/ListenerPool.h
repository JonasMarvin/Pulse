#pragma once

#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <unordered_set>
#include <tuple>

#include "Pulse/Events/EventListener.h"

namespace Pulse::Events::Internal {
	class PLS_API ListenerPool {
	public:
		ListenerPool();
		~ListenerPool();

        template <typename... Args>
        void Enqueue(std::unordered_set<std::shared_ptr<EventListener<Args...>>> eventListeners, Args... args);
		
		template <typename... Args>
        void Enqueue(std::unordered_set<UnsafeEventListener<Args...>>& eventListeners, Args... args);

	private:
		std::vector<std::thread> threads_;
		std::queue<std::function<void()>> tasks_;
		
		std::condition_variable condition_;
		std::condition_variable conditionEmpty_;
		mutable std::mutex mutex_;

		bool isClosing_ = false;

		const size_t threadCount_ = std::thread::hardware_concurrency();

	}; // class ListenerPool

} // namespace Pulse::Events::Internal

#include "Pulse/Events/ListenerPool.tpp"
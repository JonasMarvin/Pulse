#pragma once

#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>

#include "Pulse/Events/EventListener.h"
#include "Pulse/Core.h"

namespace Pulse::Events {
	class PLS_API ListenerPool {
	public:
		ListenerPool(size_t threadCount = std::thread::hardware_concurrency());
		~ListenerPool();

		
		template <typename... Args>
		void Enqueue(std::shared_ptr<EventListenerBase<Args...>> eventListener, Args... args) {
			eventListener->SetEnqeuedInThread(true);
			{
				std::unique_lock<std::mutex> lock(mutex_);
				++activeAndQueuedTasks_;
			}
			
			auto task = [this, eventListener, args...]() mutable {
				eventListener->Invoke(std::move(args)...);
				eventListener->SetEnqeuedInThread(false);

				{
					std::unique_lock<std::mutex> lock(mutex_);
					--activeAndQueuedTasks_;
					if (activeAndQueuedTasks_ == 0) {
						conditionEmpty_.notify_one();
					}
				}
			};

			{
				std::unique_lock<std::mutex> lock(mutex_);
				tasks_.emplace(std::move(task));
				condition_.notify_one();
			}
        }
		
	private:

		std::vector<std::thread> threads_;
		std::queue<std::function<void()>> tasks_;
		std::condition_variable condition_;
		std::condition_variable conditionEmpty_;
		mutable std::mutex mutex_;
		size_t activeAndQueuedTasks_;
		bool isRunning_;

	}; // class ListenerPool

} // namespace Pulse::Events
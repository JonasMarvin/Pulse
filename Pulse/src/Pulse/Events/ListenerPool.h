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

namespace Pulse::Events {
	class PLS_API ListenerPool {
	public:
		ListenerPool(size_t threadCount = std::thread::hardware_concurrency());
		~ListenerPool();

		
        template <typename... Args>
        void Enqueue(std::vector<std::shared_ptr<EventListenerBase<Args...>>> eventListeners, std::vector<std::tuple<Args...>> argsList) {
            {
                std::unique_lock<std::mutex> lock(mutex_);
                activeAndQueuedTasks_ += eventListeners.size();
            }

            for (size_t i = 0; i < eventListeners.size(); ++i) {
                auto& eventListener = eventListeners[i];
                auto& args = argsList[i];

                auto task = [this, eventListener, args]() mutable {
                    std::apply([eventListener](auto&&... args) { eventListener->Invoke(std::forward<decltype(args)>(args)...); }, args);

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
                }
            }

            condition_.notify_all();
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
#include "ListenerPool.h"

#include <mutex>
#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>

namespace Pulse::Events {
	ListenerPool::ListenerPool(size_t threadCount)
	: activeAndQueuedTasks_(0), isRunning_(true) {
		for (size_t i = 0; i < threadCount; ++i) {
			threads_.emplace_back([this]() {
				while (true) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(mutex_);
						condition_.wait(lock, [this]() {
							return !tasks_.empty() || !isRunning_;
						});
						if (!isRunning_ && tasks_.empty()) {
							return;
						}
						task = std::move(tasks_.front());
						tasks_.pop();
					}
					task();
				}
			});
		}
	}

	ListenerPool::~ListenerPool() {
		{
			std::unique_lock<std::mutex> lock(mutex_);
			isRunning_ = false;
		}
		condition_.notify_all();

		{
			std::unique_lock<std::mutex> lock(mutex_);
			conditionEmpty_.wait(lock, [this]() {return activeAndQueuedTasks_ == 0; });
		}

		for (std::thread &thread : threads_) {
			if (thread.joinable()) {
				thread.join();
			}
		}
	}

} // namespace Pulse::Events
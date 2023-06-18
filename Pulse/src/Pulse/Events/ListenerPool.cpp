#include "ListenerPool.h"

#include <mutex>
#include <functional>
#include <thread>
#include <condition_variable>
#include <queue>

namespace Pulse::Events::Internal {
	ListenerPool::ListenerPool() {
		for (size_t i = 0; i < threadCount_; ++i) {
			threads_.emplace_back([this]() {
				while (true) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(mutex_);
						condition_.wait(lock, [this]() {
							return !tasks_.empty() || isClosing_;
						});
						if (isClosing_) {
							return;
						}

						task = std::move(tasks_.front());
						tasks_.pop();
						conditionEmpty_.notify_one();
					}
					task();
				}
			});
		}
	}

	ListenerPool::~ListenerPool() {

		{
			std::unique_lock<std::mutex> lock(mutex_);
			isClosing_ = true;
			condition_.notify_all();
			conditionEmpty_.wait(lock, [this]() {
				return tasks_.empty();
			});
		}

		for (std::thread& thread : threads_) {
			if (thread.joinable()) {
				thread.join();
			}
		}
	}

} // namespace Pulse::Events::Internal
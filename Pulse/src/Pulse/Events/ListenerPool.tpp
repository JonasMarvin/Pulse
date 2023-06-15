namespace Pulse::Events::Internal {
        
    template <typename... Args>
    void Enqueue(std::vector<std::shared_ptr<EventListenerBase<Args...>>> eventListeners, std::vector<std::tuple<Args...>> argsList) {
        size_t threadBatchSize = eventListeners.size() / threads_.size();
        {
            std::unique_lock<std::mutex> lock(mutex_);
            activeAndQueuedTasks_ += eventListeners.size();
        }
        std::queue<std::function<void()>> tasks;
        for (size_t i = 0; i < eventListeners.size(); ++i) {
            auto& eventListener = eventListeners[i];
            auto& args = argsList[i];
            auto task = [eventListener, args]() mutable {
                std::apply([eventListener](auto&&... args) { eventListener->Invoke(std::forward<decltype(args)>(args)...); }, args);
            };

            tasks.emplace(std::move(task));
        }

        {
            std::unique_lock<std::mutex> lock(mutex_);
            while (!tasks.empty()) {
                tasks_.emplace(std::move(tasks.front()));
                tasks.pop();
            }
        }

        condition_.notify_all();
    }
    
} // namespace Pulse::Events::Internal
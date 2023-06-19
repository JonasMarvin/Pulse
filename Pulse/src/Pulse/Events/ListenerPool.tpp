namespace Pulse::Events::Internal {
        
    template <typename... Args>
    void ListenerPool::Enqueue(std::unordered_set<std::shared_ptr<EventListener<Args...>>> eventListeners, Args... args) {
        
        auto args_tuple = std::make_tuple(args...);

        std::queue<std::function<void()>> tasks;

        for (auto& eventListener : eventListeners) {
            eventListener->_SetEnqeuedInThread(true);
            auto task_args = args_tuple;
            auto task = [eventListener, task_args]() mutable {
                std::apply(
                    [eventListener](auto&&... args) {
                        eventListener->Invoke(std::forward<decltype(args)>(args)...);
                        eventListener->_SetEnqeuedInThread(false);
                    },
                    task_args
                );
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

    // Unsafe system:

    template <typename... Args>
    void ListenerPool::Enqueue(std::unordered_set<UnsafeEventListener<Args...>*> eventListeners, Args... args) {
        auto args_tuple = std::make_tuple(args...);

        std::queue<std::function<void()>> tasks;

        for (auto& eventListener : eventListeners) {
            eventListener->_SetEnqeuedInThread(true);
            auto task_args = args_tuple;
            auto task = [eventListener, task_args]() mutable {
                std::apply(
                    [eventListener](auto&&... args) {
                        eventListener->Invoke(std::forward<decltype(args)>(args)...);
                        eventListener->_SetEnqeuedInThread(false);
                    },
                    task_args
                );
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
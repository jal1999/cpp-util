#ifndef UTIL_EXECUTOR_H
#define UTIL_EXECUTOR_H

#include <future>
#include <thread>

namespace util {
    class Executor {
    public:
        Executor() = default;

        template <typename ReturnType, typename Callable, typename... Args>
        requires std::invocable<Callable, Args...>
        static std::future<ReturnType> submit(Callable task, Args... args)
        {
            return std::async(task, args...);
        }

        template <typename Callable, typename... Args>
        requires std::invocable<Callable, Args...>
        static void execute(Callable task, Args... args)
        {
            auto t = std::jthread{task, args...};
        }
    };
}

#endif

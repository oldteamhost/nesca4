/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#ifndef NESCA_THREAD_H
#define NESCA_THREAD_H

#include <functional>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

class thread_pool{
public:
  explicit thread_pool(size_t numThreads);

  /*Реализация enqueue тут потому что компилятор жалуется.*/
  template <class F, class... Args>
  auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> result = task->get_future();
    {
      std::unique_lock<std::mutex> lock(queueMutex);
      if (stop){throw std::runtime_error("enqueue on stopped ThreadPool");}
      tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return result;
  }

  ~thread_pool();

private:
  std::vector<std::thread> workers;
  std::queue<std::function<void()>> tasks;

  std::mutex queueMutex;
  std::condition_variable condition;

  bool stop;
};

#endif


/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ThreadPool
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

namespace RType {
  namespace Server {
    class ThreadPool {
      public:
        ThreadPool(size_t nb);
        void InitThreadPool();
        void CloseThreadPool();
        void AddTask(const std::function<void()>& job);
        size_t GetRunning();
        size_t GetTaskRemaining();
      private:
        void ThreadMain();
        size_t _nb_of_threads = 0;
        size_t _running = 0;
        std::vector<std::thread> _threads;
        std::condition_variable mutex_c;
        std::queue<std::function<void()>> _tasks;
        std::mutex queue_mutex;
        bool close_all = false;
    };
  }
}

#endif /* !THREADPOOL_HPP_ */

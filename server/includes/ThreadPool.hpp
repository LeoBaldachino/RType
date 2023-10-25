/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ThreadPool.hpp
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
    /**
     * @class ThreadPool
     * @brief Class to manage a pool of threads
     * 
     * This class is used to manage a pool of threads for the server.
     */
    class ThreadPool {
      public:
        /**
         * @brief Construct a new ThreadPool object
         * 
         * @param nb The number of threads in the pool
         */
        ThreadPool(size_t nb);
        /**
         * @brief Initialize the ThreadPool
         */
        void InitThreadPool();
        /**
         * @brief Close the ThreadPool
         */
        void CloseThreadPool();
        /**
         * @brief Add a task to the ThreadPool
         * 
         * @param job The function to be executed by the thread
         */
        void AddTask(const std::function<void()>& job);
        /**
         * @brief Get the number of running threads
         * 
         * @return size_t The number of running threads
         */
        size_t GetRunning();
        /**
         * @brief Get the number of remaining tasks
         * 
         * @return size_t The number of remaining tasks
         */
        size_t GetTaskRemaining();
      private:
        /**
         * @brief Main function for the thread
         */
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
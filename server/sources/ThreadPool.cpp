/*
** EPITECH PROJECT, 2023
** B-CCP-400-MLH-4-1-theplazza-younes.boufrioua
** File description:
** RType::Server::ThreadPool
*/

#include "../includes/ThreadPool.hpp"

RType::Server::ThreadPool::ThreadPool(size_t nb)
{
    this->_nb_of_threads = nb;
}

void RType::Server::ThreadPool::InitThreadPool() {
    this->_threads.resize(this->_nb_of_threads);
    for (size_t i = 0; i < this->_nb_of_threads; i++)
        this->_threads[i] = std::thread(&RType::Server::ThreadPool::ThreadMain, this);
}

void RType::Server::ThreadPool::CloseThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        this->close_all = true;
    }
    this->mutex_c.notify_all();
    for (int i = 0; i < this->_threads.size(); i++)
        this->_threads[i].join();
    this->_threads.clear();
}

void RType::Server::ThreadPool::ThreadMain()
{
    bool ex = false;
    while (1) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if (ex)
                this->_running -= 1;
            this->mutex_c.wait(lock, [this] {
                return !this->_tasks.empty() || this->close_all;
            });
            if (this->close_all)
                return;
            task = this->_tasks.front();
            this->_tasks.pop();
            this->_running += 1;
            ex = true;
        }
        task();
    }
}

void RType::Server::ThreadPool::AddTask(const std::function<void()>& job) {
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->_tasks.push(job);
    }
    mutex_c.notify_one();
}

size_t RType::Server::ThreadPool::GetTaskRemaining()
{
    return (this->_tasks.size());
}


size_t RType::Server::ThreadPool::GetRunning()
{
    return (this->_running);
}

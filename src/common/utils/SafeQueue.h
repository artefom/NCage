//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_SAFEQUEUE_H
#define PLAYIN_SAFEQUEUE_H


#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>

template<class T> class SafeQueue
{
public:
    SafeQueue(void)
            : q()
            , m()
            , c()
    {}

    ~SafeQueue(void)
    {}

    inline unsigned long long int size() {
        return q.size();
    }

    // Add an element to the queue.
    void enqueue(T t)
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(t);
        c.notify_one();
    }

    // Get the "front"-element.
    // If the queue is empty, wait till a element is avaiable.
    T dequeue(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while(q.empty())
        {
            // release lock as long as the wait and reaquire it afterwards.
            c.wait(lock);
        }
        T val = q.front();
        q.pop();
        return val;
    }

private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};
#endif


#endif //PLAYIN_SAFEQUEUE_H

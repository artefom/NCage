//
// Created by artef on 25.01.2017.
//

#ifndef PLAYIN_THREAD_FACTORY_H
#define PLAYIN_THREAD_FACTORY_H


#include <thread>
#include <iostream>
#include <mutex>
#include <windows.h>
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
int manager_thread(T**, std::mutex*, std::condition_variable* cv, std::queue< void (T::*)() >* );

template<class T>
int manager_thread(T** ref, std::mutex* m_ptr, std::condition_variable* cv_ptr,  std::queue< void (T::*)() >*  events_ptr ) {

    std::condition_variable& cv = *cv_ptr;
    std::mutex& m = *m_ptr;
    std::queue< void (T::*)() >& events = *events_ptr;

    // Initializing new class instance in thread stack
    T instance;

    {
        std::unique_lock<std::mutex> lk(m);
        *ref = &instance;
    }
    // Releasing mutex to allow AsyncClassManager continue
    cv.notify_all();

    std::cout << "Thread listening for events!" << std::endl;

    while (true) {

        std::unique_lock<std::mutex> lk(m);
        //std::cout << "Waiting for event!" << std::endl;
        if (events.size() == 0) {
            cv.wait(lk, [events_ptr] { return events_ptr->size() > 0; });
        }
        //std::cout << "event found!" << std::endl;

        while (events.size() > 0) {
            void (T::*e)() = events.front();
            events.pop();

            // Check for posion pill
            if (e == 0) {
                //std::cout << "Found NULL!" << std::endl;
                goto end_label;
            } else {
                //std::cout << "Not null event found!" << std::endl;
                // Call something
                (instance.*e)();
            }
        }

    }
    end_label:;
    std::cout << "Thread finished!" << std::endl;

    {
        std::unique_lock<std::mutex> lk(m);
        *ref = 0;    }
    cv.notify_all();

    return 0;
}

template<class T>
class AsyncClassManager {
public:

    AsyncClassManager() : c(0), t(manager_thread<T>,&c,&m,&cv,&events) {

        t.detach();
        {
            std::unique_lock<std::mutex> lk(m);
            // Wait for thread creating c!
            cv.wait(lk,[this]{return c!=0;});
        }

        std::cout << "AsyncManager Initialized!" << std::endl;
    }

    ~AsyncClassManager() {

        std::cout << "Destroying AsyncManager!" << std::endl;
        {
            std::unique_lock<std::mutex> lk(m);
            std::cout << "Pushing 0!" << std::endl;
            events.push(0);
        }

        cv.notify_all();
        std::cout << "Waiting for thread to finish!" << std::endl;

        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [this] { return c == 0; });
        }

        std::cout << "AsyncManager Destroyed!" << std::endl;
        //t.join();
    }

    void call( void (T::*method)(void) ) {
        std::unique_lock<std::mutex> lk(m);
        events.push(method);
        lk.unlock();
        cv.notify_all();
    }

private:

    // Event queue

    // Condition variable for notifying if thread was created or dead;
    std::condition_variable cv;

    std::queue< void (T::*)() >  events;

    std::mutex m;

    std::thread t;

    T* c;
};

//template<class T>
//AsyncClassManager<T> create_async_class() {
//    AsyncClassManager<T> ret{};
//    return ret;
//}


#endif //PLAYIN_THREAD_FACTORY_H

//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_EVENT_H
#define PLAYIN_EVENT_H

#include <vector>
#include <iostream>

template<class T>
class Event {
public:

    std::vector<T> storage;

    void operator()() {
        for (T& v : storage) {
            v();
        }
    }

    template<class A1>
    void operator()(A1 arg1) {
        for (T& v : storage) {
            v(arg1);
        }
    }

    template<class A1, class A2>
    void operator()(A1 arg1, A2 arg2) {
        for (T& v : storage) {
            v(arg1,arg2);
        }
    }

    void add(T func) {
        storage.push_back(func);
    }

};


#endif //PLAYIN_EVENT_H

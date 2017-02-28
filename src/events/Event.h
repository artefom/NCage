//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_EVENT_H
#define PLAYIN_EVENT_H

#include <vector>
#include <iostream>
#include <functional>
#include <memory>

template<class T>
class Event {
public:

    std::vector< T > storage;
    std::vector< std::pair< std::weak_ptr<void>, T> > weak_storage;

    void operator()() {
        for (T& v : storage) {
            v();
        }

        for (std::pair<std::weak_ptr<void>, T >& p : weak_storage) {

            std::weak_ptr<void>& w_ptr = p.first;
            T& v = p.second;

            std::shared_ptr<void> ptr = w_ptr.lock();
            if (ptr) {
                v();
            };

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

    template<class M, class C1, class C2>
    inline void connect_weak(M m, std::weak_ptr<C1> w_ptr, C2 c) {

        add_weak(std::bind( m, c ),w_ptr);

    }

    template<class M, class C1, class C2, class A1>
    inline void connect_weak(M m, std::weak_ptr<C1> w_ptr, C2 c, A1 a1) {

        add_weak(std::bind( m, c, a1 ),w_ptr);

    }

public:

    void add(T func) {
        storage.push_back(func);
    }

    void add_weak(T func, std::weak_ptr<void> ptr) {

        weak_storage.push_back( std::pair<std::weak_ptr<void>, T>(ptr,func) );
    }

};


#endif //PLAYIN_EVENT_H

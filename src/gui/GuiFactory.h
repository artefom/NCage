//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIFACTORY_H
#define PLAYIN_GUIFACTORY_H


#include <memory>
#include <iostream>

class GuiFactory {
public:

    template<class T> static std::shared_ptr<T> create(){

        T* raw_ptr = reinterpret_cast<T*>( new char[sizeof(T)] );

        std::shared_ptr<T> ret = std::shared_ptr<T>(raw_ptr);

        new (ret.get()) T( move( std::weak_ptr<T>(ret) ) );

        return ret;

    }

    template<class T, class A1> static std::shared_ptr<T> create(A1 arg1){

            T* raw_ptr = reinterpret_cast<T*>( new char[sizeof(T)] );

            std::shared_ptr<T> ret = std::shared_ptr<T>(raw_ptr);

            new (ret.get()) T( move( std::weak_ptr<T>(ret) ), arg1 );

            return ret;

    }

};


#endif //PLAYIN_GUIFACTORY_H

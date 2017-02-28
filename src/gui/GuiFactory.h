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

        std::shared_ptr<T> ret = std::make_shared<T>();

        ret->setSelf(ret);

        ret->postInit();

        return ret;

    }

};


#endif //PLAYIN_GUIFACTORY_H

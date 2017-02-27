//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_GUIBASE_H
#define PLAYIN_GUIBASE_H

#include <memory>
#include <vector>

#include <functional>
#include <Vec2d.h>
#include <iostream>
#include "Event.h"


class GuiBase {
private:

    Vec2d pos_min;

    Vec2d pos_max;

    GuiBase* parent;

public:

    Event< std::function< void( Vec2d )  > > MouseMoveEvent;
    Event< std::function< void(int, int, Vec2d ) > > MouseEvent;
    Event< std::function< void() > > AfterResizeEvent;
    Event< std::function< void() > > MouseEnterEvent;
    Event< std::function< void() > > MouseLeaveEvent;

    GuiBase();


    inline GuiBase *getParent() const {
        return parent;
    }

    inline void setParent(GuiBase *i_parent) {
        parent = i_parent;
    }

    inline Vec2d getPositionMin() const {
        return pos_min;
    }

    inline Vec2d getPositionMax() const {
        return pos_max;
    }

    inline Vec2d getSize() const {
        return pos_max-pos_min;
    }

    inline void setPositionMin(Vec2d position) {
        beforeResize();
        Vec2d size = getSize();
        pos_min = position;
        pos_max = pos_min + size;
        afterResize();
    }

    inline void setPositionMax(Vec2d position) {
        beforeResize();
        Vec2d size = getSize();
        pos_max = position;
        pos_min = pos_max-size;
        afterResize();
    }

    inline void setSizeMin(Vec2d size) {
        beforeResize();
        pos_max = pos_min+size;
        afterResize();
    }

    inline void setSizeMax(Vec2d size) {
        beforeResize();
        pos_min = pos_max-size;
        afterResize();
    }

    virtual void beforeResize();

    virtual void afterResize();

    virtual void draw();

    // Mouse event in relative coordinates
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {

    }

    // Event when mouse moves over gui
    virtual void OnMouseMove(Vec2d mousePos) {

    }

    // Estimates weather mouse lies within current gui
    // Mousepos is in local coordinates
    virtual bool hasMouse(Vec2d mousepos) {
        if (mousepos.x < getSize().x && mousepos.x > 0 &&
            mousepos.y < getSize().y && mousepos.y > 0)
            return true;
        return false;
    }

    virtual ~GuiBase() {};
};


#endif //PLAYIN_GUIBASE_H
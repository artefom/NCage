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
#include <utils/glutUtils.h>
#include "Event.h"


class GuiBase {
private:

    Vec2d pos_min;

    Vec2d pos_max;

    GuiBase* parent;

public:

    std::weak_ptr<GuiBase> self;

    Event< std::function< void( Vec2d )  > > MouseMoveEvent;
    Event< std::function< void(int, int, Vec2d ) > > MouseEvent;
    Event< std::function< void() > > AfterResizeEvent;
    Event< std::function< void() > > MouseEnterEvent;
    Event< std::function< void() > > MouseLeaveEvent;

    Event< std::function< void() > > UpdateEvent;

    bool should_update;

    GuiBase(const std::weak_ptr<GuiBase>&& i_self);

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
        //beforeResize();
        Vec2d size = getSize();
        pos_min = position;
        pos_max = pos_min + size;
        //afterResize();
    }

    inline void setPositionMax(Vec2d position) {
        //beforeResize();
        Vec2d size = getSize();
        pos_max = position;
        pos_min = pos_max-size;
        //afterResize();
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

    virtual void pushBuffer() {

    };

    virtual void draw();

    virtual void popBuffer() {

    };

    virtual void Update();

    virtual void drawBuffered();

    // Mouse event in relative coordinates
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    // Event when mouse moves over gui
    virtual void OnMouseMove(Vec2d mousePos);

    virtual void OnMouseEnter();

    virtual void OnMouseLeave();

    // Estimates weather mouse lies within current gui
    // Mousepos is in local coordinates
    virtual bool hasMouse(Vec2d mousepos);

    virtual ~GuiBase() {};
};


#endif //PLAYIN_GUIBASE_H

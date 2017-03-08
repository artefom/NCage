//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIBUTTON_H
#define PLAYIN_GUIBUTTON_H

#include <resources/constants.h>
#include <functional>

#include "GuiBase.h"
#include "Event.h"


class GuiButton : public GuiBase {

public:

    Event< std::function< void() > > MouseClickEvent;

    GuiButton(const std::weak_ptr<GuiButton> &&i_self);

    virtual void draw();

    virtual void OnClick();

    virtual void OnMouseEnter();

    virtual void OnMouseLeave();

    // Mouse event in relative coordinates
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);


protected:

    bool isPressed;
    bool isHovered;

};


#endif //PLAYIN_GUIBUTTON_H

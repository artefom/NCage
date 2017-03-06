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

    GuiButton( ) {

        isPressed = false;
        isHovered = false;

       // MouseClickEvent.connect_weak(&GuiButton::OnClick, self, this);
//        MouseClickEvent.connect(&GuiButton::hello, this, 1);
        //MouseClickEvent.add( std::bind(&GuiButton::OnClick, this ) );
    }

    virtual void postInit() {
        GuiBase::postInit();
        MouseClickEvent.connect_weak(&GuiButton::OnClick, self, this);
    }

    virtual void draw() {
        if (isPressed && isHovered) {
            glColor(constants::gui_button_pressed);
        } else
        if (!isPressed && isHovered){
            glColor(constants::gui_button_hover);
        } else {
            glColor(constants::gui_frame_foreground);
        }

        drawRect(Vec2d::ZERO,getSize());

        glColor(constants::gui_frame_accent1);

        drawHRect(Vec2d::ZERO,getSize());

    }

    virtual void OnClick() {
        std::cout << "Hello, i'm button!" << std::endl;
    }

    virtual void OnMouseEnter() {
        isHovered = true;
        Update();
    }

    virtual void OnMouseLeave() {
        isHovered = false;
        Update();
    }

    // Mouse event in relative coordinates
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {

        GuiBase::OnMouseEvent(button,state,mousePos);
        // Right mouse down
        if (button == 0) {
            if (state == 0) {
                // Mouse down case
                isPressed = true;
            } else {
                // Mouse up case

                if (isPressed && isHovered) {
                    MouseClickEvent();
                }

                isPressed = false;
            }
            Update();
        }

    }


protected:

    bool isPressed;
    bool isHovered;

};


#endif //PLAYIN_GUIBUTTON_H

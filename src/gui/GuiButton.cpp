//
// Created by artef on 27.02.2017.
//

#include "GuiButton.h"

GuiButton::GuiButton(const std::weak_ptr<GuiButton> &&i_self) : GuiBase(i_self) {

    isPressed = false;
    isHovered = false;

    MouseClickEvent.connect_weak(&GuiButton::OnClick, self, this);

    // MouseClickEvent.connect_weak(&GuiButton::OnClick, self, this);
//        MouseClickEvent.connect(&GuiButton::hello, this, 1);
    //MouseClickEvent.add( std::bind(&GuiButton::OnClick, this ) );
}

void GuiButton::draw() {
    if (isPressed && isHovered) {
        glColor(constants::gui_button_pressed);
    } else if (!isPressed && isHovered) {
        glColor(constants::gui_button_hover);
    } else {
        glColor(constants::gui_frame_foreground);
    }

    drawRect(Vec2d::ZERO, getSize());

    glColor(constants::gui_frame_accent1);

    drawHRect(Vec2d::ZERO, getSize());

}

void GuiButton::OnClick() {
    std::cout << "Hello, i'm button!" << std::endl;
}

void GuiButton::OnMouseEnter() {
    isHovered = true;
    Update();
}

void GuiButton::OnMouseLeave() {
    isHovered = false;
    Update();
}

void GuiButton::OnMouseEvent(int button, int state, Vec2d mousePos) {

    GuiBase::OnMouseEvent(button, state, mousePos);
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

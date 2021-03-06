//
// Created by artef on 27.02.2017.
//

#include <Logger.h>
#include <render/RenderManager.h>
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
        RenderManager::color(constants::gui_button_pressed);
    } else if (!isPressed && isHovered) {
        RenderManager::color(constants::gui_button_hover);
    } else {
        RenderManager::color(constants::gui_frame_background);
    }

    RenderManager::drawrect(Vec2d::ZERO, getSize());

    RenderManager::color(constants::gui_frame_accent1);

    RenderManager::drawhrect(Vec2d::ZERO, getSize());

}

void GuiButton::OnClick() {
    Logger::info("Button pressed!");
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
    if (button == GLFW_MOUSE_BUTTON_1) {
        if (state == GLFW_PRESS) {
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

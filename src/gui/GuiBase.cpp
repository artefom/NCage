//
// Created by artef on 27.01.2017.
//

#include "GuiBase.h"

GuiBase::GuiBase() :
        pos_min(0,0),
        pos_max(0,0),
        parent(0) {

}

void GuiBase::beforeResize() {

}

void GuiBase::afterResize() {

}

void GuiBase::draw() {

}

void GuiBase::OnMouseEvent(int button, int state, Vec2d mousePos) {

}

void GuiBase::postInit() {}

void GuiBase::OnMouseMove(Vec2d mousePos) {

}

void GuiBase::OnMouseEnter() {
    MouseEnterEvent();
}

void GuiBase::OnMouseLeave() {
    MouseLeaveEvent();
}

bool GuiBase::hasMouse(Vec2d mousepos) {
    if (mousepos.x < getSize().x && mousepos.x > 0 &&
        mousepos.y < getSize().y && mousepos.y > 0)
        return true;
    return false;
}

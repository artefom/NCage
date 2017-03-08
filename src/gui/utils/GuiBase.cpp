//
// Created by artef on 27.01.2017.
//

#include "GuiBase.h"

GuiBase::GuiBase(const std::weak_ptr<GuiBase>&& i_self) :
        self(i_self),
        pos_min(0,0),
        pos_max(0,0),
        parent(0),
        should_update(true) {

}

void GuiBase::beforeResize() {

}

void GuiBase::afterResize() {

}

void GuiBase::draw() {
    should_update = false;
}

void GuiBase::OnMouseEvent(int button, int state, Vec2d mousePos) {

}

void GuiBase::OnMouseMove(Vec2d mousePos) {

}

void GuiBase::OnMouseEnter() {
    MouseEnterEvent();
}

void GuiBase::OnMouseLeave() {
    MouseLeaveEvent();
}

bool GuiBase::hasMouse(Vec2d mousepos) {
    return mousepos.x < getSize().x && mousepos.x >= 0 &&
           mousepos.y < getSize().y && mousepos.y >= 0 &&
           mousepos.x < getSize().x && mousepos.x >= 0 &&
           mousepos.y < getSize().y && mousepos.y >= 0;
}

void GuiBase::Update() {
    if (should_update == false) {
        should_update = true;
        UpdateEvent();
    }
}

void GuiBase::drawBuffered() {
    should_update = false;
    draw();
}

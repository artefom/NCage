//
// Created by artef on 27.02.2017.
//

#include <Logger.h>
#include "GuiWindow.h"

GuiWindow::CloseButton::CloseButton(const std::weak_ptr<GuiWindow::CloseButton> &&i_self) : GuiButton(i_self) {}

void GuiWindow::CloseButton::draw() {
    if (isPressed && isHovered) {
        RenderManager::color(constants::gui_close_button_pressed);
    } else if (!isPressed && isHovered) {
        RenderManager::color(constants::gui_close_button_hover);
    } else {
        RenderManager::color(constants::gui_close_button);
    }

    RenderManager::drawrect(Vec2d::ZERO, getSize());
}

GuiWindow::GuiWindow(const std::weak_ptr<GuiWindow> &&i_self, constants::FRAME_CULL_MODE i_cull_mode) : GuiFrame(i_self,
                                                                                                                 i_cull_mode) {
    Logger::info("Gui window created");

    dragging = false;
    padding_top = Vec2d(4, 15);
    padding_bottom = Vec2d(4, 4);

    closeBtn = GuiFactory::create<CloseButton>();
    add(closeBtn);

    workFrame = GuiFactory::create<GuiFrame>(constants::CULL_SCISSOR);
    add(workFrame);

    closeBtn->MouseClickEvent.connect_weak(&GuiWindow::OnCloseButtonClick, self, this);
}

void GuiWindow::draw() {
    //glColor4f(0.8,0.5,0.3,0.5);
    //glColor(constants::gui_frame_foreground);


    // If rendering to texuture, dont mix color with Black background
    // Instead, pass full color
    if (cull_mode == constants::CULL_TEXTURE) {
        glBlendFunc(GL_ONE, GL_ONE);

        RenderManager::color(constants::gui_frame_foreground);
        RenderManager::drawrect(Vec2d::ZERO, getSize());

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        RenderManager::color(constants::gui_frame_foreground);
        RenderManager::drawhrect(Vec2d::ZERO, getSize());
    }


    RenderManager::color(constants::gui_frame_background);
    RenderManager::drawrect(workFrame->getPositionMin(), workFrame->getPositionMax());

    GuiFrame::draw();

    RenderManager::color(constants::gui_frame_accent1);
    RenderManager::drawhrect(workFrame->getPositionMin() - ProjectionManager::getPixelSize(),
                             workFrame->getPositionMax());

    //glColor(constants::gui_frame_accent1);
    //drawHRect( Vec2d::ZERO, getSize()-ProjectionManager::getPixelSize() );

}

void GuiWindow::afterResize() {

    GuiFrame::afterResize();

    double button_size_x = (double) std::round(padding_top.y * 1.5);

    closeBtn->setSizeMin(Vec2d(button_size_x, padding_top.y));
    closeBtn->setPositionMin(
            Vec2d(getSize().x - closeBtn->getSize().x - padding_bottom.x + ProjectionManager::getPixelSize().x, 0));

    workFrame->setPositionMin(padding_top);
    workFrame->setSizeMin(getSize() - padding_bottom - padding_top);

}

void GuiWindow::OnMouseEvent(int button, int state, Vec2d mousePos) {

    GuiFrame::OnMouseEvent(button, state, mousePos);

    if (ClickedGuis.find(button) == ClickedGuis.end()) {
        if (button == 0 && state == GLFW_PRESS) {
            dragging = true;
            dragging_pos = mousePos;
        } else {
            dragging = false;
        }
    }

}

void GuiWindow::OnMouseMove(Vec2d mousePos) {

    if (dragging) {
        setPositionMin(getPositionMin() + (mousePos - dragging_pos));
        mousePos = dragging_pos;
        Update();
    }

    GuiFrame::OnMouseMove(mousePos);
}

void GuiWindow::OnCloseButtonClick() {
    Logger::info("Closing window!");
}

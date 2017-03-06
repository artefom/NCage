//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIWINDOW_H
#define PLAYIN_GUIWINDOW_H

#include "GuiFrame.h"
#include "GuiButton.h"
#include "GuiFactory.h"
#include "GuiView.h"

class GuiWindow : public GuiFrame {
public:


    class CloseButton : public GuiButton {
        virtual void draw() {
            if (isPressed && isHovered) {
                glColor(constants::gui_close_button_pressed);
            } else if (!isPressed && isHovered) {
                glColor(constants::gui_close_button_hover);
            } else {
                glColor(constants::gui_close_button);
            }

            drawRect(Vec2d::ZERO, getSize());

            Vec2d real_size = getSize();
            real_size.y-=ProjectionManager::getPixelSize().y;

            glColor(constants::gui_close_button);
            drawHRect(Vec2d::ZERO, real_size);
        }
    };

    Vec2d padding_top;
    Vec2d padding_bottom;

    std::shared_ptr<GuiButton> closeBtn;
    std::shared_ptr<GuiFrame> workFrame;

    std::shared_ptr<GuiView> viewGui;

    GuiWindow() {
        std::cout << "Gui window created!" << std::endl;

        dragging = false;
        padding_top = Vec2d(4, 15);
        padding_bottom = Vec2d(4, 4);

    }

    virtual void postInit() {

        closeBtn = GuiFactory::create<CloseButton>();
        add(closeBtn);

        workFrame = GuiFactory::create<GuiFrame>();
        add(workFrame);

        GuiFrame::postInit();
        closeBtn->MouseClickEvent.connect_weak(&GuiWindow::OnCloseButtonClick, self, this);
    }

    virtual void draw() {
        //glColor4f(0.8,0.5,0.3,0.5);
        //glColor(constants::gui_frame_foreground);


        // If rendering to texuture, dont mix color with Black background
        // Instead, pass full colod
        if (cull_mode == constants::CULL_TEXTURE) {
            glBlendFunc(GL_ONE,GL_ONE);

            glColor(constants::gui_frame_foreground);
            drawRect( Vec2d::ZERO, getSize() );

            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        } else {
            glColor(constants::gui_frame_foreground);
            drawRect( Vec2d::ZERO, getSize() );
        }




        glColor(constants::gui_frame_accent1);
        drawHRect( workFrame->getPositionMin()-ProjectionManager::getPixelSize(), workFrame->getPositionMax() );

        glColor(constants::gui_frame_background);
        drawRect( workFrame->getPositionMin(), workFrame->getPositionMax() );

        //glColor(constants::gui_frame_accent1);
        //drawHRect( Vec2d::ZERO, getSize()-ProjectionManager::getPixelSize() );
        GuiFrame::draw();

    }

    virtual void afterResize() {

        GuiFrame::afterResize();

        closeBtn->setSizeMin(Vec2d(padding_top.y * 1.5, padding_top.y));
        closeBtn->setPositionMin(Vec2d(getSize().x - closeBtn->getSize().x - padding_bottom.x, 0));

        workFrame->setPositionMin(padding_top);
        workFrame->setSizeMin(getSize() - padding_bottom - padding_top);

    }

    Vec2d dragging_pos;
    bool dragging;

    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {

        GuiFrame::OnMouseEvent(button, state, mousePos);

        if (ClickedGuis.find(button) == ClickedGuis.end()) {
            if (button == 0 && state == 0) {
                dragging = true;
                dragging_pos = mousePos;
            } else {
                dragging = false;
            }
        }

    }

    virtual void OnMouseMove(Vec2d mousePos) {

        if (dragging) {
            setPositionMin(getPositionMin() + (mousePos - dragging_pos));
            Update();
        }

        GuiFrame::OnMouseMove(mousePos);
    }

    virtual void OnCloseButtonClick() {
        std::cout << "Closing window!" << std::endl;
    }

};


#endif //PLAYIN_GUIWINDOW_H

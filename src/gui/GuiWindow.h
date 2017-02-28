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
            } else
            if (!isPressed && isHovered){
                glColor(constants::gui_close_button_hover);
            } else {
                glColor(constants::gui_close_button);
            }

            drawRect(Vec2d::ZERO,getSize());
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
        padding_top = Vec2d(4,15);
        padding_bottom = Vec2d(4,4);

        closeBtn = GuiFactory::create<CloseButton>();
        add(closeBtn);

        workFrame = GuiFactory::create<GuiFrame>();
        add(workFrame);

    }

    virtual void postInit() {
        GuiFrame::postInit();
        closeBtn->MouseClickEvent.connect_weak(&GuiWindow::OnCloseButtonClick,self,this);
    }

    virtual void draw() {
        glColor(constants::gui_frame_foreground);
        drawRect(Vec2d::ZERO,getSize());
        glColor(constants::gui_frame_background);
        drawRect(workFrame->getPositionMin(),workFrame->getPositionMax());
        glColor(constants::gui_frame_accent1);
        drawHRect(Vec2d::ZERO,getSize());
        drawHRect(workFrame->getPositionMin(),workFrame->getPositionMax());
        GuiFrame::draw();
    }

    virtual void afterResize() {
        closeBtn->setSizeMin(Vec2d(padding_top.y*1.5,padding_top.y));
        closeBtn->setPositionMin(Vec2d(getSize().x-closeBtn->getSize().x-padding_bottom.x,0));

        workFrame->setPositionMin( padding_top );
        workFrame->setSizeMin( getSize()-padding_bottom-padding_top );
    }

    Vec2d dragging_pos;
    bool dragging;
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {
        GuiFrame::OnMouseEvent(button,state,mousePos);

        if ( ClickedGuis.find(button) == ClickedGuis.end() ) {
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
        }

        GuiFrame::OnMouseMove(mousePos);
    }

    virtual void OnCloseButtonClick() {
        std::cout << "Closing window!" << std::endl;
    }

};


#endif //PLAYIN_GUIWINDOW_H

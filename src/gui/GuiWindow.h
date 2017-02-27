//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIWINDOW_H
#define PLAYIN_GUIWINDOW_H

#include "GuiFrame.h"
#include "GuiButton.h"
#include "GuiFactory.h"

class GuiWindow : public GuiFrame {
public:

    GuiWindow() {
        std::cout << "Gui window created!" << std::endl;

        std::shared_ptr< GuiButton > btn = GuiFactory::create<GuiButton>();
        btn->setPositionMin(Vec2d(0.04,0.04));
        btn->setSizeMin(Vec2d(0.02,0.02));
        add(btn);

    }
    virtual void draw() {
        glColor(constatns::gui_frame_background);
        drawRect(Vec2d::ZERO,getSize());
        GuiFrame::draw();
    }


};


#endif //PLAYIN_GUIWINDOW_H

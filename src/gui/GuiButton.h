//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIBUTTON_H
#define PLAYIN_GUIBUTTON_H

#include <constants.h>
#include "GuiBase.h"


class GuiButton : public GuiBase {
public:

    GuiButton() {
        MouseEnterEvent.add(std::bind(&GuiButton::OnMouseEnter, this ));
        MouseLeaveEvent.add(std::bind(&GuiButton::OnMouseLeave, this ));
    }

    virtual void draw() {
        glColor(constatns::gui_accent_1);
        drawRect(Vec2d::ZERO,getSize());
    }

    virtual void OnMouseEnter() {
        std::cout << "Mouse entered!" << std::endl;
    }

    virtual void OnMouseLeave() {
        std::cout << "Mouse exitted!" << std::endl;
    }
};


#endif //PLAYIN_GUIBUTTON_H

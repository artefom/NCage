//
// Created by artef on 27.02.2017.
//

#ifndef PLAYIN_GUIWINDOW_H
#define PLAYIN_GUIWINDOW_H

#include <gui/GuiTextureView.h>
#include "GuiFrame.h"
#include "GuiButton.h"
#include "GuiFactory.h"
#include "GuiView.h"

class GuiWindow : public GuiFrame {
public:


    class CloseButton : public GuiButton {

    public:

        CloseButton(const std::weak_ptr<CloseButton> &&i_self);;

        virtual void draw();
    };

    Vec2d padding_top;
    Vec2d padding_bottom;

    std::shared_ptr<GuiButton> closeBtn;
    std::shared_ptr<GuiFrame> workFrame;

    std::shared_ptr<GuiView> viewGui;

    GuiWindow(const std::weak_ptr<GuiWindow>&& i_self,
              constants::FRAME_CULL_MODE i_cull_mode = constants::CULL_TEXTURE);


    virtual void draw();

    virtual void afterResize();

    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    virtual void OnMouseMove(Vec2d mousePos);

    virtual void OnCloseButtonClick();

protected:
    Vec2d dragging_pos;
    bool dragging;

};


#endif //PLAYIN_GUIWINDOW_H

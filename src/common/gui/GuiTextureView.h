//
// Created by artef on 04.03.2017.
//

#ifndef PLAYIN_TEXTUREDISPLAY_H
#define PLAYIN_TEXTUREDISPLAY_H

#include <ProjectionManager.h>
#include "glutUtils.h"
#include "GuiView.h"

class GuiTextureView : public GuiView {
public:

    GuiTextureView(const std::weak_ptr<GuiTextureView>&& i_self) : GuiView(i_self) {};

    virtual void localDraw() {

        glColor(Color(255,0,0));
        drawRect(Vec2d(0,0),Vec2d(10,10));

    }

};


#endif //PLAYIN_TEXTUREDISPLAY_H

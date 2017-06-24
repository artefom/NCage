//
// Created by artef on 04.03.2017.
//

#ifndef PLAYIN_TEXTUREDISPLAY_H
#define PLAYIN_TEXTUREDISPLAY_H

#include <ProjectionManager.h>
#include <render/RenderManager.h>
#include "glutUtils.h"
#include "GuiView.h"

class GuiTextureView : public GuiView {
public:

    GuiTextureView(const std::weak_ptr<GuiTextureView>&& i_self) : GuiView(i_self) {};

    virtual void localDraw() {

        RenderManager::color(Color(255, 0, 0));
        RenderManager::drawrect(Vec2d(0, 0), Vec2d(10, 10));

    }

};


#endif //PLAYIN_TEXTUREDISPLAY_H

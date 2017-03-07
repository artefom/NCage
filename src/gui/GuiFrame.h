//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_GUIFRAME_H
#define PLAYIN_GUIFRAME_H

#include <vector>
#include <glutUtils.h>
#include <memory.h>
#include <mathUtils.h>
#include <unordered_map>
#include <utils/FBTexture.h>

#include "resources/constants.h"
#include "GuiBase.h"
#include "ProjectionManager.h"


class GuiFrame : public GuiBase {
protected:

    // Sub-elements of frame
    // Order of elements in this vector is responsible
    // for drawing order and click processing
    // To move Gui Element on top, put it on top of this vector.
    std::vector< std::shared_ptr<GuiBase> > children;

    // Gui that lies under mouse.
    std::shared_ptr<GuiBase> MouseGui;

    std::unordered_map< int,std::shared_ptr<GuiBase> > ClickedGuis;

    constants::FRAME_CULL_MODE cull_mode;

    FBTexture cull_tex;


public:

    //Vec2d texture_span;


    GuiFrame(const std::weak_ptr<GuiFrame>&& i_self,
             constants::FRAME_CULL_MODE i_cull_mode = constants::CULL_NONE) : GuiBase(i_self)
    {
        //texture_span = getSize()*0.9;
        setRenderMode(i_cull_mode);

    }

    void setRenderMode(constants::FRAME_CULL_MODE mode) {
        cull_mode = mode;

        if (cull_mode == constants::CULL_TEXTURE) {
            updateTexture();
        } else {
            cull_tex.Destroy();
        }

        Update();
    }

    void updateTexture() {
        //if (cull_tex.isInitialized()) return;

        if (cull_mode == constants::CULL_TEXTURE) {

            Vec2i min_pos = ProjectionManager::project_i(Vec2d::ZERO);
            Vec2i max_pos = ProjectionManager::project_i(getSize());
            Vec2i size = mutils::abs(max_pos - min_pos);//+Vec2i(1,1);

            if (size.x == 0 || size.y == 0)
                return;

//        print("Texture updated:",getSize());
//        print("Texture size:",size);

            cull_tex.Init(size);
        }
    }

    constants::FRAME_CULL_MODE getRenderMode() const {
        return cull_mode;
    }

    // Mouse event in relative coordinates
    // Internal function (tight bounds)
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    virtual void OnMouseEnter();

    virtual void OnMouseLeave();

    // Mouse event when cursor moves over current gui instance
    virtual void OnMouseMove(Vec2d mousePos);

    virtual void pushBuffer() {
        cull_tex.bind();

        //print(cull_tex.getSize());

        glPushMatrix();

        glLoadIdentity();

        glClear(GL_COLOR_BUFFER_BIT);
    }

    virtual void draw();

    virtual void popBuffer() {

        glPopMatrix();

        cull_tex.unbind();
    }

    virtual void drawBuffered() {

        if (cull_mode == constants::CULL_TEXTURE) {

            if (should_update) {
                pushBuffer();
                draw();
                popBuffer();
                should_update = false;
            }

            Vec2d tex_p1 = Vec2d::ZERO;
            Vec2d tex_p2 = getSize();

            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, cull_tex.getTexId());

            glColor4f(1, 1, 1, 1);
            glBegin(GL_QUADS);

            //glNormal3f(0, 0, 1);

            glTexCoord2f(0.0f, 1.0f);
            glVertex2d(tex_p1.x, tex_p1.y);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2d(tex_p2.x, tex_p1.y);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2d(tex_p2.x, tex_p2.y);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2d(tex_p1.x, tex_p2.y);

            glEnd();
            // unbind texture
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        } else if (cull_mode == constants::CULL_SCISSOR) {

        } else if (cull_mode == constants::CULL_NONE) {
            draw();
        }

    }

    virtual void add(std::shared_ptr<GuiBase> gui) {

        children.push_back(gui);

        gui->UpdateEvent.add_weak(std::bind(&GuiFrame::Update,this),self);

        Update();
    }

    virtual void afterResize() {
        GuiBase::afterResize();
        //texture_span = getSize()*0.9;
        updateTexture();

        Update();
    }

};


#endif //PLAYIN_GUIFRAME_H

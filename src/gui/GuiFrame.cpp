//
// Created by artef on 27.01.2017.
//

#include "GuiFrame.h"

void GuiFrame::OnMouseEvent(int button, int state, Vec2d mousePos) {

    // Call base's mouse event
    GuiBase::OnMouseEvent(button,state,mousePos);


    if (state == GLFW_RELEASE) {
        auto it = ClickedGuis.find(button);
        if (it != ClickedGuis.end()) {
            std::shared_ptr<GuiBase> &ClickedGui = it->second;

            Vec2d localMpos = mutils::map(mousePos, ClickedGui->getPositionMin(), ClickedGui->getPositionMax(),
                                          Vec2d::ZERO, ClickedGui->getSize());
            ClickedGui->OnMouseEvent(button, state, localMpos);

            ClickedGuis.erase(it);
        }
    }

    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        std::shared_ptr<GuiBase>& v = *it;

        //Vec2d localMpos = mutils::map(mousePos,v->getPositionMin(),v->getPositionMax(),Vec2d::ZERO,v->getSize());
        Vec2d localMpos = mousePos - v->getPositionMin();

        if ( v->hasMouse(localMpos) ) {

            if (state == GLFW_PRESS) {

                auto it2 = ClickedGuis.find(button);

                if (it2 != ClickedGuis.end()) {
                    it2->second->OnMouseEvent(button, state, localMpos);
                    ClickedGuis.erase(it2);
                }

                ClickedGuis.insert( std::pair< int, std::shared_ptr<GuiBase> >(button,v) );
                v->OnMouseEvent(button, state, localMpos);

            }

            break;
        }
    }

}

void GuiFrame::OnScroll(Vec2d scale) {
    if (MouseGui) {
        MouseGui->OnScroll(scale);
    }
}

void GuiFrame::OnMouseEnter() {
    GuiBase::OnMouseEnter();
}

void GuiFrame::OnMouseLeave() {
    if (MouseGui) {
        MouseGui->OnMouseLeave();
        MouseGui = 0;
    }
    GuiBase::OnMouseLeave();
}

void GuiFrame::OnMouseMove(Vec2d mousePos) {
    std::shared_ptr<GuiBase> newMouseGui;

    Vec2d localMpos( Vec2d::ZERO );

    //for (std::shared_ptr<GuiBase> v : children) {
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        std::shared_ptr<GuiBase>& v = *it;

        localMpos = mutils::map(mousePos,v->getPositionMin(),v->getPositionMax(),Vec2d::ZERO,v->getSize());
        if ( v->hasMouse(localMpos) ) {
            newMouseGui = v;
            break;
        }
    }

    // Process MouseEnter\Exit Events.
    if (newMouseGui != MouseGui) {
        if (MouseGui) {
            MouseGui->OnMouseLeave();
            //MouseGui->MouseLeaveEvent();
        }
        MouseGui = newMouseGui;
        if (newMouseGui) {
            newMouseGui->OnMouseEnter();
            //newMouseGui->MouseEnterEvent();
        }
    } else MouseGui = newMouseGui;

    if (MouseGui)
        MouseGui->OnMouseMove(localMpos);

    for (auto v : ClickedGuis) {
        std::shared_ptr<GuiBase>& ClickedGui = v.second;
        if (ClickedGui && ClickedGui != MouseGui) {
            Vec2d clickedLocalMpos = mutils::map(mousePos, ClickedGui->getPositionMin(),
                                                 ClickedGui->getPositionMax(), Vec2d::ZERO, ClickedGui->getSize());;
            ClickedGui->OnMouseMove(clickedLocalMpos);
        }
    }
}

void GuiFrame::draw() {


    for (std::shared_ptr<GuiBase> &v : children) {

        {
            safePushMatrix mat;
            glTranslate(v->getPositionMin());
//
            v->drawBuffered();
//            v->pushBuffer();
//            v->draw();
//            v->popBuffer();
//
//            glColor( Color(0,255,0) );
//            drawRect(Vec2d(0,0),Vec2d(5,5));
        }

    }
//
//    glColor( Color(255,0,0) );
//    drawRect(Vec2d(0,0),Vec2d(5,5));
//
}

GuiFrame::GuiFrame(const std::weak_ptr<GuiFrame> &&i_self, constants::FRAME_CULL_MODE i_cull_mode) :
        GuiBase(i_self),
        resized(false) {
    //texture_span = getSize()*0.9;
    setRenderMode(i_cull_mode);

}

void GuiFrame::setRenderMode(constants::FRAME_CULL_MODE mode) {
    cull_mode = mode;

    if (cull_mode == constants::CULL_TEXTURE && !cull_tex.isInitialized()) {

        Vec2i min_pos = ProjectionManager::project_i(Vec2d::ZERO);
        Vec2i max_pos = ProjectionManager::project_i(getSize());
        Vec2i size = Vec2i::apply<std::abs>(max_pos - min_pos);//+Vec2i(1,1);
        cull_tex.Init(size);

    } else {
        cull_tex.Destroy();
    }

    resized = false;

    Update();
}

void GuiFrame::updateTexture() {

    Vec2i min_pos = ProjectionManager::project_i(Vec2d::ZERO);
    Vec2i max_pos = ProjectionManager::project_i(getSize());
    Vec2i size = Vec2i::apply<std::abs>(max_pos - min_pos);//+Vec2i(1,1);

    if (size.x == 0 || size.y == 0)
        return;

    if ((cull_tex.getSize() != size).any()) {
        cull_tex.resize(size);
    }

}

void GuiFrame::updateScissor() {

    Vec2i p1 = ProjectionManager::project_i(Vec2d::ZERO);
    Vec2i p2 = ProjectionManager::project_i(getSize());

    Vec2i size = mutils::abs(p1 - p2);
    Vec2i pos_min = mutils::min(p1, p2);


    scissor_min = pos_min;
    scissor_size = size;

    //scissor_size = mutils::abs(max_pos - scissor_min);
}

constants::FRAME_CULL_MODE GuiFrame::getRenderMode() const {
    return cull_mode;
}

void GuiFrame::popBuffer() {

    glPopMatrix();

    cull_tex.unbind();
}

void GuiFrame::drawBuffered() {

    if (cull_mode == constants::CULL_TEXTURE) {

        if (resized) {
            updateTexture();
            resized = false;
        }

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

        should_update = false;

        updateScissor();

        ProjectionManager::pushScissor();
        ProjectionManager::setScissorClamped(scissor_min, scissor_size);

        draw();

        ProjectionManager::popScissor();

    } else if (cull_mode == constants::CULL_NONE) {

        should_update = false;

        draw();
    }

}

void GuiFrame::add(std::shared_ptr<GuiBase> gui) {

    children.push_back(gui);

    gui->UpdateEvent.add_weak(std::bind(&GuiFrame::Update, this), self);

    Update();
}

void GuiFrame::afterResize() {
    GuiBase::afterResize();
    resized = true;

    Update();
}

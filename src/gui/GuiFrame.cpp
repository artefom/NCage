//
// Created by artef on 27.01.2017.
//

#include "GuiFrame.h"
#include "ProjectionManager.h"

void GuiFrame::OnMouseEvent(int button, int state, Vec2d mousePos) {

    // Call base's mouse event
    GuiBase::OnMouseEvent(button,state,mousePos);


    if (state == 1) {
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

        Vec2d localMpos = mutils::map(mousePos,v->getPositionMin(),v->getPositionMax(),Vec2d::ZERO,v->getSize());
        if ( v->hasMouse(localMpos) ) {

            if (state == 0) {

                auto it = ClickedGuis.find(button);

                if (it != ClickedGuis.end()) {
                    it->second->OnMouseEvent(button, state, localMpos);
                    ClickedGuis.erase(it);
                }

                ClickedGuis.insert( std::pair< int, std::shared_ptr<GuiBase> >(button,v) );
                v->OnMouseEvent(button, state, localMpos);

            }

            break;
        }
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

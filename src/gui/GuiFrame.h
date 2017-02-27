//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_GUIFRAME_H
#define PLAYIN_GUIFRAME_H

#include <vector>
#include <freeglut.h>
#include <glutUtils.h>
#include <memory.h>
#include <mathUtils.h>

#include "constants.h"
#include "GuiBase.h"


class GuiFrame : public GuiBase {
public:

    // Gui that lies under mouse.
    std::shared_ptr<GuiBase> MouseGui;

    // Sub-elements of frame
    std::vector< std::shared_ptr<GuiBase> > children;

    // Mouse event in relative coordinates
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos) {
        for (std::shared_ptr<GuiBase> v : children) {
            Vec2d localMpos = mutils::map(mousePos,v->getPositionMin(),v->getPositionMax(),Vec2d::ZERO,v->getSize());
            if ( v->hasMouse(localMpos) ) {
                std::cout << "SUCCESS!" << std::endl;
                v->OnMouseEvent(button, state, localMpos);
                break;
            }
        }
    }

    // Mouse event when cursor moves over current gui instance
    virtual void OnMouseMove(Vec2d mousePos) {
        std::shared_ptr<GuiBase> newMouseGui;
        for (std::shared_ptr<GuiBase> v : children) {
            Vec2d localMpos = mutils::map(mousePos,v->getPositionMin(),v->getPositionMax(),Vec2d::ZERO,v->getSize());
            if ( v->hasMouse(localMpos) ) {
                newMouseGui = v;
                v->OnMouseMove(localMpos);
                break;
            }
        }

        // Process MouseEnter\Exit Events.

        if (newMouseGui != MouseGui) {
            if (MouseGui) {
                MouseGui->MouseLeaveEvent();
            }
            MouseGui = newMouseGui;
            if (newMouseGui) {
                newMouseGui->MouseEnterEvent();
            }
        } else MouseGui = newMouseGui;
    }

    virtual void draw() {
        GuiBase::draw();
        for (std::shared_ptr<GuiBase>& v : children) {

            glPushMatrix();
                glTranslate(v->getPositionMin());
                v->draw();
            glPopMatrix();

        }
    }

    virtual void add(std::shared_ptr<GuiBase> gui) {
        children.push_back(gui);
    }

};


#endif //PLAYIN_GUIFRAME_H

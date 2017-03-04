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

#include "resources/constants.h"
#include "GuiBase.h"


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

public:

    GuiFrame() {

    }

    // Mouse event in relative coordinates
    // Internal function (tight bounds)
    virtual void OnMouseEvent(int button, int state, Vec2d mousePos);

    virtual void OnMouseEnter();

    virtual void OnMouseLeave();

    // Mouse event when cursor moves over current gui instance
    virtual void OnMouseMove(Vec2d mousePos);

    virtual void draw();

    virtual void add(std::shared_ptr<GuiBase> gui) {
        children.push_back(gui);
    }

};


#endif //PLAYIN_GUIFRAME_H

//
// Created by artef on 25.01.2017.
//

#ifndef PLAYIN_GUIMANAGER_H
#define PLAYIN_GUIMANAGER_H


#include <iostream>
#include <memory>
#include <SafeQueue.h>
#include <GuiFrame.h>
#include <GuiWindow.h>
#include <GuiFactory.h>

#include "GuiBase.h"

class GuiManager {

public:

    static SafeQueue<int> input_events;

    static void Init();

    static void PostInit() {
        std::shared_ptr< GuiWindow > wnd = GuiFactory::create<GuiWindow>();

        wnd->setPositionMin( Vec2d( 0.2,0.2) );
        wnd->setSizeMin(Vec2d(0.1,0.2));

        GuiRoot.add(wnd);
    };

    static void display_gui();

    static void hide_gui();

    static void terminate();

    static void OnMouseMove(double x, double y);

    static void OnMouseDown(int button, int state, double x, double y);

    static void OnResize(double width, double height);;

    static void draw() {
        GuiRoot.draw();
    }

    // Structure of gui lying beneath cursor
    static std::vector< std::shared_ptr<GuiBase> > under_mouse;

private:

    static GuiFrame GuiRoot;

    GuiManager() {};


};


#endif //PLAYIN_GUIMANAGER_H

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
#include <stack>
#include <GuiView.h>

#include "GuiBase.h"

class GuiManager {

public:

    static std::shared_ptr< GuiView > render_view;

    static SafeQueue<int> input_events;

    static Vec2d guiScale;

    // Initialize GUI Manager
    static void Init();

    // Initialization AFTER background thread was created
    static void PostInit();

    // Enables gui
    static void display_gui();

    // Disables gui
    static void hide_gui();

    // Terminates gui
    static void terminate();

    // Mouse Move event
    static void OnMouseMove(double x, double y);

    // Mouse Down event
    static void OnMouseDown(int button, int state, double x, double y);

    // Called on resize
    static void OnResize(double width, double height);;

    // Draw call
    static void draw();

    static std::stack< std::shared_ptr<GuiBase> > clickStack;
    // Structure of gui lying beneath cursor
    static std::stack< std::shared_ptr<GuiBase> > under_mouse;

private:

    static GuiFrame GuiRoot;

    GuiManager() {};


};


#endif //PLAYIN_GUIMANAGER_H

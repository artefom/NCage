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

    static std::shared_ptr<GuiView> render_view;

    static SafeQueue<int> input_events;

    // Initialize GUI Manager
    static void Init();

    // Initialization AFTER background thread was created
    static void PostInit();

    // Terminates gui
    static void terminate();

    // Mouse Move event
    static void OnMouseMove(Vec2d mouse_pos);

    // Mouse Down event
    static void OnMouseDown(int button, int state, Vec2d mouse_pos);

    // Called on resize
    static void OnResize(Vec2d size);

    // Draw call
    static void draw();

private:

    static GuiFrame GuiRoot;

    GuiManager() {};


};


#endif //PLAYIN_GUIMANAGER_H

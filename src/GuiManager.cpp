//
// Created by artef on 25.01.2017.
//

#include "GuiManager.h"
#include "BackgroundWorker.h"
#include <iostream>

void GuiManager::Init() {
    std::cout << "Hello from Gui manager initialization" << std::endl;

}

void GuiManager::OnMouseMove(double x, double y) {
    GuiRoot.OnMouseMove(Vec2d(x,y));
}

void GuiManager::OnMouseDown(int button, int state, double x, double y) {

    GuiRoot.OnMouseEvent(button, state, Vec2d(x, y));

    BackgroundWorker::input_events.enqueue(button);
}

void GuiManager::terminate() {

}

void GuiManager::OnResize(double width, double height) {

    GuiRoot.setPositionMin(Vec2d(0,0));
    GuiRoot.setSizeMin(Vec2d(width,height));

}

SafeQueue<int> GuiManager::input_events;

GuiFrame GuiManager::GuiRoot;
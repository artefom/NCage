//
// Created by artef on 25.01.2017.
//

#include "GuiManager.h"
#include "BackgroundWorker.h"
#include <iostream>

void GuiManager::Init() {
    std::cout << "Hello from Gui manager initialization" << std::endl;
    guiScale = Vec2d::ONE;
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

    double resized_width = width*guiScale.x;
    double resized_height = height*guiScale.y;

    GuiRoot.setPositionMin( Vec2d::ZERO );
    GuiRoot.setSizeMin( Vec2d(width,height) );

    render_view->setPositionMin( Vec2d::ZERO );
    render_view->setSizeMin( Vec2d(width,height) );
}

void GuiManager::PostInit() {

    std::shared_ptr< GuiWindow > wnd = GuiFactory::create<GuiWindow>();
    wnd->setPositionMin( Vec2d( 50,50) );
    wnd->setSizeMin(Vec2d(100,200));

    render_view = GuiFactory::create<GuiView>();

    GuiRoot.add(render_view);
    GuiRoot.add(wnd);
}

void GuiManager::draw() {
    GuiRoot.draw();
}

SafeQueue<int> GuiManager::input_events;

GuiFrame GuiManager::GuiRoot;

Vec2d GuiManager::guiScale;

std::shared_ptr<GuiView> GuiManager::render_view;
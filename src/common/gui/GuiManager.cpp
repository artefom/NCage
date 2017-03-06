//
// Created by artef on 25.01.2017.
//

#include "GuiManager.h"
#include "GuiTextureView.h"
#include "BackgroundWorker.h"
#include <iostream>

void GuiManager::Init() {
    GuiRoot = GuiFactory::create<GuiFrame>();
}

void GuiManager::OnMouseMove(Vec2d mouse_pos) {
    GuiRoot->OnMouseMove(mouse_pos);
}

void GuiManager::OnMouseDown(int button, int state, Vec2d mouse_pos) {

    GuiRoot->OnMouseEvent(button, state, mouse_pos);

    BackgroundWorker::input_events.enqueue(button);
}

void GuiManager::terminate() {

}

void GuiManager::OnResize(Vec2d size) {

    GuiRoot->setPositionMin( Vec2d::ZERO );
    GuiRoot->setSizeMin( Vec2i( size*0.5 ) );

    render_view->setPositionMin( Vec2d::ZERO );
    render_view->setSizeMin( size*0.25 );
}

void GuiManager::PostInit() {

    std::shared_ptr< GuiWindow > wnd = GuiFactory::create<GuiWindow>();
    wnd->setPositionMin( Vec2d( 50,50) );
    wnd->setSizeMin(Vec2d(100,200));

    render_view = GuiFactory::create<GuiTextureView>();

    GuiRoot->add(render_view);
    GuiRoot->add(wnd);
}

void GuiManager::draw() {


    //GuiRoot->pushBuffer();
    GuiRoot->drawBuffered();
    //GuiRoot->popBuffer();
}

SafeQueue<int> GuiManager::input_events;

std::shared_ptr<GuiFrame> GuiManager::GuiRoot;

std::shared_ptr<GuiTextureView> GuiManager::render_view;
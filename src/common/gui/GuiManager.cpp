//
// Created by artef on 25.01.2017.
//

#include "GuiManager.h"
#include "BackgroundWorker.h"

bool GuiManager::root_needs_update{true};

void GuiManager::Init() {
    GuiRoot = GuiFactory::create<GuiFrame>();
    GuiRoot->UpdateEvent.add(std::bind(&GuiManager::Update));
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
    GuiRoot->setSizeMin(Vec2i(size));

    render_view->setPositionMin( Vec2d::ZERO );
    render_view->setSizeMin(size);
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

    // draw only if root needs to be updated
    if (root_needs_update) {
        root_needs_update = false;
        glClear(GL_COLOR_BUFFER_BIT);
        GuiRoot->drawBuffered();
    }

}

void GuiManager::Update() {
    root_needs_update = true;
}

SafeQueue<int> GuiManager::input_events;

std::shared_ptr<GuiFrame> GuiManager::GuiRoot;

std::shared_ptr<GuiTextureView> GuiManager::render_view;
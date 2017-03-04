//
// Created by artef on 27.01.2017.
//

#include "BackgroundWorker.h"

void run_background_thread() {

    BackgroundWorker::Init( );

    BackgroundWorker::main_loop();

}

void exit_background_thread() {

}

bool BackgroundWorker::should_terminate;
SafeQueue<int> BackgroundWorker::input_events;
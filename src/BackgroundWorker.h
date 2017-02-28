//
// Created by artef on 27.01.2017.
//

#ifndef PLAYIN_BACKGROUND_THREAD_H
#define PLAYIN_BACKGROUND_THREAD_H


#include <iostream>
#include <SafeQueue.h>

class BackgroundWorker {

public:

    static SafeQueue<int> input_events;

    static void Init() {
        should_terminate = false;
    }

    static void terminate() {
        should_terminate = true;
    }

    // Programm enters main loop and begins listening to events through input_queue
    static void main_loop() {

        int counter = 0;
        while (!should_terminate) {

            //while (input_events.size() > 0) {
            int i = input_events.dequeue();

            //std::cout << "BG Message recieved: " << i << std::endl;

            if (i == -1) terminate();
            //}

            //std::cout << "BG Looping: " << ++counter << std::endl;
        }

    }

private:

    static bool should_terminate;

    BackgroundWorker() {};

};

void run_background_thread( );

void exit_background_thread( );

#endif //PLAYIN_BACKGROUND_THREAD_H

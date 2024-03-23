// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include "container.h"
#include <conio.h> // for if key was pressed
#include <chrono> // timer

class Engine {
public:
    Engine();
    void start();
    bool keyWasPressed();
    int delay = 200; // press delay, 200 milliseconds

private:
    std::chrono::steady_clock::time_point lastKeyPressTime;
    long long keyPressDelay;
};

#endif

// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <conio.h> // for if key was pressed
#include <chrono> // timer

class Engine {
public:
    Engine();
    void start();
    bool keyWasPressed();
    void updateBlocks();
    int delay = 200; // press delay, 200 milliseconds

    static const int HEIGHT = 10; // Use static constants for array dimensions
    static const int LENGTH = 10;
    int containerItems[HEIGHT][LENGTH] = {0}; // 2D array of container items

    void drawContainer();

private:
    std::chrono::steady_clock::time_point lastKeyPressTime;
    long long keyPressDelay;
};

#endif

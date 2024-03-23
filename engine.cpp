// engine.cpp
#include "engine.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()

void Engine::start() {
    // Implementation of start() method
}

Engine::Engine() : keyPressDelay(Engine::delay) { // Initialize keyPressDelay and lastKeyPressTime
    lastKeyPressTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(keyPressDelay);
}

bool Engine::keyWasPressed() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count();

    if (_kbhit() && elapsed > keyPressDelay) {
        while (_kbhit()) _getch(); // Clear buffer
        lastKeyPressTime = std::chrono::steady_clock::now();
        return true;
    }
    return false;
}

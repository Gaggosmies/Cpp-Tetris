// engine.cpp
#include "engine.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()

void Engine::start() {
    int firstBlock[1][3] = {1};

    if(firstBlock[0][4] == 0 && firstBlock[0][5] == 0 && firstBlock[0][6] == 0) {
        containerItems[0][4] = 1;
        containerItems[0][5] = 1;
        containerItems[0][6] = 1;
    }
}

void Engine::updateBlocks()
{
    this->drawContainer();
}

void Engine::drawContainer()
{
    // Draw the container contents and side boundaries
    for (int i = 0; i < HEIGHT; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < LENGTH; j++)
        {
            std::cout << containerItems[i][j]; // Use array values for drawing
        }
        std::cout << " |" << std::endl;
    }

    // Draw the bottom boundary of the container
    std::cout << "+ ";
    for (int i = 0; i < LENGTH; i++)
    {
        std::cout << '-';
    }
    std::cout << " +" << std::endl;
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

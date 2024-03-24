// main.cpp
#include "engine.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int blockDelay = 100; // milliseconds
    int blockUpdateDelay = 5; // x * blockDelay milliseconds
    int updateBlocks = 0; // counter for block update

    Engine gameEngine;
    gameEngine.start(); // todo: implement start() method
    gameEngine.updateBlocks();

    while (true) {
        // handle key presses
        if(gameEngine.handlePressedKey())
        {
            // if down pressed, update blocks immediately
            updateBlocks = 0;
            continue;    
        }

        if(updateBlocks > blockUpdateDelay) {
            gameEngine.updateBlocks();
            updateBlocks = 0;
        }

        updateBlocks++;
        std::this_thread::sleep_for(std::chrono::milliseconds(blockDelay)); // wait for blockDelay milliseconds
    }

    return 0;
}

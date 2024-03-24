// main.cpp
#include "engine.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int blockDelay = 200; // milliseconds
    int blockUpdateDelay = 5; // x * blockDelay milliseconds
    int updateBlocks = 0;

    Engine gameEngine;
    gameEngine.start(); // todo: implement start() method
    gameEngine.updateBlocks();

    while (true) {
        if(updateBlocks > blockUpdateDelay) {
            system ("CLS");
            gameEngine.updateBlocks();
            updateBlocks = 0;
        }

        updateBlocks++;
        std::this_thread::sleep_for(std::chrono::milliseconds(blockDelay)); // wait for blockDelay milliseconds
    }

    return 0;
}

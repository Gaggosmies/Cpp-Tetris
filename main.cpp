// main.cpp
#include "engine.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    int blockDelay = 500; // 500 milliseconds
    Engine gameEngine;
    gameEngine.start(); // todo: implement start() method
    Container container;
    container.initializeContainer();

    while (true) {
        // std::cout << "Pressed:" << gameEngine.keyWasPressed() << std::endl;

        
        std::this_thread::sleep_for(std::chrono::milliseconds(blockDelay)); // wait for blockDelay milliseconds
    }

    return 0;
}

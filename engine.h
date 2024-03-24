// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <conio.h> // for if key was pressed
#include <chrono> // timer

class Engine {
public:
    Engine();
    void start();
    bool handlePressedKey();
    void updateBlocks();

    int delay = 200; // press delay, 200 milliseconds
    int blockMovementSize = 8; // 8 bits

    uint64_t gameContainer = 0xFF; // 64 bit container
    uint64_t blockContainer = 0; // 64 bit container for blocks
    void drawContainer();

private:
    std::chrono::steady_clock::time_point lastKeyPressTime;
    long long keyPressDelay;
    bool hasOverlap(uint64_t container, uint64_t bits);
    void clearBits(uint64_t& container, uint64_t bits);
    void setBits(uint64_t& container, uint64_t bits);
};

#endif

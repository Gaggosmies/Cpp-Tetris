// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <conio.h> // for if key was pressed
#include <chrono> // timer

#define LAST_ROW 0xFF00000000000000
#define FIRST_ROW 0x00000000000000FF
#define BASIC_BLOCK 0x7000000000000000
#define BASIC_BLOCK_SIDEWAYS 0x2020200000000000
#define LEFT_SIDE 0x8080808080808080
#define RIGHT_SIDE 0x0101010101010101

class Engine {
public:
    Engine();
    void start();
    bool handlePressedKey();
    void updateBlocks();

    int delay = 200; // press delay, 200 milliseconds
    int blockMovementSize = 8; // 8 bits

    uint64_t gameContainer = 0; // 64 bit container
    uint64_t blockContainer = 0; // 64 bit container for blocks
    int gamePoints = 0;
    void drawContainer();

private:
    std::chrono::steady_clock::time_point lastKeyPressTime;
    long long keyPressDelay;
    bool hasOverlap(uint64_t container, uint64_t bits);
    bool areAllBitsSet(uint64_t container, uint64_t mask);
    void clearBits(uint64_t& container, uint64_t bits);
    void setBits(uint64_t& container, uint64_t bits);
};

#endif

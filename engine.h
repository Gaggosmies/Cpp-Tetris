// engine.h
#ifndef ENGINE_H
#define ENGINE_H

#include <conio.h> // for if key was pressed
#include <chrono> // timer
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#define LAST_ROW 0xFF00000000000000
#define FIRST_ROW 0x00000000000000FF

#define BASIC_BLOCK_NUM 0
#define BASIC_BLOCK 0xE000000000000000
#define BASIC_BLOCK_SIDEWAYS 0x4040400000000000

#define Z_BLOCK_NUM 1
#define Z_BLOCK 0xC060000000000000
#define Z_BLOCK_SIDEWAYS 0x40C0800000000000

#define SQUARE_BLOCK_NUM 2
#define SQUARE_BLOCK 0xC0C0000000000000
#define SQUARE_BLOCK_SIDEWAYS 0xC0C0000000000000

#define MAX_BLOCK_NUM 3

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
    
    int blockNumber = 0;
    int goneDown = 0;
    int goneRight = 0;

    struct Block {
        uint64_t normal;
        uint64_t sideways;
    };

    uint64_t gameContainer = 0; // 64 bit container
    uint64_t blockContainer = 0; // 64 bit container for blocks
    int gamePoints = 0;
    bool isSideways = false;
    void drawContainer();
    Block blocks[MAX_BLOCK_NUM] = {
        {BASIC_BLOCK, BASIC_BLOCK_SIDEWAYS},
        {Z_BLOCK, Z_BLOCK_SIDEWAYS},
        {SQUARE_BLOCK, SQUARE_BLOCK_SIDEWAYS}
    };

private:
    std::chrono::steady_clock::time_point lastKeyPressTime;
    long long keyPressDelay;
    bool hasOverlap(uint64_t container, uint64_t bits);
    bool areAllBitsSet(uint64_t container, uint64_t mask);
    void clearBits(uint64_t& container, uint64_t bits);
    void setBits(uint64_t& container, uint64_t bits);
};

#endif

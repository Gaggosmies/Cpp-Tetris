// engine.cpp
#include "engine.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()

void Engine::start() {
    blockContainer = 0x7000000000000000;
}

bool Engine::hasOverlap(uint64_t container, uint64_t bits) {
    return (container & bits) != 0;
}

bool Engine::areAllBitsSet(uint64_t container, uint64_t mask) {
    return (container & mask) == mask;
}

void Engine::clearBits(uint64_t& container, uint64_t bits) {
    container &= ~bits;
}

void Engine::setBits(uint64_t& container, uint64_t bits) {
    container |= bits;
}


void Engine::updateBlocks()
{
    uint64_t temp;

    // Remove the first row if all bits are set
    while(areAllBitsSet(gameContainer, FIRST_ROW)) {
        gameContainer = gameContainer >> 8; // remove the last row
        gamePoints++;
    }

    // Check for overlap
    if(hasOverlap(gameContainer, blockContainer >> blockMovementSize) || hasOverlap(blockContainer, FIRST_ROW)) {
        temp = blockContainer;
        clearBits(blockContainer, temp);
        setBits(gameContainer, temp);

        blockContainer = BASIC_BLOCK; // new block

        if(hasOverlap(gameContainer, LAST_ROW)) {
            std::cout << "Game Over!" << std::endl;
            exit(0);
        }
    }
    else // can move downwards
    {
        temp = blockContainer;
        clearBits(blockContainer, temp);
        setBits(blockContainer, temp >> blockMovementSize);
    }

    this->drawContainer();
}

void Engine::drawContainer()
{
    system ("CLS"); // Clear the console
    std::cout << "-- GAGGO TETRIS --" << std::endl;

    std::cout << "Points: " << gamePoints << std::endl;

    std::cout << "| ";
    for (int i = 0; i < 64; ++i) { // Loop for each bit from 0 to 63
        // Correctly extract the bit using right shift, starting from MSB to LSB
        int bit = (gameContainer >> (63 - i)) & 1;
        int activeBit = (blockContainer >> (63 - i)) & 1;

        if (activeBit == 1) {
            // Print 2 for active bit
            std::cout << '2';
        }
        else
        {
            // Print the bit
            std::cout << bit;
        }
        
        // Print a separator after each byte
        if ((i + 1) % 8 == 0) {
            std::cout << " |"; // Newline after each row (8 bits)
            if (i != 63) {
                std::cout << std::endl << "| "; // Prepare for the next row if not the last bit
            }
        }
    }
    std::cout << std::endl; // Newline after the entire printing
}


Engine::Engine() : keyPressDelay(Engine::delay) { // Initialize keyPressDelay and lastKeyPressTime
    lastKeyPressTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(keyPressDelay);
}

bool Engine::handlePressedKey() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastKeyPressTime).count();

    if (_kbhit() && elapsed > keyPressDelay) {
        // Clear the buffer by reading all available characters
        char lastChar = 0;
        while (_kbhit()) {
            lastChar = _getch(); // Read the next character in the buffer
        }
        lastKeyPressTime = std::chrono::steady_clock::now();
        
        switch (lastChar)
        {
        case 'a':
            blockContainer = blockContainer << 1;
            drawContainer();
            break;

        case 'd':
            blockContainer = blockContainer >> 1;
            drawContainer();
            break;

        case 'w':  
            // todo rotate
            break;

        case 's':   
            updateBlocks();
            break;
        
        default:
            return false;
            break;
        }
        return true;
    }
    return false;
}

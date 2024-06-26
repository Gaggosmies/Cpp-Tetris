// engine.cpp
#include "engine.h"
#include <iostream>
#include <conio.h> // for _kbhit() and _getch()

void Engine::start() {
    blockContainer = blocks[0].normal;
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

void Engine::removeFullRows() {
    uint64_t rowMask = 0xFF; // Mask for the first row.
    uint64_t newRowContainer = 0; // Container for the new game state.
    int shiftAmount = 0; // How many rows have been removed.

    for (int i = 0; i < 64; i += 8) {
        uint64_t currentRow = (gameContainer >> i) & rowMask;
        if (currentRow != rowMask) { // If the row is not full
            // Shift this row down by `shiftAmount` rows and add it to `newRowContainer`.
            newRowContainer |= (currentRow << i) >> (shiftAmount * 8);
        } else { // If the row is full
            shiftAmount++; // Increase the number of rows to shift.
            gamePoints++; // Assuming you have a gamePoints variable to increment.
        }
    }

    gameContainer = newRowContainer;
}



void Engine::updateBlocks()
{
    uint64_t temp;

    removeFullRows();

    // Check for overlap
    if(hasOverlap(gameContainer, blockContainer >> blockMovementSize) || hasOverlap(blockContainer, FIRST_ROW)) {
        temp = blockContainer;
        clearBits(blockContainer, temp);
        setBits(gameContainer, temp);

        srand(time(0)); // seed the random number generator with the current time
        blockNumber = rand() % MAX_BLOCK_NUM; // get a random number between 0 and MAX_BLOCK_NUM-1

        blockContainer = blocks[blockNumber].normal; // new block
        isSideways = false; // reset sideways

        goneDown = 0;
        goneRight = 0;

        if(hasOverlap(gameContainer, BASIC_BLOCK)) {
            std::cout << "Game Over!" << std::endl;
            exit(0);
        }
    }
    else // can move downwards
    {
        temp = blockContainer;
        clearBits(blockContainer, temp);
        setBits(blockContainer, temp >> blockMovementSize);
        goneDown++;
    }

    this->drawContainer();
}

void Engine::drawContainer()
{
    system ("CLS"); // Clear the console
    std::cout << "-- GAGGO TETRIS --" << std::endl;

    std::cout << "Points: " << gamePoints << std::endl;

    std::cout << "|";
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
            std::cout << (bit ? '1' : ' ');
        }
        
        // Print a separator after each byte
        if ((i + 1) % 8 == 0) {
            std::cout << "|"; // Newline after each row (8 bits)
            if (i != 63) {
                std::cout << std::endl << "|"; // Prepare for the next row if not the last bit
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
            if(!hasOverlap(blockContainer, LEFT_SIDE) && !hasOverlap(blockContainer << 1, gameContainer))
            {
                blockContainer = blockContainer << 1;
                goneRight--;
                drawContainer();
            }
            break;

        case 'd':
            if(!hasOverlap(blockContainer, RIGHT_SIDE) && !hasOverlap(blockContainer >> 1, gameContainer))
            {
                blockContainer = blockContainer >> 1;
                goneRight++;
                drawContainer();
            }
            break;

        case 'w':
            uint64_t temp;
            temp = isSideways ? blocks[blockNumber].normal : blocks[blockNumber].sideways; // turn the block
            for(int i = 0; i < goneRight; i++)
            {
                temp = temp >> 1;
            }
            for (int i = 0; i < goneDown; i++)
            {
                temp = temp >> 8;
            }

            if(!hasOverlap(temp, gameContainer))
            {
                if(goneRight > 4 && hasOverlap(temp, LEFT_SIDE)) // if trying to overlap left side
                {
                    break;
                }
                else if(goneRight < 4 && hasOverlap(temp, RIGHT_SIDE)) // if trying to overlap right side
                {
                    break;
                }
                else if(hasOverlap(temp, LAST_ROW) || hasOverlap(temp, FIRST_ROW)) // trying to overlap top or bottom
                {
                    break;
                }

                // otherwise all good to toggle
                blockContainer = temp;
                isSideways = !isSideways; // toggle sideways
                drawContainer();
            }
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

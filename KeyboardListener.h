#pragma once

#include "ObjectDisplayGrid.h"
#include "Player.h"

class KeyboardListener {
private:
    ObjectDisplayGrid* grid;
    Player* player;
    bool running = false;

public:
    KeyboardListener(ObjectDisplayGrid* grid, Player* player);

    /**
     * Starts the keyboard listener
     */
    void start();

    /**
     * Stops the keyboard listener
     */
    void stop();
};


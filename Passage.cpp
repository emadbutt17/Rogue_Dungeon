//
// Created by constantine on 9/13/20.
//

#include "ObjectDisplayGrid.h"
#include "Passage.h"
#include <algorithm>
#include <iostream>
#include <assert.h>

Passage::Passage(std::string name) : Structure('#'), door('+') {
    this->name = name;
}

void Passage::setPosX(int x) {
    xVec.push_back(x);
}

void Passage::setPosY(int y) {
    yVec.push_back(y);
}

void Passage::draw() {
    ObjectDisplayGrid* display = ObjectDisplayGrid::getGrid();
    for (size_t i = 1; i < xVec.size(); i++) {
        int x1 = xVec[i - 1];
        int y1 = yVec[i - 1];
        int x2 = xVec[i];
        int y2 = yVec[i];

        // draw in y direction
        if (x1 == x2) {
            int max = std::max(y1 + 1, y2);
            for (int y = std::min(y1, y2 + 1); y < max; y++) {
                display->add(this, x1, y);
            }
        }
        else {
            int max = std::max(x1, x2);
            for (int x = std::min(x1, x2); x < max; x++) {
                display->add(this, x, y1);
            }
        }
    }

    // draw doors
    display->add(&door, xVec.front(), yVec.front());
    display->add(&door, xVec.back(), yVec.back());
}

bool Passage::canMove(int x, int y) {
    for (size_t i = 1; i < xVec.size(); i++) {
        int x1 = xVec[i - 1];
        int y1 = yVec[i - 1];
        int x2 = xVec[i];
        int y2 = yVec[i];
        if (x >= std::min(x1, x2) && x <= std::max(x1, x2) && y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }
    return false;
}

std::string Passage::toString() {
    std::string str = "Passage connecting room " + std::to_string(id->getFirst()) + " to room " + std::to_string(id->getSecond()) + "\n";

    str += "points: \n";
    for (int i = 0; i < xVec.size(); i++) {
        str += "   [" + std::to_string(xVec[i]) + ", " + std::to_string(yVec[i]) + "]\n";
    }

    str += "creatures: \n";
    for (Creature* creature : creatures) {
        str += "   " + creature->toString() + "\n";
    }

    str += "items: \n";
    for (Item* item : items) {
        str += "   " + item->toString() + "\n";
    }

    str += "\n";
    return str;
}

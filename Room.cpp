//
// Created by constantine on 9/13/20.
//
#include "Room.h"


Room::Room(std::string _name) : Structure('X'), floor('.') {
    this->name = name;
}

bool Room::canMove(int x, int y) {
    return (x >= posX + 1 && x < posX + width - 1)
        && (y >= posY + 1 && y < posY + height - 1);
}

void Room::draw() {
    ObjectDisplayGrid* display = ObjectDisplayGrid::getGrid();
    // draw top and bottom walls, treating self as wall
    for (int x = posX; x < posX + width; x++) {
        display->add(this, x, posY);
        display->add(this, x, posY + height - 1);
    }
    // draw left and right walls
    for (int y = posY + 1; y < posY + height - 1; y++) {
        display->add(this, posX, y);
        display->add(this, posX + width - 1, y);

        // draw floor
        for (int x = posX + 1; x < posX + width - 1; x++) {
            display->add(&floor, x, y);
        }
    }
}

std::string Room::toString() {
    std::string str = "Room: " + id->toString() + "\n";
    Structure::toString();
    str += "width: " + std::to_string(width) + "\n";
    str += "height: " + std::to_string(height) + "\n";

    str += "creatures: \n";
    for (Creature* creature : creatures) {
        str += "   " + creature->toString();
    }

    str += "items: \n";
    for (Item* item : items) {
        str += "   " + item->toString();
    }

    str += "\n";
    return str;
}

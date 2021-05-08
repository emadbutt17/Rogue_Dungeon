//
// Created by constantine on 9/13/20.
//
#include "Structure.h"

Structure::Structure(char type) : Displayable(type) {
}

void Structure::addCreature(Creature* c) {
    creatures.push_back(c);
}

void Structure::addItem(Item* m) {
    items.push_back(m);
}

void Structure::setWidth(int w) {
    width = w;
}

void Structure::setHeight(int h) {
    height = h;
}

std::string Structure::toString() {
    std::string str = "";
    if (visible) {
        str = "visible ";
    }
    str += name + " " + std::to_string(type);
    str += " at position (" + std::to_string(posX) + "," + std::to_string(posY) + ")\n";
    return str;
}

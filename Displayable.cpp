//
// Created by constantine on 9/13/20.
//

#include "Displayable.h"
#include "ObjectDisplayGrid.h"

Displayable::Displayable(char _type) : type(_type) {}

Displayable::Displayable() : Displayable('?') {}

TwoTuple* Displayable::getId() {
    return id;
}

char Displayable::getType() {
    return type;
}

void Displayable::setType(char t) {
    type = t;
}

int Displayable::getPosX() {
    return posX;
}

void Displayable::setPos(int x, int y) {
    setPosX(x);
    setPosY(y);
}

void Displayable::setPosX(int x) {
    posX = x;
}

int Displayable::getPosY() {
    return posY;
}

void Displayable::setMaxHit(int hits) {
    maxHit = hits;
}

int Displayable::getMaxHit() {
    return maxHit;
}

void Displayable::setPosY(int y) {
    posY = y;
}

std::string Displayable::getName() {
    return name;
}

void Displayable::setName(std::string n) {
    name = n;
}

void Displayable::setId(int roomPart, int thingPart) {
    id = new TwoTuple(roomPart, thingPart);
}

void Displayable::setVisible() {
    visible = true;
}

void Displayable::setInvisible() {
    visible = false;
}

bool Displayable::isVisible() {
    return visible;
}

bool Displayable::isInvisible() {
    return !visible;
}

void Displayable::setHallucinating(bool stateOfMind) {
    hallucinating = stateOfMind;
}

bool Displayable::isHallucinating() {
    return hallucinating;
}

// TODO: needed here?
int Displayable::getRandom(int ub) {
    int retval = (ub == 0) ? 0 : -1;//rand.nextInt(ub); //TODO figure out random C++
    return retval;
}

void Displayable::draw() {
    ObjectDisplayGrid::getGrid()->add(this);
}

std::string Displayable::toString() {
    std::string str = "   type: " + type; //Prints struct null not valid for creatures for some reason
    if (id == NULL) {
        str += "   id: null\n";
    } else {
        str += "   id: " + id->toString() + "\n";
    }

    str += "   name: " + name + "\n";
    str += "   posX: " + std::to_string(posX) + ", ";
    str += "posY: " + std::to_string(posY) + "\n";
    return str;
}

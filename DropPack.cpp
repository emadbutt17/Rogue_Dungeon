//
// Created by constantine on 9/13/20.
//

#include "DropPack.h"

DropPack::DropPack(std::string name, Displayable* owner) :CreatureAction(owner){ //TODO: Is it ok that owner is Displayal (instead of player)
    this->name = name;
}

std::string DropPack::toString() {
    std::string str = "DropPack " + this->msgText;
    return str;
}

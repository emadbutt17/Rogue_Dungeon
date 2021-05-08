//
// Created by constantine on 9/13/20.
//

#include "EndGame.h"

EndGame::EndGame(std::string name, Creature* owner): CreatureAction(owner) {
    this->name = name;
}

std::string EndGame::toString() {
    std::string str = "EndGame " + msgText;
    str += " name " + name;
    return str;
}

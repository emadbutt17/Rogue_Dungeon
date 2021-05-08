#include "TeleportOwner.h"


TeleportOwner::TeleportOwner(std::string name, Creature* owner): CreatureAction(owner){
    this->name = name;

}

std::string TeleportOwner::toString() {
    std::string str = "Teleport " + msgText;
    return str;
}
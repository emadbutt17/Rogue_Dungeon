#include "ChangeDisplayType.h"

ChangeDisplayedType::ChangeDisplayedType(std::string name, Creature* owner): CreatureAction(owner){
    this->name = name;

}

std::string ChangeDisplayedType::toString() {
    std::string str = "ChangeDisplayCharacter z";
    str += " name " + this->name;
    return str;
}

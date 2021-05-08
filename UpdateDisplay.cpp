#include "UpdateDisplay.h"


UpdateDisplay::UpdateDisplay(std::string name, Creature* owner): CreatureAction(owner){
    this->name = name;

}

std::string UpdateDisplay::toString() {
    std::string str = "UpdateDisplay " + msgText;
    str += " name " + name;
    return str;
}
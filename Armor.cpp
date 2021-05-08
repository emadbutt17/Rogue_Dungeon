#include "Armor.h"

Armor::Armor(std::string name){
    type = DungeonChar::ARMOR;
    this->name = name;
}

std::string Armor::toString() {
    std::string str = this->CLASSID;
    str += Item::toString();
    if (this->visible) {
        str = "visible ";
    }
    str += "Armor: " + type;
    return str;
}

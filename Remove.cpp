#include "Remove.h"

Remove::Remove(std::string name, Creature* owner): CreatureAction(owner){
    this->name = name;

}

std::string Remove::toString() {
    std::string str = "Remove " + msgText;
    return str;
}

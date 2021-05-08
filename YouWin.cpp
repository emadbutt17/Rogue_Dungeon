#include "YouWin.h"


YouWin::YouWin(std::string name, Creature* owner): CreatureAction(owner){
    this->name = name;

}

std::string YouWin::toString() {
    std::string str = "Print " + msgText;
    return str;
}
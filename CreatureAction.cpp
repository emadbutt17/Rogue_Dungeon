#include "CreatureAction.h"

CreatureAction::CreatureAction(Displayable* owner):Action(owner){
    this->owner = (Displayable*)  owner;
}
Creature* CreatureAction::getOwner(){
    return  (Creature*) owner;
}



#include "ItemAction.h"

ItemAction::ItemAction(Item* owner): Action(owner){
    this->owner = owner;
}
Item* ItemAction::getOwner(){
    return  (Item*) owner;
}


#ifndef ITEMACTION_H_
#define ITEMACTION_H_

#include "Action.h"
#include "Item.h"

class ItemAction : Action{

public:
    ItemAction(Item* owner);
    virtual Item* getOwner();

protected:
    std::string msgText;
    //Item owner; //TODO: is this supposed to be here? Not in analagous CreatureAction
};

#endif



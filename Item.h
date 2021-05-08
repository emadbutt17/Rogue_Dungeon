#ifndef ITEM_H_
#define ITEM_H_

#include <vector>
#include "Displayable.h"
//Resolve Circular dependencies:
//#include "CreatureAction.h"
class CreatureAction;  //Item > CreatureAction > Creature > Item
//#include "ItemAction.h"
class ItemAction; //Item > ItemAction > Item
class Creature;

class Item : public Displayable{
    
protected:
    Displayable* owner = nullptr;
    int intValue = -1;
    std::vector<ItemAction*> itemActions;
    std::vector<CreatureAction*> creatureActions;
public:
    Item();
    virtual void setOwner(Displayable* newOwner);
    virtual void setIntValue(int ah);
    virtual void setItemAction(ItemAction* action);

    bool hasOwner();

    /**
     * Adds the item to the dungeon at the position, clearing the owner
     * @param x  X pos
     * @param y  Y pos
     */
    virtual void addToDungeon(int x, int y);

    /**
     * Adds the item to the given creature
     * @param owner  New owner
     */
    virtual void addToCreature(Creature* owner);
};


#endif




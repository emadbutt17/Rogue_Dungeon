//
// Created by constantine on 9/13/20.
//

#include "Dungeon.h"
#include "Item.h"

Item::Item() {
}

void Item::setOwner(Displayable* newOwner) {
    owner = newOwner;
}

void Item::setIntValue(int ah) {
    intValue = ah;
}

void Item::setItemAction(ItemAction* action) {
    itemActions.push_back(action);
}

bool Item::hasOwner() {
    return owner != nullptr;
}

void Item::addToDungeon(int x, int y) {
    setPos(x, y);
    setOwner(nullptr);
    Dungeon::getDungeon()->addItem(this);
}

void Item::addToCreature(Creature* owner) {
    setPos(-1, -1);
    setOwner(owner);
    Dungeon::getDungeon()->removeItem(this);
}

#pragma once

#include "ObjectDisplayGrid.h"
#include <string>
#include <queue>
#include "Item.h"
#include "Armor.h"
#include "Sword.h"
#include "Creature.h"

class Player : public Creature {
private:
    const int DEBUG = 1;
    const std::string CLASSID = "game.displayable.creature.Player";
    const int MAX_PACK_SIZE = 5;
    int moveCount = 0;
    int score = 0;
    // inventory
    Sword* weapon = NULL;
    Armor* armor = NULL;
    std::vector<Item*> pack;

public:
    Player(std::string name);
    std::string toString();

    // pack

    /**
     * Adds the given item to the pack
     * @param item  Item to add
     */
    void addToPack(Item* item);

    /**
     * Picks up an item from the current player position
     */
    void pickupItem();

    /**
     * Removes the item at the given index from the pack
     * @param index  Item index in the pack
     * @return Removed item, NULL if nothing removed
     */
    Item* removeFromPack(int index);

    /**
     * Picks up an item from the current player position
     */
    void dropItem(int index);

    /**
     * Sets the given item to the current player armor. Adds it to the pack if not present
     * @param armor  New armor
     */
    void setArmor(Armor* armor);

    /**
     * Sets the given item to the current player weapon. Adds it to the pack if not present
     * @param weapon  New weapon
     */
    void setWeapon(Sword* weapon);

    /**
     * Checks if the pack is empty
     * @return true if the pack is empty
     */
    virtual bool packEmpty();

    /**
     * Displays all the items in the pack
     */
    virtual void displayPack();

    /**
     * Hide display of the pack
     */
    virtual void hidePack();

    // health

    /**
     * Adds or removes HP, also runs relevant update functions
     * @param amount  Amount to add. Make negaitve to subtract
     */
    virtual void addHp(int amount);

    /**
     * Updates the display of HP and score in the object display grid top line
     */
    virtual void updateStatus();
};



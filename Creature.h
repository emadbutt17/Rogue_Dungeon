#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>
#include <vector>
//#include "Dungeon.h" //Commented out to resolve dependencies (also not needed here)
#include "ObjectDisplayGrid.h"
#include "CreatureAction.h"
//class CreatureAction; //Forward declaration to deal with circular dependencies.
#include "Displayable.h"

#include "Item.h"



class Creature : public Displayable{
private:
    const int DEBUG = 0;
    const std::string CLASSID = "CREATURE";
protected:
    std::string name;
    int damageInflicted = -1;
    int hp = -1;
    int hpMoves = 0;
    int score = 0;
    std::vector<CreatureAction *> deathActions;
    std::vector<CreatureAction *> hitActions;
    std::vector<Item *> pack;


public:
    Creature();
    Creature(char type);

    /**
     * Moves the create the given amount
     * @param x  X offset
     * @param y  Y offset
     */
	virtual void move(int x, int y);
    virtual std::string toString();
    virtual void setHpMoves(int hpm);
    virtual void addHitAction(CreatureAction* da);
    virtual void addDeathAction(CreatureAction* ha);

    /**
     * Sets the initial HP for the creature. Does not perform actions on HP update
     * @param h  Initial HP
     */
    virtual void setHp(int h);

    /**
     * Checks if the creature is alivve
     * @return  true if alive
     */
    virtual bool isAlive();

    /**
     * Adds or removes HP, also runs relevant update functions
     * @param amount  Amount to add. Make negaitve to subtract
     */
    virtual void addHp(int amount);

    /**
     * Handles a collision at the given position
     * @param x  X position
     * @param y  Y position
     * @return  True if the player collided with something. False if there is no monster at the space
     */
    virtual bool handleCollision(int x, int y);

    /**
     * Damages the creature
     * @param maxHit  Maximum damage to deal
     * @return  Damage dealt
     */
    virtual int damage(int maxHit);

    /**
     * Called when the creature dies
     */
    virtual void handleDeath();
};

#endif



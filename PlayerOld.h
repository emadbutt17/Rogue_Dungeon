#pragma once

#include "GridChar.h"
#include "ObjectDisplayGrid.h"
#include <string>
#include <queue>
#include "Item.h"
#include "Armor.h"
#include "Sword.h"
#include "Creature.h"


class Player : public GridChar {
private:
	ObjectDisplayGrid* grid;
    const int DEBUG = 1;
    const std::string CLASSID = "game.displayable.creature.Player";
    std::queue<char> inputQueue;
    Item* weapon = NULL;
    const int MAX_PACK_SIZE = 5;
    Item* armor = NULL;
    int moveCount = 0;


public:
	Player(ObjectDisplayGrid* grid, int x, int y);
    std::string toString() ;
    void setArmor(Armor* armor) ;
    void setWeapon(Sword* sword) ;
    void move(int x, int y) ;


    };




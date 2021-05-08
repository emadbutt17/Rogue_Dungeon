//
// Created by constantine on 9/13/20.
//

#ifndef ROGUE_DUNGEON_DROPPACK_H
#define ROGUE_DUNGEON_DROPPACK_H

#include <string>
#include "Creature.h"
#include "CreatureAction.h"
#include "ObjectDisplayGrid.h"
#include "Player.h"

class DropPack: public CreatureAction{
private:
    const std::string CLASSID = "DropPack";
public:
    //DropPack(std::string name, Player* owner) ;
    DropPack(std::string name, Displayable* owner) ;
    std::string toString() ;
};


#endif //ROGUE_DUNGEON_DROPPACK_H

//
// Created by constantine on 9/13/20.
//

#ifndef ROGUE_DUNGEON_ENDGAME_H
#define ROGUE_DUNGEON_ENDGAME_H
#include <string>
#include "CreatureAction.h"
#include "Creature.h"
#include "ObjectDisplayGrid.h"
#include "Dungeon.h"

class EndGame : public CreatureAction{
private:
    const std::string CLASSID = "EndGame";
    const int DEBUG = 0;
public:
    EndGame(std::string name, Creature* owner);
    std::string toString();
};

#endif //ROGUE_DUNGEON_ENDGAME_H

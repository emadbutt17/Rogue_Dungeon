#ifndef TELEPORTOWNER_H_
#define TELEPORTOWNER_H_

#include <string>
#include "TwoTuple.h"
#include "Creature.h"
#include "Dungeon.h"
#include "CreatureAction.h"

class TeleportOwner : public CreatureAction{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "Teleport";
public:
    TeleportOwner(std::string name, Creature* owner);
    std::string toString() ;

};


#endif

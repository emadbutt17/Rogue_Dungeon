#ifndef MONSTER_H_
#define MONSTER_H_

#include <string.h>
#include "Displayable.h"
#include "CreatureAction.h"
#include "Creature.h"

class Monster: public Creature{
private:
    const int DEBUG = 0;
    const std::string CLASSID = "Monster";
public:
    Monster();
    //std::string toString() ;
};

#endif




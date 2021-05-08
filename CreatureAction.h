#ifndef CREATUREACTION_H_
#define CREATUREACTION_H_

#include "Action.h"
//#include "Creature.h"
class Creature;

class CreatureAction : public Action{

public:
    CreatureAction(Displayable* owner); //TODO: IS it okay that owner is Displayable* instead of Creature*? Throws an error when calling constructor otherwise (type mistmach)
    Creature* getOwner();

};

#endif



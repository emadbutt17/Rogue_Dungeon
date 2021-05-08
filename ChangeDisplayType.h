#ifndef CHANGEDISPLAYTYPE_H_
#define CHANGEDISPLAYTYPE_H_

#include <string>
#include "ObjectDisplayGrid.h"
//#include "Player.h"
#include "Creature.h"
#include "CreatureAction.h"

class ChangeDisplayedType : public CreatureAction{

private:
    const int DEBUG = 1;
    const std::string CLASSID = "ChangeDisplayCharacter";
public:
    ChangeDisplayedType(std::string name, Creature* owner);
    std::string toString() ;

};


#endif

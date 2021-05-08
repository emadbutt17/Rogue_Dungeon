#ifndef UPDATEDISPLAY_H_
#define UPDATEDISPLAY_H_

#include <string>
#include "Creature.h"
#include "CreatureAction.h"

class UpdateDisplay : public CreatureAction{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "UpdateDisplay";
public:
    UpdateDisplay(std::string name, Creature* owner);
    std::string toString() ;


    };


#endif

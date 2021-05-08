#ifndef YOUWIN_H_
#define YOUWIN_H_

#include <string>
#include "Creature.h"
#include "CreatureAction.h"

class YouWin : public CreatureAction{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "YouWin";
public:
    YouWin(std::string name, Creature* owner);
    std::string toString() ;

};


#endif

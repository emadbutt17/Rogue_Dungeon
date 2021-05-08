#ifndef REMOVE_H_
#define REMOVE_H_

#include <string>
#include "ObjectDisplayGrid.h"
#include "Creature.h"
#include "CreatureAction.h"

class Remove : public CreatureAction{

private:
    const std::string CLASSID = "Remove";
public:
    Remove(std::string name, Creature* owner);
    std::string toString();


    };


#endif

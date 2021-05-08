//
// Created by constantine on 9/13/20.
//

#ifndef ROGUE_DUNGEON_HALLUCINATE_H
#define ROGUE_DUNGEON_HALLUCINATE_H
#include "Dungeon.h"
#include "Item.h"
#include "ObjectDisplayGrid.h"
#include "Displayable.h"
#include "ItemAction.h"
#include <string>

class Hallucinate : public ItemAction{
private:
    const std::string CLASSID = "Hallucinate";
    const int DEBUG = 0;
    int counter = 0;
public:
    Hallucinate(Item* owner);
    std::string toString();

    };

#endif //ROGUE_DUNGEON_HALLUCINATE_H

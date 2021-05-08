//
// Created by constantine on 9/13/20.
//

#ifndef ROGUE_DUNGEON_BLESCURSEITEM_H
#define ROGUE_DUNGEON_BLESCURSEITEM_H

#include "Item.h"
#include "ObjectDisplayGrid.h"
//#include "Player.h"
#include "ItemAction.h"
#include <string>

class BlessCurseItem : public ItemAction{
private:
    const std::string CLASSID = "BlessCuseItemAction";
    const int DEBUG = 0;
    int counter = 0;
public:
    BlessCurseItem(Item* owner);
    std::string toString() ;

    };

#endif //ROGUE_DUNGEON_BLESCURSEITEM_H

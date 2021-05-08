#ifndef SCROLL_H_
#define SCROLL_H_

#include "ObjectDisplayGrid.h"
#include "DungeonChar.h"
//#include "ItemAction.h"
//#include "CreatureAction.h"
#include "Item.h"

class Scroll : public Item{

private:
    bool unread = true;

public:
    Scroll(std::string name);


};

#endif



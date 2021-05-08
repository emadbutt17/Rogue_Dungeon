#ifndef ARMOR_H_
#define ARMOR_H_

#include <vector>
#include <string>
#include "DungeonChar.h"
//#include "ItemAction.h"
class ItemAction;
#include "ObjectDisplayGrid.h"

#include "Item.h"

class Armor : public Item{

private:
    const std::string CLASSID = "Armor";
    std::vector<ItemAction*> immunities;

public:
    Armor(std::string name);
    std::string toString() ;

};

#endif



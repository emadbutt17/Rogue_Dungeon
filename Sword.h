#ifndef SWORD_H_
#define SWORD_H_

#include <vector>
#include <string>
#include "ObjectDisplayGrid.h"
#include "DungeonChar.h"
#include "Displayable.h"
#include "Item.h"

class Sword : public Item{

private:
    const std::string CLASSID = "DefaultSword";

public:
    Sword(std::string name);


};


#endif



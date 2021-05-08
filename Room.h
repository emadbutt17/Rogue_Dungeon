#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include "ObjectDisplayGrid.h"
#include "Item.h"
#include "Displayable.h"
#include "Creature.h"
#include "Structure.h"

class Room : public Structure {

private:
    const int DEBUG = 1;
    const std::string CLASSID = "Room";

    Displayable floor;
public:
    Room(std::string name) ;
    std::string toString() ;

    // abstract methods
    virtual bool canMove(int x, int y);
    virtual void draw();
};


#endif

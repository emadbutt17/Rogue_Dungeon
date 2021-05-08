#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <string>
#include <vector>
#include "Item.h"
#include "Creature.h"
#include "Displayable.h"

class Structure : public Displayable{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "Structure";
protected:
    int width = -1;
    int height = -1;
    std::string name = "???";
    std::vector<Creature *> creatures;
    std::vector<Item *> items;
public:
    Structure(char type);

    virtual void addCreature(Creature* c);
    virtual void addItem(Item* m);
    virtual void setWidth(int w);
    virtual void setHeight(int h);
    virtual std::string toString();

    /**
     * Checks if a creature can move into the given space
     * @param x  X position
     * @param y  Y position
     * @return  True if the space is availble
     */
    virtual bool canMove(int x, int y) = 0;

    /**
     * Draws this displayable to the display grid
     */
    virtual void draw() = 0;
};

#endif



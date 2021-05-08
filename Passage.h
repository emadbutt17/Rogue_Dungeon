#ifndef PASSAGE_H_
#define PASSAGE_H_

#include <vector>
#include <string>
#include "TwoTuple.h"
#include "ObjectDisplayGrid.h"
#include "Item.h"
#include "Creature.h"
#include "Structure.h"

class Passage : public Structure{

private:
    const int DEBUG = 0;
    const std::string CLASSID = "Passage";

    // note Prof. Midkiff used a two tuple object here, kept as two vectors for simplicity (more like students would do)
    std::vector<int> xVec;
    std::vector<int> yVec;

    std::vector<Creature* > creatures;
    std::vector<Item* > items;

    Displayable door;

public:
    Passage(std::string name) ;
    virtual void setPosX(int x) ;
    virtual void setPosY(int y) ;
    std::string toString() ;

    // abstract methods
    virtual bool canMove(int x, int y);
    virtual void draw();
};


#endif

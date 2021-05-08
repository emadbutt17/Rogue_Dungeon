#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_
#include "TwoTuple.h"

class Displayable {

private:
     const int DEBUG = 0;
     bool hallucinating = false;
     const std::string CLASSID = "Displayable";
protected:
    char type;
    TwoTuple* id = NULL;
    int posX = -1;
    int posY = -1;
    int maxHit = -1;
    std::string name;
    int getRandom(int ub);
    Displayable();
public :
    Displayable(char _type);

    // TODO: some of these can move to subclasses

    // getters
    virtual TwoTuple* getId();
    virtual std::string getName();
    virtual char getType();
    virtual int getPosX();
    virtual int getPosY();
    virtual int getMaxHit();
    virtual bool isVisible();
    virtual bool isInvisible();
    bool isHallucinating();
    virtual std::string toString();

    // setters
    virtual void setId(int roomPart, int thingPart);
    virtual void setName(std::string n);
    virtual void setType(char t);
    virtual void setPos(int x, int y);
    virtual void setPosX(int x);
    virtual void setPosY(int y);
    virtual void setMaxHit(int hits);
    virtual void setVisible();
    virtual void setInvisible();
    void setHallucinating(bool stateOfMind);

    // TODO: does this need to be public?
    bool visible = true;

    /**
     * Draws this displayable to the display grid
     */
    virtual void draw();
};

#endif



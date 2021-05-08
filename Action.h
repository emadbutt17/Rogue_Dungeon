#ifndef ACTION_H_
#define ACTION_H_

#include "Displayable.h"
#include <string>
//#include "Creature.h" //Commented out to resolve circular dependency of Action and Creature Action
class Creature; //forward declare to resolve dependency 
class Action{

private:
    const std::string CLASSID = "game.action.Action";
    const int DEBUG = 0;

protected:
    std::string msgText;
    std::string name;
    Displayable* owner; 
    int intValue;
    char charValue;

public:
    Action(Displayable* owner);
    virtual void setOwner(Displayable * owner); 
    virtual void setMessage(std::string msg);
    virtual void setIntValue(int v);
    virtual void setCharValue(char v) ;
};



#endif



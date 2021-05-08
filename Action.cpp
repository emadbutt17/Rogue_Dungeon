//
// Created by constantine on 9/13/20.
//

#include "Action.h"
#include <iostream>

Action::Action(Displayable* owner) { //TODO: Should this be displayable? Doesn't make sense for anything but a creature to do an action
    this->owner = owner;
}

void Action::setOwner(Displayable* owner) {
    this->owner =  owner;
}

void Action::setMessage(std::string msg) {
    std::cout << CLASSID + ".setMessage: " + msg << std::endl;
    msgText = msg;
}

void Action::setIntValue(int v) {
    if (DEBUG > 0) {
        std::cout << CLASSID + ".setIntValue v: " << v<< std::endl;
    }
    intValue = v;
}

void Action::setCharValue(char v) {
    if (DEBUG > 0) {
        std::cout << CLASSID + ".setCharValue v: " << v << std::endl;
    }
    charValue = v;
}

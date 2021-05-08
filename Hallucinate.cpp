//
// Created by constantine on 9/13/20.
//

#include "Hallucinate.h"

Hallucinate::Hallucinate(Item* owner): ItemAction(owner) {
    //ObjectDisplayGrid.getObjectDisplayGrid().registerInputObserver(this); // TODO: Figure out how to translate this to C++
}

std::string Hallucinate::toString() {
    std::string str = "Print " + msgText;
    return str;
}
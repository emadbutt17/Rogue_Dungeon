//
// Created by constantine on 9/13/20.
//

#include "BlessCurseItem.h"

BlessCurseItem::BlessCurseItem(Item* owner): ItemAction(owner) {
}

std::string BlessCurseItem::toString() {
    std::string str = "Print " + msgText;
    return str;
}

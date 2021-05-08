//
// Created by constantine on 9/13/20.
//

#include "Creature.h"
#include "Dungeon.h"
#include <assert.h>
#include <sstream>

Creature::Creature(char type) : Displayable(type) {}

Creature::Creature() : Creature('?') {}

void Creature::move(int x, int y) {
	int newX = this->posX + x;
	int newY = this->posY + y;
    // first, check if we collide with another creature
    if (!handleCollision(newX, newY)) {
        // if not, check if the space is empty to move to
        if (Dungeon::getDungeon()->canMove(newX, newY)) {
            ObjectDisplayGrid* display = ObjectDisplayGrid::getGrid();
            display->remove(this);
            this->posX = newX;
            this->posY = newY;
            display->add(this);
            display->update();
        }
    }
}

void Creature::setHp(int h) {
    assert (hp < 100 && hp > -100) ;//: CLASSID + ".setHP hp bad value, h is " + h.to_string();
    hp = h;
}

bool Creature::isAlive() {
    return hp > 0;
}

int Creature::damage(int maxHit) {
    // deal random damage up to maxHit
    // TODO: armor and weapon
    int damage = rand() % (maxHit + 1);
    if (damage > 0) {
        addHp(-damage);
    }
    return damage;
}

void Creature::addHp(int amount) {
    // TODO: min and max
    hp += amount;
    // TODO: run death actions
    if (hp <= 0) {
        handleDeath();
    }
}

void Creature::handleDeath() {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    grid->remove(this);
    grid->update();
}

void Creature::setHpMoves(int hpm) {
    hpMoves = hpm;
}

void Creature::addDeathAction(CreatureAction* da) {
    deathActions.push_back(da);
}

bool Creature::handleCollision(int x, int y) {
    Creature* creature = Dungeon::getDungeon()->getCreatureAt(x, y);
    if (creature != nullptr) {
        // damage the creature
        // if the creature is still alive, they damage us back
        std::stringstream msg;
        msg << "Dealt ";
        msg << creature->damage(this->getMaxHit());
        msg << " damage";
        if (creature->isAlive()) {
            msg << ", took ";
            msg << this->damage(creature->getMaxHit());
            msg << " damage";
        }
        ObjectDisplayGrid::getGrid()->writeToBottom(0, msg.str());
        return true;
    }
    return false;
}

void Creature::addHitAction(CreatureAction* ha) {
    hitActions.push_back(ha);
}

std::string Creature::toString() {
    std::string str = "Creature: " + id->toString() + "\n";
    str += Displayable::toString();
    str += "   name: " + name + "\n";

    str += "   immunities: ";

    str += "   deathAction: ";
    for (CreatureAction* deathAction : deathActions) {
        str += "      " ;//+ deathAction->toString(); //TODO: Define to string for actions!
    }

    str += "   hitActions: ";
    for (CreatureAction* hitAction : hitActions) {
        str += "      " ;//+ hitAction->toString();//TODO: Define to string for actions!
    }
    return str;
}

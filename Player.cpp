#include "Player.h"
#include "Dungeon.h"
#include <string>
#include <sstream>

Player::Player(std::string name) : Creature('@') {
    this->name = name;
}

std::string Player::toString() {
    //return Creature::toString();
    return "The player";
}

// inventory

void Player::addToPack(Item* item) {
    if (std::find(pack.begin(), pack.end(), item) == pack.end()) {
        pack.push_back(item);
    }
    item->addToCreature(this);
}

void Player::pickupItem() {
    // no pickup if the pack is full
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    if (pack.size() >= 9) {
        grid->writeInfo("Player pack is full");
        return;
    }

    // get an item at the player position
    Dungeon* dungeon = Dungeon::getDungeon();
    // TODO: handle multiple items at the position
    Item* item = dungeon->getItemAt(posX, posY);
    if (item) {
        grid->remove(item);
        addToPack(item);
        grid->writeInfo("Picked up item " + item->getName());
    }
    else {
        grid->writeInfo("No item at player position");
    }
}

Item* Player::removeFromPack(int index) {
    if (index < pack.size()) {
        // get the item from the pack
        Item* item = pack[index];
        // place it in the dungeon
        item->addToDungeon(posX, posY);
        // erase it
        pack.erase(pack.begin() + index);
        // unequip it if equipt
        if (item == weapon) {
            weapon == nullptr;
        }
        if (item == armor) {
            armor == nullptr;
        }
        // return item
        return item;
    }
    return nullptr;
}

void Player::dropItem(int index) {
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid();
    // if we have an item, set it to the current position
    Item* item = removeFromPack(index);
    if (item) {
        // draw the item on the grid below the player
        grid->remove(this);
        grid->add(item);
        grid->add(this);
        grid->writeInfo("Dropped item " + item->getName());
    }
    else {
        grid->writeInfo("No item at index " + std::to_string(index));
    }
}

void Player::setArmor(Armor* armor) {
    this->armor = armor;
    addToPack(armor);
}

void Player::setWeapon(Sword* sword) {
    weapon = sword;
    addToPack(sword);
}

// health

void Player::addHp(int amount) {
    Creature::addHp(amount);
    updateStatus();
}

void Player::updateStatus() {
    ObjectDisplayGrid::getGrid()->writeToTop(0, "HP: " + std::to_string(hp) + ", Score: " + std::to_string(score));
}

bool Player::packEmpty() {
    return pack.empty();;
}

void Player::displayPack() {
    std::stringstream packStr;
    packStr << "Pack: ";
    // print lovely empty message
    if (pack.empty()) {
        packStr << "Empty";
    }
    else {
        for (int i = 0; i < pack.size(); i++) {
            packStr << i + 1 << ": " << pack[i]->getName();
            if (pack[i] == weapon) {
                packStr << " (h)";
            }
            if (pack[i] == armor) {
                packStr << "(w)";
            }

            packStr << "  ";
        }
    }
    ObjectDisplayGrid::getGrid()->writePack(packStr.str());
}

void Player::hidePack() {
    ObjectDisplayGrid::getGrid()->writePack("");
}



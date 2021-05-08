#include "Dungeon.h"
#include <iostream>
#include <cassert>

Dungeon* Dungeon::INSTANCE = nullptr; //Define static variable outside of class declaration

Dungeon* Dungeon::getDungeon(std::string dungeonName, int width, int height, int top, int bottom) {
    if (INSTANCE == NULL) {
        INSTANCE = new Dungeon(dungeonName, width, height, top, bottom);
    }
    return INSTANCE;
}

Dungeon* Dungeon::getDungeon() {
    if (INSTANCE == NULL) {
        std::cerr << "Attempted to call getDungeon on uninitialized dungeon" << std::endl;
        exit(1);
    }
    return INSTANCE;
}

Dungeon::Dungeon(std::string _name, int width, int height, int top, int bottom)
    : name(_name), gameWidth(width), gameHeight(height), topHeight(top), bottomHeight(bottom) {
}

Dungeon::~Dungeon() {
    for (Room* obj : rooms) {
        delete obj;
    }
    rooms.clear();
    for (Passage* obj : passages) {
        delete obj;
    }
    passages.clear();
    for (Item* obj : items) {
        delete obj;
    }
    items.clear();
    for (Creature* obj : creatures) {
        delete obj;
    }
    creatures.clear();
    player = nullptr;
}

// properties

int Dungeon::getGameHeight() {
    return this->gameHeight;
}

int Dungeon::getGameWidth() {
    return this->gameWidth;
}

int Dungeon::getTopHeight() {
    return this->topHeight;
}

int Dungeon::getBottomHeight() {
    return this->bottomHeight;
}

// vectors

void Dungeon::addRoom(Room* room) {
    //std::cout << CLASSID <<  ".addRoom adding Room to Dugneon" << std::endl;
    rooms.push_back(room);
}

std::vector<Room*>& Dungeon::getRooms() {
    return rooms;
}

void Dungeon::addPassage(Passage* passage) {
    passages.push_back(passage);
}

std::vector<Passage*>& Dungeon::getPassages() {
    return passages;
}

void Dungeon::addCreature(Creature* creature) {
    creatures.push_back(creature);
}

std::vector<Creature*>& Dungeon::getCreatures() {
    return creatures;
}

void Dungeon::setPlayer(Player* pl) {
    if (DEBUG > 0) {
        std::cout << CLASSID <<  ".addPlayer "  << std::endl;
    }
    // assert (player == null) : "game.Dungeon.addPlayer: attempting to add second player "+player;
    this->player = pl;
    addCreature(pl);
}

Player* Dungeon::getPlayer() {
    return player;
}

void Dungeon::addItem(Item* item) {
    items.push_back(item);
}

std::vector<Item*>& Dungeon::getItems() {
    return items;
}

void Dungeon::removeItem(Item* item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

Item* Dungeon::getItemAt(int x, int y) {
    // loop backwards, the item most recently added to the dungeon is the one on top
    // handles dropping multiple items on the same space, as we remove from the dungeon when the item is grabbed
    for (std::vector<Item*>::reverse_iterator iterator = items.rbegin(); iterator != items.rend(); iterator++) {
        Item* item = *iterator;
        if (!item->hasOwner() && item->getPosX() == x && item->getPosY() == y) {
            return item;
        }
    }
    return nullptr;
}

void Dungeon::draw() {
    // draw rooms first, then passages for the sake of overlaps
    for (Room* room : rooms) {
        room->draw();
    }
    for (Passage* passage : passages) {
        passage->draw();
    }

    // then add creatures and items in
    for (Item* item : items) {
        // owned items are invisible
        if (!item->hasOwner()) {
            item->draw();
        }
    }
    for (Creature* creature : creatures) {
        creature->draw();
    }

    // update after everything was drawn
    ObjectDisplayGrid::getGrid()->update();
}

bool Dungeon::canMove(int x, int y) {
    // try all rooms, then all passages
    for (Room* room : rooms) {
        if (room->canMove(x, y)) {
            return true;
        }
    }
    for (Passage* passage : passages) {
        if (passage->canMove(x, y)) {
            return true;
        }
    }

    return false;
}

Creature* Dungeon::getCreatureAt(int x, int y) {
    for (Creature* creature : creatures) {
        if (creature->isAlive() && creature->getPosX() == x && creature->getPosY() == y) {
            return creature;
        }
    }
    return nullptr;
}
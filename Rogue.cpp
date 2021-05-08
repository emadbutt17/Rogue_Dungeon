#include "ObjectDisplayGrid.h"
#include "Player.h"
#include "KeyboardListener.h"
#include "Dungeon.h"
#include "MyXMLHandler.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>  


Displayable* makeDisplayable(char type, int x, int y) {
    Displayable* displayable = new Displayable(type);
    displayable->setPos(x, y);
    return displayable;
}

int main(int argc, char* argv[]) {
    // get filename from command line
    std::string fileName;
    switch (argc) {
    case 2:
        fileName = "./xmlFiles/" + ((std::string) argv[1]);
        break;
    case 3:
        fileName = "xmlFiles/" + ((std::string) argv[1]);
        break;
    default:
        std::cout << "Usage:" << std::endl;
        std::cout << "   C++ Rogue <dungeon filename>" << std::endl;
        return -1;
    }
    std::cout << fileName << std::endl;

    // parse dungeon
    Dungeon* dungeon = MyXMLHandler::parseDungeon(fileName);
    // create display grid
    ObjectDisplayGrid* grid = ObjectDisplayGrid::getGrid(
        dungeon->getGameWidth(), dungeon->getTopHeight(),
        dungeon->getGameHeight(), dungeon->getBottomHeight());

    // draw dungeon
    dungeon->draw();
    Player* player = dungeon->getPlayer();
    player->updateStatus();

    // set up keyboard listener
    srand(time(NULL));
    KeyboardListener* listener = new KeyboardListener(grid, player);
    listener->start();

    // cleanup
    delete listener;
    delete grid;
    delete dungeon;

    return 0;
}
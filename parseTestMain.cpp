#include <iostream>
#include <string>
#include "ObjectDisplayGrid.h"
#include "Dungeon.h"
#include "Player.h"
#include "KeyboardListener.h"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include "MyXMLHandler.h"
#include <exception>

/*
 * I have a bad habit of not using Make, but here is the compiler command I used (not that KeyboardListerner.cpp is not linked cuz its not needed for this testing main file):
 * g++ -g -I /home/croros/xerces-c-3.1.1-x86_64-linux-gcc-3.4/include/ -L /home/croros/xerces-c-3.1.1-x86_64-linux-gcc-3.4/lib/ Action.cpp Armor.cpp BlessCurseItem.cpp ChangeDisplayType.cpp Creature.cpp CreatureAction.cpp
 * Displayable.cpp DropPack.cpp DungeonChar.cpp Dungeon.cpp EndGame.cpp GridChar.cpp Hallucinate.cpp ItemAction.cpp Item.cpp Monster.cpp MyXMLHandler.cpp ObjectDisplayGrid.cpp
 * parseTestMain.cpp Passage.cpp Player.cpp Remove.cpp Room.cpp Scroll.cpp Structure.cpp Sword.cpp TeleportOwner.cpp TwoTuple.cpp UpdateDisplay.cpp YouWin.cpp -o test -lxerces-c -lncurses -std=c++11
 *
 */

int main(int argc, char* argv[]) {
    int DEBUG = 1;

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
            std::cout<<"Usage:"<< std::endl;
            std::cout<<"   C++ Rogue <dungeon filename>"<< std::endl;
            return -1;
    }
    std::cout<< fileName<< std::endl;

    // parse dungeon
    Dungeon* myDungeon = MyXMLHandler::parseDungeon(fileName);
    if (DEBUG > 0) {
        if (myDungeon != NULL) {
            std::cout << myDungeon << std::endl;
        } else {
            std::cout << "dungeon is null" << std::endl;
        }

        std::cout << "gameHeight: " + myDungeon->getGameHeight() << std::endl;
        std::cout << "width: " + myDungeon->getGameWidth() << std::endl;
        //std::cout<<"topHeight: " + ObjectDisplayGrid.getTopMessageHeight() << std::endl;
        //std::cout<<"bottomHeight: " + ObjectDisplayGrid.getBottomMessageHeight() << std::endl;
        for (Room* room : myDungeon->getRooms()) {
            std::cout << room->toString() << std::endl;
        }
        for (Passage* passage : myDungeon->getPassages()) {
            std::cout << passage->toString() << std::endl;
        }
        for (Item* item : myDungeon->getItems()) {
            std::cout << item->toString() << std::endl;
        }
        for (Creature* creature : myDungeon->getCreatures()) {
            std::cout << creature->toString() << std::endl;
        }
    }

    xercesc::XMLPlatformUtils::Terminate(); //valgrind will say there's memory errors if not included
	return 0;
}


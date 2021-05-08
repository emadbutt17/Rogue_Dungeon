#ifndef DUNGEONCHAR_H_
#define DUNGEONCHAR_H_


#include <string.h>
#include "Displayable.h"

class DungeonChar: public Displayable{

public:
    const std::string CLASSID = "CHAR";
    static const char INVISIBLE = ' ';
    static const char ROOMFLOOR = '.';
    static const char PASSAGEFLOOR = '#';
    static const char JUNCTION = '+';
    static const char ROOMWALL = 'X';
    static const char PLAYER = '@';
    static const char TROLL = 'T';
    static const char HOBGOBLIN = 'H';
    static const char SNAKE = 'S';
    static const char SCROLL = '%';
    static const char ARMOR = '[';
    static const char SWORD = '|';
    static const char GOLD = '$';


    const char DUNGEONCHARS[12] = {INVISIBLE, ROOMFLOOR, PASSAGEFLOOR, JUNCTION, ROOMWALL,
        PLAYER, TROLL, HOBGOBLIN, SNAKE,
        SCROLL, ARMOR, SWORD
    };

    const char CREATURECHARS[4] = {TROLL, HOBGOBLIN, SNAKE, PLAYER};
    const char ITEMCHARS[4] = {SCROLL, PLAYER, ARMOR, SWORD};

    DungeonChar(int x, int y, char t);


};



#endif

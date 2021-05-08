#ifndef DUNGEON_H_
#define DUNGEON_H_
#include <vector>
#include <queue>
#include "Room.h"
#include "Passage.h"
#include "Item.h"
#include "Creature.h"
#include "Player.h"
#include "Displayable.h"

class Dungeon { //TODO InputObserver, Runnable (pure virtual)

private:
    static Dungeon* INSTANCE;

    const std::string CLASSID = "Dungeon";
    const int DEBUG = 0;
    std::string name = NULL;
    std::vector<Room *> rooms;
    std::vector<Passage *> passages;
    std::vector<Item *> items;
    std::vector<Creature *> creatures;

    /** Player instance */
    Player* player = NULL;
    std::vector<TwoTuple> traversable;
    //std::queue<char> inputQueue;
    //TwoTuple* traversableCoordinateArray = NULL;
    bool traversableChanged = true;

    /** Keeps track of the game area size */
    int gameHeight, gameWidth;
    /** Keeps track of the how many lines from the top and bottom are reserved for text, to pass to display grid */
    int topHeight, bottomHeight;

    /**
     * Creates a new dungeon
     * @param name    Dungeon name
     * @param width   Dungeon width
     * @param height  Dungeon height
     * @param top     Top message area size
     * @param bottom  Bottom message area size
     */
    Dungeon(std::string dungeonName, int width, int height, int top, int bottom);

public:
    const bool TRAVERSABLE = true;
    const bool NOT_TRAVERSABLE = false;
    const bool NOT_EMPTY_OK = true;
    const bool SHOULD_BE_EMPTY = false;

    /**
     * Gets the current dungeon instance, assumes it was initialized in the parameterized function
     */
    static Dungeon* getDungeon();

    /**
     * Creates a new dungeon, or gets the singleton instance if fetched before
     * @param name    Dungeon name
     * @param width   Dungeon width
     * @param height  Dungeon height
     * @param top     Top message area size
     * @param bottom  Bottom message area size
     */
    static Dungeon* getDungeon(std::string dungeonName, int width, int height, int top, int bottom);

    ~Dungeon();

 
    bool gameOn = true;

    int getGameWidth();
    int getGameHeight();
    int getTopHeight();
    int getBottomHeight();

    // structure
    void addRoom(Room* room);
    std::vector<Room*>& getRooms();
    void addPassage(Passage* passage);
    std::vector<Passage*>& getPassages();

    // creatures
    void addCreature(Creature* creature);
    std::vector<Creature*>& getCreatures();
    void setPlayer(Player* player);
    Player* getPlayer();

    // items
    void addItem(Item* item);
    std::vector<Item*>& getItems();

    /**
     * Removes an item from the dungeon
     * @param item  Item to remove
     */
    void removeItem(Item* item);

    /**
     * Gets the item at the given position
     * @param x  X position
     * @param y  Y position
     * @return  Item at the position, nullprt if no creature is there
     */
    Item* getItemAt(int x, int y);

    /**
     * Draws the dungeon for the first time
     */
    virtual void draw();

    /**
     * Checks if a creature can move into the given space
     * @param x  X position
     * @param y  Y position
     * @return  True if the space is availble
     */
    virtual bool canMove(int x, int y);

    /**
     * Gets the creature at the given position
     * @param x  X position
     * @param y  Y position
     * @return  Creature at the position, nullprt if no creature is there
     */
    virtual Creature* getCreatureAt(int x, int y);
};

#endif



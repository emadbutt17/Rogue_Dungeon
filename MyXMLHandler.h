#ifndef MYXMLHANDLER_H_
#define MYXMLHANDLER_H_

#include <vector>
#include <stack>
#include <string>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include "Room.h"
#include "Dungeon.h"
#include "Displayable.h"
#include "ObjectDisplayGrid.h"
#include "Monster.h"

class MyXMLHandler : public xercesc::DefaultHandler{
private:
    int DEBUG = 2;
    std::string CLASSID = "MyXMLHandler";
    std::string data ;
    std::stack<Displayable* > displayableStack;
    std::stack<Action* > actionStack;
    Room* currentRoom = NULL;
    Dungeon* xmlDungeon = NULL;


    int topHeight = -1;
    bool bActionIntValue = false;
    bool bActionCharValue = false;
    bool bActionMessage = false;
    bool bItemIntValue = false;
    // SPM  bool bArmor = false;
    bool bBottomHeight = false;
    bool bDungeon = false;
    bool bGameHeight = false;
    bool bHeight = false;
    bool bHp = false;
    bool bHpMoves = false;
    bool bMaxhit = false;
    bool bPosX = false;
    bool bPosY = false;
    bool bRoom = false;
    bool bTopHeight = false;
    bool bType = false;
    bool bVisible = false;
    bool bWidth = false;

    void globalizeThingCoordinates(Displayable* room, Displayable* thing) ;

public:
    /**
     * Parses the given XML file into a dungeon. Mostly to make this cleaner between the step 1 and 2 test files, having this code in main is fine
     * @param path   filepath
     * @return dungeon  Parsed dungeon
     */
    static Dungeon* parseDungeon(std::string path);

    Dungeon* getDungeon();
    MyXMLHandler();
    void startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes);
    void endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName);
    void characters(const XMLCh * ch, const XMLSize_t	length );
    std::string toString();


};
#endif

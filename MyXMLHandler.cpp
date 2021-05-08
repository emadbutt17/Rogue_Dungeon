#include <iostream>
#include <algorithm>
#include "MyXMLHandler.h"
#include <type_traits>
#include <iostream>
#include <cassert>
#include "Scroll.h"
#include "Sword.h"
#include "Armor.h"
#include "Remove.h"
#include "YouWin.h"
#include "TeleportOwner.h"
#include "DropPack.h"
#include "ChangeDisplayType.h"
#include "UpdateDisplay.h"
#include "EndGame.h"
#include "BlessCurseItem.h"
#include "Hallucinate.h"

//From https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
    //return std::is_base_of<Base, T>::value; //Only works with senior-most parent class
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


//From https://www.tutorialspoint.com/case-insensitive-string-comparison-in-cplusplus
int case_insensitive_match(std::string s1, std::string s2) {
    //convert s1 and s2 into lower case strings
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower); //std overloads tolower, ::tolower is the definition in the global namespace
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1.compare(s2) == 0)
        return 1; //The strings are same
    return 0; //not matched
}

inline std::string boolToString(bool booleanValue){
    return booleanValue ? "true": "false";
}

std::string xmlChToString(const XMLCh* xmlChName, int length = -1){
    char * chStarName = xercesc::XMLString::transcode(xmlChName); //use char * because need to release buffer when done
    if(length == -1){
        std::string StrName(chStarName);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }
    else{
        std::string StrName(chStarName,0,length);
        xercesc::XMLString::release(&chStarName);
        return StrName;
    }



}

const XMLCh* getXMLChAttributeFromString(const xercesc::Attributes& attributes, const char * strGet){
    XMLCh * xmlChGet = xercesc::XMLString::transcode(strGet);
    const XMLCh * xmlChAttr = attributes.getValue(xmlChGet);
    xercesc::XMLString::release((&xmlChGet));
    return xmlChAttr;
}


Dungeon* MyXMLHandler::parseDungeon(std::string path) {
    try {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n";
        std::cout << "Exception message is: \n"
            << message << "\n";
        xercesc::XMLString::release(&message);
        exit(1);
    }

    Dungeon* myDungeon = NULL;
    try {
        xercesc::SAX2XMLReader* parser = xercesc::XMLReaderFactory::createXMLReader();
        MyXMLHandler* handler = new MyXMLHandler();
        parser->setContentHandler(handler);
        parser->setErrorHandler(handler);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
        //Encode string as UTF-16, but transcode needs casting as const char * (not std::string)
        XMLCh* fileNameXMLEnc = xercesc::XMLString::transcode(path.c_str());
        parser->parse(fileNameXMLEnc);
        xercesc::XMLString::release(&fileNameXMLEnc);
        myDungeon = handler->getDungeon();
        delete handler;
        delete parser;
    }
    catch (const xercesc::XMLException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        xercesc::XMLString::release(&message);
        exit(1);
    }
    catch (const xercesc::SAXParseException& toCatch) {
        char* message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        xercesc::XMLString::release(&message);
        exit(1);
    }
    catch (std::exception& e) {
        std::cout << e.what() << '\n';
        exit(1);
    }
    catch (...) {
        std::cout << "Unexpected Exception \n";
        exit(1);
    }

    //valgrind will say there's memory errors if not included
    xercesc::XMLPlatformUtils::Terminate();

    return myDungeon;
}

Dungeon* MyXMLHandler::getDungeon(){
    return xmlDungeon;
}
MyXMLHandler::MyXMLHandler(){
    //Doesn't do anything, empty stacks already Declared in header
}
void MyXMLHandler::startElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName, const xercesc::Attributes& attributes) {
	std:: cout << "Stack size:" << displayableStack.size() << std::endl;
    char * qNameStr = xercesc::XMLString::transcode(qName); //use char * because need to release buffer when done
    if (DEBUG > 1) {
        std::cout << CLASSID << ".startElement qName: " << qNameStr << std::endl;
    }
    if(case_insensitive_match(qNameStr,"Dungeon")){
        bDungeon = true;
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        int width = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"width")));
        topHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"topHeight")));
        if (DEBUG > 0) {
            std::cout << CLASSID << ".startElement topHeight: " << topHeight << std::endl;
        }
        int gameHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"gameHeight")));
        int bottomHeight = std::stoi(xmlChToString(getXMLChAttributeFromString(attributes,"bottomHeight")));
        //ObjectDisplayGrid.getObjectDisplayGrid(gameHeight, width, topHeight, bottomHeight);
        xmlDungeon = Dungeon::getDungeon(name, width, gameHeight, topHeight, bottomHeight);
        //displayableStack.push(xmlDungeon);

    }
    else if(case_insensitive_match(qNameStr,"Rooms")){
        // do nothing
    }
    else if(case_insensitive_match(qNameStr,"Room")){
        if(DEBUG > 0){
            std::cout << CLASSID <<  ".startElement ROOM encountered and created" <<std::endl;
        }
        bRoom = true;
        //std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name")); //Xml files don't have a name attributes,  though parserXML.pdf refers to it

        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        currentRoom = new Room("Room #"+room);
        xmlDungeon->addRoom(currentRoom);
        currentRoom->setId(std::stoi(room), 0);
        displayableStack.push(currentRoom);
    }
    else if(case_insensitive_match(qNameStr,"Monster")){
        Monster* monster = new Monster();
        xmlDungeon->addCreature(monster);
        currentRoom->addCreature(monster);
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        monster->setName(name);
        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        std::string serial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        monster->setId(std::stoi(room), std::stoi(serial));
        displayableStack.push(monster);
    }
    else if (case_insensitive_match(qNameStr,"Passages")) {
        // do nothing
    }
    else if(case_insensitive_match(qNameStr,"Passage")){
        //std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name")); //Based on XML file, Passages don't have names
        Passage* passage = new Passage("");
        xmlDungeon->addPassage(passage);
        std::string room1 = xmlChToString(getXMLChAttributeFromString(attributes,"room1"));
        std::string room2 = xmlChToString(getXMLChAttributeFromString(attributes,"room2"));
        passage->setId(std::stoi(room1), std::stoi(room2));
        displayableStack.push(passage);
    }
    else if(case_insensitive_match(qNameStr,"Player")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        Player* player = new Player(name);
        xmlDungeon->setPlayer(player);
        currentRoom->addCreature(player);
        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        std::string serial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        player->setId(std::stoi(room), std::stoi(serial));
        displayableStack.push(player);
    }
    else if(case_insensitive_match(qNameStr,"Scroll")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        Item* scroll = new Scroll(name);
        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        std::string serial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        displayableStack.push(scroll);
        scroll->setId(std::stoi(room), std::stoi(serial));

    }
    else if(case_insensitive_match(qNameStr,"Armor")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        Armor* armor = new Armor(name);
        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        std::string serial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        armor->setId(std::stoi(room), std::stoi(serial));
        displayableStack.push(armor);

    }
    else if(case_insensitive_match(qNameStr,"Sword")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        Sword* sword = new Sword(name);
        std::string room = xmlChToString(getXMLChAttributeFromString(attributes,"room"));
        std::string serial = xmlChToString(getXMLChAttributeFromString(attributes,"serial"));
        sword->setId(std::stoi(room), std::stoi(serial));
        displayableStack.push(sword);
    }
    else if(case_insensitive_match(qNameStr,"CreatureAction")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
        assert(instanceof<Creature>(displayableStack.top())) ; //: CLASSID + ".startElement, should be Creature, is " + displayableStack.top();
        Creature* owner = (Creature*) displayableStack.top();
        CreatureAction* action = NULL;
        if(name.compare("Remove")==0){
            action = new Remove(name, owner);
        }
        else if(name.compare("YouWin")==0) {
            action = new YouWin(name, owner);
        }
        else if(name.compare("Teleport")==0) {
            action = new TeleportOwner(name, owner);
        }
        else if(name.compare("UpdateDisplay")==0) {
            action = new UpdateDisplay(name, owner);
        }
        else if(name.compare("ChangeDisplayedType")==0) {
            action = new ChangeDisplayedType(name, owner);
        }
        else if(name.compare("EndGame")==0) {
            action = new EndGame(name, owner);
        }
        else if(name.compare("DropPack")==0) {
            action = new DropPack(name, (Player*) owner);
        }
        else {
            assert (false);// : CLASSID + ".startElement unknown action: " + name;
        }


        actionStack.push(action);
        if(type.compare("death")==0){
            owner->addDeathAction(action);
        }
        else if(type.compare("hit")==0){
            owner->addHitAction(action);
        }
        else{
            assert (false);// : CLASSID + ".startElement unknown action type: " + type;
        }

    }
    else if(case_insensitive_match(qNameStr,"ItemAction")){
        std::string name = xmlChToString(getXMLChAttributeFromString(attributes,"name"));
        std::string type = xmlChToString(getXMLChAttributeFromString(attributes,"type"));
        // Item owner = (Item) itemStack.top();
        Item* owner = (Item*) displayableStack.top();
        ItemAction* action = NULL;
        if(name.compare("BlessArmor")==0){
            action = new BlessCurseItem(owner);
        }
        else if(name.compare("Hallucinate")==0){
            action = new Hallucinate(owner);
        }
        else {
            assert (false) ;//: CLASSID + ".startElement unknown item action: " + name;
        }

        actionStack.push((Action *)action);
        owner->setItemAction(action);
    }
    else if(case_insensitive_match(qNameStr,"bottomHeight")){
        bBottomHeight = true;
    }
    else if(case_insensitive_match(qNameStr,"gameHeight")){
        bGameHeight = true;
    }
    else if(case_insensitive_match(qNameStr,"Height")){
        bHeight = true;
    }
    else if(case_insensitive_match(qNameStr,"hp")){
        bHp = true;
    }
    else if(case_insensitive_match(qNameStr,"hpMoves")){
        bHpMoves = true;
    }
    else if(case_insensitive_match(qNameStr,"maxhit")){
        bMaxhit = true;
    }
    else if(case_insensitive_match(qNameStr,"actionMessage")){
        bActionMessage = true;
    }
    else if(case_insensitive_match(qNameStr,"posX")){
        bPosX = true;
    }
    else if(case_insensitive_match(qNameStr,"posY")){
        bPosY = true;
    }
    else if(case_insensitive_match(qNameStr,"topHeight")){
        bTopHeight = true;
    }
    else if(case_insensitive_match(qNameStr,"type")){
        bType = true;
    }
    else if(case_insensitive_match(qNameStr,"visible")){
        bVisible = true;
    }
    else if(case_insensitive_match(qNameStr,"width")){
        bWidth = true;
    }
    else if(case_insensitive_match(qNameStr,"ActionIntValue")){
        bActionIntValue = true;
    }
    else if(case_insensitive_match(qNameStr,"ActionCharValue")){
        bActionCharValue = true;
    }
    else if(case_insensitive_match(qNameStr,"ItemIntValue")){
        bItemIntValue = true;
    }
    else{
        assert (false); //: "MyXMLHandler: no bX for qName " + qName;
    }
    xercesc::XMLString::release(&qNameStr);
}
void MyXMLHandler::endElement(const XMLCh* uri, const XMLCh* localName, const XMLCh* qName){
	std:: cout << "Stack size:" << displayableStack.size() << std::endl;
    if(bActionIntValue){
        actionStack.top()->setIntValue(std::stoi(data));
        bActionIntValue = false;
    }
    else if(bActionCharValue){
        actionStack.top()->setCharValue(data.c_str()[0]);
        bActionCharValue = false;
    }
    else if(bActionMessage){
        actionStack.top()->setMessage(data);
        bActionMessage = false;
    }
    else if(bItemIntValue){
        if (instanceof<Item>(displayableStack.top()))    {
            ((Item *) displayableStack.top())->setIntValue(std::stoi(data));
        } else {
            assert (false); //: CLASSID + ".endElement ItemIntValue stack corruption, found " + displayableStack.top()->toString();
        }
        bItemIntValue = false;
    }
    else if(bPosX){
        displayableStack.top()->setPosX(std::stoi(data));
        bPosX = false;
    }
    else if(bPosY){
        if (instanceof<Room>(displayableStack.top()) || instanceof<Passage>(displayableStack.top())) {
            if (DEBUG > 0) {
                std::cout << CLASSID << ".endElement bPosY limb, topHeight : " << topHeight << std::endl;
            }
            displayableStack.top()->setPosY(std::stoi(data));
        } else {
            displayableStack.top()->setPosY(std::stoi(data));
        }
        bPosY = false;
    }
    else if(bWidth){
        ((Room *) displayableStack.top())->setWidth(std::stoi(data));
        bWidth = false;
    }
    else if(bHeight){
        ((Room*) displayableStack.top())->setHeight(std::stoi(data));
        bHeight = false;
    }
    else if(bTopHeight){
        topHeight = std::stoi(data);
        //ObjectDisplayGrid.setTopMessageHeight(topHeight);
        bTopHeight = false;
    }
    else if(bType){
        const char* chars= data.c_str();
        displayableStack.top()->setType(chars[0]);
        if (DEBUG > 0) {
            std::cout << CLASSID << ".endElement tos " << displayableStack.top() << std::endl;
            std::cout << CLASSID << ".endElement chars for bType == true: " << new std::string(chars) << std::endl;
            std::cout << CLASSID + ".endElement type " << chars[0] << std::endl;
        }
        bType = false;
    }
    else if(bHp){
        ((Creature *) displayableStack.top())->setHp(std::stoi(data));
        bHp = false;
    }
    else if(bHpMoves){
        ((Creature *) displayableStack.top())->setHpMoves(std::stoi(data));
        bHpMoves = false;
    }
    else if (bMaxhit){
        ((Creature *) displayableStack.top())->setMaxHit(std::stoi(data));
        bMaxhit = false;
    }
    else if(bActionMessage){
        Action* action = actionStack.top();
        action->setMessage(data);
        bActionMessage = false;
    }
    else if(bVisible){
        switch (std::stoi(data)) {
            case 1:
                ((Displayable*) displayableStack.top())->setVisible();
                break;
            case 0:
                ((Displayable *) displayableStack.top())->setInvisible();
                break;
            default:
                assert (false) ;//: CLASSID + ".endElement bad value for visible: " + data;
                break;
        }
        bVisible = false;
    }
    char *  qNameStr = xercesc::XMLString::transcode(qName);
    if(case_insensitive_match(qNameStr,"Room")){
        assert (instanceof<Room>(displayableStack.top())) ;//: "corrupt elementStack, should be Room, is " + displayableStack.top();

        if (displayableStack.top() == NULL) {
            std::cout << "ROOM: NULL displayable stack corruption" << std::endl;
        } else {
            Room* room = (Room*) displayableStack.top();
            displayableStack.pop();
            std::cout << CLASSID + ".endElement adding room to Dungeon"<< std::endl;
        }
    }
    else if(case_insensitive_match(qNameStr,"ItemAction")){
        Action* action = (Action*) actionStack.top();
        actionStack.pop();
    }
    else if(case_insensitive_match(qNameStr,"CreatureAction")){
        Action* action = (Action*) actionStack.top();
        actionStack.pop();
    }
    else if(case_insensitive_match(qNameStr,"Monster")){
        assert (instanceof<Monster>(displayableStack.top())) ;//: "corrupt elementStack, should be Monster\n";
        Monster* monster = (Monster *) displayableStack.top();
        displayableStack.pop();
        globalizeThingCoordinates(currentRoom, monster);
    }
    else if(case_insensitive_match(qNameStr,"Passage")){
        assert (instanceof<Passage>(displayableStack.top())); //: "corrupt elementStack, should be Passage\n";
        Passage* passage = (Passage*) displayableStack.top();
        displayableStack.pop();
    }
    else if(case_insensitive_match(qNameStr,"Player")){
        assert (instanceof<Player>(displayableStack.top())); //: "corrupt elementStack, should be Player\n";
        Player* player = (Player*) displayableStack.top();
        displayableStack.pop();
        globalizeThingCoordinates(currentRoom, player);
    }
    else if(case_insensitive_match(qNameStr,"Scroll")){
        assert (instanceof<Scroll>(displayableStack.top())); //: "corrupt elementStack, should be Scroll\n";
        Scroll* scroll = (Scroll*) displayableStack.top();
        displayableStack.pop();
        globalizeThingCoordinates(currentRoom, scroll);
        currentRoom->addItem(scroll);
        xmlDungeon->addItem(scroll);
    }
    else if(case_insensitive_match(qNameStr,"Armor")){
        assert (instanceof<Armor>(displayableStack.top())) ;//: "corrupt elementStack, should be Armor\n";
        Armor* armor = (Armor*) displayableStack.top();
        displayableStack.pop();
        if (instanceof<Player>(displayableStack.top())) {
            Player* player = (Player*) displayableStack.top();
            armor->setPosX(player->getPosX());
            armor->setPosY(player->getPosY());
            player->setArmor(armor);
            armor->setOwner(player);
        } 
        else {
            globalizeThingCoordinates(currentRoom, armor);
            // TODO: not really using room item list, can we remove?
            currentRoom->addItem(armor);
            xmlDungeon->addItem(armor);
        }
    }
    else if(case_insensitive_match(qNameStr,"Sword")){
        assert (instanceof<Sword>(displayableStack.top())) ;//: "corrupt elementStack, should be Sword\n";
        Sword* sword = (Sword*) displayableStack.top();
        displayableStack.pop();
        if (instanceof<Player>(displayableStack.top())) {
            Player* player = (Player*) displayableStack.top();
            sword->setPosX(player->getPosX());
            sword->setPosY(player->getPosY());
            player->setWeapon(sword);
            sword->setOwner(player);
        } else {
            globalizeThingCoordinates(currentRoom, sword);
            currentRoom->addItem(sword);
            xmlDungeon->addItem(sword);
        }
    }

}

void MyXMLHandler::globalizeThingCoordinates(Displayable* room, Displayable* thing) {
    int posX = room->getPosX();
    posX += thing->getPosX();
    thing->setPosX(posX);

    int posY = room->getPosY();
    posY += thing->getPosY();
    thing->setPosY(posY);
}


void MyXMLHandler::characters(const XMLCh * ch, const XMLSize_t	length ){
    data = xmlChToString(ch,(int)length) ;
    if (DEBUG > 1) {
        //std::cout << CLASSID + ".characters: " << std::string(chStr, 0, (int) length) << std::endl;
        std::cout << CLASSID + ".characters: " << data << std::endl;
        std::cout.flush();
    }
}
std::string MyXMLHandler::toString(){
    std::string str = CLASSID + ".MyXMLHandler:\n";
    /*if (!displayableStack.empty()) {
        str += "   elementStack:\n";
        for (Displayable* displayable : displayableStack) {
            str += displayable->toString();
        }
    } else {
        str += "   elementStack: NULL\n";
    }*/ //TODO: Figure out stack (can't traverse stack like above in c++

    /*if (!actionStack.empty()) {
        str += "   elementStack:\n";
        for (Action* action : actionStack) {
            str += action->toString();
        }
    } else {
        str += "   elementStack: NULL\n";
    }*/ //TODO : action->Tostring doesn't exist yet

    str += "   data: " + data + "\n";
    if (currentRoom != NULL) {
        str += "   currentRoom:\n";
        str += currentRoom->toString();
    } else {
        str += "   currentRoom: NULL\n";
    }
    //if (xmlDungeon != NULL) {
    //    str += "   dungeon:\n";
    //    str += xmlDungeon->toString();
    //} else {
    //    str += "   dungeon: NULL\n";
    //}

    str += "bDungeon: " + boolToString(bDungeon) + "\n";
    str += "bRoom: " + boolToString(bRoom) + "\n";
    str += "bWidth: " + boolToString(bWidth) + "\n";
    str += "bHeight: " + boolToString(bHeight) + "\n";
    str += "bTopHeight: " + boolToString(bTopHeight) + "\n";
    str += "bGameHeight: " + boolToString(bGameHeight) + "\n";
    str += "bBottomHeight: " + boolToString(bBottomHeight) + "\n";
    str += "bPosX: " + boolToString(bPosX) + "\n";
    str += "bPosY: " + boolToString(bPosY) + "\n";
    str += "bType: " + boolToString(bType) + "\n";
    str += "bHp: " + boolToString(bHp) + "\n";
    // str += "bArmor: " + bArmor + "\n";
    str += "bMaxhit: " + boolToString(bMaxhit) + "\n";

    return str;
}


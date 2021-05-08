# This make file uses some more complex features to make it less work to maintain.
# For the minimum needed to work with the curses library, see SimpleMakefile

# Compiler to use
CC=g++
# Extra compilation arguments
CPPFLAGS=-std=c++11 -g

# List of dependencies
# "$(wildcard *.cpp)" could automatically get all cpp files in the folder, but I prefer manually listing them so we just build what we need
# Alphabetical order would be helpful here
CLASSES=Action.cpp Armor.cpp BlessCurseItem.cpp ChangeDisplayType.cpp Creature.cpp CreatureAction.cpp \
  Displayable.cpp DropPack.cpp DungeonChar.cpp Dungeon.cpp EndGame.cpp Hallucinate.cpp ItemAction.cpp Item.cpp KeyboardListener.cpp Monster.cpp MyXMLHandler.cpp ObjectDisplayGrid.cpp \
  Passage.cpp Player.cpp Remove.cpp Room.cpp Scroll.cpp Structure.cpp Sword.cpp TeleportOwner.cpp TwoTuple.cpp UpdateDisplay.cpp YouWin.cpp

SOURCES=Rogue.cpp $(CLASSES)
HEADERS=curses.h Rogue.h $(CLASSES:.cpp=.h)
EXECUTABLE=rogue
EXECUTABLE_TEST=parseTest

# Object files is simply all cpp files with subbed extension
OBJECTS = $(SOURCES:.cpp=.o)
# For testing, different main file, all classes though
OBJECTS_TEST = parseTestMain.o $(CLASSES:.cpp=.o)

# Check if building on Windows or Linux
ifeq ($(OS),Windows_NT)
	# Add the include directory for extra header files
	CPPFLAGS += -I .\include -I ..\xerces\include
	# Add in pdcurses and xerces from the lib folder. For some reason pdcurses won't search directly
	LIBRARIES=lib\pdcurses.a -lxerces-c_3 -L..\xerces\lib
	# by running rm within cmd, it does not error on missing files
	RM=cmd /c del
	# Windows introduced the tar command that can make zip files
	ZIP=tar -acvf
else
	# use ncurses library when building on linux
	# install using "sudo apt-get install libncurses5-dev libncursesw5-dev"
	# install using "sudo apt-get install -y libxerces-c-dev"
	LIBRARIES=-lncurses -lxerces-c
	# running -f means it does not error on missing files
	RM=rm -f
	# Linux needs the zip command to do zip files
	ZIP=zip
endif

# Build the project, default command
$(EXECUTABLE): $(OBJECTS)
	# Could not get xerces to properly link on Windows, it was designed for visual studio
	# if someone has better luck with it...
	ifeq ($(OS),Windows_NT)
		$(error Cannot compile Xerces using $(CC) on Windows)
	endif
	$(CC) -g $(CPPFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LIBRARIES)	

# Build the test method
$(EXECUTABLE_TEST): $(OBJECTS_TEST)
	ifeq ($(OS),Windows_NT)
		$(error Cannot compile Xerces using $(CC) on Windows)
	endif
	$(CC) -g $(CPPFLAGS) -o $(EXECUTABLE_TEST) $(OBJECTS_TEST) $(LIBRARIES)
	
# Compile .o files
# Cannot think of a good way to watch only the required headers for each .o file
%.o : %.cpp $(HEADERS)
	$(CC) -c $(CPPFLAGS) $<

# Clean the project
clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE).exe
	$(RM) $(EXECUTABLE)
	$(RM) $(EXECUTABLE_TEST).exe
	$(RM) $(EXECUTABLE_TEST)
	$(RM) $(EXECUTABLE)
	$(RM) $(EXECUTABLE).zip

# Clean then build
cleanmake: clean $(EXECUTABLE)

# Build then run
run: $(EXECUTABLE)
	$(EXECUTABLE)

# Create a zip file with all relevant files to build the project
ZIPFILES=$(SOURCES) $(HEADERS) Makefile SimpleMakefile pdcurses.a
zip: $(ZIPFILES)
	$(ZIP) $(EXECUTABLE).zip $(ZIPFILES)

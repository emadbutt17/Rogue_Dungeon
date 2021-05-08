#include <curses.h>
#include <iostream>
#include "ObjectDisplayGrid.h"
#ifdef _WIN32
	#include <windows.h>
#endif

ObjectDisplayGrid::ObjectDisplayGrid(int _width, int _topHeight, int _gridHeight, int _bottomHeight)
	: width(_width), topHeight(_topHeight), gridHeight(_gridHeight), bottomHeight(_bottomHeight) {
	// create the 2D array of grid characters
	objectGrid = new std::vector<Displayable*>*[width];
	for (int i = 0; i < width; i++) {
		// create inner stack array, calls the stack's constructor
		objectGrid[i] = new std::vector<Displayable*>[gridHeight];
	}

	// initialize ncurses

	// set command window size if running on windows, useful when running in Visual Studio
	// as far as I am aware, no way to do this on linux
	int totalHeight = topHeight + gridHeight + bottomHeight;
	#ifdef _WIN32
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD size = { (short)width, (short)(totalHeight) };
		SMALL_RECT DisplayArea = { 0, 0, (short)(size.X - 1), (short)(size.Y - 1) };
		SetConsoleScreenBufferSize(handle, size);
		SetConsoleWindowInfo(handle, TRUE, &DisplayArea);
	#endif

	// initializes ncurses
	initscr();
	// makes characters typed immediately available, instead of waiting for enter to be pressed
	cbreak();
	// stops typed characters from being shown, makes it easier to get keypresses
	noecho();
	// clears the screen to start
	clear();
}

ObjectDisplayGrid* ObjectDisplayGrid::INSTANCE = NULL;

ObjectDisplayGrid* ObjectDisplayGrid::getGrid(int width, int topHeight, int gridHeight, int bottomHeight) {
	if (INSTANCE == NULL) {
		INSTANCE = new ObjectDisplayGrid(width, topHeight, gridHeight, bottomHeight);
	}
	return INSTANCE;
}

ObjectDisplayGrid* ObjectDisplayGrid::getGrid() {
	if (INSTANCE == NULL) {
		std::cerr << "Attempted to call getGrid on uninitialized grid" << std::endl;
		exit(1);
	}
	return INSTANCE;
}

ObjectDisplayGrid::~ObjectDisplayGrid() {
	// free memory from the dynamically sized object grid
	for (int i = 0; i < width; i++) {
		// delete the column
		delete[] objectGrid[i];
	}
	// delete the array of columns
	delete[] objectGrid;
	objectGrid = NULL;

	// free ncurses data
	endwin();
}

bool ObjectDisplayGrid::isValid(int x, int y) {
	return (0 <= x) && (x < width) && (0 <= y) && (y < gridHeight);
}

void ObjectDisplayGrid::updateChar(int x, int y) {
	std::vector<Displayable*>& stack = objectGrid[x][y];
	// if the stack is empty, draw a space
	if (stack.empty()) {
		mvaddch(y, x, ' ');
	}
	else {
		mvaddch(topHeight + y, x, objectGrid[x][y].back()->getType());
	}
}

void ObjectDisplayGrid::add(Displayable* disp) {
	add(disp, disp->getPosX(), disp->getPosY());
}

void ObjectDisplayGrid::add(Displayable* disp, int x, int y) {
	if (isValid(x, y)) {
		objectGrid[x][y].push_back(disp);
		updateChar(x, y);
	}
}

void ObjectDisplayGrid::remove(Displayable* disp) {
	remove(disp, disp->getPosX(), disp->getPosY());
}

void ObjectDisplayGrid::remove(Displayable* disp, int x, int y) {
	if (isValid(x, y)) {
		// null means pop top
		if (disp == nullptr) {
			this->objectGrid[x][y].pop_back();
		}
		else {
			// if given a specific displayable, remove that, helpful for removing items
			// this could also be accomplished by popping elements from the stack onto a temp stack, then pushing the temp stack back
			// however, felt cleaner to use vectors
			std::vector<Displayable*>& stack = this->objectGrid[x][y];
			stack.erase(std::remove(stack.begin(), stack.end(), disp), stack.end());
		}
		// draw the new top
		updateChar(x, y);
	}
}

void ObjectDisplayGrid::writeToTop(int line, std::string message) {
	if (line >= 0 && line < topHeight) {
		mvaddstr(line, 0, message.c_str());
		clrtoeol();
		update();
	}
}

void ObjectDisplayGrid::writeToBottom(int line, std::string message) {
	if (line >= 0 && line < bottomHeight) {
		mvaddstr(topHeight + gridHeight + line, 0, message.c_str());
		clrtoeol();
		update();
	}
}

void ObjectDisplayGrid::writeInfo(std::string message) {
	writeToBottom(0, "Info: " + message);
}

void ObjectDisplayGrid::writePack(std::string message) {
	writeToBottom(2, message);
}

void ObjectDisplayGrid::update() {
	// move the cursor to be non-visible
	move(topHeight + gridHeight + bottomHeight, width);
	refresh();
}

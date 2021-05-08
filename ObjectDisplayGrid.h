#pragma once
#include <string>
#include <vector>
#include "Displayable.h"

class ObjectDisplayGrid {
private:
	/** Singleton instance of the display grid */
	static ObjectDisplayGrid* INSTANCE;

	/** Keeps track of the characters on the screen. Note that std::vector would work too */
	std::vector<Displayable*>** objectGrid;
	/** Keeps track of the grid display area */
	int width, gridHeight;
	/** Keeps track of the how many lines from the top and bottom are reserved for text */
	int topHeight, bottomHeight;

	/**
	 * Creates a new display grid using the given parameters
	 * @param width          Overall width
	 * @param topHeight      Height of top area
	 * @param gridHeight     Height of grid
	 * @param bottomHeight   Height of bottom area
	 */
	ObjectDisplayGrid(int width, int topHeight, int gridHeight, int bottomHeight);

	/**
	 * Updates the character drawn at the given position. Assumes position is valid
	 * @param x  X position
	 * @param y  Y position
	 */
	void updateChar(int x, int y);

public:
	/**
	 * Creates the object display grid with the given properties, or uses the existing grid if one was already created
	 * @param width          Overall width
	 * @param topHeight      Height of top area
	 * @param gridHeight     Height of grid
	 * @param bottomHeight   Height of bottom area
	 * @return  The display instance
	 */
	static ObjectDisplayGrid* getGrid(int width, int topHeight, int gridHeight, int bottomHeight);

	/**
	 * Gets the existing object display grid. Assumes the parameterized version was called.
	 * @return  The display instance
	 */
	static ObjectDisplayGrid* getGrid();

	/** Object deconstructor, to delete the grid character matrix */
	~ObjectDisplayGrid();

	/**
	 * Adds an object to the display grid using the object's position
	 * @param disp  Object to add to display
	 */
	virtual void add(Displayable* disp);

	/**
	 * Adds a displayable to the given position
	 * @param disp  Displayable to display
	 * @param x     X position
	 * @param y     Y position
	 */
	virtual void add(Displayable* disp, int x, int y);

	/**
	 * Removes a specific object from its current position
	 * @param disp  Object to remove
	 */
	virtual void remove(Displayable* disp);

	/**
	 * Removes a object from the given position
	 * @param disp  Object to remove for validation, can use null for no validation
	 * @param x     X position
	 * @param y     Y position
	 */
	virtual void remove(Displayable* ch, int x, int y);

	/**
	 * Writes a message to the top of the screen at the given line relative
	 * @param line    line number
	 * @param message message to write
	 */
	virtual void writeToTop(int line, std::string message);

	/**
	 * Writes a message to the bottom of the screen at the given line relative
	 * @param line    line number
	 * @param message message to write
	 */
	virtual void writeToBottom(int line, std::string message);

	/**
	 * Writes a message to the standard info location
	 * @param message  message to write
	 */
	virtual void writeInfo(std::string message);

	/**
	 * Writes a message to the standard pack location
	 * @param message  message to write
	 */
	virtual void writePack(std::string message);

	/**
	 * Refreshes the display with the latest information
	 */
	virtual void update();

	/**
	 * Checks if the space is in valid grid coordinates
	 * @param x  X position
	 * @param y  Y position
	 */
	virtual bool isValid(int x, int y);
};


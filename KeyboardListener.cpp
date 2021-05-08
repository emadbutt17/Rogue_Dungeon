#include "KeyboardListener.h"
#include <stdio.h>
#include <curses.h>

KeyboardListener::KeyboardListener(ObjectDisplayGrid* grid, Player* player) {
	this->grid = grid;
	this->player = player;
}

void KeyboardListener::start() {
	running = true;
	char input = getchar();
	while (running && input != EOF) {
		switch (input) {
		case 'x':
			running = false;
			break;
		// showing pack while dead seems fine
		case 'i':
			player->displayPack();
			break;
		default:
			// some functions only work if the player is alive
			if (player->isAlive()) {
				// stop showing pack since we moved
				player->hidePack();

				switch (input) {
				// movement
				case 'k':
					player->move(0, -1);
					break;
				case 'h':
					player->move(-1, 0);
					break;
				case 'l':
					player->move(0, 1);
					break;
				case 'j':
					player->move(1, 0);
					break;
				// inventory
				case 'p':
					player->pickupItem();
					break;
				case 'd':
					if (player->packEmpty()) {
						grid->writeInfo("Pack is empty");
					}
					else {
						// get a second key press
						grid->writeInfo("Press number between 1-9");
						player->displayPack();
						input = getchar();
						if (input >= '1' && input <= '9') {
							// chars are just numbers, so subtracting 1 will index keys 1-9 to numbers 0-8
							player->dropItem(input - '1');
						}
						else {
							grid->writeInfo("Invalid pack index");
						}
						player->hidePack();
					}
				}
			}
		}

		

		input = getchar();
	}
}

void KeyboardListener::stop() {
	running = false;
}

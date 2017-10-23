/*
 * GuiMode.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "GuiManager.h"



int startGuiMode() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	GuiManager* manager = managerCreate();
	if (manager == NULL) {
		SDL_Log("ERROR: Failed to create GUI manager\n");
		SDL_Quit();
		return 0;
	}
	SDL_Event event;
	int dragging = 0;
	while (true) {
		// Get sdl event
		SDL_WaitEvent(&event);
		// Catch quit
		if (event.type == SDL_QUIT) {
			break;
		}
		// Catch window closing
		if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
			break;
		}
		// Check for drag & drop
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (manager->activeWin == GAME_WINDOW_ACTIVE) { // Game is the active window
				if(managerHandlerCheckifDragAndDrop(manager, &event, &dragging) == MANAGER_QUIT) {
					break;
				}
			}
		}
		if (dragging) {
			if (event.type == SDL_MOUSEMOTION) { // If dragging, get location
				if (managerHandlerDragDropEvent (manager, &event) == MANAGER_QUIT) {
					break;
				}
			}
			// Handle dropped chess piece
			if (event.type == SDL_MOUSEBUTTONUP) {
				if(managerHandlerDropItem (manager, &event) == MANAGER_QUIT) {
					break;
				}
				// turn off dragging
				dragging = 0;
			}
		}
		// Handle all other events
		else if (event.type == SDL_MOUSEBUTTONUP) {
			if (managerHandleEvent(manager, &event) == MANAGER_QUIT) {
				break;
			}
		}
		managerDraw(manager);
	}
	managerDestroy(manager);
	SDL_Quit();
	return 0;
}

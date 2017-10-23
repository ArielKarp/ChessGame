/*
 * GuiManager.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef GUIMANAGER_H_
#define GUIMANAGER_H_

#include "MainWindow.h"
#include "LoadWindow.h"
#include "XMLParser.h"
#include "SettingWindow.h"
#include "GameWindow.h"
#include "GameWindow.h"
#include "ConsoleMode.h"
#include <math.h>

typedef enum{
	MAIN_WINDOW_ACTIVE,
	LOAD_WINDOW_ACTIVE,
	SETTING_WINDOW_ACTIVE,
	GAME_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
	MANAGER_QUIT,
	MANAGER_NONE,
}MANAGER_EVENT;

typedef struct {
	BasicWindow* mainWin;
	BasicWindow* loadWin;
	BasicWindow* setWin;
	BasicWindow* gameWin;
	ACTIVE_WINDOW activeWin;
	ACTIVE_WINDOW previousWin;
	Game* game;
	int loadSlotNum;
	char* slotsArray[5];
	bool userMoves;
} GuiManager;

/**
 * Create GuiManager structure
 * @return
 */
GuiManager* managerCreate();

/**
 * Destroy GuiManager and all of it's screens
 * @param src
 */
void managerDestroy(GuiManager* src);


/**
 * Draw active screen
 * @param src
 */
void managerDraw(GuiManager* src);


/**
 * Handle all GuiManager events
 * @param src
 * @param event
 * @return
 */
MANAGER_EVENT managerHandleEvent(GuiManager* src, SDL_Event* event);

/**
 * Handle results of main events
 * @param src
 * @param eventNum
 * @return
 */
MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* src, int eventNum);

/**
 * Check if xml was loaded
 * @param xmlMessage
 */
void checkXmlLoad(XML_MESSAGE xmlMessage);

/**
 * Handle results of setting events
 * @param src
 * @param eventNum
 * @return
 */
MANAGER_EVENT handleManagerDueToSettingEvent(GuiManager* src, int eventNum);

/**
 * Handle results of game events- control buttons
 * @param src
 * @param eventNum
 * @return
 */
MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* src, int eventNum);

/**
 * Test if event is drag&drop, handle accordingly and activate drag mode in GameWindow
 * @param src
 * @param event
 * @param dragging - fill value, 0- false, 1- true
 * @return
 */
MANAGER_EVENT managerHandlerCheckifDragAndDrop(GuiManager* src, SDL_Event* event, int* dragging);

/**
 * Update location of clicked chess pieces
 * @param src
 * @param event
 * @return
 */
MANAGER_EVENT managerHandlerDragDropEvent(GuiManager* src, SDL_Event* event);

/**
 * Handle dropped item on location, ionitiate computers turn if needed
 * @param src
 * @param event
 * @return
 */
MANAGER_EVENT managerHandlerDropItem (GuiManager* src, SDL_Event* event);

/**
 * Restart game- return all pieces to starting position
 * @param src
 * @return
 */
bool restartGameInWindow(GuiManager* src);

/**
 * Undo move- as defined in Game module
 * @param src
 * @return
 */
bool undoGameInWindow(GuiManager* src);

/**
 * Check status of game for player, show message box (TIE, CHECK, MATE) if required
 * @param src
 * @return
 */
MANAGER_EVENT getForGameStatus(GuiManager* src);

/**
 * If required, pop-up a message box for user's input to save the current game
 * @param src
 * @return
 */
MANAGER_EVENT checkIfSaveTheGame(GuiManager* src);

/**
 * Initiate computers move
 * @param src
 */
void doComputersMove(GuiManager* src);

/**
 *  Turn on/off undo button as game state:
 *  On if 1 player mode and history exists
 *  Off otherwise
 * @param src
 */
void setUndoButtonActive(GuiManager* src);

#endif /* GUIMANAGER_H_ */

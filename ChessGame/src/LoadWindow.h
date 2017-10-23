/*
 * LoadWindow.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef LOADWINDOW_H_
#define LOADWINDOW_H_
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "BasicButton.h"
#include "BasicWindow.h"
#define SLOT_BTN_HEIGHT 66
#define SLOT_BTN_WIDTH 168
#define LOAD_BTN_HEIGHT 83
#define LOAD_BTN_WIDTH 205
#define SLOT_OFFSET_X (SLOT_BTN_WIDTH + 25)
#define SLOT_OFFSET_Y 26
#define LOAD_X 299
#define LOAD_Y 413
#define BACK_X 720
#define BACK_Y 32
#define SLOT_X 124
#define SLOT_Y 172
#define SLOT_SECOND_X 223
#define SLOT_SECOND_Y 260
#define LOAD_NUM_OF_BUTTENS 7
#define SLOT1_BTN "graphics/slot_1_pushed.bmp"
#define SLOT2_BTN "graphics/slot_2_pushed.bmp"
#define SLOT3_BTN "graphics/slot_3_pushed.bmp"
#define SLOT4_BTN "graphics/slot_4_pushed.bmp"
#define SLOT5_BTN "graphics/slot_5_pushed.bmp"
#define SLOT1_BTN_NOT_SELECTED "graphics/slot_1_not.bmp"
#define SLOT2_BTN_NOT_SELECTED "graphics/slot_2_not.bmp"
#define SLOT3_BTN_NOT_SELECTED "graphics/slot_3_not.bmp"
#define SLOT4_BTN_NOT_SELECTED "graphics/slot_4_not.bmp"
#define SLOT5_BTN_NOT_SELECTED "graphics/slot_5_not.bmp"
#define LOAD_SAVE_BTN "graphics/load_pushed.bmp"
#define LOAD_SAVE_BTN_NOT_SELECTED "graphics/load_not.bmp"
#define BACKROUND_LOAD "graphics/1_player_2_players_screen.bmp"
#define SLOTS_NUMS 5
#define SLOT_SIZE_PATH 30
#define MINUS_BACK_START 2
#define SLOT1 "files/file_1.xml"
#define SLOT2 "files/file_2.xml"
#define SLOT3 "files/file_3.xml"
#define SLOT4 "files/file_4.xml"
#define SLOT5 "files/file_5.xml"

typedef enum {
	LOAD_SLOT_1 = 0, LOAD_SLOT_2, LOAD_SLOT_3, LOAD_SLOT_4, LOAD_SLOT_5, LOAD_BACK, LOAD_DATA
} LOAD_EVENT;

typedef struct load_window_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	SDL_Texture* windowBackRound;
	//All widgets in our window
	Widget** widgets;
	Widget* pressedSlot;
	int numOfWidgets;
	char slotsArray[SLOTS_NUMS][SLOT_SIZE_PATH];
	int activeSlotsArray[SLOTS_NUMS];
}LoadWindow;


/**
 * Create a load window
 * @return BasicWindow reference
 */
BasicWindow* createLoadWindow();

/**
 * Destroy load window
 * @param src of load window to be destroyed
 */
void destroyLoadWindow(BasicWindow* src);

/**
 * Draw load window and all relevant buttons
 * @param src
 */
void drawLoadWindow(BasicWindow* src);

/**
 * Handler functions for events of load window
 * @param src window in
 * @param event occured event
 * @param eventNum return value of clicked button
 */
void handleEventLoadWindow(BasicWindow* src, SDL_Event* event, int* eventNum);

/**
 * Hide load window
 * @param src
 */
void loadWindowHide(BasicWindow* src);

/**
 * Show load window
 * @param src
 */
void loadWindowShow(BasicWindow* src);

bool saveToFile(BasicWindow* src);


#endif /* LOADWINDOW_H_ */

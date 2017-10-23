/*
 * MainWindow.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "BasicButton.h"
#include "BasicWindow.h"
#define BUTTON_HEIGHT 90
#define BUTTON_WIDTH 226
#define OFFSET_Y 100
#define OFFSET_X BUTTON_WIDTH/2
#define RECTX WIN_WIDTH/2 - OFFSET_X
#define RECTY_START 160
#define RECTY_OPTIONS RECTY_START + OFFSET_Y
#define RECTY_EXIT RECTY_OPTIONS + OFFSET_Y
#define START_BTN "graphics/start_pushed.bmp"
#define LOAD_BTN "graphics/load_pushed.bmp"
#define EXIT_BTN "graphics/exit_pushed.bmp"
#define BACK_RND "graphics/main_win.bmp"


#define MAIN_NUM_OF_BUTTENS 3

typedef enum {
	MAIN_START = 0, MAIN_LOAD, MAIN_QUIT
} MAIN_EVENT;

typedef struct main_window_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	SDL_Texture* windowBackRound;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;

}MainWindow;

/**
 * Creates a main window
 */
BasicWindow* createMainWindow();

/**
 * create main window widgets
 * @param renderer
 * @return an array of references to widget structures
 */
Widget** createMainWindowWidgets(SDL_Renderer* renderer);

/**
 * Destroy main window
 * @param src
 */
void destroyMainWindow(BasicWindow* src);

/**
 * Draws the main window, all relevant buttons as well
 * @param src
 */
void drawMainWindow(BasicWindow* src);

/**
 * Handler functions for events of main window
 * @param src window in
 * @param event occured event
 * @param eventNum return value of clicked button
 */
void handleEventMainWindow(BasicWindow* src, SDL_Event* event, int* eventNum);

/**
 * Hide main window
 * @param src
 */
void mainWindowHide(BasicWindow* src);

/**
 * Show main window
 * @param src
 */
void mainWindowShow(BasicWindow* src);

#endif /* MAINWINDOW_H_ */

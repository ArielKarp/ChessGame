	/*
 * SettingWindow.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef SETTINGWINDOW_H_
#define SETTINGWINDOW_H_

#include "BasicButton.h"
#include "BasicWindow.h"
#define SETTINGS_BACKROUND "graphics/1_player_2_players_screen.bmp"
#define PLAYERS_BTN_HEIGHT 99
#define PLAYERS_BTN_WIDTH 169

#define SETTING_NUM_OF_BUTTENS 10
#define SETTINGS_BTN_WIDTH 168
#define SETTINGS_BTN_HEIGHT 68
#define BACK_START_BTN_WIDTH 200
#define HEIGHT_OFFSET 20
#define PLAYER_OFFSET_Y 102
#define PLAYER_OFFSET_X BACK_START_BTN_WIDTH/2
#define PLAYER_1_X WIN_WIDTH/2 - 200 + HEIGHT_OFFSET
#define PLAYER_2_X WIN_WIDTH/2 + 12
#define COLOR_W WIN_WIDTH/2 - 90
#define COLOR_B WIN_WIDTH/2 + 30
#define DIFF_NOOB_X 30
#define DIFF_HARD_X 602
#define PLAYER_Y WIN_HEIGHT/2 - PLAYER_OFFSET_Y
#define DIFF_Y 222
#define COLOR_Y WIN_HEIGHT/2 + 10
#define BACK_START_BTN_HEIGHT (WIN_HEIGHT/4)*3
#define BACKBTN_HEIGHT 720
#define BACKBTN_WIDTH 30
#define BACKBTN_HEIGHT_WIDTH 53
#define STARTBTN_WIDTH 211
#define STARTBTN_HEIGHT 84

#define PLAYER1_BTN "graphics/1_player_activated_btn.bmp"
#define PLAYER1_BTN_NOT_SELECTED "graphics/1_player_btn.bmp"
#define PLAYER2_BTN "graphics/2_player_activated_btn.bmp"
#define PLAYER2_BTN_NOT_SELECTED "graphics/2_player_btn.bmp"
#define NOOB_BTN "graphics/noob_activated_btn.bmp"
#define NOOB_BTN_NOT_SELECTED "graphics/noob_btn.bmp"
#define EASY_BTN "graphics/easy_activated_btn.bmp"
#define EASY_BTN_NOT_SELECTED "graphics/easy_btn.bmp"
#define MOODERATE_BTN "graphics/moderate_activated_btn.bmp"
#define MOODERATE_BTN_NOT_SELECTED "graphics/moderate_btn.bmp"
#define HARD_BTN "graphics/hard_activated_btn.bmp"
#define HARD_BTN_NOT_SELECTED "graphics/hard_btn.bmp"
#define WHITE_BTN "graphics/white_activated_btn.bmp"
#define WHITE_BTN_NOT_SELECTED "graphics/white_btn.bmp"
#define BLACK_BTN "graphics/black_activated_btn.bmp"
#define BLACK_BTN_NOT_SELECTED "graphics/black_btn.bmp"
#define START_GAME_BTN "graphics/start_game_activated_btn.bmp"
#define START_GAME_BTN_NOT_SELECTED "graphics/start_game.bmp"

typedef enum {
	//MAIN_START = 0, MAIN_SETTING, MAIN_QUIT, MAIN_NONE
	SETTING_SINGLE_PLAYER = 0,
	SETTING_TWO_PLAYER,
	SETTING_NOOB,
	SETTING_EASY,
	SETTING_MODERATE,
	SETTING_HARD,
	SETTING_WHITE,
	SETTING_BLACK,
	SETTING_BACK,
	SETTING_START
} SETTING_EVENT;

typedef struct setting_window_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	SDL_Texture* windowBackRound;
	//All widgets in our window
	Widget** widgets;
	int numOfWidgets;

} SettingWindow;


/**
 * Create setting window
 * @return
 */
BasicWindow* createSettingWindow();

/**
 * Create setting window widgets
 * @param renderer
 * @return
 */
Widget** createSettingWindowWidgets(SDL_Renderer* renderer);

/**
 * Destroy setting window and it's widgets
 * @param src
 */
void destroySettingWindow(BasicWindow* src);

/**
 * Draw setting window and buttons
 * @param src
 */
void drawSettingWindow(BasicWindow* src);

/**
 * Handler functions for events of setting window
 * @param src window in
 * @param event occured event
 * @param eventNum return value of clicked button
 */
void handleEventSettingWindow(BasicWindow* src, SDL_Event* event, int* eventNum);

/**
 * Function that checks if start button can be activated (shown on screen)
 * @param src
 * @return
 */
bool checkStartValueForSettings(BasicWindow* src);

/**
 * Set all buttons to in- active
 * @param src
 */
void setAllButtonsToFalse(BasicWindow* src);

/**
 * Hide setting window
 * @param src
 */
void settingWindowHide(BasicWindow* src);

/**
 * Show setting window
 * @param src
 */
void settingWindowShow(BasicWindow* src);

/**
 * Check if one ot two player button is clicked
 * @param src
 * @return
 */
bool isSettingsButtonActive(BasicWindow* src);

#endif /* SETTINGWINDOW_H_ */

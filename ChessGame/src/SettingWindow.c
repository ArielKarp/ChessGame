/*
 * SettingWindow.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "SettingWindow.h"

//Helper function to create buttons in the setting window
Widget** createSettingWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL) {
		return NULL;
	}
	int i = 0;
	Widget** widgets = malloc(sizeof(Widget*) * SETTING_NUM_OF_BUTTENS);
	if (widgets == NULL) {
		return NULL;
	}
	SDL_Rect singplePlayerR = { .x = PLAYER_1_X, .y = PLAYER_OFFSET_Y, .h =
			PLAYERS_BTN_HEIGHT, .w = PLAYERS_BTN_WIDTH };
	SDL_Rect twoPlayerR = { .x = PLAYER_2_X, .y = PLAYER_OFFSET_Y, .h =
			PLAYERS_BTN_HEIGHT, .w = PLAYERS_BTN_WIDTH };
	SDL_Rect noobR = { .x = DIFF_NOOB_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT,
			.w = SETTINGS_BTN_WIDTH };
	SDL_Rect easyR = { .x = PLAYER_1_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT,
			.w = SETTINGS_BTN_WIDTH };
	SDL_Rect moderateR = { .x = PLAYER_2_X, .y = DIFF_Y, .h =
			SETTINGS_BTN_HEIGHT, .w = SETTINGS_BTN_WIDTH };
	SDL_Rect hardR = { .x = DIFF_HARD_X, .y = DIFF_Y, .h = SETTINGS_BTN_HEIGHT,
			.w = SETTINGS_BTN_WIDTH };
	SDL_Rect whiteR = { .x = PLAYER_1_X, .y = COLOR_Y, .h = SETTINGS_BTN_HEIGHT,
			.w = SETTINGS_BTN_WIDTH };
	SDL_Rect blackR = { .x = PLAYER_2_X, .y = COLOR_Y, .h = SETTINGS_BTN_HEIGHT,
			.w = SETTINGS_BTN_WIDTH };
	SDL_Rect backR = { .x = BACKBTN_HEIGHT, .y = BACKBTN_WIDTH, .h =
			BACKBTN_HEIGHT_WIDTH, .w = BACKBTN_HEIGHT_WIDTH };
	SDL_Rect startR = { .x = 295, .y = 444, .h = STARTBTN_HEIGHT, .w =
			STARTBTN_WIDTH };
	widgets[0] = createBasicButton(renderer, &singplePlayerR,
	PLAYER1_BTN, PLAYER1_BTN_NOT_SELECTED,
	false);
	widgets[1] = createBasicButton(renderer, &twoPlayerR,
	PLAYER2_BTN, PLAYER2_BTN_NOT_SELECTED,
	false);
	widgets[2] = createBasicButton(renderer, &noobR,
	NOOB_BTN, NOOB_BTN_NOT_SELECTED, false);
	widgets[3] = createBasicButton(renderer, &easyR,
	EASY_BTN, EASY_BTN_NOT_SELECTED, false);
	widgets[4] = createBasicButton(renderer, &moderateR,
	MOODERATE_BTN, MOODERATE_BTN_NOT_SELECTED,
	false);
	widgets[5] = createBasicButton(renderer, &hardR,
	HARD_BTN, HARD_BTN_NOT_SELECTED, false);
	widgets[6] = createBasicButton(renderer, &whiteR,
	WHITE_BTN, WHITE_BTN_NOT_SELECTED,
	false);
	// Black button
	widgets[7] = createBasicButton(renderer, &blackR,
			BLACK_BTN, BLACK_BTN_NOT_SELECTED,
			false);
	// back button
	widgets[8] = createBasicButton(renderer, &backR, BACK_BTN,
	BACK_BTN_NOT_SELECTED, true);
	widgets[9] = createBasicButton(renderer, &startR,
	START_GAME_BTN, START_GAME_BTN_NOT_SELECTED,
	false);

	for (i = 0; i < SETTING_NUM_OF_BUTTENS; i++) {
		if (NULL == widgets[i]) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			destroyWidget(widgets[3]); //NULL SAFE
			destroyWidget(widgets[4]); //NULL SAFE
			destroyWidget(widgets[5]); //NULL SAFE
			destroyWidget(widgets[6]); //NULL SAFE
			destroyWidget(widgets[7]); //NULL SAFE
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}
BasicWindow* createSettingWindow() {
	BasicWindow* res = malloc(sizeof(BasicWindow));
	SettingWindow* data = malloc(sizeof(SettingWindow));
	SDL_Window* window = SDL_CreateWindow("Setting Window",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH,
			WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createSettingWindowWidgets(renderer);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL
			|| widgets == NULL) {
		free(res);
		free(data);
		free(widgets);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	SDL_Surface* loadingSurface = SDL_LoadBMP(SETTINGS_BACKROUND);
	if (loadingSurface == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		free(res);
		free(data);
		free(widgets);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	SDL_Texture* backRoundTexture = SDL_CreateTextureFromSurface(renderer,
			loadingSurface);
	if (renderer == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		free(res);
		free(data);
		free(widgets);
		//We first destroy the renderer
		SDL_FreeSurface(loadingSurface);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	data->widgets = widgets;
	data->numOfWidgets = SETTING_NUM_OF_BUTTENS;
	data->window = window;
	data->windowRenderer = renderer;
	data->windowBackRound = backRoundTexture;
	res->data = (void*) data;
	res->destroyWindow = destroySettingWindow;
	res->drawWindow = drawSettingWindow;
	res->handleEventWindow = handleEventSettingWindow;
	return res;
}
void destroySettingWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	SettingWindow* data = (SettingWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		data->widgets[i]->destroyWidget(data->widgets[i]);
	}
	free(data->widgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	SDL_DestroyTexture(data->windowBackRound);
	free(data);
	free(src);
}
void drawSettingWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	SettingWindow* data = (SettingWindow*) src->data;

	//Draw window
	SDL_SetWindowPosition(data->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetRenderDrawColor(data->windowRenderer, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR);
	SDL_RenderClear(data->windowRenderer);
	SDL_RenderCopy(data->windowRenderer, data->windowBackRound,
	NULL, NULL);
	int i = 0;
	// Check if player 1 is active
	int isSingActive = getActiveStatus(data->widgets[SETTING_SINGLE_PLAYER]);
	int isTwoActive = getActiveStatus(data->widgets[SETTING_TWO_PLAYER]);
	if (isSingActive == -1) {
		// Error
		return;
	}
	(data->widgets[SETTING_BACK])->drawWidget(data->widgets[SETTING_BACK]);

	if (isSingActive == 1) {
		// 1 player is Active
		// Draw all
		for (i = 0; i < data->numOfWidgets; i++) {
			(data->widgets[i])->drawWidget(data->widgets[i]);
		}
	} else if (isTwoActive == 1) {
		// 2 player is active
		(data->widgets[SETTING_SINGLE_PLAYER])->drawWidget(data->widgets[SETTING_SINGLE_PLAYER]);
		(data->widgets[SETTING_TWO_PLAYER])->drawWidget(data->widgets[SETTING_TWO_PLAYER]);
		(data->widgets[SETTING_BACK])->drawWidget(data->widgets[SETTING_BACK]);
		(data->widgets[SETTING_START])->drawWidget(data->widgets[SETTING_START]);
	} else {
		(data->widgets[SETTING_SINGLE_PLAYER])->drawWidget(
				data->widgets[SETTING_SINGLE_PLAYER]);
		(data->widgets[SETTING_TWO_PLAYER])->drawWidget(
				data->widgets[SETTING_TWO_PLAYER]);
		(data->widgets[SETTING_START])->drawWidget(
				data->widgets[SETTING_START]);

	}

	SDL_RenderPresent(data->windowRenderer);
}

void handleEventSettingWindow(BasicWindow* src, SDL_Event* event, int* eventNum) {
	if (src == NULL || event == NULL) {
		*eventNum = 1;
		return;
	}
	SettingWindow* data = (SettingWindow*) src->data;
	int i = 0, j = 0;		//, sumClicked = 0;
	int answer = -1;
	int clickedButton = -1;
	for (; i < data->numOfWidgets; i++) {
		//isBasicButtonClicked(data->widgets[i], event, &answer);
		data->widgets[i]->isClicked(data->widgets[i], event, &answer);
		if (answer == 1) {
			clickedButton = i;
			if (i == 0) {		// 1 player
				// remove hard coded
				for (j = SETTING_NOOB; j < SETTING_BACK; j++) {
					changeActive(data->widgets[j], false);
				}
				changeActive(data->widgets[SETTING_SINGLE_PLAYER], true);
				changeActive(data->widgets[SETTING_TWO_PLAYER], false);
				//changeActive(data->widgets[SETTING_START], false);
			}
			if (i == 1) {				// 2player
				// turn off other buttons
				for (j = SETTING_NOOB; j < SETTING_BACK; j++) {
					changeActive(data->widgets[j], false);
				}
				changeActive(data->widgets[SETTING_SINGLE_PLAYER], false);
				changeActive(data->widgets[SETTING_TWO_PLAYER], true);
				//changeActive(data->widgets[SETTING_START], true);
			}
			if (i >= SETTING_NOOB && i < SETTING_WHITE) {
				// Some diff was clicked
				for (j = SETTING_NOOB; j < SETTING_WHITE; j++) {
					changeActive(data->widgets[j], false);
				}
				changeActive(data->widgets[i], true);
			}
			if (i >= SETTING_WHITE && i < SETTING_BACK) {
				for (j = SETTING_WHITE; j < SETTING_BACK; j++) {
					changeActive(data->widgets[j], false);
				}
				changeActive(data->widgets[i], true);
			}
		}
	}
	// update start button
	changeActive(data->widgets[SETTING_START], checkStartValueForSettings(src));
	// Here a scheme of what to do or return
	*eventNum = clickedButton;
	return;
}

bool checkStartValueForSettings(BasicWindow* src) {
	if (NULL == src) {
		return false;
	}
	int j = 0;
	int sumClicked = 0;
	SettingWindow* data = (SettingWindow*) src->data;
	if (getActiveStatus(data->widgets[SETTING_TWO_PLAYER])) {
		return true;
	}
	if (getActiveStatus(data->widgets[SETTING_SINGLE_PLAYER])) {
		// player 1 active
		for (j = SETTING_NOOB; j < SETTING_BACK; j++) {
			if (getActiveStatus(data->widgets[j]) == true) {
				sumClicked++;
			}
		}
		if (sumClicked == 2) { // diff and color clicked
			return true;
		}
	}
	//default value
	return false;
}

void setAllButtonsToFalse(BasicWindow* src) {
	int i = 0;
	SettingWindow* data = (SettingWindow*) src->data;
	for (i = 0; i < data->numOfWidgets; i++) {
		changeActive(data->widgets[i], false);
	}
	return;
}

void settingWindowHide(BasicWindow* src) {
	SettingWindow* data = (SettingWindow*) src->data;
	SDL_HideWindow(data->window);
}

void settingWindowShow(BasicWindow* src) {
	SettingWindow* data = (SettingWindow*) src->data;
	SDL_ShowWindow(data->window);
}

bool isSettingsButtonActive(BasicWindow* src) {

	SettingWindow* data = (SettingWindow*) src->data;

	if ((1 == getActiveStatus(data->widgets[SETTING_SINGLE_PLAYER]))
			|| (1 == getActiveStatus(data->widgets[SETTING_TWO_PLAYER]))) {
		return true;
	} else {
		return false;
	}
}

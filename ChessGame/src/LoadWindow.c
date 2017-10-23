/*
 * LoadWindow.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "LoadWindow.h"

//Helper function to create buttons in the simple window;
Widget** createLoadWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL) {
		return NULL;
	}
	int i = 0;
	Widget** widgets = malloc(sizeof(Widget*) * LOAD_NUM_OF_BUTTENS);
	if (widgets == NULL) {
		return NULL;
	}

	SDL_Rect slot1R = { .x = SLOT_X, .y = SLOT_Y, .h = SLOT_BTN_HEIGHT, .w =
	SLOT_BTN_WIDTH };
	SDL_Rect slot2R = { .x = SLOT_X + SLOT_OFFSET_X, .y = SLOT_Y, .h =
	SLOT_BTN_HEIGHT, .w = SLOT_BTN_WIDTH };
	SDL_Rect slot3R = { .x = SLOT_X + (2 * SLOT_OFFSET_X), .y = SLOT_Y, .h =
	SLOT_BTN_HEIGHT, .w = SLOT_BTN_WIDTH };
	SDL_Rect slot4R = { .x = SLOT_SECOND_X, .y = SLOT_SECOND_Y, .h =
	SLOT_BTN_HEIGHT, .w =
	SLOT_BTN_WIDTH };
	SDL_Rect slot5R = { .x = SLOT_SECOND_X + SLOT_OFFSET_X, .y = SLOT_SECOND_Y,
			.h = SLOT_BTN_HEIGHT, .w = SLOT_BTN_WIDTH };
	SDL_Rect backR = { .x = BACK_X, .y = BACK_Y, .h =
	BACK_BTN_HEIGHT, .w = BACK_BTN_WIDTH };
	SDL_Rect loadR = { .x = LOAD_X, .y =
	LOAD_Y, .h = LOAD_BTN_HEIGHT, .w = LOAD_BTN_WIDTH };
	widgets[0] = createBasicButton(renderer, &slot1R, SLOT1_BTN,
	SLOT1_BTN_NOT_SELECTED, false);
	widgets[1] = createBasicButton(renderer, &slot2R, SLOT2_BTN,
	SLOT2_BTN_NOT_SELECTED, false);
	widgets[2] = createBasicButton(renderer, &slot3R, SLOT3_BTN,
	SLOT3_BTN_NOT_SELECTED, false);
	widgets[3] = createBasicButton(renderer, &slot4R, SLOT4_BTN,
	SLOT4_BTN_NOT_SELECTED, false);
	widgets[4] = createBasicButton(renderer, &slot5R, SLOT5_BTN,
	SLOT5_BTN_NOT_SELECTED, false);
	widgets[5] = createBasicButton(renderer, &backR, BACK_BTN,
	BACK_BTN_NOT_SELECTED, true);
	widgets[6] = createBasicButton(renderer, &loadR, LOAD_SAVE_BTN,
	LOAD_SAVE_BTN_NOT_SELECTED, true);

	for (i = 0; i < LOAD_NUM_OF_BUTTENS; i++) {
		if (NULL == widgets[i]) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			destroyWidget(widgets[3]); //NULL SAFE
			destroyWidget(widgets[4]); //NULL SAFE
			destroyWidget(widgets[5]); //NULL SAFE
			destroyWidget(widgets[6]); //NULL SAFE
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}
BasicWindow* createLoadWindow() {
	BasicWindow* res = malloc(sizeof(BasicWindow));
	LoadWindow* data = malloc(sizeof(LoadWindow));

	// Initialize slots array with null terminated character
	int i = 0;
	for (; i <SLOTS_NUMS; i++) {
		data->slotsArray[i][0] = '\0';
	}


	// Fill slots array with predefined paths (SLOT1-SLOT5)
	strcpy(data->slotsArray[0], SLOT1);
	strcpy(data->slotsArray[1], SLOT2);
	strcpy(data->slotsArray[2], SLOT3);
	strcpy(data->slotsArray[3], SLOT4);
	strcpy(data->slotsArray[4], SLOT5);

	SDL_Window* window = SDL_CreateWindow("Load Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createLoadWindowWidgets(renderer);
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
	SDL_Surface* loadingSurface = SDL_LoadBMP(BACKROUND_LOAD);
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
	data->pressedSlot = NULL;
	data->widgets = widgets;
	data->numOfWidgets = LOAD_NUM_OF_BUTTENS;
	data->window = window;
	data->windowRenderer = renderer;
	data->windowBackRound = backRoundTexture;
	res->data = (void*) data;
	res->destroyWindow = destroyLoadWindow;
	res->drawWindow = drawLoadWindow;
	res->handleEventWindow = handleEventLoadWindow;

	return res;
}
void destroyLoadWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	LoadWindow* data = (LoadWindow*) src->data;
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
void drawLoadWindow(BasicWindow* src) {
	FILE* fptr;
	int len = 0;

	if (src == NULL) {
		return;
	}
	LoadWindow* data = (LoadWindow*) src->data;

	//Draw window
	SDL_SetWindowPosition(data->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetRenderDrawColor(data->windowRenderer, 255, 255, 255, 255);
	SDL_RenderClear(data->windowRenderer);
	SDL_RenderCopy(data->windowRenderer, data->windowBackRound,
	NULL, NULL);
	int i = 0;
	(data->widgets[LOAD_BACK])->drawWidget(data->widgets[LOAD_BACK]);

	for (; i < data->numOfWidgets - MINUS_BACK_START; i++) {

		fptr = fopen(data->slotsArray[i], "r");
		if (NULL == fptr) {
			continue;
		}
		fseek(fptr, 0, SEEK_END);

		len = ftell(fptr);

		if (len > 0) {
			data->activeSlotsArray[i] = 1;
			(data->widgets[i])->drawWidget(data->widgets[i]);
		}
		else{
			data->activeSlotsArray[i] = 0;
		}
		fclose(fptr);

	}

	int isSlot1Active = getActiveStatus(data->widgets[LOAD_SLOT_1]);
	int isSlot2Active = getActiveStatus(data->widgets[LOAD_SLOT_2]);
	int isSlot3Active = getActiveStatus(data->widgets[LOAD_SLOT_3]);
	int isSlot4Active = getActiveStatus(data->widgets[LOAD_SLOT_4]);
	int isSlot5Active = getActiveStatus(data->widgets[LOAD_SLOT_5]);

	if (isSlot1Active == 1 || isSlot2Active == 1 || isSlot3Active == 1
			|| isSlot4Active == 1 || isSlot5Active == 1) {
		(data->widgets[LOAD_DATA])->drawWidget(data->widgets[LOAD_DATA]);
	}

	SDL_RenderPresent(data->windowRenderer);
}

void handleEventLoadWindow(BasicWindow* src, SDL_Event* event, int* eventNum) {
	if (src == NULL || event == NULL) {
		*eventNum = 1;
		return;
	}
	LoadWindow* data = (LoadWindow*) src->data;
	int i = 0;
	int answer = -1;
	int clickedButton = -1;
	for (; i < data->numOfWidgets; i++) {
		data->widgets[i]->isClicked(data->widgets[i], event, &answer);
		if (answer == 1) {
			clickedButton = i;

			if (i >= 0 && i < 5 && (data->activeSlotsArray[i]==1)) {
				// Set slot to active
				// First time a slot was selected
				if (NULL == data->pressedSlot) {
					data->pressedSlot = data->widgets[i];
					// turn pressed btn to active
					changeActive(data->widgets[i], true);
				}
				// Different slot was chosen, change slots
				else if (data->pressedSlot != data->widgets[i]) {
					// turn pressed btn to active
					changeActive(data->pressedSlot, false);
					// turn pressedSlot to off
					changeActive(data->widgets[i], true);
					// update pressedBtn
					data->pressedSlot = data->widgets[i];
				}
				// turn load to true
				changeActive(data->widgets[LOAD_DATA], true);
			}
		}
	}
	// Here a scheme of what to do or return
	*eventNum = clickedButton;
	return;
}

void loadWindowHide(BasicWindow* src) {
	LoadWindow* data = (LoadWindow*) src->data;
	SDL_HideWindow(data->window);
}

void loadWindowShow(BasicWindow* src) {
	LoadWindow* data = (LoadWindow*) src->data;
	SDL_ShowWindow(data->window);
}

bool saveToFile(BasicWindow* src) {

	if (src == NULL) {
		return false;
	}
	int ret;

	int i = 3;
	LoadWindow* data = (LoadWindow*) src->data;

	if (NULL == data) {
		return false;
	}

	ret = remove(data->slotsArray[i + 1]);

	if (ret != 0) {
		// remove start failed
		return false;
	}

	for (; i >= 0; i--) {

		ret = rename(data->slotsArray[i], data->slotsArray[i + 1]);

		if (ret != 0) {
			// rename failed
			return false;
		}

	}

	return true;
}

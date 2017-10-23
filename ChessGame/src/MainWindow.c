/*
 * MainWindow.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "MainWindow.h"

//Helper function to create buttons in the simple window;
Widget** createMainWindowWidgets(SDL_Renderer* renderer) {
	if (renderer == NULL) {
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * MAIN_NUM_OF_BUTTENS);
	if (widgets == NULL) {
		return NULL;
	}
	SDL_Rect startR = { .x = RECTX, .y = RECTY_START, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH };
	SDL_Rect loadR = { .x = RECTX, .y = RECTY_OPTIONS, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH };
	SDL_Rect exitR = { .x = RECTX, .y = RECTY_EXIT, .h = BUTTON_HEIGHT, .w = BUTTON_WIDTH };
	widgets[0] = createBasicButton(renderer, &startR, START_BTN,
			START_BTN, true);
	widgets[1] = createBasicButton(renderer, &loadR, LOAD_BTN,
			LOAD_BTN, true);
	widgets[2] = createBasicButton(renderer, &exitR, EXIT_BTN,
			EXIT_BTN, true);
	if (widgets[0] == NULL || widgets[1] == NULL || widgets[2] == NULL) {
		destroyWidget(widgets[0]); //NULL SAFE
		destroyWidget(widgets[1]); //NULL SAFE
		destroyWidget(widgets[2]); //NULL SAFE
		free(widgets);
		return NULL;
	}
	return widgets;
}
BasicWindow* createMainWindow() {
	BasicWindow* res = malloc(sizeof(BasicWindow));
	MainWindow* data = malloc(sizeof(MainWindow));
	SDL_Window* window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** widgets = createMainWindowWidgets(renderer);
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
	SDL_Surface* loadingSurface = SDL_LoadBMP(BACK_RND);
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
	data->numOfWidgets = MAIN_NUM_OF_BUTTENS;
	data->window = window;
	data->windowRenderer = renderer;
	data->windowBackRound = backRoundTexture;
	res->data = (void*) data;
	res->destroyWindow = destroyMainWindow;
	res->drawWindow = drawMainWindow;
	res->handleEventWindow = handleEventMainWindow;
	return res;
}
void destroyMainWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	MainWindow* data = (MainWindow*) src->data;
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		//destroyWidget(data->widgets[i]);
		data->widgets[i]->destroyWidget(data->widgets[i]);
	}
	free(data->widgets);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	SDL_DestroyTexture(data->windowBackRound);
	free(data);
	free(src);
}
void drawMainWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	MainWindow* data = (MainWindow*) src->data;
	//Draw window
	SDL_SetRenderDrawColor(data->windowRenderer, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR, WHITE_COLOR);
	SDL_SetWindowPosition(data->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_RenderClear(data->windowRenderer);
	SDL_RenderCopy(data->windowRenderer, data->windowBackRound,
			NULL, NULL);
	int i = 0;
	for (; i < data->numOfWidgets; i++) {
		(data->widgets[i])->drawWidget(data->widgets[i]);
	}
	SDL_RenderPresent(data->windowRenderer);
}

void handleEventMainWindow(BasicWindow* src, SDL_Event* event, int* eventNum) {
	if (src == NULL || event == NULL) {
		*eventNum = 1;
		return;
	}
	MainWindow* data = (MainWindow*) src->data;
	int i = 0;
	int answer = -1;
	int clickedButton = -1;
	for (; i < data->numOfWidgets; i++) {
		data->widgets[i]->isClicked(data->widgets[i], event, &answer);
		if (answer == 1) {
			clickedButton = i;
		}

	}
	// Here a scheme of what to do or return
	*eventNum = clickedButton;
	return;
}

void mainWindowHide(BasicWindow* src) {
	MainWindow* data = (MainWindow*) src->data;
	SDL_HideWindow(data->window);
}

void mainWindowShow(BasicWindow* src) {
	MainWindow* data = (MainWindow*) src->data;
	SDL_ShowWindow(data->window);
}

/*
 * GameWindow.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "GameWindow.h"

//Helper function to create buttons in the game window
Widget** createGameWindowControlButtons(SDL_Renderer* renderer) {
	if (renderer == NULL) {
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * GAME_NUM_OF_CONTROL_BUTTONS);
	if (widgets == NULL) {
		return NULL;
	}
	int i = 0;
	SDL_Rect restartR = { .x = X_BTNS_OFFSET, .y = Y_BTN_RESTARAT, .h =
			BTN_HEIGHT, .w = BTN_WIDTH };
	SDL_Rect saveR = { .x = X_BTNS_OFFSET,
			.y = Y_BTN_RESTARAT + (Y_BTNS_OFFSET), .h = BTN_HEIGHT, .w =
					BTN_WIDTH };
	SDL_Rect loadR = { .x = X_BTNS_OFFSET, .y = Y_BTN_RESTARAT
			+ (2 * Y_BTNS_OFFSET), .h = BTN_HEIGHT, .w = BTN_WIDTH };
	SDL_Rect undoR = { .x = X_BTNS_OFFSET, .y = Y_BTN_RESTARAT + 2
			+ (3 * Y_BTNS_OFFSET), .h = BTN_HEIGHT, .w = BTN_WIDTH };
	SDL_Rect mainMenuR = { .x = X_BTNS_OFFSET, .y = Y_BTN_MAINMENU, .h =
			BTN_HEIGHT, .w = BTN_WIDTH };
	SDL_Rect exitR = { .x = X_BTNS_OFFSET, .y = Y_BTN_MAINMENU + Y_BTNS_OFFSET,
			.h = BTN_HEIGHT, .w = BTN_WIDTH };
	widgets[0] = createBasicButton(renderer, &restartR, RESTART_ACTIVE_BUTTON,
	RESTART_BUTTON, true);
	widgets[1] = createBasicButton(renderer, &saveR, SAVE_ACTIVE_BUTTON,
	SAVE_BUTTON, true);
	widgets[2] = createBasicButton(renderer, &loadR, LOAD_ACTIVE_BUTTON,
	LOAD_BUTTON, true);

	widgets[3] = createBasicButton(renderer, &undoR, UNDO_ACTIVE_BOTTUN,
	UNDO_BOTTUN, false);
	widgets[4] = createBasicButton(renderer, &mainMenuR,
	MAIN_MENU_ACTIVE_BUTTON, MAIN_MENU_ACTIVE_BUTTON, true);
	widgets[5] = createBasicButton(renderer, &exitR, EXIT_ACTIVE_BUTTON,
	EXIT_ACTIVE_BUTTON, true);

	for (i = 0; i < GAME_NUM_OF_CONTROL_BUTTONS; i++) {
		if (NULL == widgets[i]) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			destroyWidget(widgets[3]); //NULL SAFE
			destroyWidget(widgets[4]); //NULL SAFE
			destroyWidget(widgets[5]); //NULL SAFE
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}

Widget** createGameWindowWhitePieces(SDL_Renderer* renderer) {
	if (NULL == renderer) {
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * NUMBER_OF_WHITE_PIECES);
	if (NULL == widgets) {
		return NULL;
	}
	int i = 0;
	SDL_Rect pieceR = { .x = 0, .y = 0, .h = PIECE_SIZE, .w = PIECE_SIZE };
	widgets[0] = createBasicLabel(renderer, &pieceR, WHITE_PAWN_IMG);
	widgets[1] = createBasicLabel(renderer, &pieceR, WHITE_KNIGHT_IMG);
	widgets[2] = createBasicLabel(renderer, &pieceR, WHITE_BISHOP_IMG);
	widgets[3] = createBasicLabel(renderer, &pieceR, WHITE_ROOK_IMG);
	widgets[4] = createBasicLabel(renderer, &pieceR, WHITE_QUEEN_IMG);
	widgets[5] = createBasicLabel(renderer, &pieceR, WHITE_KING_IMG);

	for (i = 0; i < NUMBER_OF_WHITE_PIECES; i++) {
		if (NULL == widgets[i]) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			destroyWidget(widgets[3]); //NULL SAFE
			destroyWidget(widgets[4]); //NULL SAFE
			destroyWidget(widgets[5]); //NULL SAFE
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}

Widget** createGameWindowBlackPieces(SDL_Renderer* renderer) {
	if (NULL == renderer) {
		return NULL;
	}
	Widget** widgets = malloc(sizeof(Widget*) * NUMBER_OF_WHITE_PIECES);
	if (NULL == widgets) {
		return NULL;
	}
	int i = 0;
	SDL_Rect pieceR = { .x = 0, .y = 0, .h = PIECE_SIZE, .w = PIECE_SIZE };
	widgets[0] = createBasicLabel(renderer, &pieceR, BLACK_PAWN_IMG);
	widgets[1] = createBasicLabel(renderer, &pieceR, BLACK_KNIGHT_IMG);
	widgets[2] = createBasicLabel(renderer, &pieceR, BLACK_BISHOP_IMG);
	widgets[3] = createBasicLabel(renderer, &pieceR, BLACK_ROOK_IMG);
	widgets[4] = createBasicLabel(renderer, &pieceR, BLACK_QUEEN_IMG);
	widgets[5] = createBasicLabel(renderer, &pieceR, BLACK_KING_IMG);

	for (i = 0; i < NUMBER_OF_WHITE_PIECES; i++) {
		if (NULL == widgets[i]) {
			destroyWidget(widgets[0]); //NULL SAFE
			destroyWidget(widgets[1]); //NULL SAFE
			destroyWidget(widgets[2]); //NULL SAFE
			destroyWidget(widgets[3]); //NULL SAFE
			destroyWidget(widgets[4]); //NULL SAFE
			destroyWidget(widgets[5]); //NULL SAFE
			free(widgets);
			return NULL;
		}
	}
	return widgets;
}

BasicWindow* createGameWindow() {
	BasicWindow* res = malloc(sizeof(BasicWindow));
	GameWindow* data = malloc(sizeof(GameWindow));
	SDL_Window* window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	Widget** gameControlButtons = createGameWindowControlButtons(renderer);
	Widget** gameBoardWhitePieces = createGameWindowWhitePieces(renderer);
	Widget** gameBoardBlackPieces = createGameWindowBlackPieces(renderer);
	if (res == NULL || data == NULL || window == NULL || renderer == NULL
			|| gameControlButtons == NULL) {
		free(res);
		free(data);
		free(gameControlButtons);
		//We first destroy the renderer
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	SDL_Surface* loadingSurface = SDL_LoadBMP(GAME_WINDOW_BACKROUND);
	if (loadingSurface == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		free(res);
		free(data);
		free(gameControlButtons);
		free(gameBoardWhitePieces);
		free(gameBoardBlackPieces);
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
		free(gameControlButtons);
		free(gameBoardWhitePieces);
		free(gameBoardBlackPieces);
		//We first destroy the renderer
		SDL_FreeSurface(loadingSurface);
		SDL_DestroyRenderer(renderer); //NULL safe
		SDL_DestroyWindow(window); //NULL safe
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);

	data->draggingMode = 0;
	data->xDraggingLocation = 0;
	data->yDraggingLocation = 0;
	data->iPiece = 0;
	data->jPiece = 0;
	data->controlButtons = gameControlButtons;
	data->BlackPieceLabels = gameBoardBlackPieces;
	data->WhitePieceLabels = gameBoardWhitePieces;
	data->numOfControlButtons = GAME_NUM_OF_CONTROL_BUTTONS;
	data->window = window;
	data->windowRenderer = renderer;
	data->windowBackRound = backRoundTexture;
	res->data = (void*) data;
	res->destroyWindow = destroyGameWindow;
	res->drawWindow = NULL;
	res->handleEventWindow = handleEventGameWindow;
	return res;
}
void destroyGameWindow(BasicWindow* src) {
	if (src == NULL) {
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	int i = 0;
	// Destroy control buttons
	for (i = 0; i < data->numOfControlButtons; i++) {
		data->controlButtons[i]->destroyWidget(data->controlButtons[i]);
	}
	// Destroy white pieces labels
	for (i = 0; i < NUMBER_OF_WHITE_PIECES; i++) {
		data->WhitePieceLabels[i]->destroyWidget(data->WhitePieceLabels[i]);
	}
	// Destroy black pieces labels
	for (i = 0; i < NUMBER_OF_BLACK_PIECES; i++) {
		data->BlackPieceLabels[i]->destroyWidget(data->BlackPieceLabels[i]);
	}
	free(data->controlButtons);
	free(data->WhitePieceLabels);
	free(data->BlackPieceLabels);
	SDL_DestroyRenderer(data->windowRenderer);
	SDL_DestroyWindow(data->window);
	SDL_DestroyTexture(data->windowBackRound);
	free(data);
	free(src);
}

// Waterfall design for simplicity
// Return revelant index by board char
int ConvertCharToNumberInArr(char piece) {
	switch (piece) {
	case ('M'):
	case ('m'):
		return 0;
	case ('N'):
	case ('n'):
		return 1;
	case ('B'):
	case ('b'):
		return 2;
	case ('R'):
	case ('r'):
		return 3;
	case ('Q'):
	case ('q'):
		return 4;
	case ('K'):
	case ('k'):
		return 5;
	}
	return -1;
}

void drawGameWindow(BasicWindow* src, char gameBoard[BOARD_ROW][BOARD_COL]) {
	if (src == NULL) {
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	SDL_SetWindowPosition(data->window, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED);
	//Draw window
	SDL_SetRenderDrawColor(data->windowRenderer, WHITE_COLOR, WHITE_COLOR,
			WHITE_COLOR, WHITE_COLOR);
	SDL_RenderClear(data->windowRenderer);
	SDL_RenderCopy(data->windowRenderer, data->windowBackRound, NULL, NULL);
	int i = 0, j = 0;
	for (; i < data->numOfControlButtons; i++) {
		(data->controlButtons[i])->drawWidget(data->controlButtons[i]);
	}

	SDL_Rect current_location = { .x = 0, .y = 0, .h = 0, .w = 0 };
	// Show pieces
	for (i = 0; i < NUM_INTER; i++) {
		for (j = 0; j < NUM_INTER; j++) {
			// calculate correct location:
			char current_position = gameBoard[i][j];
			// if dragging mode enabled and relevant piece selected
			if (data->draggingMode && data->iPiece == i && data->jPiece == j) {
				fillRect(&current_location, data->xDraggingLocation,
						data->yDraggingLocation, PIECE_HEIGHT, PIECE_WIDTH);
			} else {
				fillRect(&current_location, calculateXLocation(j),
						calculateYLocation(i), PIECE_HEIGHT, PIECE_WIDTH);
			}
			if (current_position != GAME_EMPTY_ENTRY_FOR_GUI) {
				if (islower(current_position)) {
					// draw white piece in location i,j
					copyRectFromGivenLocation(
							data->WhitePieceLabels[ConvertCharToNumberInArr(
									current_position)], &current_location);
					data->WhitePieceLabels[ConvertCharToNumberInArr(
							current_position)]->drawWidget(
							data->WhitePieceLabels[ConvertCharToNumberInArr(
									current_position)]);
				} else { // draw black piece in location i,j
					copyRectFromGivenLocation(
							data->BlackPieceLabels[ConvertCharToNumberInArr(
									current_position)], &current_location);
					data->BlackPieceLabels[ConvertCharToNumberInArr(
							current_position)]->drawWidget(
							data->BlackPieceLabels[ConvertCharToNumberInArr(
									current_position)]);
				}

			}
		}
	}
	SDL_RenderPresent(data->windowRenderer);
}

int calculateXLocation(int i) {
	return (i) * PIECE_WIDTH + X_LOCATION_OFFSET;
}

int calculateYLocation(int j) {
	return Y_LOCATION_OFFSET - (j + 1) * PIECE_HEIGHT;
}

// Return control button pressed
void handleEventGameWindow(BasicWindow* src, SDL_Event* event, int* eventNum) {
	if (src == NULL || event == NULL) {
		*eventNum = 1;
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	int i = 0;
	int answer = -1;
	int clickedButton = -1;
	for (; i < data->numOfControlButtons; i++) {
		data->controlButtons[i]->isClicked(data->controlButtons[i], event,
				&answer);
		if (answer == 1) {
			clickedButton = i;
		}

	}
	// Here a scheme of what to do or return
	*eventNum = clickedButton;
	return;
}

void gameWindowHide(BasicWindow* src) {
	GameWindow* data = (GameWindow*) src->data;
	SDL_HideWindow(data->window);
}

void gameWindowShow(BasicWindow* src) {
	GameWindow* data = (GameWindow*) src->data;
	SDL_ShowWindow(data->window);
}

void setGameWindowDraggingParameters(BasicWindow* src, int i, int j,
		int dragging) {
	if (NULL == src) {
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	data->iPiece = i;
	data->jPiece = j;
	data->draggingMode = dragging;
	return;
}
void setGameWindowToMoveParams(BasicWindow* src, int xLocation, int yLocation) {
	if (NULL == src) {
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	data->xDraggingLocation = xLocation;
	data->yDraggingLocation = yLocation;
	return;
}

void getIndexPieces(BasicWindow* src, int* i, int* j) {
	if (NULL == src) {
		return;
	}
	GameWindow* data = (GameWindow*) src->data;
	if (NULL == data) {
		return;
	}
	*i = data->iPiece;
	*j = data->jPiece;
}

void changeUndoButton(BasicWindow* src, bool status) {
	if (NULL == src) {
		return;
	}

	GameWindow* data = (GameWindow*) src->data;
	if (NULL == data) {
		return;
	}
	changeActive(data->controlButtons[GAME_UNDO], status);
	return;
}

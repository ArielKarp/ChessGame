/*
 * GuiManager.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "GuiManager.h"


// Buttons for message boxes
const SDL_MessageBoxButtonData finishedGameButtons[] = {
    {0, 0, "Exit" },
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Main Menu" },
};

const SDL_MessageBoxButtonData CheckGameButtons[] = {
    {0, 0, "O.k" },
};

const SDL_MessageBoxButtonData SaveGameButtons[] = {
    { 0, 0, "Yes" },
	{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "No" },
};


const SDL_MessageBoxColorScheme colorScheme = {
    { /* .colors (.r, .g, .b) */
        /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
        { 206,   204,   153 },
        /* [SDL_MESSAGEBOX_COLOR_TEXT] */
        {   10, 10,   10 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
        { 255, 255,   0 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
        {   153,   195, 153 },
        /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
        { 255,   255, 51 }
    }
};
const SDL_MessageBoxData msgBoxDataTie = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL, /* .window */
    "Tie", /* .title */
    "Game is over!", /* .message */
    SDL_arraysize(finishedGameButtons), /* .numbuttons */
	finishedGameButtons, /* .buttons */
    &colorScheme /* .colorScheme */
};

const SDL_MessageBoxData msgBoxDataCheck = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL, /* .window */
    "Check", /* .title */
    "Game is Check!", /* .message */
    SDL_arraysize(CheckGameButtons), /* .numbuttons */
	CheckGameButtons, /* .buttons */
    &colorScheme /* .colorScheme */
};

const SDL_MessageBoxData msgBoxDataMate = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL, /* .window */
    "Check-Mate", /* .title */
    "Game is over!", /* .message */
    SDL_arraysize(finishedGameButtons), /* .numbuttons */
	finishedGameButtons, /* .buttons */
    &colorScheme /* .colorScheme */
};

const SDL_MessageBoxData msgBoxDataSave = {
    SDL_MESSAGEBOX_INFORMATION, /* .flags */
    NULL, /* .window */
    "Save Game", /* .title */
    "Would you like to save the game?", /* .message */
    SDL_arraysize(SaveGameButtons), /* .numbuttons */
	SaveGameButtons, /* .buttons */
    &colorScheme /* .colorScheme */
};

GuiManager* managerCreate() {
	GuiManager* res = (GuiManager*) malloc(sizeof(GuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	FILE* fptr;
	int i = 0;
	// Create only main window
	res->mainWin = createMainWindow();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}

	res->game = GameCreate(HISTORY_SIZE);
	if (res->game == NULL) { // Failed to create the game
		SDL_Log("ERROR: Failed to create game\n");
		res->mainWin->destroyWindow(res->mainWin);
		free(res);
		return NULL;
	}
	res->loadWin = NULL;
	res->setWin = NULL;
	res->gameWin = NULL;
	res->activeWin = MAIN_WINDOW_ACTIVE;
	res->previousWin = MAIN_WINDOW_ACTIVE;
	res->loadSlotNum = 0;
	res->userMoves = false;
	res->slotsArray[0] = SLOT1;
	res->slotsArray[1] = SLOT2;
	res->slotsArray[2] = SLOT3;
	res->slotsArray[3] = SLOT4;
	res->slotsArray[4] = SLOT5;
	for (i = 0 ; i < SLOTS_NUMS; i++) {
	if( access( res->slotsArray[i], F_OK ) == -1 ) {
		fptr = fopen(res->slotsArray[i], "w");
		if (NULL == fptr) {
			return NULL;
		}
		fclose(fptr);
	}
	}
	return res;
}
void managerDestroy(GuiManager* src) {
	if (!src) {
		return;
	}
	if (NULL != src->game)
		GameDestroy(src->game);
	if (NULL != src->mainWin)
		src->mainWin->destroyWindow(src->mainWin);
	if (NULL != src->loadWin)
		src->loadWin->destroyWindow(src->loadWin);
	if (NULL != src->setWin)
		src->setWin->destroyWindow(src->setWin);
	if (NULL != src->gameWin)
		src->gameWin->destroyWindow(src->gameWin);
	free(src);
}
void managerDraw(GuiManager* src) {
	if (!src) {
		return;
	}
	// Draw active window
	if (src->activeWin == MAIN_WINDOW_ACTIVE) {
		src->mainWin->drawWindow(src->mainWin);
	}
	if (src->activeWin == LOAD_WINDOW_ACTIVE) {
		src->loadWin->drawWindow(src->loadWin);
	}
	if (src->activeWin == SETTING_WINDOW_ACTIVE) {
		src->setWin->drawWindow(src->setWin);
	}
	if (src->activeWin == GAME_WINDOW_ACTIVE) {
		drawGameWindow(src->gameWin, src->game->gameBoard);
	}
}
MANAGER_EVENT handleManagerDueToMainEvent(GuiManager* src, int eventNum) {
	if (src == NULL) {
		return MANAGER_NONE;
	}

	switch (eventNum) {
	case MAIN_START:
		src->activeWin = SETTING_WINDOW_ACTIVE;
		src->previousWin = MAIN_WINDOW_ACTIVE;
		restartGameInWindow(src);
		if (NULL == src->setWin) {
			// Create setting window
			src->setWin = createSettingWindow();
			if (NULL == src->setWin) {
				SDL_Log("ERROR: Could not create setting window\n");
				return MANAGER_QUIT;
			}
		}
		mainWindowHide(src->mainWin);
		settingWindowHide(src->setWin);
		settingWindowShow(src->setWin);
		break;
	case MAIN_LOAD:
		// Change screen to load
		src->activeWin = LOAD_WINDOW_ACTIVE;
		src->previousWin = MAIN_WINDOW_ACTIVE;
		if (NULL == src->loadWin) {
			// Create load window
			src->loadWin = createLoadWindow();
			if (NULL == src->loadWin) {
				SDL_Log("ERROR: Could not create load window\n");
				return MANAGER_QUIT;
			}
		}
		loadWindowShow(src->loadWin);
		loadWindowHide(src->loadWin);
		loadWindowShow(src->loadWin);
		// Hide main window
		mainWindowHide(src->mainWin);
		return MANAGER_NONE;
	case MAIN_QUIT:
		return MANAGER_QUIT;
	default:
		return MANAGER_NONE;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToLoadEvent(GuiManager* src, int eventNum) {
	XML_MESSAGE xmlMessage;

	if (src == NULL) {
		return MANAGER_NONE;
	}

	switch (eventNum) {
	case LOAD_SLOT_1:
		src->loadSlotNum = 1;
		return MANAGER_NONE;
	case LOAD_SLOT_2:
		src->loadSlotNum = 2;
		return MANAGER_NONE;
	case LOAD_SLOT_3:
		src->loadSlotNum = 3;
		return MANAGER_NONE;
	case LOAD_SLOT_4:
		src->loadSlotNum = 4;
		return MANAGER_NONE;
	case LOAD_SLOT_5:
		src->loadSlotNum = 5;
		return MANAGER_NONE;
	case LOAD_BACK:
		loadWindowHide(src->loadWin);
		// Update prev and current win
		src->activeWin = src->previousWin;
		src->previousWin = LOAD_WINDOW_ACTIVE;
		if (src->activeWin == MAIN_WINDOW_ACTIVE) {
			mainWindowShow(src->mainWin);
			mainWindowHide(src->mainWin);
			mainWindowShow(src->mainWin);
		} else {
			// Game window is active
			gameWindowShow(src->gameWin);
			gameWindowHide(src->gameWin);
			gameWindowShow(src->gameWin);
		}
		return MANAGER_NONE;
	case LOAD_DATA:
		switch(src->loadSlotNum){
			case 0:
				break;
			case 1:
				xmlMessage = LoadGameFromXML(SLOT1, src->game);
				checkXmlLoad(xmlMessage);
				break;
			case 2:
				xmlMessage = LoadGameFromXML(SLOT2, src->game);
				checkXmlLoad(xmlMessage);
				break;
			case 3:
				xmlMessage = LoadGameFromXML(SLOT3, src->game);
				checkXmlLoad(xmlMessage);
				break;
			case 4:
				xmlMessage = LoadGameFromXML(SLOT4, src->game);
				checkXmlLoad(xmlMessage);
				break;
			case 5:
				xmlMessage = LoadGameFromXML(SLOT5, src->game);
				checkXmlLoad(xmlMessage);
				break;
		}
		// create game window in case it does not exist
		if (NULL == src->gameWin) {
			src->gameWin = createGameWindow();
			if (NULL == src->gameWin) {
				SDL_Log("ERROR: Could not create game window\n");
				return MANAGER_QUIT;
			}
		}
		src->activeWin = GAME_WINDOW_ACTIVE;
		src->previousWin = LOAD_WINDOW_ACTIVE;
		loadWindowHide(src->loadWin);
		gameWindowShow(src->gameWin);
		gameWindowHide(src->gameWin);
		gameWindowShow(src->gameWin);
		src->userMoves = false;
		doComputersMove(src);
		getForGameStatus(src);
		return MANAGER_NONE;
	default:
		return MANAGER_NONE;
	}
	return MANAGER_NONE;

}

void checkXmlLoad(XML_MESSAGE xmlMessage) {

	if ((xmlMessage == XML_PATH_FAIL) || (xmlMessage == XML_OPEN_FILE_FAIL)
			|| (xmlMessage == XML_CLOSE_FILE_FAIL)
			|| (xmlMessage == XML_ERROR_READ_FAIL)) {
		SDL_Log("ERROR: File doesn't exist or cannot be opened\n");
	}
}

MANAGER_EVENT handleManagerDueToSettingEvent(GuiManager* src, int eventNum) {
	if (src == NULL) {
		return MANAGER_NONE;
	}

	switch (eventNum) {
	case SETTING_BACK:
		setAllButtonsToFalse(src->setWin);
		settingWindowHide(src->setWin);
		src->activeWin = MAIN_WINDOW_ACTIVE;
		src->previousWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(src->mainWin);
		mainWindowHide(src->mainWin);
		mainWindowShow(src->mainWin);
		return MANAGER_NONE;
		break;
	case SETTING_START:

		if (isSettingsButtonActive(src->setWin)) {
			// create game window in case it does not exits
			if (NULL == src->gameWin) {
				src->gameWin = createGameWindow();
				if (NULL == src->gameWin) {
					SDL_Log("ERROR: Could not create game window\n");
					return MANAGER_QUIT;
				}
			}
			src->userMoves = false;
			src->activeWin = GAME_WINDOW_ACTIVE;
			src->previousWin = SETTING_WINDOW_ACTIVE;
			settingWindowHide(src->setWin);
			gameWindowShow(src->gameWin);
			gameWindowHide(src->gameWin);
			gameWindowShow(src->gameWin);
			doComputersMove(src);
		}
		break;
	case SETTING_SINGLE_PLAYER:
		src->game->gameMode = ONE_PLAYER_MODE;
		break;
	case SETTING_TWO_PLAYER:
		src->game->gameMode = TWO_PLAYER_MODE;
		break;
	case SETTING_NOOB:
		src->game->difficulty = 1;
		break;
	case SETTING_EASY:
		src->game->difficulty = 2;
		break;
	case SETTING_MODERATE:
		src->game->difficulty = 3;
		break;
	case SETTING_HARD:
		src->game->difficulty = 4;
		break;
	case SETTING_WHITE:
		src->game->userColor = WHITE;
		break;
	case SETTING_BLACK:
		src->game->userColor = BLACK;
		break;
	default:
		return MANAGER_NONE;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT handleManagerDueToGameEvent(GuiManager* src, int eventNum) {
	if (NULL == src) {
		return MANAGER_NONE;
	}

	switch (eventNum) {
	case GAME_RESTART:
		src->userMoves = false;
		restartGameInWindow(src);
		src->game->currentPlayer = GAME_PLAYER_1_SYMBOL;
		doComputersMove(src);
		break;
	case GAME_SAVE:
		return checkIfSaveTheGame(src);
		break;
	case GAME_LOAD:
		checkIfSaveTheGame(src);
		gameWindowHide(src->gameWin);
		src->activeWin = LOAD_WINDOW_ACTIVE;
		src->previousWin = GAME_WINDOW_ACTIVE;
		// create load window in case it does not exits
		if (NULL == src->loadWin) {
			src->loadWin = createLoadWindow();
			if (NULL == src->loadWin) {
				SDL_Log("ERROR: Could not create load window\n");
				return MANAGER_QUIT;
			}
		}
		loadWindowShow(src->loadWin);
		loadWindowHide(src->loadWin);
		loadWindowShow(src->loadWin);
		break;
	case GAME_UNDO:
		undoGameInWindow(src);
		setUndoButtonActive(src);
		break;
	case GAME_MAIN_MENU:
		if (NULL != src->setWin) {
			setAllButtonsToFalse(src->setWin);
		}
		checkIfSaveTheGame(src);
		GameDestroy(src->game);
		src->game = GameCreate(HISTORY_SIZE);
		if (NULL == src->game) {
			SDL_Log("ERROR: Failed to create game\n");
			return MANAGER_QUIT;
		}
		src->userMoves = false;
		gameWindowHide(src->gameWin);
		src->activeWin = MAIN_WINDOW_ACTIVE;
		src->previousWin = MAIN_WINDOW_ACTIVE;
		mainWindowShow(src->mainWin);
		mainWindowHide(src->mainWin);
		mainWindowShow(src->mainWin);
		break;
	case GAME_EXIT:
		checkIfSaveTheGame(src);
		return MANAGER_QUIT;
	}
	return MANAGER_NONE;
}

MANAGER_EVENT managerHandleEvent(GuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL) {
		return MANAGER_NONE;
	}

	int eventNum = -1;
	if (src->activeWin == MAIN_WINDOW_ACTIVE) {
		src->mainWin->handleEventWindow(src->mainWin, event, &eventNum);
		// Map is- Start- 0, Load- 1, Exit - 2
		return handleManagerDueToMainEvent(src, eventNum);
	}
	if (src->activeWin == LOAD_WINDOW_ACTIVE) {
		src->loadWin->handleEventWindow(src->loadWin, event, &eventNum);
		// Map is- slot1- 0, slot2-1, slot3- 2, slot4-3, slot5-4, back-5, load- 6
		return handleManagerDueToLoadEvent(src, eventNum);
	}
	if (src->activeWin == SETTING_WINDOW_ACTIVE) {
		src->setWin->handleEventWindow(src->setWin, event, &eventNum);
		// Map is- SETTING_SINGLE_PLAYER=0, SETTING_TWO_PLAYER, SETTING_NOOB, SETTING_EASY, SETTING_MODERATE, SETTING_HARD, SETTING_WHITE, SETTING_BLACK, SETTING_BACK, SETTING_START
		return handleManagerDueToSettingEvent(src, eventNum);
	}
	if (src->activeWin == GAME_WINDOW_ACTIVE) {
		src->gameWin->handleEventWindow(src->gameWin, event, &eventNum);
		// Map is- 	GAME_RESTART = 0, GAME_SAVE, GAME_LOAD, GAME_UNDO, GAME_MAIN_MENU, GAME_EXIT
		return handleManagerDueToGameEvent(src, eventNum);
	}
	return MANAGER_NONE;
}

// Check if a chess piece was clicked
MANAGER_EVENT managerHandlerCheckifDragAndDrop(GuiManager* src, SDL_Event* event, int* dragging) {
	if (NULL == src || NULL == event) {
		return MANAGER_NONE;
	}

	int xLoc = event->button.x;
	int yLoc = event->button.y;
	*dragging = 0;
	if (xLoc > X_LOCATION_OFFSET && xLoc < (X_LOCATION_OFFSET + BOARD_SIZE) && yLoc < Y_LOCATION_OFFSET && yLoc > (Y_LOCATION_OFFSET - BOARD_SIZE)) { // Check valid location

		// get i, j of the clicked tile by converting pixel location to board location
		int j = floor((event->button.x - X_LOCATION_OFFSET) / PIECE_WIDTH);
		int i = floor((Y_LOCATION_OFFSET - event->button.y) / PIECE_HEIGHT);
		// check if the pieces is current's player's
		char current_position = src->game->gameBoard[i][j];
		if (current_position != GAME_EMPTY_ENTRY) {
			// if yes- dragging is enabled
			if (src->game->gameMode == TWO_PLAYER_MODE) {
				if (LowerOrUpperReverse(src->game, current_position)) {
					// set moving piece in GameWindow
					*dragging = 1;
				} else {	// o.w it's not
					*dragging = 0;
				}
			} else { //single player mode
				if ((src->game->userColor == WHITE && islower(current_position)) || (src->game->userColor == BLACK && isupper(current_position))){
					*dragging = 1;
				} else {
					*dragging = 0;
				}
			}
		}
		setGameWindowDraggingParameters(src->gameWin, i, j , *dragging);
	}
	return MANAGER_NONE;
}

MANAGER_EVENT managerHandlerDragDropEvent(GuiManager* src, SDL_Event* event) {
	if (NULL == src || NULL == event) {
		return MANAGER_NONE;
	}

	// Game window is active
	// set moving location to GameWindow
	int xLocation = event->motion.x - PIECES_OFFSET;
	int yLocation = event->motion.y - PIECES_OFFSET;
	setGameWindowToMoveParams(src->gameWin, xLocation, yLocation);
	return MANAGER_NONE;

}

MANAGER_EVENT managerHandlerDropItem (GuiManager* src, SDL_Event* event) {
	if (NULL == src || NULL == event) {
		return MANAGER_NONE;
	}
	MANAGER_EVENT rc = MANAGER_NONE;
	// get starting position
	int i = 0 , j = 0;
	GAME_MESSAGE gameSuccess = GAME_SUCCESS;
	getIndexPieces(src->gameWin, &i, &j);
	// calculate dropping k,l
	int l = floor((event->button.x - X_LOCATION_OFFSET) / PIECE_WIDTH);
	int k = floor((Y_LOCATION_OFFSET - event->button.y) / PIECE_HEIGHT);
	if (InBoardLimits(k, l) && (i != k || j != l)) {
		gameSuccess = GameSetMove(src->game, i, j, k, l); // Move was set by current user
		// Check game status and exit accordingly
		if (gameSuccess == GAME_SUCCESS) {
			// update that user moves
			src->userMoves = true;
			rc = getForGameStatus(src);
			// If game not done, play as computer:
			// check if 1 player mode, if so, set computer mode
			if (src->game->gameMode == ONE_PLAYER_MODE) {
				int z = 0, x = 0, c = 0, v = 0, suggest;
				// get computer move
				suggest = minimaxSuggestMove(src->game, src->game->difficulty, &z, &x, &c, &v);
				if (suggest == -2) {
					SDL_Log("ERROR: standard function malloc has failed\n");
					return MANAGER_QUIT;
				}
				// set move, no need to check computer's game status
				GameSetMove(src->game, z, x, c, v);
				// Draw game board
				managerDraw(src);
				// check status and print as follows
				rc = getForGameStatus(src);
			}
		}
		setUndoButtonActive(src);
	}
	// Turn off dragging
	setGameWindowDraggingParameters(src->gameWin, 0, 0 , 0);
	// return with rc updated
	return rc;
}

MANAGER_EVENT getForGameStatus(GuiManager* src) {
	int buttonid = 0;

	CHECK_MODE chekmode= getGameStatus(src->game);

	if (chekmode == TIE) {
		// Show game is over:
		if (SDL_ShowMessageBox(&msgBoxDataTie, &buttonid) < 0) {
			SDL_Log("ERROR: displaying message box\n");
			return MANAGER_QUIT;
		}
		if (buttonid == -1) {
			// no selection
		} else {
			if (buttonid == 0) {
				// user chose to exit
				return MANAGER_QUIT;
			} else {
				// Go to main menu
				if (NULL != src->setWin) {
					setAllButtonsToFalse(src->setWin);
				}
				GameDestroy(src->game);
				src->game = GameCreate(HISTORY_SIZE);
				if (NULL == src->game) {
					SDL_Log("ERROR: Failed to create game\n");
					return MANAGER_QUIT;
				}
				gameWindowHide(src->gameWin);
				src->activeWin = MAIN_WINDOW_ACTIVE;
				src->previousWin = MAIN_WINDOW_ACTIVE;
				mainWindowShow(src->mainWin);
				mainWindowHide(src->mainWin);
				mainWindowShow(src->mainWin);
				return MANAGER_NONE;
			}
		}
	}

	if (chekmode == MATE) {
		// Show game is over:
		if (SDL_ShowMessageBox(&msgBoxDataMate, &buttonid) < 0) {
			SDL_Log("ERROR: displaying message box\n");
			return MANAGER_QUIT;
		}
		if (buttonid == -1) {
			// no selection
		} else {
			if (buttonid == 0) {
				// user chose to exit
				return MANAGER_QUIT;
			} else {
				// Go to main menu
				if (NULL != src->setWin) {
					setAllButtonsToFalse(src->setWin);
				}
				GameDestroy(src->game);
				src->game = GameCreate(HISTORY_SIZE);
				if (NULL == src->game) {
					SDL_Log("ERROR: Failed to create game\n");
					return MANAGER_QUIT;
				}
				gameWindowHide(src->gameWin);
				src->activeWin = MAIN_WINDOW_ACTIVE;
				src->previousWin = MAIN_WINDOW_ACTIVE;
				mainWindowShow(src->mainWin);
				mainWindowHide(src->mainWin);
				mainWindowShow(src->mainWin);
				return MANAGER_NONE;
			}
		}
	}

	if (chekmode == CHECK) {
		if (SDL_ShowMessageBox(&msgBoxDataCheck, &buttonid) < 0) {
			SDL_Log("ERROR: displaying message box\n");
			return MANAGER_QUIT;
		}
		if (buttonid == -1) {
			// no selection
		} else {
			// user chose o.k
			return MANAGER_NONE;
		}
	}
	return MANAGER_NONE;
}

MANAGER_EVENT checkIfSaveTheGame(GuiManager* src) {
	if (NULL == src) {
		return MANAGER_NONE;
	}
	int buttonid = 0;
	if (src->userMoves) {
		if (SDL_ShowMessageBox(&msgBoxDataSave, &buttonid) < 0) {
			SDL_Log("ERROR: displaying message box\n");
			return MANAGER_QUIT;
		}
		if (buttonid == -1) {
			// no selection
		} else {
			if (buttonid == 0) {
				// user chose to save
				saveToFile(src->setWin);
				SaveGameToXMLFile(SLOT1,src->game);
				src->userMoves= false;
				return MANAGER_NONE;
			} else {
				// cancel
				return MANAGER_NONE;
			}
		}
	}
	return MANAGER_NONE;
}



bool restartGameInWindow(GuiManager* src) {
	if (src == NULL) {
		return false;
	}
	if (NULL == src->game) {
		return NULL;
	}

	if (NULL != src->game->historyMoves) { // Destroy old history
		ArrayListDestroy(src->game->historyMoves);
	}
	src->game->historyMoves = ArrayListCreate(HISTORY_SIZE);
	// If array list creation fails, free all memory are return NULL
	if (NULL == src->game->historyMoves) {
		free(src->game);
		src->game = NULL;
		return NULL;
	}
	src->game->historySize = HISTORY_SIZE;
	initGameBoard(src->game->gameBoard);
	src->game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	src->game->whiteKingLocation[0] = WHITE_PIECES_BACK_LINE;
	src->game->whiteKingLocation[1] = KING_Y_LOCATION;
	src->game->blackKingLocation[0] = BLACK_PIECES_BACK_LINE;
	src->game->blackKingLocation[1] = KING_Y_LOCATION;
	src->game->whitePieces[0] = PAWN_NUMS; //Pawns white number
	src->game->whitePieces[1] = BISHOP_NUMS; //Bishops white number
	src->game->whitePieces[2] = ROOK_NUMS; //Rooks white number
	src->game->whitePieces[3] = KNIGHT_NUMS; //Knights white number
	src->game->whitePieces[4] = QUEEN_NUMS; //Queens white number
	src->game->whitePieces[5] = KING_NUMS; //Kings white number
	src->game->blackPieces[0] = PAWN_NUMS; //Pawns black number
	src->game->blackPieces[1] = BISHOP_NUMS; //Bishops black number
	src->game->blackPieces[2] = ROOK_NUMS; //Rooks black number
	src->game->blackPieces[3] = KNIGHT_NUMS; //Knights black number
	src->game->blackPieces[4] = QUEEN_NUMS; //Queens black number
	src->game->blackPieces[5] = KING_NUMS; //Kings black number

	return true;
}

bool undoGameInWindow(GuiManager* src) {

	if (src->game->gameMode == ONE_PLAYER_MODE && ArrayListSize(src->game->historyMoves) > 1) {
		GAME_MESSAGE undo1;
		GAME_MESSAGE undo2;
		DataMember* undo1Member;
		DataMember* undo2Member;

		//get last element from array list and make undo
		undo1Member = ArrayListGetLast(src->game->historyMoves);
		if (NULL == undo1Member) {
			printf("Empty history, move cannot be undone\n");
			return false;
		}

		undo1 = GameUndoPrevMove(src->game);
		if (undo1 == GAME_NO_HISTORY) {
			printf("Empty history, move cannot be undone\n");
			return false;
		}
		if (undo1 == GAME_INVALID_ARGUMENT || undo1 == GAME_INVALID_MOVE) {
			perror_command("invalid command");
			return false;
		}

		//get last element from array list and make undo
		undo2Member = ArrayListGetLast(src->game->historyMoves);

		if (NULL == undo2Member) {
			printf("Empty history, move cannot be undone\n");
			return false;
		}

		undo2 = GameUndoPrevMove(src->game);
		if (undo2 == GAME_NO_HISTORY) {
			printf("Empty history, move cannot be undone\n");
			return false;
		}
		if (undo2 == GAME_INVALID_ARGUMENT || undo1 == GAME_INVALID_MOVE) {
			perror_command("invalid command");
			return false;
		}

		return true;

	} else if (src->game->gameMode == TWO_PLAYER_MODE){
		printf("Undo command not available in 2 players mode\n");
	}
	return false;

}

void doComputersMove(GuiManager* src) {
	if (NULL == src) {
		return;
	}
	if (src->game->gameMode == ONE_PLAYER_MODE && ((src->game->userColor == BLACK && src->game->currentPlayer == GAME_PLAYER_1_SYMBOL) || (src->game->userColor == WHITE && src->game->currentPlayer == GAME_PLAYER_2_SYMBOL))){
		// if game mdoe is 1 player, make first move by computer
		int z = 0, x = 0, c = 0, v = 0, suggest;
		// get computer move
		suggest = minimaxSuggestMove(src->game, src->game->difficulty, &z, &x,
				&c, &v);
		if (suggest == MEM_ALLOC_ERROR) {
			SDL_Log("ERROR: standard function malloc has failed\n");
		}
		// set move
		GameSetMove(src->game, z, x, c, v);
	}
}

void setUndoButtonActive(GuiManager* src) {
	if (NULL == src) {
		return;
	}
	// set undo button mode
	if (src->game->gameMode == ONE_PLAYER_MODE && ArrayListSize(src->game->historyMoves) > 1) {
		changeUndoButton(src->gameWin, true);
	} else {
		changeUndoButton(src->gameWin, false);
	}
	return;
}


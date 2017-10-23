/*
 * GameWindow.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_


#include "BasicWindow.h"
#include "BasicButton.h"
#include "BasicLabel.h"
#include "SettingWindow.h"

#define GAME_NUM_OF_CONTROL_BUTTONS 6
#define NUMBER_OF_WHITE_PIECES 6
#define NUMBER_OF_BLACK_PIECES 6
#define X_LOCATION_OFFSET 303
#define Y_LOCATION_OFFSET 490
#define PIECE_WIDTH 49
#define PIECE_HEIGHT 48.1
#define BOARD_COL 8
#define BOARD_ROW 8
#define GAME_EMPTY_ENTRY_FOR_GUI '_'
#define BOARD_SIZE 390
#define PIECES_OFFSET 25
#define X_BTNS_OFFSET 55
#define Y_BTNS_OFFSET 64
#define Y_BTN_RESTARAT 75
#define BTN_HEIGHT 62
#define BTN_WIDTH 153
#define Y_BTN_MAINMENU 405
#define PIECE_SIZE 50
#define NUM_INTER 8



#define BLACK_PAWN_IMG "graphics/black_pawn.bmp"
#define BLACK_KNIGHT_IMG "graphics/black_knight.bmp"
#define BLACK_BISHOP_IMG "graphics/black_bishop.bmp"
#define BLACK_ROOK_IMG "graphics/black_rook.bmp"
#define BLACK_QUEEN_IMG "graphics/black_queen.bmp"
#define BLACK_KING_IMG "graphics/black_king.bmp"

#define WHITE_PAWN_IMG "graphics/white_pawn.bmp"
#define WHITE_KNIGHT_IMG "graphics/white_knigt.bmp"
#define WHITE_BISHOP_IMG "graphics/white_bishop.bmp"
#define WHITE_ROOK_IMG "graphics/white_rook.bmp"
#define WHITE_QUEEN_IMG "graphics/white_queen.bmp"
#define WHITE_KING_IMG "graphics/white_king.bmp"

#define GAME_WINDOW_BACKROUND "graphics/game_board.bmp"
#define RESTART_BUTTON "graphics/restart_activated_btn.bmp"
#define RESTART_ACTIVE_BUTTON "graphics/restart_activated_btn.bmp"
#define UNDO_BOTTUN "graphics/undo_btn.bmp"
#define UNDO_ACTIVE_BOTTUN "graphics/undo_activated_btn.bmp"
#define SAVE_BUTTON "graphics/save_activated_btn.bmp"
#define SAVE_ACTIVE_BUTTON "graphics/save_activated_btn.bmp"
#define LOAD_BUTTON "graphics/load_activated_btn.bmp"
#define LOAD_ACTIVE_BUTTON "graphics/load_activated_btn.bmp"
#define MAIN_MENU_ACTIVE_BUTTON "graphics/main_menu_activated_btn.bmp"
#define EXIT_ACTIVE_BUTTON "graphics/exit_game_activated_btn.bmp"

typedef enum {
	GAME_RESTART = 0, GAME_SAVE, GAME_LOAD, GAME_UNDO, GAME_MAIN_MENU, GAME_EXIT, GAME_MOVE_PIECE
} GAME_EVENT;

typedef struct game_window_t {
	SDL_Window* window;
	SDL_Renderer* windowRenderer;
	SDL_Texture* windowBackRound;
	//All widgets in our window
	Widget** controlButtons;
	Widget** WhitePieceLabels;
	Widget** BlackPieceLabels;
	int numOfControlButtons;
	int xDraggingLocation;
	int yDraggingLocation;
	int iPiece;
	int jPiece;
	int draggingMode;

}GameWindow;


/**
 * Create game window
 * @return
 */
BasicWindow* createGameWindow();

/**
 * Create game window control buttons
 * @param renderer
 * @return
 */
Widget** createGameWindowControlButtons(SDL_Renderer* renderer);

/**
 * Create game window white pieces labels
 * @param renderer
 * @return
 */
Widget** createGameWindowWhitePieces(SDL_Renderer* renderer);

/**
 * Create game window black pieces labels
 * @param renderer
 * @return
 */
Widget** createGameWindowBlackPieces(SDL_Renderer* renderer);

/**
 * Destroy game window and it's widgets
 * @param src
 */
void destroyGameWindow(BasicWindow* src);

/**
 * Change undo button in game window with status given
 * @param src input window
 * @param status to be updated
 */
void changeUndoButton(BasicWindow* src, bool status);

/**
 * Draw game window and buttons with regard to game board status
 * @param src
 */
void drawGameWindow(BasicWindow* src, char gameBoard[BOARD_ROW][BOARD_COL]);

/**
 * Handler functions for events of game window
 * @param src window in
 * @param event occured event
 * @param eventNum return value of clicked button
 */
void handleEventGameWindow(BasicWindow* src, SDL_Event* event, int* eventNum);

/**
 * Hide game window
 * @param src
 */
void gameWindowHide(BasicWindow* src);

/**
 * Show game window
 * @param src
 */
void gameWindowShow(BasicWindow* src);


/**
 * Calculate x location in pixels
 * @param i in game row
 * @return x pixel location
 */
int calculateXLocation(int i);

/**
 * Calculate y location in pixels
 * @param j in game collumn
 * @return y pixel location
 */
int calculateYLocation(int j);

/**
 * Set window with dragging parameters
 * @param src GameWindow structure
 * @param i
 * @param j
 * @param dragging
 */
void setGameWindowDraggingParameters(BasicWindow* src,int i, int j , int dragging);

/**
 * Set x and y location of the source piece
 * @param src
 * @param xLocation
 * @param yLocation
 */
void setGameWindowToMoveParams(BasicWindow* src, int xLocation, int yLocation);

/**
 * Return i,j of source piece location
 * @param src
 * @param i
 * @param j
 */
void getIndexPieces(BasicWindow* src, int* i, int* j);

#endif /* GAMEWINDOW_H_ */

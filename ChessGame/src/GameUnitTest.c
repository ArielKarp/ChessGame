/*
 * GameTester.c
 *
 *  Created on: 18 ����� 2017
 *      Author: User
 */
#include "Game.h"
#include "unit_test_util.h"

#define HISTORY_SIZE 3


static bool createCopyTest() {
	Game* game=GameCreate(HISTORY_SIZE);
	Game* copy=GameCopy(game);
	////GamePrintBoard(game);
	////GamePrintBoard(copy);
	GameDestroy(game);
	//GamePrintBoard(copy);
	GameDestroy(copy);
	return true;
}

static bool currPlayerTest() {
	Game* game=GameCreate(HISTORY_SIZE);
	//GamePrintBoard(game);
	char player=GameGetCurrentPlayer(game);
	ASSERT_TRUE(player=='W');
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	player=GameGetCurrentPlayer(game);
	ASSERT_TRUE(player=='B');
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	player=GameGetCurrentPlayer(game);
	ASSERT_TRUE(player=='W');
	GameDestroy(game);
	return true;
}

static bool doAndUndoMove() {
	Game* game=GameCreate(HISTORY_SIZE);
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,2,4,2));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	GameDestroy(game);
	return true;
}

static bool whiteStartMovesTest() {
	Game* game=GameCreate(HISTORY_SIZE);
	//B2->B4
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,2,4,2));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game)); //B2
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,2,3,2));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));//B2
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,2,1,2));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,2,3,2));
	//GamePrintBoard(game);

	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//B3->B4
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,2,4,2));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);

	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game)); //B2
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,2,6,2));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,1
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,1,4,1));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,1,3,1));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,1,1,1));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,1,3,1));
	//GamePrintBoard(game);

	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,1,4,1));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,1,6,1));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,0
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,3,4,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,3,3,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,3,1,3));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,3,3,3));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,3,4,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,3,6,3));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,2
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,4,4,4));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,4,3,4));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,4,1,4));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,4,3,4));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,4,4,4));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,4,6,4));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,3
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,5,4,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,5,3,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,5,1,5));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,5,3,5));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,5,4,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,5,6,5));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,4
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,6,4,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,6,3,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,6,1,6));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,6,3,6));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,6,4,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,6,6,6));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,5
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,7,4,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,7,3,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,7,1,7));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,7,3,7));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,7,4,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,7,6,7));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,6
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,8,4,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,8,3,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,2,8,1,8));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,8,3,8));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,8,4,8));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,3,8,6,8));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking 1,7
	//HORSE MOVES CHECK
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,2,3,1));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,2,3,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,7,3,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,7,3,8));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);

	GameDestroy(game);
	return true;
}

static bool blackStartMovesTest() {
	Game*  game=GameCreate(HISTORY_SIZE);
	//GamePrintBoard(game);
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,1,5,1));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,1,6,1));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,1,8,1));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,1,6,1));
	//GamePrintBoard(game);
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,1,5,1));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	//printf("I fail here\n");
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));//A7
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,1,1,1));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finished checking A7
	//GamePrintBoard(game);
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,2,5,2));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,2,6,2));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,2,8,2));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,2,6,2));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,2,5,2));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,2,1,2));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,3,5,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,3,6,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,3,8,3));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,3,6,3));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,3,5,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,3,1,3));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,4,5,4));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,4,6,4));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,4,8,4));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,4,6,4));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//printf("################3 DEBUG BEITCH~~~~~~~~~~~~~~~~\n");
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,4,5,4));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,4,1,4));
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//GamePrintBoard(game);
	//printf("################3 DEBUG BEITCH~~~~~~~~~~~~~~~~\n");
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,5,5,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,5,6,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,5,8,5));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,5,6,5));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,5,5,5));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,5,1,5));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,6,5,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,6,6,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,6,8,6));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,6,6,6));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	//GamePrintBoard(game);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,6,5,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,6,1,6));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,7,5,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,7,6,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,7,8,7));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,7,6,7));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,7,5,7));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,7,1,7));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,8,5,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,8,6,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,7,8,8,8));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,8,6,8));
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,6,8,5,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_INVALID_ARGUMENT==GameSetMove(game,6,8,1,8));
	ASSERT_TRUE(GAME_NO_HISTORY==GameUndoPrevMove(game)); //finish
	//HORSE MOVE CHECK
	if (game->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		game->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,7,6,6));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,7,6,8));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,2,6,1));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,2,6,3));
	ASSERT_TRUE(GAME_SUCCESS==GameUndoPrevMove(game));
	GameDestroy(game);
	return true;
}

static bool fewMoves(){
	Game* game=GameCreate(HISTORY_SIZE);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,1,4,1));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,1,6,1));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,1,3,1));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,5,5,5));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,1,3,5));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,2,6,3));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,2,3,2));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,6,5,3));
	//GamePrintBoard(game);
	GameDestroy(game);
	return true;
}
static bool fewMoves2(){
	Game* game=GameCreate(HISTORY_SIZE);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,5,4,5));
	//GamePrintBoard(game);

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,5,5,5));
	//printf("%d\n",GameSetMove(game,1,4,5,8));

	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,4,5,8));
	//GamePrintBoard(game);
	GameDestroy(game);
	return true;
}

static bool fewMoves3(){
	Game* game=GameCreate(HISTORY_SIZE);
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,5,4,5));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,4,6,4));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,2,4,4,4));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,2,7,4));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,6,4,3));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,7,6,7));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,7,3,6));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,6,7,7));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,4,3,7,6));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,8,5,7,6));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,3,6,5,7));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,7,6,6,6));
	ASSERT_TRUE(GAME_SUCCESS==GameSetMove(game,1,4,3,6));
	//GamePrintBoard(game);
	//printf("%d, %c\n", getGameStatus(game), game->currentPlayer);
	ASSERT_TRUE(getGameStatus(game)== MATE);
	GameDestroy(game);
	return true;
}

static bool checkBoard(){
	Game* game=GameCreate(HISTORY_SIZE);
	game->gameBoard[0][0]='_';
	game->gameBoard[0][1]='_';
	game->gameBoard[0][2]='k';
	game->gameBoard[0][3]='r';
	game->gameBoard[0][4]='_';
	game->gameBoard[0][5]='b';
	game->gameBoard[0][6]='_';
	game->gameBoard[0][7]='r';
	game->gameBoard[1][0]='m';
	game->gameBoard[1][1]='m';
	game->gameBoard[1][2]='m';
	game->gameBoard[1][3]='_';
	game->gameBoard[1][4]='_';
	game->gameBoard[1][5]='m';
	game->gameBoard[1][6]='m';
	game->gameBoard[1][7]='m';
	game->gameBoard[2][0]='_';
	game->gameBoard[2][1]='_';
	game->gameBoard[2][2]='n';
	game->gameBoard[2][3]='_';
	game->gameBoard[2][4]='_';
	game->gameBoard[2][5]='_';
	game->gameBoard[2][6]='_';
	game->gameBoard[2][7]='_';
	game->gameBoard[3][0]='_';
	game->gameBoard[3][1]='_';
	game->gameBoard[3][2]='_';
	game->gameBoard[3][3]='_';
	game->gameBoard[3][4]='_';
	game->gameBoard[3][5]='_';
	game->gameBoard[3][6]='_';
	game->gameBoard[3][7]='_';
	game->gameBoard[4][0]='_';
	game->gameBoard[4][1]='_';
	game->gameBoard[4][2]='_';
	game->gameBoard[4][3]='_';
	game->gameBoard[4][4]='Q';
	game->gameBoard[4][5]='_';
	game->gameBoard[4][6]='b';
	game->gameBoard[4][7]='_';
	game->gameBoard[5][0]='_';
	game->gameBoard[5][1]='_';
	game->gameBoard[5][2]='M';
	game->gameBoard[5][3]='_';
	game->gameBoard[5][4]='M';
	game->gameBoard[5][5]='_';
	game->gameBoard[5][6]='_';
	game->gameBoard[5][7]='_';
	game->gameBoard[6][0]='M';
	game->gameBoard[6][1]='M';
	game->gameBoard[6][2]='_';
	game->gameBoard[6][3]='_';
	game->gameBoard[6][4]='_';
	game->gameBoard[6][5]='M';
	game->gameBoard[6][6]='M';
	game->gameBoard[6][7]='M';
	game->gameBoard[7][0]='R';
	game->gameBoard[7][1]='N';
	game->gameBoard[7][2]='B';
	game->gameBoard[7][3]='K';
	game->gameBoard[7][4]='_';
	game->gameBoard[7][5]='B';
	game->gameBoard[7][6]='_';
	game->gameBoard[7][7]='R';
	game->blackKingLocation[0]=7;
	game->blackKingLocation[1]=3;
	game->whiteKingLocation[0]=0;
	game->whiteKingLocation[1]=2;
	game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	//GamePrintBoard(game);
	ASSERT_TRUE(getGameStatus(game)== CHECK);
	GameDestroy(game);
	return true;
}

static bool checkMateBoard(){
	Game* game=GameCreate(HISTORY_SIZE);
	game->gameBoard[0][0]='_';
	game->gameBoard[0][1]='R';
	game->gameBoard[0][2]='_';
	game->gameBoard[0][3]='_';
	game->gameBoard[0][4]='k';
	game->gameBoard[0][5]='_';
	game->gameBoard[0][6]='_';
	game->gameBoard[0][7]='_';
	game->gameBoard[1][0]='R';
	game->gameBoard[1][1]='_';
	game->gameBoard[1][2]='_';
	game->gameBoard[1][3]='_';
	game->gameBoard[1][4]='_';
	game->gameBoard[1][5]='_';
	game->gameBoard[1][6]='_';
	game->gameBoard[1][7]='_';
	game->gameBoard[2][0]='_';
	game->gameBoard[2][1]='_';
	game->gameBoard[2][2]='_';
	game->gameBoard[2][3]='_';
	game->gameBoard[2][4]='_';
	game->gameBoard[2][5]='_';
	game->gameBoard[2][6]='_';
	game->gameBoard[2][7]='_';
	game->gameBoard[3][0]='_';
	game->gameBoard[3][1]='_';
	game->gameBoard[3][2]='_';
	game->gameBoard[3][3]='_';
	game->gameBoard[3][4]='_';
	game->gameBoard[3][5]='_';
	game->gameBoard[3][6]='_';
	game->gameBoard[3][7]='_';
	game->gameBoard[4][0]='_';
	game->gameBoard[4][1]='_';
	game->gameBoard[4][2]='_';
	game->gameBoard[4][3]='_';
	game->gameBoard[4][4]='_';
	game->gameBoard[4][5]='_';
	game->gameBoard[4][6]='_';
	game->gameBoard[4][7]='_';
	game->gameBoard[5][0]='_';
	game->gameBoard[5][1]='K';
	game->gameBoard[5][2]='_';
	game->gameBoard[5][3]='_';
	game->gameBoard[5][4]='_';
	game->gameBoard[5][5]='_';
	game->gameBoard[5][6]='_';
	game->gameBoard[5][7]='_';
	game->gameBoard[6][0]='_';
	game->gameBoard[6][1]='_';
	game->gameBoard[6][2]='_';
	game->gameBoard[6][3]='_';
	game->gameBoard[6][4]='_';
	game->gameBoard[6][5]='_';
	game->gameBoard[6][6]='_';
	game->gameBoard[6][7]='_';
	game->gameBoard[7][0]='_';
	game->gameBoard[7][1]='_';
	game->gameBoard[7][2]='_';
	game->gameBoard[7][3]='_';
	game->gameBoard[7][4]='_';
	game->gameBoard[7][5]='_';
	game->gameBoard[7][6]='_';
	game->gameBoard[7][7]='_';
	game->blackKingLocation[0]=5;
	game->blackKingLocation[1]=1;
	game->whiteKingLocation[0]=0;
	game->whiteKingLocation[1]=4;
	ASSERT_TRUE(getGameStatus(game)==MATE);
	GameDestroy(game);
	return true;
}

static bool tieBoard(){
	Game* game=GameCreate(HISTORY_SIZE);
	game->gameBoard[0][0]='_';
	game->gameBoard[0][1]='_';
	game->gameBoard[0][2]='_';
	game->gameBoard[0][3]='_';
	game->gameBoard[0][4]='_';
	game->gameBoard[0][5]='_';
	game->gameBoard[0][6]='_';
	game->gameBoard[0][7]='k';
	game->gameBoard[1][0]='_';
	game->gameBoard[1][1]='_';
	game->gameBoard[1][2]='_';
	game->gameBoard[1][3]='_';
	game->gameBoard[1][4]='_';
	game->gameBoard[1][5]='_';
	game->gameBoard[1][6]='_';
	game->gameBoard[1][7]='_';
	game->gameBoard[2][0]='_';
	game->gameBoard[2][1]='_';
	game->gameBoard[2][2]='_';
	game->gameBoard[2][3]='_';
	game->gameBoard[2][4]='_';
	game->gameBoard[2][5]='_';
	game->gameBoard[2][6]='Q';
	game->gameBoard[2][7]='M';
	game->gameBoard[3][0]='_';
	game->gameBoard[3][1]='_';
	game->gameBoard[3][2]='_';
	game->gameBoard[3][3]='_';
	game->gameBoard[3][4]='_';
	game->gameBoard[3][5]='_';
	game->gameBoard[3][6]='M';
	game->gameBoard[3][7]='_';
	game->gameBoard[4][0]='_';
	game->gameBoard[4][1]='_';
	game->gameBoard[4][2]='_';
	game->gameBoard[4][3]='_';
	game->gameBoard[4][4]='_';
	game->gameBoard[4][5]='M';
	game->gameBoard[4][6]='_';
	game->gameBoard[4][7]='_';
	game->gameBoard[5][0]='_';
	game->gameBoard[5][1]='_';
	game->gameBoard[5][2]='_';
	game->gameBoard[5][3]='_';
	game->gameBoard[5][4]='_';
	game->gameBoard[5][5]='_';
	game->gameBoard[5][6]='_';
	game->gameBoard[5][7]='_';
	game->gameBoard[6][0]='_';
	game->gameBoard[6][1]='_';
	game->gameBoard[6][2]='_';
	game->gameBoard[6][3]='_';
	game->gameBoard[6][4]='_';
	game->gameBoard[6][5]='_';
	game->gameBoard[6][6]='_';
	game->gameBoard[6][7]='_';
	game->gameBoard[7][0]='_';
	game->gameBoard[7][1]='_';
	game->gameBoard[7][2]='_';
	game->gameBoard[7][3]='_';
	game->gameBoard[7][4]='_';
	game->gameBoard[7][5]='_';
	game->gameBoard[7][6]='K';
	game->gameBoard[7][7]='_';
	game->blackKingLocation[0]=7;
	game->blackKingLocation[1]=6;
	game->whiteKingLocation[0]=0;
	game->whiteKingLocation[1]=7;
	ASSERT_TRUE(getGameStatus(game)==TIE);
	GameDestroy(game);
	return true;
}

int main() {
	printf("############################-createCopyTest-#################################\n");
	RUN_TEST(createCopyTest);
	printf("############################-currPlayerTest-#################################\n");
	RUN_TEST(currPlayerTest);
	printf("############################-doAndUndoMove-#################################\n");
	RUN_TEST(doAndUndoMove);
	printf("############################-whiteStartMovesTest-#################################\n");
	RUN_TEST(whiteStartMovesTest);
	printf("############################-blackStartMovesTest-#################################\n");
	RUN_TEST(blackStartMovesTest);
	printf("############################-fewMoves-#################################\n");
	RUN_TEST(fewMoves);
	printf("############################-fewMoves2-#################################\n");
	RUN_TEST(fewMoves2);
	printf("############################-checkBoard-#################################\n");
	RUN_TEST(checkBoard);
	printf("############################-tieBoard-#################################\n");
	RUN_TEST(tieBoard);
	printf("############################-checkMateBoard-#################################\n");
	RUN_TEST(checkMateBoard);
	printf("############################-fewMoves3-#################################\n");
	RUN_TEST(fewMoves3);
	return 0;
}

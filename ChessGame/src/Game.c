/*
 * Game.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#include "Game.h"

//Creates a new game with a specified history size.
Game* GameCreate(int historySize) {
	if (historySize <= 0) {
		return NULL;
	}
	Game* returnGame = (Game*) malloc(sizeof(Game));
	if (NULL == returnGame) {
		return NULL;
	}
	returnGame->historyMoves = ArrayListCreate(historySize);
	// If array list creation fails, free all memory are return NULL
	if (NULL == returnGame->historyMoves) {
		free(returnGame);
		returnGame = NULL;
		return NULL;
	}

	//initialize board parameters
	returnGame->historySize = historySize;
	initGameBoard(returnGame->gameBoard);
	returnGame->currentPlayer = GAME_PLAYER_1_SYMBOL;
	returnGame->whiteKingLocation[0] = WHITE_PIECES_BACK_LINE;
	returnGame->whiteKingLocation[1] = KING_Y_LOCATION;
	returnGame->blackKingLocation[0] = BLACK_PIECES_BACK_LINE;
	returnGame->blackKingLocation[1] = KING_Y_LOCATION;
	returnGame->difficulty = DEFAULT_DIFFICULTY;
	returnGame->gameMode = ONE_PLAYER_MODE;
	returnGame->userColor = WHITE;
	returnGame->whitePieces[0] = PAWN_NUMS; //Pawns white number
	returnGame->whitePieces[1] = BISHOP_NUMS; //Bishops white number
	returnGame->whitePieces[2] = ROOK_NUMS; //Rooks white number
	returnGame->whitePieces[3] = KNIGHT_NUMS; //Knights white number
	returnGame->whitePieces[4] = QUEEN_NUMS; //Queens white number
	returnGame->whitePieces[5] = KING_NUMS; //Kings white number
	returnGame->blackPieces[0] = PAWN_NUMS; //Pawns black number
	returnGame->blackPieces[1] = BISHOP_NUMS; //Bishops black number
	returnGame->blackPieces[2] = ROOK_NUMS; //Rooks black number
	returnGame->blackPieces[3] = KNIGHT_NUMS; //Knights black number
	returnGame->blackPieces[4] = QUEEN_NUMS; //Queens black number
	returnGame->blackPieces[5] = KING_NUMS; //Kings black number
	return returnGame;
}

//Set GAME_EMPTY_ENTRY in every entry of the board
void initGameBoard(char board[GAME_N_ROWS][GAME_N_COLUMNS]) {
	int i = 1, j = 0;
	for (; i < (GAME_N_ROWS - 1); i++) {

		//enter the start game by the chess piece rules
		if (i == WHITE_PIECES_FRONT_LINE) {
			for (j = 0; j < GAME_N_COLUMNS; j++) {
				board[i][j] = WHITE_PAWN;
			}
		}

		if ((i > WHITE_PIECES_FRONT_LINE) && (i < BLACK_PIECES_FRONT_LINE)) {
			for (j = 0; j < GAME_N_COLUMNS; j++) {
				board[i][j] = GAME_EMPTY_ENTRY;
			}
		}

		if (i == BLACK_PIECES_FRONT_LINE) {
			for (j = 0; j < GAME_N_COLUMNS; j++) {
				board[i][j] = BLACK_PAWN;
			}
		}

		//initialize board chars
		board[WHITE_PIECES_BACK_LINE][0] = WHITE_ROOK;
		board[WHITE_PIECES_BACK_LINE][1] = WHITE_KNIGHT;
		board[WHITE_PIECES_BACK_LINE][2] = WHITE_BISHOP;
		board[WHITE_PIECES_BACK_LINE][3] = WHITE_QUEEN;
		board[WHITE_PIECES_BACK_LINE][4] = WHITE_KING;
		board[WHITE_PIECES_BACK_LINE][5] = WHITE_BISHOP;
		board[WHITE_PIECES_BACK_LINE][6] = WHITE_KNIGHT;
		board[WHITE_PIECES_BACK_LINE][7] = WHITE_ROOK;

		board[BLACK_PIECES_BACK_LINE][0] = BLACK_ROOK;
		board[BLACK_PIECES_BACK_LINE][1] = BLACK_KNIGHT;
		board[BLACK_PIECES_BACK_LINE][2] = BLACK_BISHOP;
		board[BLACK_PIECES_BACK_LINE][3] = BLACK_QUEEN;
		board[BLACK_PIECES_BACK_LINE][4] = BLACK_KING;
		board[BLACK_PIECES_BACK_LINE][5] = BLACK_BISHOP;
		board[BLACK_PIECES_BACK_LINE][6] = BLACK_KNIGHT;
		board[BLACK_PIECES_BACK_LINE][7] = BLACK_ROOK;
	}
}

//Creates a copy of a given game.
Game* GameCopy(Game* src) {
	if (NULL == src) {
		return NULL;
	}
	Game* returnGame = GameCreate(src->historySize);
	if (NULL == returnGame) {
		return NULL;
	}
	//copy all parameters of game
	returnGame->currentPlayer = src->currentPlayer;
	returnGame->whiteKingLocation[0] = src->whiteKingLocation[0];
	returnGame->whiteKingLocation[1] = src->whiteKingLocation[1];
	returnGame->blackKingLocation[0] = src->blackKingLocation[0];
	returnGame->blackKingLocation[1] = src->blackKingLocation[1];
	returnGame->difficulty = src->difficulty;
	returnGame->gameMode = src->gameMode;
	returnGame->userColor = src->userColor;
	returnGame->whitePieces[0] = src->whitePieces[0]; //Pawns white number
	returnGame->whitePieces[1] = src->whitePieces[1]; //Bishops white number
	returnGame->whitePieces[2] = src->whitePieces[2]; //Rooks white number
	returnGame->whitePieces[3] = src->whitePieces[3]; //Knights white number
	returnGame->whitePieces[4] = src->whitePieces[4]; //Queens white number
	returnGame->whitePieces[5] = src->whitePieces[5]; //Kings white number
	returnGame->blackPieces[0] = src->blackPieces[0]; //Pawns black number
	returnGame->blackPieces[1] = src->blackPieces[1]; //Bishops black number
	returnGame->blackPieces[2] = src->blackPieces[2]; //Rooks black number
	returnGame->blackPieces[3] = src->blackPieces[3]; //Knights black number
	returnGame->blackPieces[4] = src->blackPieces[4]; //Queens black number
	returnGame->blackPieces[5] = src->blackPieces[5]; //Kings black number

	// If copy array failed then free all memory and return NULL
	if (copyArrayFromArrayList(src->historyMoves,
			returnGame->historyMoves) != true) {
		free(returnGame);
		returnGame = NULL;
		return NULL;
	}
	// Copy board
	copyBoard(returnGame->gameBoard, src->gameBoard);
	return returnGame;
}

//copy board values
void copyBoard(char destBoard[GAME_N_ROWS][GAME_N_COLUMNS],
		char srcBoard[GAME_N_ROWS][GAME_N_COLUMNS]) {
	int i = 0, j = 0;
	for (; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			destBoard[i][j] = srcBoard[i][j];
		}
	}
}

//Frees all memory allocation associated with a given game.
void GameDestroy(Game* src) {
	if (NULL == src) {
		return;
	}
	ArrayListDestroy(src->historyMoves);
	if (NULL != src) {
		free(src);
	}
	src = NULL;
}

//Sets the next move in a given game by specifying column index.
GAME_MESSAGE GameSetMove(Game* src, int row_source, int col_source,
		int row_dest, int col_dest) {
	GAME_MESSAGE rc = GAME_SUCCESS;

	if (NULL == src) {
		rc = GAME_INVALID_ARGUMENT;
		return rc;
	}

	if ((GameIsValidMovement(src, row_source, col_source, row_dest, col_dest))
			&& (!IsKingCompromisedByMove(src, row_source, col_source, row_dest,
					col_dest))) {

		//check which chess piece is it
		switch (src->gameBoard[row_dest][col_dest]) {
		case WHITE_PAWN:
			src->whitePieces[0]--;
			break;
		case BLACK_PAWN:
			src->blackPieces[0]--;
			break;
		case WHITE_BISHOP:
			src->whitePieces[1]--;
			break;
		case BLACK_BISHOP:
			src->blackPieces[1]--;
			break;
		case WHITE_ROOK:
			src->whitePieces[2]--;
			break;
		case BLACK_ROOK:
			src->blackPieces[2]--;
			break;
		case WHITE_KNIGHT:
			src->whitePieces[3]--;
			break;
		case BLACK_KNIGHT:
			src->blackPieces[3]--;
			break;
		case WHITE_QUEEN:
			src->whitePieces[4]--;
			break;
		case BLACK_QUEEN:
			src->blackPieces[4]--;
			break;
		case WHITE_KING:
			src->whitePieces[5]--;
			break;
		case BLACK_KING:
			src->blackPieces[5]--;
			break;
		default:
			break;
		}

	} else {

		rc = GAME_INVALID_ARGUMENT;
		return rc;
	}

	//History is full- remove last and shift to left
	if (ArrayListSize(src->historyMoves) == src->historySize) {
		ArrayListRemoveFirst(src->historyMoves);
	}

	// Add move to the end of the array
	if (ArrayListAddLast(src->historyMoves, row_source, col_source,
			TransCharToPiece(src->gameBoard[row_source][col_source]), row_dest,
			col_dest, TransCharToPiece(src->gameBoard[row_dest][col_dest]))
			!= ARRAY_LIST_SUCCESS) {
	}

	// Change player's turn
	if (src->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		src->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		src->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}

	// handle king's location
	if (src->gameBoard[row_source][col_source] == WHITE_KING) {
		src->whiteKingLocation[0] = row_dest;
		src->whiteKingLocation[1] = col_dest;
	} else if (src->gameBoard[row_source][col_source] == BLACK_KING) {
		src->blackKingLocation[0] = row_dest;
		src->blackKingLocation[1] = col_dest;
	}

	src->gameBoard[row_dest][col_dest] = src->gameBoard[row_source][col_source];
	src->gameBoard[row_source][col_source] = GAME_EMPTY_ENTRY;

	return rc;
}

//translate char to chess piece
char* TransCharToString(char c) {
	switch (c) {
	case WHITE_PAWN:
		return "pawn";
	case BLACK_PAWN:
		return "pawn";
	case WHITE_BISHOP:
		return "bishop";
	case BLACK_BISHOP:
		return "bishop";
	case WHITE_ROOK:
		return "rook";
	case BLACK_ROOK:
		return "rook";
	case WHITE_KNIGHT:
		return "knight";
	case BLACK_KNIGHT:
		return "knight";
	case WHITE_QUEEN:
		return "queen";
	case BLACK_QUEEN:
		return "queen";
	case WHITE_KING:
		return "king";
	case BLACK_KING:
		return "king";
	default:
		break;
	}
	return "\0";
}

//translate char to chess piece
ChessPiece TransCharToPiece(char c) {
	switch (c) {
	case WHITE_PAWN:
		return PAWN;
	case BLACK_PAWN:
		return PAWN;
	case WHITE_BISHOP:
		return BISHOP;
	case BLACK_BISHOP:
		return BISHOP;
	case WHITE_ROOK:
		return ROOK;
	case BLACK_ROOK:
		return ROOK;
	case WHITE_KNIGHT:
		return KNIGHT;
	case BLACK_KNIGHT:
		return KNIGHT;
	case WHITE_QUEEN:
		return QUEEN;
	case BLACK_QUEEN:
		return QUEEN;
	case WHITE_KING:
		return KING;
	case BLACK_KING:
		return KING;
	case GAME_EMPTY_ENTRY:
		return NONE;
	default:
		break;
	}
	return NONE;
}

//Returns the current player of the specified game.
char GameGetCurrentPlayer(Game* src) {
	if (NULL == src) {
		return GAME_EMPTY_ENTRY;
	}
	if (src->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		return GAME_PLAYER_1_SYMBOL;
	}
	return GAME_PLAYER_2_SYMBOL;
}

//the function prints the board game.
GAME_MESSAGE GamePrintBoard(Game* src) {
	GAME_MESSAGE rc = GAME_SUCCESS;
	if (NULL == src) {
		rc = GAME_INVALID_ARGUMENT;
		return rc;
	}

	int row = GAME_N_ROWS - 1;

	for (; row >= 0; row--) {

		printf("%d| %c %c %c %c %c %c %c %c |\n", row + 1,
				src->gameBoard[row][0], src->gameBoard[row][1],
				src->gameBoard[row][2], src->gameBoard[row][3],
				src->gameBoard[row][4], src->gameBoard[row][5],
				src->gameBoard[row][6], src->gameBoard[row][7]);

	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");

	return rc;
}

// Checks if a disk can be put in the specified valid location.
bool GameIsValidMovement(Game* src, int row_source, int col_source,
		int row_dest, int col_dest) {
	if (NULL == src) {
		return false;
	}
	//check if the source and dest is the same
	if ((row_source == row_dest) && (col_source == col_dest)) {
		return false;
	}

	char source_piece = src->gameBoard[row_source][col_source];
	//check if the source piece is not empty and does not belongs to the enemy
	if (isMoveAllowed(src, row_source, col_source, row_dest, col_dest) == false) {
		return false;
	}

	//check which chess piece is it
	switch (source_piece) {
	case WHITE_PAWN:
		return PawnIsValidMove(src, GAME_PLAYER_1_SYMBOL, row_source,
				col_source, row_dest, col_dest);
	case BLACK_PAWN:
		return PawnIsValidMove(src, GAME_PLAYER_2_SYMBOL, row_source,
				col_source, row_dest, col_dest);
	case WHITE_BISHOP:
	case BLACK_BISHOP:
		return BishopIsValidMove(src, row_source, col_source, row_dest,
				col_dest);
	case WHITE_ROOK:
	case BLACK_ROOK:
		return RookIsValidMove(src, row_source, col_source, row_dest, col_dest);
	case WHITE_KNIGHT:
	case BLACK_KNIGHT:
		return KnightIsValidMove(row_source, col_source, row_dest, col_dest);
	case WHITE_QUEEN:
	case BLACK_QUEEN:
		return QueenIsValidMove(src, row_source, col_source, row_dest, col_dest);
	case WHITE_KING:
	case BLACK_KING:
		return KingIsValidMove(row_source, col_source, row_dest, col_dest);
	default:
		return false;
	}

}

//Checks if a disk can be put in the specified valid location for pawn chess piece.
bool PawnIsValidMove(Game* src, char current_player, int row_source,
		int col_source, int row_dest, int col_dest) {
	int delta_x = col_dest - col_source;
	int delta_y = row_dest - row_source;
	char dest_piece = src->gameBoard[row_dest][col_dest];

	//chess piece rules for pawn
	if ((delta_x == -1) || (delta_x == 1)) {
		if ((current_player == GAME_PLAYER_1_SYMBOL) && (delta_y == 1)
				&& (isupper(dest_piece))) {
			return true;
		}
		if ((current_player == GAME_PLAYER_2_SYMBOL) && (delta_y == -1)
				&& (islower(dest_piece))) {
			return true;
		}
	}

	//chess piece rules for pawn
	if (delta_x == 0) {
		if ((current_player == GAME_PLAYER_1_SYMBOL) && (delta_y == 1)
				&& ((dest_piece) == GAME_EMPTY_ENTRY)) {
			return true;
		}
		if ((current_player == GAME_PLAYER_2_SYMBOL) && (delta_y == -1)
				&& ((dest_piece) == GAME_EMPTY_ENTRY)) {
			return true;
		}

		if ((current_player == GAME_PLAYER_1_SYMBOL) && (delta_y == 2)
				&& (row_source == 1) && ((dest_piece) == GAME_EMPTY_ENTRY)
				&& (src->gameBoard[row_source + 1][col_source]
						== GAME_EMPTY_ENTRY)) {
			return true;
		}
		if ((current_player == GAME_PLAYER_2_SYMBOL) && (delta_y == -2)
				&& (row_source == 6) && ((dest_piece) == GAME_EMPTY_ENTRY)
				&& (src->gameBoard[row_source - 1][col_source]
						== GAME_EMPTY_ENTRY)) {
			return true;
		}
	}

	return false;
}

//Checks if a disk can be put in the specified valid location for bishop chess piece.
bool BishopIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest) {
	int delta_x = col_dest - col_source;
	int delta_y = row_dest - row_source;
	int temp_x = row_source;
	int temp_y = col_source;
	int num_moves = 0;

	//chess piece rules for bishop
	if (abs(delta_x) != abs(delta_y)) {
		return false;
	}
	if (abs(delta_x) == abs(delta_y)) {
		for (; num_moves < abs(delta_x) - 1; num_moves++) {
			if ((row_dest > row_source) && (col_dest > col_source)) {
				temp_x++;
				temp_y++;
				if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
					return false;
				}
			}
			if ((row_dest > row_source) && (col_dest < col_source)) {
				temp_x++;
				temp_y--;
				if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
					return false;
				}
			}
			if ((row_dest < row_source) && (col_dest > col_source)) {
				temp_x--;
				temp_y++;
				if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
					return false;
				}
			}
			if ((row_dest < row_source) && (col_dest < col_source)) {
				temp_x--;
				temp_y--;
				if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
					return false;
				}
			}
		}

	}
	return true;
}

//Checks if a disk can be put in the specified valid location for rook chess piece.
bool RookIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest) {
	int delta_x = col_dest - col_source;
	int delta_y = row_dest - row_source;
	int temp_x = row_source;
	int temp_y = col_source;
	int num_moves = 0;
	int iterations_num = 0;
	if ((abs(delta_x) > 0) && (delta_y == 0)) {
		iterations_num = abs(delta_x);
	} else if ((delta_x == 0) && (abs(delta_y) > 0)) {
		iterations_num = abs(delta_y);
	} else {
		return false;
	}

	//chess piece rules for rook
	for (; num_moves < iterations_num - 1; num_moves++) {
		if ((delta_x == 0) && (row_dest > row_source)) {
			temp_x++;
			if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
				return false;
			}
		}
		if ((delta_x == 0) && (row_dest < row_source)) {
			temp_x--;
			if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
				return false;
			}
		}
		if ((col_dest > col_source) && (delta_y == 0)) {
			temp_y++;
			if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
				return false;
			}
		}
		if ((col_dest < col_source) && (delta_y == 0)) {
			temp_y--;
			if (src->gameBoard[temp_x][temp_y] != GAME_EMPTY_ENTRY) {
				return false;
			}
		}

	}
	return true;
}

//Checks if a disk can be put in the specified valid location for knight chess piece.
bool KnightIsValidMove(int row_source, int col_source, int row_dest,
		int col_dest) {
	int delta_x = col_dest - col_source;
	int delta_y = row_dest - row_source;

	//chess piece rules for knight
	if ((delta_x == 1) && (delta_y == 2)) {
		return true;
	}
	if ((delta_x == 2) && (delta_y == 1)) {
		return true;
	}
	if ((delta_x == 2) && (delta_y == -1)) {
		return true;
	}
	if ((delta_x == 1) && (delta_y == -2)) {
		return true;
	}
	if ((delta_x == -1) && (delta_y == -2)) {
		return true;
	}
	if ((delta_x == -2) && (delta_y == -1)) {
		return true;
	}
	if ((delta_x == -2) && (delta_y == 1)) {
		return true;
	}
	if ((delta_x == -1) && (delta_y == 2)) {
		return true;
	}

	return false;
}

//Checks if a disk can be put in the specified valid location for king chess piece.
bool KingIsValidMove(int row_source, int col_source, int row_dest, int col_dest) {
	int delta_x = col_dest - col_source;
	int delta_y = row_dest - row_source;

	//chess piece rules for king
	if ((delta_x == 1) && (delta_y == 0)) {
		return true;
	}
	if ((delta_x == 1) && (delta_y == -1)) {
		return true;
	}
	if ((delta_x == 0) && (delta_y == -1)) {
		return true;
	}
	if ((delta_x == -1) && (delta_y == -1)) {
		return true;
	}
	if ((delta_x == -1) && (delta_y == 0)) {
		return true;
	}
	if ((delta_x == -1) && (delta_y == 1)) {
		return true;
	}
	if ((delta_x == 0) && (delta_y == 1)) {
		return true;
	}
	if ((delta_x == 1) && (delta_y == 1)) {
		return true;
	}

	return false;
}

//Checks if a disk can be put in the specified valid location for queen chess piece.
bool QueenIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest) {
	if (RookIsValidMove(src, row_source, col_source, row_dest, col_dest)) {
		return true;
	}
	if (BishopIsValidMove(src, row_source, col_source, row_dest, col_dest)) {
		return true;
	}

	return false;
}

//Checks if a king is compromised by another chess piece enemy.
bool IsKingCompromisedByMove(Game* src, int row_source, int col_source,
		int row_dest, int col_dest) {
	Game* copy_game = GameCopy(src);
	char source_piece = copy_game->gameBoard[row_source][col_source];
	if (TransCharToPiece(source_piece) == KING) {
		// update in case king moves
		if (GameGetCurrentPlayer(copy_game) == GAME_PLAYER_1_SYMBOL) {
			copy_game->whiteKingLocation[0] = row_dest;
			copy_game->whiteKingLocation[1] = col_dest;
		} else if (GameGetCurrentPlayer(copy_game) == GAME_PLAYER_2_SYMBOL) {
			copy_game->blackKingLocation[0] = row_dest;
			copy_game->blackKingLocation[1] = col_dest;
		}
	}
	copy_game->gameBoard[row_dest][col_dest] =
			copy_game->gameBoard[row_source][col_source];
	copy_game->gameBoard[row_source][col_source] =
	GAME_EMPTY_ENTRY;
	bool isComp = IsKingCompromised(copy_game);
	GameDestroy(copy_game);
	return isComp;
}

bool IsKingCompromised(Game* src) {
	int i = 0;
	int j = 0;
	char current_position;
	char king_row;
	char king_col;
	// Check current player
	if (GameGetCurrentPlayer(src) == GAME_PLAYER_1_SYMBOL) {
		king_row = src->whiteKingLocation[0];
		king_col = src->whiteKingLocation[1];
	} else if (GameGetCurrentPlayer(src) == GAME_PLAYER_2_SYMBOL) {
		king_row = src->blackKingLocation[0];
		king_col = src->blackKingLocation[1];
	}

	//checks for each enemy chess piece if it can eats the king by his chess rules.
	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			current_position = src->gameBoard[i][j];
			if ((current_position != GAME_EMPTY_ENTRY)
					&& (LowerOrUpper(src, current_position))) {
				if (GameIsValidMovement(src, i, j, king_row, king_col)) {
					return true;
				}
			}
		}
	}
	return false;
}

//Checks if a current position is lower or upper char which it means it belongs to player 1 or 2.
bool LowerOrUpper(Game* src, char current_position) {

	if (GameGetCurrentPlayer(src) == GAME_PLAYER_1_SYMBOL) {
		return isupper(current_position);
	}
	if (GameGetCurrentPlayer(src) == GAME_PLAYER_2_SYMBOL) {
		return islower(current_position);
	}
	return false;

}

//Checks if a current position is lower or upper char which it means it belongs to player 1 or 2.
bool LowerOrUpperReverse(Game* src, char current_position) {

	if (GameGetCurrentPlayer(src) == GAME_PLAYER_1_SYMBOL) {
		return islower(current_position);
	}
	if (GameGetCurrentPlayer(src) == GAME_PLAYER_2_SYMBOL) {
		return isupper(current_position);
	}
	return false;

}

//Removes a disc that was put in the previous move and changes the current player's turn.
GAME_MESSAGE GameUndoPrevMove(Game* src) {
	GAME_MESSAGE rc = GAME_SUCCESS;
	ChessPiece sourcePiece;
	ChessPiece destPiece;

	if (NULL == src) {
		rc = GAME_INVALID_ARGUMENT;
		return rc;
	}
	if (ArrayListIsEmpty(src->historyMoves) == true) {
		rc = GAME_NO_HISTORY;
		return rc;
	}
	// Change player's turn
	if (src->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		src->currentPlayer = GAME_PLAYER_2_SYMBOL;
	} else {
		src->currentPlayer = GAME_PLAYER_1_SYMBOL;
	}
	DataMember* lastMove = ArrayListGetLast(src->historyMoves);

	// Catch hazard- trying to pass null to ArrayListGetLast
	if (NULL == lastMove) {
		rc = GAME_INVALID_ARGUMENT;
		return rc;
	}
	// Clear relevant entry in the board

	sourcePiece = lastMove->player;
	destPiece = lastMove->enemy;

	//check which chess piece is the one to undo and put it in the board
	if (src->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		switch (sourcePiece) {
		case PAWN:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_PAWN;
			break;
		case BISHOP:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_BISHOP;
			break;
		case ROOK:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_ROOK;
			break;
		case KNIGHT:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_KNIGHT;
			break;
		case QUEEN:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_QUEEN;
			break;
		case KING:
			src->gameBoard[lastMove->i][lastMove->j] = WHITE_KING;
			src->whiteKingLocation[0] = lastMove->i;
			src->whiteKingLocation[1] = lastMove->j;
			break;
		default:
			break;
		}

		//check which chess piece is the one to undo and put it in the board
		switch (destPiece) {
		case NONE:
			src->gameBoard[lastMove->k][lastMove->l] = GAME_EMPTY_ENTRY;
			break;
		case PAWN:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_PAWN;
			src->blackPieces[0]++;
			break;
		case BISHOP:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_BISHOP;
			src->blackPieces[1]++;
			break;
		case ROOK:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_ROOK;
			src->blackPieces[2]++;
			break;
		case KNIGHT:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_KNIGHT;
			src->blackPieces[3]++;
			break;
		case QUEEN:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_QUEEN;
			src->blackPieces[4]++;
			break;
		case KING:
			src->gameBoard[lastMove->k][lastMove->l] = BLACK_KING;
			src->blackPieces[5]++;
			src->whiteKingLocation[0] = lastMove->k;
			src->whiteKingLocation[1] = lastMove->l;
			break;
		default:
			break;
		}
	}

	//check which chess piece is the one to undo and put it in the board
	else if (src->currentPlayer == GAME_PLAYER_2_SYMBOL) {
		switch (sourcePiece) {
		case PAWN:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_PAWN;
			break;
		case BISHOP:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_BISHOP;
			break;
		case ROOK:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_ROOK;
			break;
		case KNIGHT:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_KNIGHT;
			break;
		case QUEEN:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_QUEEN;
			break;
		case KING:
			src->gameBoard[lastMove->i][lastMove->j] = BLACK_KING;
			src->whiteKingLocation[0] = lastMove->i;
			src->whiteKingLocation[1] = lastMove->j;
			break;
		default:
			break;
		}

		//check which chess piece is the one to undo and put it in the board
		switch (destPiece) {
		case NONE:
			src->gameBoard[lastMove->k][lastMove->l] = GAME_EMPTY_ENTRY;
			break;
		case PAWN:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_PAWN;
			src->whitePieces[0]++;
			break;
		case BISHOP:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_BISHOP;
			src->whitePieces[1]++;
			break;
		case ROOK:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_ROOK;
			src->whitePieces[2]++;
			break;
		case KNIGHT:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_KNIGHT;
			src->whitePieces[3]++;
			break;
		case QUEEN:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_QUEEN;
			src->whitePieces[4]++;
			break;
		case KING:
			src->gameBoard[lastMove->k][lastMove->l] = WHITE_KING;
			src->whitePieces[5]++;
			src->whiteKingLocation[0] = lastMove->k;
			src->whiteKingLocation[1] = lastMove->l;
			break;
		default:
			break;
		}
	}

// Remove last move
	ArrayListRemoveLast(src->historyMoves);
	return rc;
}

CHECK_MODE getGameStatus(Game* src) {
	int possibleMoves = getAllMoves(src);
	CHECK_MODE returnCode = PASS;
	// Check for errors
	if (possibleMoves == -1) {
		returnCode = FAIL_MODE;
		return returnCode;
	}
	// Check or Mate options
	if (IsKingCompromised(src) == true) {
		returnCode = CHECK;
		if (possibleMoves == 0) {
			returnCode = MATE;
			return returnCode;
		}
	}
	// Tie option
	if (possibleMoves == 0) {
		returnCode = TIE;
	}
	return returnCode;
}

//get all moves for specific game
int getAllMoves(Game* src) {
	int result = 0;
	int i = 0;
	int j = 0;
	char current_position;
	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			int tempRes = 0;
			current_position = src->gameBoard[i][j];
			if ((current_position != GAME_EMPTY_ENTRY)
					&& (LowerOrUpperReverse(src, current_position))) {
				// get all possible moves number for position without movesArr
				tempRes = getAllPossibleMoves(src, current_position, i, j,
				NULL, false);
				if (tempRes == -1) {
					// Something went terribly wrong
					return -1;
				}
				result += tempRes;
			}
		}
	}
	return result;
}

int getAllPossibleMoves(Game* src, char piece, int row_source, int col_source,
		int*** movesArr, bool fillMoves) {
	//check which chess piece is it
	switch (piece) {
	case WHITE_PAWN:
	case BLACK_PAWN:
		return GetPawnMoves(src, piece, row_source, col_source, movesArr,
				fillMoves);
	case WHITE_BISHOP:
	case BLACK_BISHOP:
		return GetBishopMoves(src, row_source, col_source, movesArr, fillMoves);
	case WHITE_ROOK:
	case BLACK_ROOK:
		return GetRookMoves(src, row_source, col_source, movesArr, fillMoves);
	case WHITE_KNIGHT:
	case BLACK_KNIGHT:
		return GetKnightMoves(src, row_source, col_source, movesArr, fillMoves);
	case WHITE_QUEEN:
	case BLACK_QUEEN:
		return GetQueenMoves(src, row_source, col_source, movesArr, fillMoves);
	case WHITE_KING:
	case BLACK_KING:
		return GetKingMoves(src, row_source, col_source, movesArr, fillMoves);
	default:
		return -1;
	}
	return -1;
}

//get all moves for specific game for pawn chess piece
int GetPawnMoves(Game* src, char piece, int row_source, int col_source,
		int*** movesArr, bool fillMoves) {
	int resultMoves[NUM_OF_MOVES][NUM_OF_CORDS];
	memset(resultMoves, 0, sizeof(resultMoves));
	int i = 0;
	int k = 0;
	int l = 0;
	int ReturnSize = 0;
	// Player is black
	if (isupper(piece)) {
		memcpy(resultMoves,
				(int[][NUM_OF_CORDS] ) { { row_source - 1, col_source },
								{ row_source - 2, col_source }, { row_source
										- 1, col_source - 1 }, { row_source - 1,
										col_source + 1 } }, sizeof resultMoves);
	} else if (islower(piece)) {
		memcpy(resultMoves,
				(int[][NUM_OF_CORDS] ) { { row_source + 1, col_source },
								{ row_source + 2, col_source }, { row_source
										+ 1, col_source - 1 }, { row_source + 1,
										col_source + 1 } }, sizeof resultMoves);
	}
	for (; i < 4; i++) {
		k = resultMoves[i][0];
		l = resultMoves[i][1];
		// If move is not valid or king is compromised
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& PawnIsValidMove(src, GameGetCurrentPlayer(src), row_source,
						col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			ReturnSize++;
		} else {
			// Put -1 for future use
			resultMoves[i][0] = -1;
			resultMoves[i][1] = -1;
		}
	}
	// Fill movesArr if requested
	if (fillMoves && ReturnSize > 0) {
		fillMovesArray(movesArr, ReturnSize, NUM_OF_MOVES, NUM_OF_CORDS,
				resultMoves);
	}
	return ReturnSize;
}

//get all moves for specific game for knight chess piece
int GetKnightMoves(Game* src, int row_source, int col_source, int*** movesArr,
bool fillMoves) {
	int i = 0;
	int k = 0;
	int l = 0;
	int ReturnSize = 0;
	int resultMoves[8][NUM_OF_CORDS] = { { row_source + 2, col_source + 1 }, {
			row_source + 1, col_source + 2 },
			{ row_source - 1, col_source + 2 },
			{ row_source - 2, col_source + 1 },
			{ row_source - 2, col_source - 1 },
			{ row_source - 1, col_source - 2 },
			{ row_source + 1, col_source - 2 },
			{ row_source + 2, col_source - 1 } };
	for (; i < 8; i++) {
		// If move is not valid or king is compromised
		k = resultMoves[i][0];
		l = resultMoves[i][1];
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& KnightIsValidMove(row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			ReturnSize++;
		} else {
			resultMoves[i][0] = -1;
			resultMoves[i][1] = -1;
		}
	}
	// Fill movesArr if requested
	if (fillMoves && ReturnSize > 0) {
		fillMovesArray(movesArr, ReturnSize, 8, NUM_OF_CORDS, resultMoves);
	}
	return ReturnSize;
}

//get all moves for specific game for king chess piece
int GetKingMoves(Game* src, int row_source, int col_source, int*** movesArr,
bool fillMoves) {
	int i = 0;
	int k = 0;
	int l = 0;
	int ReturnSize = 0;
	int resultMoves[8][NUM_OF_CORDS] = { { row_source + 1, col_source }, {
			row_source + 1, col_source + 1 }, { row_source, col_source + 1 }, {
			row_source - 1, col_source + 1 }, { row_source - 1, col_source }, {
			row_source - 1, col_source - 1 }, { row_source, col_source - 1 }, {
			row_source + 1, col_source - 1 } };
	for (; i < 8; i++) {
		// If move is not valid or king is compromised
		k = resultMoves[i][0];
		l = resultMoves[i][1];
		if (InBoardLimits(k, l) && KingIsValidMove(row_source, col_source, k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			ReturnSize++;
		} else {
			resultMoves[i][0] = -1;
			resultMoves[i][1] = -1;
		}
	}
	// Fill movesArr if requested
	if (fillMoves && ReturnSize > 0) {
		fillMovesArray(movesArr, ReturnSize, 8, NUM_OF_CORDS, resultMoves);
	}
	return ReturnSize;
}

//get all moves for specific game for rook chess piece
int GetRookMoves(Game* src, int row_source, int col_source, int*** movesArr,
bool fillMoves) {
	int resultMoves[14][NUM_OF_CORDS];
	memset(resultMoves, -1, sizeof(resultMoves));
	int i = 0;
	int k = 0;
	int l = 0;
	int indexArr = 0;
	// 4 ways of movement
	// Right
	for (i = 1; i < abs(GAME_N_COLUMNS - col_source); i++) {
		k = row_source;
		l = col_source + i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& RookIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Left
	for (i = 1; i < (col_source + 1); i++) {
		k = row_source;
		l = col_source - i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& RookIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Up
	for (i = 1; i < abs(GAME_N_ROWS - row_source); i++) {
		k = row_source + i;
		l = col_source;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& RookIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Down
	for (i = 1; i < (row_source + 1); i++) {
		k = row_source - i;
		l = col_source;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& RookIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Fill movesArr if requested
	if (fillMoves && indexArr > 0) {
		fillMovesArray(movesArr, indexArr, 14, NUM_OF_CORDS, resultMoves);
	}
	return indexArr;
}

//get all moves for specific game for bishop chess piece
int GetBishopMoves(Game* src, int row_source, int col_source, int*** movesArr,
bool fillMoves) {
	int resultMoves[13][NUM_OF_CORDS];
	memset(resultMoves, -1, sizeof(resultMoves));
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int indexArr = 0;
	// 4 diagonal ways of movement
	// Right-up
	// Get distance values
	int colDiff = GAME_N_COLUMNS - col_source;
	int rowDiff = GAME_N_ROWS - row_source;
	int colDist = MAX(colDiff, col_source);
	int rowDist = MAX(rowDiff, row_source);
	for (i = 1, j = 1; i < colDist && j < rowDist; i++, j++) {
		k = row_source + j;
		l = col_source + i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& BishopIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Left-up
	for (i = 1, j = 1; i < colDist && j < rowDist; i++, j++) {
		k = row_source + j;
		l = col_source - i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& BishopIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Right-down
	for (i = 1, j = 1; i < colDist && j < rowDist; i++, j++) {
		k = row_source - j;
		l = col_source + i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& BishopIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Left-down
	for (i = 1, j = 1; i < colDist && j < rowDist; i++, j++) {
		k = row_source - j;
		l = col_source - i;
		if (InBoardLimits(k, l)
				&& isMoveAllowed(src, row_source, col_source, k, l)
				&& BishopIsValidMove(src, row_source, col_source, k, l)
				&& !IsKingCompromisedByMove(src, row_source, col_source, k,
						l)) {
			resultMoves[indexArr][0] = k;
			resultMoves[indexArr][1] = l;
			indexArr++;
		}

	}
	// Fill movesArr if requested
	if (fillMoves && indexArr > 0) {
		fillMovesArray(movesArr, indexArr, 13, NUM_OF_CORDS, resultMoves);
	}
	return indexArr;
}

//get all moves for specific game for quees chess piece
int GetQueenMoves(Game* src, int row_source, int col_source, int*** movesArr,
bool fillMoves) {
	// if moves are requested
	if (fillMoves) {
		int** tempBishopMoves = NULL;
		int** tempRookMoves = NULL;
		int** tmovesArr = NULL;
		int numOfBishopMoves = 0, numOfRookMoves = 0, movesArrIndex = 0, i = 0,
				queenMoves = 0;
		numOfBishopMoves = GetBishopMoves(src, row_source, col_source,
				&tempBishopMoves, fillMoves);
		numOfRookMoves = GetRookMoves(src, row_source, col_source,
				&tempRookMoves, fillMoves);
		if (numOfBishopMoves > 0 && NULL == tempBishopMoves) {
			//bail out
			return -1;
		}
		if (numOfRookMoves > 0 && NULL == tempRookMoves) {
			//bail out
			return -1;
		}
		queenMoves = numOfBishopMoves + numOfRookMoves;
		if (queenMoves > 0) {
			tmovesArr = (int**) calloc(queenMoves, (sizeof(int*)));
			if (NULL == tmovesArr) {

				return -1;
			}
			// handles queen movesArr
			// Bishop moves first
			for (i = 0; i < numOfBishopMoves; i++, movesArrIndex++) {
				tmovesArr[movesArrIndex] = (int*) calloc(2, sizeof(int));
				if (NULL == tmovesArr[movesArrIndex]) {


					return -1;
				}
				tmovesArr[movesArrIndex][0] = tempBishopMoves[i][0];
				tmovesArr[movesArrIndex][1] = tempBishopMoves[i][1];
			}
			// Rook moves next
			for (i = 0; i < numOfRookMoves; i++, movesArrIndex++) {
				tmovesArr[movesArrIndex] = (int*) calloc(2, sizeof(int));
				if (NULL == tmovesArr[movesArrIndex]) {


					return -1;
				}
				tmovesArr[movesArrIndex][0] = tempRookMoves[i][0];
				tmovesArr[movesArrIndex][1] = tempRookMoves[i][1];
			}
		}
		// free resources
		if (NULL != tempBishopMoves) {
			for (i = 0; i < numOfBishopMoves; i++) {
				if (NULL != tempBishopMoves[i]) {
					free(tempBishopMoves[i]);
					tempBishopMoves[i] = NULL;
				}
			}
			free(tempBishopMoves);
			tempBishopMoves = NULL;
		}
		if (NULL != tempRookMoves) {
			for (i = 0; i < numOfRookMoves; i++) {
				free(tempRookMoves[i]);
				tempRookMoves[i] = NULL;
			}
			free(tempRookMoves);
			tempRookMoves = NULL;
		}
		*movesArr = tmovesArr;
		tmovesArr = NULL;
		return queenMoves;
	} else {
		return GetBishopMoves(src, row_source, col_source, NULL, false)
				+ GetRookMoves(src, row_source, col_source, NULL, false);
	}
}

//check if coordinates is in the board
bool InBoardLimits(int row_source, int col_source) {
	if (row_source
			>= 0&& row_source < GAME_N_ROWS && col_source >= 0 && col_source < GAME_N_COLUMNS) {
		return true;
	}
	return false;
}

void fillMovesArray(int*** dst, int resultSize, int srcSize, int n,
		int (*src)[n]) {
	int i = 0;
	int dstIndex = 0;
	// allocate dst
	int** tdst = (int**) calloc(resultSize, (sizeof(int*)));
	for (i = 0; i < srcSize; i++) {
		// If move is valid insert to dst
		if (src[i][0] != -1 && src[i][1] != -1) {
			tdst[dstIndex] = (int*) calloc(n, sizeof(int));
			if (NULL == tdst[dstIndex]) {
				// Failed to allocate, bail out
				return;
			}
			// Place move- n equals to 2
			tdst[dstIndex][0] = src[i][0];
			tdst[dstIndex][1] = src[i][1];

			dstIndex++;
		}
	}
	*dst = tdst;
	tdst = NULL;
	return;
}

bool isMoveAllowed(Game* src, int row_source, int col_source, int row_dest,
		int col_dest) {
	char source_piece = src->gameBoard[row_source][col_source];
	//check if the destination piece is empty and does not belongs to the player
	char dest_piece = src->gameBoard[row_dest][col_dest];
	if (isupper(source_piece)
			&& (islower(dest_piece) || GAME_EMPTY_ENTRY == dest_piece)) {
	} else if (islower(source_piece)
			&& (isupper(dest_piece) || GAME_EMPTY_ENTRY == dest_piece)) {
	} else {
		return false;
	}
	return true;
}

void learnGameBoardAndFillPieces(Game* src) {
	int i = 0, j = 0;
	char current_pos = GAME_EMPTY_ENTRY;

	// Clear pieces array
	for (i = 0; i < NUM_PIECES; i++) {
		src->whitePieces[i] = 0;
		src->blackPieces[i] = 0;
	}

	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			current_pos = src->gameBoard[i][j];
			if (current_pos != GAME_EMPTY_ENTRY) {
				// Set white & black pieces
				if (islower(current_pos)) {
					src->whitePieces[TransCharToPiece(current_pos)]++;
					if (current_pos == WHITE_KING) {
						// Set white king location
						src->whiteKingLocation[0] = i;
						src->whiteKingLocation[1] = j;
					}
				} else {
					src->blackPieces[TransCharToPiece(current_pos)]++;
					if (current_pos == BLACK_KING) {
						// Set white king location
						src->blackKingLocation[0] = i;
						src->blackKingLocation[1] = j;
					}
				}
			}
		}
	}
}

/*
 * MiniMaxAlgorithm.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */
#include <unistd.h>
#include "MiniMaxAlgorithm.h"

int memAllocFail = 0;

int minimaxSuggestMove(Game* currentGame, unsigned int maxDepth, int* i, int* j,
		int* k, int* l) {
	if (NULL == currentGame || maxDepth <= 0) {
		return -1;
	}
	// if MiniMax failed in memory allocation- return MEM_ALLOC_ERROR
	return miniMaxAlgorithm(currentGame, maxDepth, i, j, k, l);
}

int miniMaxAlgorithm(Game* currentGame, int depth, int* row_source,
		int* col_source, int* row_dest, int* col_dest) {
	int i = 0, j = 0, k = 0, value = 0, index = 0, alpha = INT_MIN, beta =
	INT_MAX;
	char currentPlayer = currentGame->currentPlayer;
	char current_position = GAME_EMPTY_ENTRY;
	int sizeOfGlobalResults = 0;

	// Hold the results in an array where every item is 5-tuple (i.e. array)
	// i,j - current location, k,l - goto position, v- value
	int** globalResults = (int**) calloc(sizeOfGlobalResults, sizeof(int*));

	// Scan the board, for each piece
	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			current_position = currentGame->gameBoard[i][j];
			if ((current_position != GAME_EMPTY_ENTRY)
					&& (LowerOrUpperReverse(currentGame, current_position))) {
				index = 0;
				value = 0;
				// current_position is a players piece, get moves of the piece
				int** movesArr = NULL;
				int tempMoves = getAllPossibleMoves(currentGame,
						current_position, i, j, &movesArr, true);
				// check tempMoves is not zero
				if (tempMoves > 0) {
					int* resultArray = (int*) calloc(tempMoves, sizeof(int));
					// For each move, call helper and get all values for all boards
					Game** rootChildren = (Game**) malloc(
							tempMoves * sizeof(Game*));
					// Allocation failure
					if (NULL == rootChildren) {
						memAllocFail = MEM_ALLOC_ERROR;
					}
					// Iterate over children
					for (k = 0; k < tempMoves && (alpha < beta); k++) {
						// Create a copy of the game
						rootChildren[k] = GameCopy(currentGame);
						if (NULL != rootChildren[k]) {		// If succeeded
							// No need to check return status, move is valid
							GameSetMove(rootChildren[k], i, j, movesArr[k][0],
									movesArr[k][1]);
							resultArray[k] = miniMaxHelper(rootChildren[k],
									depth, currentPlayer, true, alpha, beta);
							alpha = updateValue(resultArray[k], alpha, true);
							GameDestroy(rootChildren[k]);
						} else {
							memAllocFail = MEM_ALLOC_ERROR;
						}
					}
					// Find max index
					index = findIndexAndValue(resultArray, tempMoves, false,
							&value);
					// Save data needed for following calculations
					// Safe use for realloc
					int** tmpPtr = (int**) realloc(globalResults,
							(sizeOfGlobalResults + 1) * sizeof(int*));
					if (NULL == tmpPtr) {
						memAllocFail = MEM_ALLOC_ERROR;
					}
					globalResults = tmpPtr;
					tmpPtr = NULL;
					globalResults[sizeOfGlobalResults] = (int*) calloc(
					RESULT_ITEM_SIZE, sizeof(int));

					// Insert items
					// i,j location
					globalResults[sizeOfGlobalResults][0] = i;
					globalResults[sizeOfGlobalResults][1] = j;
					// destination
					globalResults[sizeOfGlobalResults][2] = movesArr[index][0];
					globalResults[sizeOfGlobalResults][3] = movesArr[index][1];
					// Insert value
					globalResults[sizeOfGlobalResults][4] = value;
					sizeOfGlobalResults++;

					// free resources
					if (NULL != rootChildren) {
						free(rootChildren);
						rootChildren = NULL;
					}
					if (NULL != resultArray) {
						free(resultArray);
						resultArray = NULL;
					}

					if (NULL != movesArr) {
						for (k = 0; k < tempMoves; k++) {
							if (NULL != movesArr[k]) {
								free(movesArr[k]);
								movesArr[k] = NULL;
							}
						}
						free(movesArr);
						movesArr = NULL;
					}

				}
			}
		}
	}
	// Clear index
	index = 0;
	// Get index of maximum result
	index = findGlobalMaxIndexAndValue(globalResults, sizeOfGlobalResults);
	// Load data to output
	*row_source = globalResults[index][0];
	*col_source = globalResults[index][1];
	*row_dest = globalResults[index][2];
	*col_dest = globalResults[index][3];

	// Free resources
	if (NULL != globalResults) {
		for (i = 0; i < sizeOfGlobalResults; i++) {
			if (NULL != globalResults[i]) {
				free(globalResults[i]);
				globalResults[i] = NULL;
			}
		}
		free(globalResults);
		globalResults = NULL;
	}

	// If allocation error occurred
	if (memAllocFail != 0) {
		return memAllocFail;
	}

	return index;

}

int miniMaxHelper(Game* currentGame, int depth, char currentPlayer,
bool minOrMax, int alpha, int beta) {
	assert(currentGame != NULL);
	int i = 0, j = 0, k = 0, gameScore = 0, newDepth = 0, possibleSteps = 0;
	char current_position = GAME_EMPTY_ENTRY;
	int sizeOfResultArray = 0, indexResultArry = 0;

	// Prepare results array
	int* resultArray = (int*) calloc(sizeOfResultArray, sizeof(int));

	newDepth = depth - 1;
	possibleSteps = getAllMoves(currentGame);
	if (newDepth == 0 || possibleSteps == 0) {
		gameScore = gameScoringFunc(currentGame, currentPlayer);
		// Free result array
		if (NULL != resultArray) {
			free(resultArray);
			resultArray = NULL;
		}
		return gameScore;
	}

	// Scan the board, for each piece
	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			current_position = currentGame->gameBoard[i][j];
			if ((current_position != GAME_EMPTY_ENTRY)
					&& (LowerOrUpperReverse(currentGame, current_position))) {
				// current_position is a players piece, get moves of the piece
				int** movesArr = NULL;
				int tempMoves = getAllPossibleMoves(currentGame,
						current_position, i, j, &movesArr, true);
				// check tempMoves is not empty
				if (tempMoves > 0) {
					sizeOfResultArray = sizeOfResultArray + tempMoves;
					// Safe use for realloc
					int* tmpPtr = (int*) realloc(resultArray,
							(sizeOfResultArray) * sizeof(int));
					if (NULL == tmpPtr) {

						memAllocFail = MEM_ALLOC_ERROR;
					}
					resultArray = tmpPtr;
					tmpPtr = NULL;
					// For each move, call helper and get all values for all boards
					Game** children = (Game**) malloc(
							tempMoves * sizeof(Game*));
					// Allocation failure
					if (NULL == children) {
						memAllocFail = MEM_ALLOC_ERROR;
					}
					// Iterate over children
					for (k = 0; k < tempMoves && (alpha < beta); k++) {
						// Create a copy of the game
						children[k] = GameCopy(currentGame);
						// If succeeded
						if (NULL != children[k]) {
							// No need to check return status, move is valid
							GameSetMove(children[k], i, j, movesArr[k][0],
									movesArr[k][1]);
							resultArray[indexResultArry] = miniMaxHelper(
									children[k], newDepth, currentPlayer,
									!minOrMax, alpha, beta);

							// Update alpha and beta
							if (!minOrMax) {
								alpha = updateValue(
										resultArray[indexResultArry], alpha,
										minOrMax);
							} else {
								beta = updateValue(resultArray[indexResultArry],
										beta, minOrMax);
							}
							// Promote index and destroy current children
							indexResultArry++;
							GameDestroy(children[k]);
						} else { // In case of memmory allocation error
							memAllocFail = MEM_ALLOC_ERROR;
						}
					}
					if (NULL != children) {
						free(children);
						children = NULL;
					}

				}
				// Free moves array
				if (NULL != movesArr) {
					for (k = 0; k < tempMoves; k++) {
						if (NULL != movesArr[k]) {
							free(movesArr[k]);
							movesArr[k] = NULL;
						}
					}
					free(movesArr);
					movesArr = NULL;
				}
			}
		}
	}

	// Free resources
	if (NULL != resultArray) {
		free(resultArray);
		resultArray = NULL;
	}

	// If some memory allocation has occurred, return an error code
	if (memAllocFail != 0) {
		return memAllocFail;
	}

	// Return alpha or beta to caller
	if (!minOrMax) {
		return alpha;
	}
	return beta;
}

int gameScoringFunc(Game* currentGame, char currentPlayer) {
	// Scoring vector: pawn = 1 , knight = 3 , bishop = 3 , rook = 5, queen = 9, king=100
	int i = 0, j = 0, scoreBoard = 0;
	char current_char = GAME_EMPTY_ENTRY;

	//Check for winner
	CHECK_MODE isWinnerBoard = getGameStatus(currentGame);
	// winner is found
	if (isWinnerBoard == MATE) {
		if (GameGetCurrentPlayer(currentGame) != currentPlayer) {
			return INT_MAX;
		} else {
			return INT_MIN;
		}
	}

	for (i = 0; i < GAME_N_ROWS; i++) {
		for (j = 0; j < GAME_N_COLUMNS; j++) {
			current_char = currentGame->gameBoard[i][j];
			if (current_char != GAME_EMPTY_ENTRY) {
				// Current player is white
				if (currentPlayer == GAME_PLAYER_1_SYMBOL) {
					// Positive piece
					if (islower(current_char)) {
						scoreBoard = scoreBoard
								+ getScoreForPiece(
										TransCharToPiece(current_char));
					} else {
						scoreBoard = scoreBoard
								- getScoreForPiece(
										TransCharToPiece(current_char));
					}
				}
				// Current player is black
				else {
					if (isupper(current_char)) {
						scoreBoard = scoreBoard
								+ getScoreForPiece(
										TransCharToPiece(current_char));
					} else {
						scoreBoard = scoreBoard
								- getScoreForPiece(
										TransCharToPiece(current_char));
					}
				}
			}
		}
	}
	return scoreBoard;
}


int getScoreForPiece(ChessPiece piece) {
	switch (piece) {
	case PAWN:
		return 1;
	case KNIGHT:
		return 3;
	case BISHOP:
		return 3;
	case ROOK:
		return 5;
	case QUEEN:
		return 9;
	case KING:
		return 100;
	case NONE:
		return 0;
	}
	return 0;
}

int findGlobalMaxIndexAndValue(int** globalResults, int sizeOfGlobalResults) {
	int i = 0, tValue = 0, tIndex = 0, flag = 0;

	for (i = 0; i < sizeOfGlobalResults; i++) {
		if (flag == 0) {
			tValue = globalResults[i][GLOBAL_RESULT_VALUE];
			tIndex = i;
			flag = 1;
		} else {
			if (globalResults[i][GLOBAL_RESULT_VALUE] > tValue) {
				tValue = globalResults[i][GLOBAL_RESULT_VALUE];
				tIndex = i;
			}
		}
	}
	return tIndex;
}

int findIndexAndValue(int* resultArray, int sizeOfResultArray, bool minOrMax,
		int* value) {
	assert(resultArray != NULL);
	int i = 0, tValue = 0, tIndex = 0, flag = 0;

	for (i = 0; i < sizeOfResultArray; i++) {
		if (flag == 0) {
			tValue = resultArray[i];
			tIndex = i;
			flag = 1;
			continue;
		} else {
			// Check min or max
			// Case min
			if (minOrMax == true) {
				if (resultArray[i] < tValue) {
					tValue = resultArray[i];
					tIndex = i;
				}
				// Case max
			} else {
				if (resultArray[i] > tValue) {
					tValue = resultArray[i];
					tIndex = i;
				}
			}
		}
	}
	// Set value and return index
	*value = tValue;
	return tIndex;
}

int updateValue(int gameValue, int value, bool minOrMax) {
	if (!minOrMax) {
		return MAX(gameValue, value);
	} else {
		return MIN(gameValue, value);
	}
}

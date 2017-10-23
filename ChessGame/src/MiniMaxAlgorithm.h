/*
 * MiniMaxAlgorithm.h
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#ifndef MINIMAXALGORITHM_H_
#define MINIMAXALGORITHM_H_
#include <assert.h>
#include "Game.h"

#define GLOBAL_RESULT_VALUE 4
#define RESULT_ITEM_SIZE 5
#define MEM_ALLOC_ERROR -2

/**
 * Return index and value
 * @param int* resultArray
 * @param int sizeOfResultArray
 * @param bool minOrMax
 * @return index
 */
int findIndexAndValue(int* resultArray, int sizeOfResultArray, bool minOrMax,
		int* value);

/** Return the index of the maximum value in global results
 * @param int** globalResults array input
 * @param int sizeOfGlobalResults size of such array
 * @return max
 */
int findGlobalMaxIndexAndValue(int** globalResults, int sizeOfGlobalResults);

/** Helper function to run mini-max algorithm for depth greater than 1
 * @param Game* currentGame
 * @param int depth
 * @param char currentPlayer
 * @return int
 */
int miniMaxHelper(Game* currentGame, int depth, char currentPlayer,
bool minOrMax, int alpha, int beta);

/** Initializer of the mini-max algorithm runs over the first depth nodes
 * @param Game* currentGame
 * @param int depth
 * @param  int i j k l:
 * i, j- source piece
 * k, l - destination of such piece
 * @return int - return a specific value if an error occurred
 */
int miniMaxAlgorithm(Game* currentGame, int depth, int* i, int* j, int* k,
		int* l);

 /** Function to be used by external entities
  * @param Game* currentGame
  * @param int maxdepth
  * @param  int i j k l:
  * i, j- source piece
  * k, l - destination of such piece
  * @return int
  */
int minimaxSuggestMove(Game* currentGame, unsigned int maxDepth, int* i, int* j,
		int* k, int* l);

/** Calculates the score of the game by given board and current player
 * If there is a winner, function returns INT_MIN or INT_MAX with regards to current player
 * o.w functions calculates the board value by a defined vector value for each piece type
 * @param Game* currentGame
 * @param char currentPlayer
 * @return int game score calculated
 * */
int gameScoringFunc(Game* currentGame, char currentPlayer);

/** Transfomation function for piece -> pre defined value for such piece
 * @param Game* currentGame
 * @param char currentPlayer
 * @return int piece value
 * */
int getScoreForPiece(ChessPiece piece);

/**
 * Update alpha/beta with regards to minOrMax value
 * @param gameValue: current board value
 * @param value: alpha or beta
 * @param minOrMax: bool value to decide to update alpha or beta
 * @return
 */
int updateValue(int gameValue, int value, bool minOrMax);

#endif /* MINIMAXALGORITHM_H_ */

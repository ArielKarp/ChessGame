#ifndef CONSOLEMODE_H_
#define CONSOLEMODE_H_
#include <stdbool.h>
#include <stdio.h>
#include "Parser.h"
#include "XMLParser.h"


#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 4
#define FROM_TO_CORD 4


/**
 * initialize console mode
 * @return
 * int
 */
int ConsoleMode();

//put auxiliary functions and constants used by the main function here.

/**
 * check if the input number is a valid int between 1 to 4
 * @param num
 * @return
 * true if valid otherwise false
 */
int checkValidInputNum(int num);

/**
 *take the game back 2 steps before by undo from the history game and print the steps
 * @param game
 * @return
 * 1 if succeeded 0 otherwise
 */
int undoMove(Game* game);

/**
 * function for changing the settings state
 * @return
 *
 */
void settingsState(Game* game);

/**
 * make move for the computer
 * @return
 *
 */
void computerMakeMove(Game* game, char* winner);

/**
 *while loop for the running game of the user vs the computer, until there is a winner
 * @param game
 * @return
 * winner result is returned
 */
char gamePlay(Game* game);

/**
 *check whi is the winner and return it to the main
 * @param game
 * @return
 * the winner is returned
 */
char gameProgress(Game* game);

/**
 *prints the exception error and exit the game
 * @param functionType
 */
void exceptionPrintAndExit(int functionType);

/**
 * Add disc to game board
 * @param game
 * @param command
 * @return 0 if some error occured, o/w 1.
 */
int addDisc(Game* game, Command command);

/**
 * Check if after gameProgress an error occurred, if so then exit gracefully using exceptionPrintAndExit
 * @param game
 * @param errorCode
 */
void checkIfGameProgressReturnedError(Game* game, char errorCode);

/**
 * Check if fgets function failed, if so exit gracefully using exceptionPrintAndExit
 * @param game
 * @param errorCode
 */
void checkIfFgetsFailed(Game* game, char* returnFgets);

/**
 * Check if creation of game returned null, if so exit gracefully using exceptionPrintAndExit
 * @param game
 */
void checkIfGameCrateFailed(Game* game);

/**
 * Reset the game
 * @param game
 * @return
 */
char restartGame(Game* game);

/**
 * change the game to default settings game
 * @param game
 * @return
 */
void defaultSettingsGame(Game* game);

/**
 * print settings game
 * @param game
 * @return
 */
void printSettingsGame(Game* game);

/**
 * convert from char type to USER_COLORs
 * @param char
 * @return
 * USER_COLOR
 */
USER_COLOR getUserColorOfColor(char currentPlayer);

/**
 * convert from char type to string
 * @param char
 * @return
 * string of color
 */
char* getStringOfColor(char currentPlayer);

/**
 * convert from char type to opposite string player
 * @param char
 * @return
 * string of opposite color
 */
char* getOppositeStringOfColor(char currentPlayer);

/**
 * convert from char type to string player
 * @param char
 * @return
 * string of current player
 */
const char * getStringCurrentPlayer(char c);


/**
 * convert from char type to string player
 * @param char
 * @return
 * string of opposite current player
 */
const char * getOppositeStringCurrentPlayer(char c);

/**
 * convert char to int
 * @param char
 * @return
 * int
 */
int convertCharToInt(char c);

/**
 * convert int to char
 * @param int
 * @return
 * char
 */
char convertIntToChar(int i);

/**
 * get opposite current player
 * @param USER_COLOR
 * @return
 * char
 */
char getOppositeCurrentPlayer(USER_COLOR userColor);

#endif

#ifndef PARSER_H_
#define PARSER_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//specify the maximum line length
#define MAX_LINE_LENGTH 1024
#define ZERO_IN_ASCII 48
#define NINE_IN_ASCII 57
#define SMALLER_IN_ASCII 60
#define BIGGER_IN_ASCII 62
#define LEN_FOR_MOVE 5
#define A_IN_ASCII 65
#define H_IN_ASCII 72
#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 4
#define DEFAULT_DIFF 2
#define DEFAULT_USER_COLOR 1
#define DEFAULT_GAME_MODE 1



//a type used to represent a command
typedef enum {
	SETTINGS_GAME_MODE=0,
	SETTINGS_DIFFICULTY,
	SETTINGS_USER_COLOR,
	SETTINGS_LOAD,
	SETTINGS_DEFAULT,
	SETTINGS_PRINT_SETTING,
	SETTINGS_START,

	USER_MOVE,
	USER_GET_MOVES,//BONUS
	USER_SAVE,
	USER_UNDO,
	USER_RESET,

	QUIT,
	INVALID_LINE,
	EXCEPTION,
} COMMAND;

typedef enum {
	VALID,
	INVALID,
	EXPERT_NOT_SUPPORTED,//BONUS
	INVALID_POSITION,
	INVALID_FORMAT,
	FILE_CANNOT_MODIFIED,
} VALIDATION;


//a new type that is used to encapsulate a parsed line
typedef struct command_t {
	COMMAND cmd;
	VALIDATION lineStatus;

	int gameMode;
	int difficulty;
	int userColor;
	char str[MAX_LINE_LENGTH];
	int xSource;
	char ySource;
	int iDest;
	char jDest;
	const char* sourceCord;
	char sourceCordChar;



} Command;

/**
 * Checks if move string is valid
 *
 * @return
 * VALIDATION type
 */
VALIDATION CheckMoveString(char* str);

/**
 * Checks if a specified string represents a valid integer between 1-8. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool ParserIsValidInt(const char* c);

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */
Command ParserPraseLine(const char* str);

/**
 * Free str if not NULL
 * @param str input string
 */
void clearStrInput(char* str);

#endif

/*
 * main.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */

#include "Parser.h"

bool ParserIsValidInt(const char* c) {

	if (c[0] < ZERO_IN_ASCII || c[0] > NINE_IN_ASCII) {
		return false;
	}

	return true;

}

VALIDATION CheckMoveString(char* str) {
	char tempstr[MAX_LINE_LENGTH];
	strncpy(tempstr,str,MAX_LINE_LENGTH);
	int i = 1;

	if (tempstr[0] != '<') {
		return INVALID;
	}
	// Check for braces
	while (tempstr[i] != ',') {
		if (tempstr[i] == '\0' || i >= MAX_LINE_LENGTH) {
			return INVALID;
		}
		i++;
	}

	while (tempstr[i] != '>' || i >= MAX_LINE_LENGTH) {
		if (tempstr[i] == '\0') {
			return INVALID;
		}
		i++;
	}

	if (tempstr[i + 1] != '\0') {
		return INVALID;
	}

	return VALID;
}

//Parses a specified line.
Command ParserPraseLine(const char* str) {
	Command returnCmd;
	returnCmd.gameMode = DEFAULT_GAME_MODE;
	returnCmd.difficulty = DEFAULT_DIFF;
	returnCmd.userColor = DEFAULT_USER_COLOR;
	returnCmd.cmd = INVALID_LINE;
	returnCmd.lineStatus = INVALID;
	char* sourceCord;
	int temp = 0;
	char sourceCordChar;
	int i = 0;
	char* copyStr = (char*) malloc((strlen(str) + 1) * sizeof(char));
	// Catch failure in malloc
	if (NULL == copyStr) {
		returnCmd.cmd = EXCEPTION;
		return returnCmd;
	}

	// copy str to copyStr
	strcpy(copyStr, str);
	const char delim[8] = " \t\r\n";
	char* cmdStr = NULL;
	cmdStr = strtok(copyStr, delim);
	// Check type of command and return with returnCommand
	if (NULL == cmdStr || strcmp(cmdStr, "\0") == 0) {
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is move
	else if (strcmp(cmdStr, "move") == 0) {
		unsigned int len = 0;
		returnCmd.cmd = USER_MOVE;

		//get the codrinates
		for (i = 0; i < 2; i++) {

			sourceCord = strtok(NULL, delim);
			if (i == 1) {
				sourceCord = strtok(NULL, delim);
			}
			if (NULL == sourceCord) {
				clearStrInput(copyStr);
				return returnCmd;
			}

			len = strlen(sourceCord);

			VALIDATION status = CheckMoveString(sourceCord);

			if (len != LEN_FOR_MOVE && status == VALID) {
				returnCmd.lineStatus = INVALID_POSITION;
				clearStrInput(copyStr);
				return returnCmd;
			}

			if ((len != LEN_FOR_MOVE) || (sourceCord[0] != SMALLER_IN_ASCII)
					|| (sourceCord[len - 1] != BIGGER_IN_ASCII)) {
				clearStrInput(copyStr);
				return returnCmd;
			}
			//check coordinates
			if ((ParserIsValidInt((char*) sourceCord + 1) == true)) {
				temp = atoi((char*) sourceCord + 1);
				if ((temp < 1) || (temp > 8)) {
					returnCmd.lineStatus = INVALID_POSITION;
					clearStrInput(copyStr);
					return returnCmd;
				} else {
					if (i == 0) {
						returnCmd.xSource = temp;
					}
					if (i == 1) {
						returnCmd.iDest = temp;
					}
				}

			}
			sourceCordChar = sourceCord[3];
			//check coordinates
			if ((sourceCordChar < A_IN_ASCII)
					|| (sourceCordChar > H_IN_ASCII)) {
				returnCmd.lineStatus = INVALID_POSITION;
				clearStrInput(copyStr);
				return returnCmd;
			} else {
				if (i == 0) {
					returnCmd.ySource = sourceCordChar;
				}
				if (i == 1) {
					returnCmd.jDest = sourceCordChar;
				}
			}

		}

		returnCmd.lineStatus = VALID;
		clearStrInput(copyStr);
		return returnCmd;

	}
	//command is save
	else if (strcmp(cmdStr, "save") == 0) {
		char* conStr = strtok(NULL, delim);

		FILE * fp = NULL;
		returnCmd.cmd = USER_SAVE;
		if (NULL != conStr) {
			strcpy(returnCmd.str, conStr);
			fp = fopen(returnCmd.str, "w");

		}

		else {
			clearStrInput(copyStr);
			return returnCmd;
		}

		if (NULL != fp) {
			returnCmd.lineStatus = VALID;
			fclose(fp);

		} else {
			returnCmd.lineStatus = FILE_CANNOT_MODIFIED;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	else if (strcmp(cmdStr, "undo") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = USER_UNDO;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is reset
	else if (strcmp(cmdStr, "reset") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = USER_RESET;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is game mode
	else if (strcmp(cmdStr, "game_mode") == 0) {
		returnCmd.cmd = SETTINGS_GAME_MODE;
		char* numStr = strtok(NULL, delim);
		if (NULL != numStr) {
			if ((ParserIsValidInt(numStr) == true)) {
				temp = atoi(numStr);
				if ((temp == 1) || (temp == 2)) {
					returnCmd.lineStatus = VALID;
					returnCmd.gameMode = temp;
				} else {
					returnCmd.lineStatus = INVALID;	//for "Wrong game mode" error when the int number is wrong
				}
			} else {
				returnCmd.lineStatus = INVALID;	//for "Wrong game mode" error when the int number is wrong
			}
		}
		clearStrInput(copyStr);
		return returnCmd;

	}

	//command is difficulty
	else if (strcmp(cmdStr, "difficulty") == 0) {

		char* numStr = strtok(NULL, delim);
		if (NULL != numStr) {
			returnCmd.cmd = SETTINGS_DIFFICULTY;
			if ((ParserIsValidInt(numStr) == true)) {
				temp = atoi(numStr);
				if ((temp >= MIN_DIFFICULTY) && (temp <= MAX_DIFFICULTY)) {	// if we add bonus feature need to expand to 5
					returnCmd.lineStatus = VALID;
					returnCmd.difficulty = temp;
				} else if (temp == 5) {
					returnCmd.lineStatus = EXPERT_NOT_SUPPORTED;//for "expert level not supported" error when the int number is wrong
				} else {

					returnCmd.lineStatus = INVALID;	//for "level not supported" error when the int number is wrong
				}
			} else {
				returnCmd.lineStatus = INVALID;	//for "level not supported" error when the int number is wrong
			}
		}
		clearStrInput(copyStr);
		return returnCmd;

	}

	//command is user color
	else if (strcmp(cmdStr, "user_color") == 0) {

		char* numStr = strtok(NULL, delim);
		if (NULL != numStr) {
			returnCmd.cmd = SETTINGS_USER_COLOR;
			if ((ParserIsValidInt(numStr) == true)) {
				temp = atoi(numStr);
				if ((temp == 0) || (temp == 1)) {
					returnCmd.lineStatus = VALID;
					returnCmd.userColor = temp;
				}
			}
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is load
	else if (strcmp(cmdStr, "load") == 0) {

		char* conStr = strtok(NULL, delim);
		FILE * fp = NULL;
		returnCmd.cmd = SETTINGS_LOAD;

		if (NULL != conStr) {
			strcpy(returnCmd.str, conStr);

			fp = fopen(conStr, "r");
		}

		else {
			clearStrInput(copyStr);
			return returnCmd;
		}

		if (NULL != fp) {
			returnCmd.lineStatus = VALID;
			fclose(fp);

		} else {
			returnCmd.lineStatus = FILE_CANNOT_MODIFIED;
		}

		clearStrInput(copyStr);

		return returnCmd;
	}

	//command is default
	else if (strcmp(cmdStr, "default") == 0) {

		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SETTINGS_DEFAULT;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is print setting
	else if (strcmp(cmdStr, "print_setting") == 0) {

		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SETTINGS_PRINT_SETTING;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is start
	else if (strcmp(cmdStr, "start") == 0) {

		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = SETTINGS_START;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	//command is quit
	else if (strcmp(cmdStr, "quit") == 0) {
		char* conStr = strtok(NULL, delim);
		if (NULL == conStr) {
			returnCmd.cmd = QUIT;
		}
		clearStrInput(copyStr);
		return returnCmd;
	}

	else {
		clearStrInput(copyStr);
		return returnCmd;
	}

	clearStrInput(copyStr);
	return returnCmd;
}

//Free str if not NULL
void clearStrInput(char* str) {
// Free str if not null
	if (NULL != str) {
		free(str);
		str = NULL;
	}
	return;
}

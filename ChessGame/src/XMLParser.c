/*
 * XMLParser.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "XMLParser.h"

XML_MESSAGE SaveGameToXMLFile(char* path, Game* src) {
	if (NULL == src || NULL == path) {
		return XML_ERROR_WRITE_FAIL;
	}
	char tempLine[MAX_LINE_LENGTH];
	int flagMode = 0;
	char tempStr [MAX_LINE_LENGTH];
	char tempNum [ROW_NUMBER];
	char tempRow [GAME_N_COLUMNS + 1];
	int row = GAME_N_ROWS - 1;

	// Open the file
	FILE* fptr = fopen(path, "w");

	if (NULL == fptr) {
		return XML_OPEN_FILE_FAIL;
	}

	// Write header
	tempLine[0] = '\0';
	strcpy(tempLine, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fputs(tempLine, fptr);

	// Write game tag
	tempLine[0] = '\0';
	strcpy(tempLine, "<game>\n");
	fputs(tempLine, fptr);

	tempLine[0] = '\0';
	strcpy(tempLine, "\t<current_turn>");
	if (src->currentPlayer == GAME_PLAYER_1_SYMBOL) {
		strcat(tempLine, "1");
	} else {
		strcat(tempLine, "0");
	}
	strcat(tempLine, "</current_turn>\n");
	fputs(tempLine, fptr);

	tempLine[0] = '\0';
	strcpy(tempLine, "\t<game_mode>");
	if (src->gameMode == ONE_PLAYER_MODE) {
		strcat(tempLine, "1");
		flagMode = 0;
	}
	else {
		strcat(tempLine, "2");
		flagMode = 1;
	}
	strcat(tempLine, "</game_mode>\n");
	fputs(tempLine, fptr);

	tempLine[0] = '\0';
	// if 2 player mode
	if (flagMode == TWO_PLAYER_MODE) {
		strcpy(tempLine, "\t<difficulty></difficulty>\n");
		strcat(tempLine, "\t<user_color></user_color>\n");
	} else {
		strcpy(tempLine, "\t<difficulty>");
		sprintf(tempNum, "%d", src->difficulty);
		strcat(tempLine, tempNum);
		strcat(tempLine, "</difficulty>\n");
		strcat(tempLine, "\t<user_color>");
		sprintf(tempNum, "%d", src->userColor);
		strcat(tempLine, tempNum);
		strcat(tempLine, "</user_color>\n");
	}

	fputs(tempLine, fptr);

	// Write board
	tempLine[0] = '\0';
	strcpy(tempLine, "\t<board>\n");
	for(; row >= 0; row--) {
		tempStr[0] = '\0';
		tempRow[0] = '\0';
		strcpy(tempStr, "\t\t<row_");
		sprintf(tempNum, "%d", (row+1));
		strcat(tempStr, tempNum);
		strcat(tempStr, ">");
		strncpy(tempRow, src->gameBoard[row], 8);
		tempRow[GAME_N_COLUMNS] = '\0';
		strcat(tempStr, tempRow);
		strcat(tempStr, "</row_");
		strcat(tempStr, tempNum);
		strcat(tempStr, ">\n");

		strcat(tempLine, tempStr);
	}
	fputs(tempLine, fptr);


	tempLine[0] = '\0';
	strcpy(tempLine, "\t</board>\n");
	fputs(tempLine, fptr);

	tempLine[0] = '\0';
	strcpy(tempLine, "\t<general>\n");
	fputs(tempLine, fptr);

	// Write white pieces
	tempLine[0] = '\0';
	sprintf(tempLine, "\t\t<white_pieces>%d,%d,%d,%d,%d,%d</white_pieces>\n", src->whitePieces[0], src->whitePieces[1], src->whitePieces[2], src->whitePieces[3], src->whitePieces[4], src->whitePieces[5]);
	fputs(tempLine, fptr);

	// Write black pieces
	tempLine[0] = '\0';
	sprintf(tempLine, "\t\t<black_pieces>%d,%d,%d,%d,%d,%d</black_pieces>\n", src->blackPieces[0], src->blackPieces[1], src->blackPieces[2], src->blackPieces[3], src->blackPieces[4], src->blackPieces[5]);
	fputs(tempLine, fptr);

	// Write white king location
	tempLine[0] = '\0';
	sprintf(tempLine, "\t\t<white_king>%d,%d</white_king>\n", src->whiteKingLocation[0], src->whiteKingLocation[1]);
	fputs(tempLine, fptr);

	// Write black king location
	tempLine[0] = '\0';
	sprintf(tempLine, "\t\t<black_king>%d,%d</black_king>\n", src->blackKingLocation[0], src->blackKingLocation[1]);
	fputs(tempLine, fptr);

	// End general section
	tempLine[0] = '\0';
	strcpy(tempLine, "\t</general>\n");

	// Write the end of the file
	strcat(tempLine, "</game>");
	fputs(tempLine, fptr);

	// Check for errors
	if (ferror(fptr) != 0) {
		return 	XML_ERROR_WRITE_FAIL;
	}

	// Write game board
	if (fclose(fptr) != 0) {
		return XML_CLOSE_FILE_FAIL;
	}

	return XML_PASS;
}

XML_MESSAGE LoadGameFromXML(char* path, Game* src) {
	if (NULL == src || NULL == path) {
		return XML_ERROR_READ_FAIL;
	}
	char tempLine[MAX_LINE_LENGTH];
	const char delimSpace[8] = " \t\r\n";
	char* clearedLine = NULL;
	int generalExists = 0;


	// if the file is missing
	if (access(path, F_OK ) == -1 ) {
	    // file does not exists
		return XML_PATH_FAIL;
	}

	// Open the file
	FILE* fptr = fopen(path, "r");

	if (NULL == fptr) {
		return XML_OPEN_FILE_FAIL;
	}

	// Parsing line by line
	while (fgets(tempLine, MAX_LINE_LENGTH, fptr)) {
		clearedLine = strtok(tempLine, delimSpace);
		if (NULL != clearedLine) {
			FillGameWithData(clearedLine, src, &generalExists);
		}
	}

	// Check if general exists
	if (generalExists == 0) {
		// No general in input file, learn the board and fill accordingly
		learnGameBoardAndFillPieces(src);
	}

	// Check for errors
	if (ferror(fptr) != 0) {
		return 	XML_ERROR_WRITE_FAIL;
	}

	// Write game board
	if (fclose(fptr) != 0) {
		return XML_CLOSE_FILE_FAIL;
	}

	return XML_PASS;

}


void FillGameWithData(char* clearedLine, Game* src, int* generalExists) {
	const char delimBraces[3] = "<>";
	const char delimCommas[2] = ",";
	char* tempLine = NULL;
	char* dataLine = NULL;
	char* parsedDataLine = NULL;
	int tempNum = 0;
	int i = 0;

	tempLine = strtok(clearedLine, delimBraces);

	// testing for the content of the tag
	if (strstr(tempLine, "current_turn") != NULL){
		dataLine = strtok(NULL, delimBraces);
		tempNum = dataLine[0] - 48;
		if (tempNum == 0) {
			src->currentPlayer = GAME_PLAYER_2_SYMBOL;
		} else {
			src->currentPlayer = GAME_PLAYER_1_SYMBOL;
		}
		return;
	}

	if (strstr(tempLine, "game_mode") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		tempNum = dataLine[0] - 48;
		if (tempNum == 1) {
			src->gameMode = ONE_PLAYER_MODE;
		} else {
			src->gameMode = TWO_PLAYER_MODE;
		}
		return;
	}
	if (strstr(tempLine, "difficulty") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		// No difficulty (2 players)
		if (dataLine[0] == '/') {
			src->difficulty = 0;
		}
		tempNum = dataLine[0] - 48;
		if (tempNum == 1) {
			src->difficulty = tempNum;
		} else {
			src->difficulty = tempNum;
		}
		return;
	}

	if (strstr(tempLine, "user_color") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		// No user color (2 players)
		if (dataLine[0] == '/') {
			src->userColor = NO_COLOR;
		}
		tempNum = dataLine[0] - 48;
		if (tempNum == 0) {
			src->userColor = BLACK;
		} else {
			src->userColor = WHITE;
		}
		return;
	}

	// Parse to see check for row
	if (strstr(tempLine, "row") != NULL) {
		// Get row number
		tempNum = tempLine[strlen(tempLine) - 1] - 48 - 1;
		dataLine = strtok(NULL, delimBraces);
		for (i = 0; i < GAME_N_COLUMNS; i++) {
			src->gameBoard[tempNum][i] = dataLine[i];
		}
		return;
	}

	if (strstr(tempLine, "general") != NULL) {
		*generalExists = 1;
		return;
	}

	if (strstr(tempLine, "white_pieces") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		parsedDataLine = strtok(dataLine, delimCommas);
		while (NULL != parsedDataLine) {
			src->whitePieces[i] = atoi(parsedDataLine);
			i++;
			parsedDataLine = strtok(NULL, delimCommas);
		}
		return;
	}

	if (strstr(tempLine, "black_pieces") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		parsedDataLine = strtok(dataLine, delimCommas);
		while (NULL != parsedDataLine) {
			src->blackPieces[i] = atoi(parsedDataLine);
			i++;
			parsedDataLine = strtok(NULL, delimCommas);
		}
		return;
	}

	if (strstr(tempLine, "white_king") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		parsedDataLine = strtok(dataLine, delimCommas);
		while (NULL != parsedDataLine) {
			src->whiteKingLocation[i] = atoi(parsedDataLine);
			i++;
			parsedDataLine = strtok(NULL, delimCommas);
		}
		return;
	}
	if (strstr(tempLine, "black_king") != NULL) {
		dataLine = strtok(NULL, delimBraces);
		parsedDataLine = strtok(dataLine, delimCommas);
		while (NULL != parsedDataLine) {
			src->blackKingLocation[i] = atoi(parsedDataLine);
			i++;
			parsedDataLine = strtok(NULL, delimCommas);
		}
		return;
	}
	return;
}

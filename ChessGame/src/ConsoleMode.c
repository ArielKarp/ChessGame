/*
 * ConsoleMode.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 */
#include "ConsoleMode.h"

int ConsoleMode() {
	//create Command and Game
	Command command;
	Game* game = GameCreate(HISTORY_SIZE);
	//exception catch in fgets
	checkIfGameCrateFailed(game);
	//init variables
	char str[MAX_LINE_LENGTH] = "0";
	char winner = '\0';

	settingsState(game);
	winner = gameProgress(game);
	if (winner == 'f') {
		GameDestroy(game);
		exit(EXIT_SUCCESS);
	}
	// Check for memory allocation errors
	checkIfGameProgressReturnedError(game, winner);

	//restart game
	while (winner == 'r') {
		GameDestroy(game);
		game = GameCreate(HISTORY_SIZE);
		winner = restartGame(game);
		// Commence 'Quit' if requested
		if (winner == 'f') {
			GameDestroy(game);
			exit(EXIT_SUCCESS);
		}
	}
	//while loop game
	while (true) {
		//get input from the user
		char* input = fgets(str, MAX_LINE_LENGTH, stdin);
		//exception catch in fgets

		checkIfFgetsFailed(game, input);
		command = ParserPraseLine(str);

		//exception command
		if (command.cmd == EXCEPTION) {
			GameDestroy(game);
			exceptionPrintAndExit(-2);
			return -2;
		}
		//quit the game
		if (command.cmd == QUIT) {
			printf("Exiting...\n");
			GameDestroy(game);
			exit(EXIT_SUCCESS);
		}
		//restart the game
		if (command.cmd == USER_RESET) {
			printf("Restarting...\n");
			GameDestroy(game);
			game = GameCreate(HISTORY_SIZE);
			restartGame(game);
			continue;
		}

		//user input is undo move command
		else if (command.cmd == USER_UNDO) {
			if (winner == GAME_PLAYER_2_SYMBOL) {
				undoMove(game);
				winner = gameProgress(game);
				checkIfGameProgressReturnedError(game, winner);
			} else {
				perror_command("the game is over");
			}
		} else if (command.cmd == USER_MOVE) {
			perror_command("the game is over");
		} else if (command.cmd == INVALID_LINE) {
			perror_command("invalid command");

		} else if (command.cmd == USER_SAVE) {
			perror_command("invalid command");

		} else {
			perror_command("invalid command");

		}
	}
}

//check if the input is valid between 1 to 4
int checkValidInputNum(int num) {
	if (num < MIN_DIFFICULTY || num > MAX_DIFFICULTY) {
		return false;
	}
	return true;
}

//execute undo move function
int undoMove(Game* game) {

	if (game->gameMode == ONE_PLAYER_MODE) {
		GAME_MESSAGE undo1;
		GAME_MESSAGE undo2;
		DataMember* undo1Member;
		DataMember* undo2Member;
		int undo1Nums[FROM_TO_CORD];
		int undo2Nums[FROM_TO_CORD];

		//get last element from array list and make undo
		undo1Member = ArrayListGetLast(game->historyMoves);

		if (NULL == undo1Member) {
			printf("Empty history, move cannot be undone\n");
			return 0;
		}

		//Coordinates for undo move
		undo1Nums[0] = undo1Member->i;
		undo1Nums[1] = undo1Member->j;
		undo1Nums[2] = undo1Member->k;
		undo1Nums[3] = undo1Member->l;

		undo1 = GameUndoPrevMove(game);
		if (undo1 == GAME_NO_HISTORY) {
			printf("Empty history, move cannot be undone\n");
			return 0;
		}
		if (undo1 == GAME_INVALID_ARGUMENT || undo1 == GAME_INVALID_MOVE) {
			perror_command("invalid command");

			return 0;
		}

		//get last element from array list and make undo
		undo2Member = ArrayListGetLast(game->historyMoves);

		if (NULL == undo2Member) {
			printf("Empty history, move cannot be undone\n");
			return 0;
		}

		//Coordinates for undo move
		undo2Nums[0] = undo2Member->i;
		undo2Nums[1] = undo2Member->j;
		undo2Nums[2] = undo2Member->k;
		undo2Nums[3] = undo2Member->l;
		undo2 = GameUndoPrevMove(game);
		if (undo2 == GAME_NO_HISTORY) {
			printf("Empty history, move cannot be undone\n");
			return 0;
		}
		if (undo2 == GAME_INVALID_ARGUMENT || undo1 == GAME_INVALID_MOVE) {
			perror_command("invalid command");

			return 0;
		}

		//prints the undo moves
		printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
				getOppositeStringOfColor(game->currentPlayer), undo1Nums[2] + 1,
				convertIntToChar(undo1Nums[3] + 1), undo1Nums[0] + 1,
				convertIntToChar(undo1Nums[1] + 1));
		printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",
				getStringOfColor(game->currentPlayer), undo2Nums[2] + 1,
				convertIntToChar(undo2Nums[3] + 1), undo2Nums[0] + 1,
				convertIntToChar(undo2Nums[1] + 1));
		return 1;

	} else {
		printf("Undo command not available in 2 players mode\n");
	}
	return 0;

}

void settingsState(Game* game) {
	Command command;
	char str[MAX_LINE_LENGTH] = "0";
	XML_MESSAGE xmlMessage;
	defaultSettingsGame(game);

	printf(
			"Specify game setting or type 'start' to begin a game with the current setting:\n");
	do {

		char* input = fgets(str, MAX_LINE_LENGTH, stdin);
		//exception catch in fgets
		if (NULL == input) {
			GameDestroy(game);
			exceptionPrintAndExit(-3);
			return;
		}

		//parse the command
		command = ParserPraseLine(str);

		//exception catch in malloc
		if (command.cmd == EXCEPTION) {
			GameDestroy(game);
			exceptionPrintAndExit(-2);
			return;
		} else if (command.cmd == QUIT) {
			printf("Exiting...\n");
			GameDestroy(game);
			exit(EXIT_SUCCESS);
		}

		//get into the requested command in order to change its setting
		else if (command.cmd == SETTINGS_GAME_MODE) {
			if (command.lineStatus == INVALID) {
				printf("Wrong game mode\n");
			} else if (command.gameMode == ONE_PLAYER_MODE + 1) {
				game->gameMode = ONE_PLAYER_MODE;
				printf("Game mode is set to 1 player\n");
			} else if (command.gameMode == TWO_PLAYER_MODE + 1) {
				game->gameMode = TWO_PLAYER_MODE;
				printf("Game mode is set to 2 players\n");
			}
		}

		else if (command.cmd == SETTINGS_DIFFICULTY) {

			if (game->gameMode == TWO_PLAYER_MODE) {
				perror_command("invalid command");

			} else if (command.lineStatus == INVALID) {
				printf(
						"Wrong difficulty level. The value should be between 1 to 5\n");

			} else if (command.lineStatus == EXPERT_NOT_SUPPORTED) {
				game->gameMode = ONE_PLAYER_MODE;
				printf(
						"Expert level not supported, please choose a value between 1 to 4:\n");

			} else if (command.lineStatus == VALID) {
				game->difficulty = command.difficulty;
			}
		}

		else if (command.cmd == SETTINGS_USER_COLOR) {
			if (game->gameMode == TWO_PLAYER_MODE) {
				perror_command("invalid command");

			} else if (command.lineStatus == VALID) {

				game->userColor = command.userColor;
			}
		} else if (command.cmd == SETTINGS_LOAD) {
			if ((command.lineStatus == INVALID)
					|| (command.lineStatus == FILE_CANNOT_MODIFIED)) {
				printf("Error: File doesn't exist or cannot be opened\n");
			} else if (command.lineStatus == VALID) {
				xmlMessage = LoadGameFromXML(command.str, game);

				//xml errors
				if ((xmlMessage == XML_PATH_FAIL)
						|| (xmlMessage == XML_OPEN_FILE_FAIL)
						|| (xmlMessage == XML_CLOSE_FILE_FAIL)
						|| (xmlMessage == XML_ERROR_READ_FAIL)) {
					printf("Error: File doesn't exist or cannot be opened\n");
				}

			}
		}

		else if (command.cmd == SETTINGS_DEFAULT) {
			defaultSettingsGame(game);
		}

		else if (command.cmd == SETTINGS_PRINT_SETTING) {
			printSettingsGame(game);
		}

		//to start the game
		else if (command.cmd == SETTINGS_START) {
			break;
		}

		else {
			perror_command("invalid command");

		}
	} while ((command.cmd != QUIT) || (command.cmd != SETTINGS_START));

	return;
}

//while loop for the user vs computer game or vs another player
char gamePlay(Game* game) {
	Command command;
	char str[MAX_LINE_LENGTH] = "0";
	char winner = '\0';
	int valid = 1;
	CHECK_MODE mode;
	XML_MESSAGE xmlSaveMessage;
	if ((valid == 1) && (game->gameMode == ONE_PLAYER_MODE)) {
		if (game->userColor != getUserColorOfColor(game->currentPlayer)) {

			// otherwise
			computerMakeMove(game, &winner);
		}
	}

//while loop until there is no winner\tie\quit\error
	while (winner == '\0') {
		//prints the turn of the next player

		if ((valid == 1) && (game->gameMode == TWO_PLAYER_MODE)) {
			GamePrintBoard(game);
			printf("%s player - enter your move:\n",
					getStringOfColor(game->currentPlayer));
		} else if ((valid == 1) && (game->gameMode == ONE_PLAYER_MODE)) {

			GamePrintBoard(game);

			printf("%s player - enter your move:\n",
					getStringOfColor(game->currentPlayer));

		}

		else if (valid == 2) {

			printf("%s player - enter your move:\n",
					getStringOfColor(game->currentPlayer));

		}
		valid = 1;
		char* input = fgets(str, MAX_LINE_LENGTH, stdin);
		//exception catch in fgets
		if (NULL == input) {
			return 'e';
		}
		command = ParserPraseLine(str);
		if (command.cmd == INVALID_LINE) {
			valid = 0;
			perror_command("invalid command");

			continue;
		} else if (command.cmd == QUIT) {

			printf("Exiting...\n");
			return 'f';
		} else if (command.cmd == USER_RESET) {
			printf("Restarting...\n");
			return 'r';
		}

		else if (command.cmd == USER_SAVE) {

			if ((command.lineStatus == INVALID)
					|| (command.lineStatus == FILE_CANNOT_MODIFIED)) {
				printf("File cannot be created or modified\n");
				valid = 2;

			} else if (command.lineStatus == VALID) {

				xmlSaveMessage = SaveGameToXMLFile(command.str, game);
				valid = 2;

				//xml errors
				if ((xmlSaveMessage == XML_PATH_FAIL)
						|| (xmlSaveMessage == XML_OPEN_FILE_FAIL)
						|| (xmlSaveMessage == XML_CLOSE_FILE_FAIL)
						|| (xmlSaveMessage == XML_ERROR_WRITE_FAIL)) {
					printf("File cannot be created or modified\n");

				}
			}
			continue;
		}

		else if (command.cmd == USER_UNDO) {
			valid = undoMove(game);
			continue;
		}

		//user move:
		else if (command.cmd == USER_MOVE) {
			//this is the area when we decrease in 1 the numbers of the row and column in the board to start from zero
			if (command.lineStatus == INVALID_POSITION) {
				printf("Invalid position on the board\n");
				printf("%s player - enter your move:\n",
						getStringOfColor(game->currentPlayer));
				valid = 0;
				continue;
			} else if (command.lineStatus == VALID) {
				int addAnswer = GameIsValidMovement(game, command.xSource - 1,
						convertCharToInt(command.ySource) - 1,
						command.iDest - 1, convertCharToInt(command.jDest) - 1);

				//check if the player chose one of his piece
				if ((LowerOrUpper(game,
						game->gameBoard[command.xSource - 1][convertCharToInt(
								command.ySource) - 1]))
						|| ((game->gameBoard[command.xSource - 1][convertCharToInt(
								command.ySource) - 1]) == GAME_EMPTY_ENTRY)) {
					printf(
							"The specified position does not contain your piece\n");
					printf("%s player - enter your move:\n",
							getStringOfColor(game->currentPlayer));
					valid = 0;
					continue;
					//check if the king is compromised after the move or the move is not valid
					//-1 is because the array of indexes start from 0
				} else if ((IsKingCompromisedByMove(game, command.xSource - 1,
						convertCharToInt(command.ySource) - 1,
						command.iDest - 1, convertCharToInt(command.jDest) - 1))
						|| (addAnswer == false)) {
					printf("Illegal move\n");
					printf("%s player - enter your move:\n",
							getStringOfColor(game->currentPlayer));
					valid = 0;
					continue;
				} else if (addAnswer == true) {

					GameSetMove(game, command.xSource - 1,
							convertCharToInt(command.ySource) - 1,
							command.iDest - 1,
							convertCharToInt(command.jDest) - 1);

					mode = getGameStatus(game);

					//check if there is a winner
					if (mode == CHECK) {
						printf("Check: %s King is threatened!\n",
								getStringCurrentPlayer(game->currentPlayer));
					}

					//if mate then game is finished
					if (mode == MATE) {
						winner = 'f';
						printf("Checkmate! %s player wins the game\n",
								getOppositeStringCurrentPlayer(
										game->currentPlayer));

						//check if there is a tie and game is finished
					} else if (mode == TIE) {
						winner = 'f';

						printf("The game is tied\n");
					}

					else if (game->gameMode == ONE_PLAYER_MODE) {
						computerMakeMove(game, &winner);
					}
				}
			}

		}
	}

	return winner;
}

void computerMakeMove(Game* game, char* winner) {
	CHECK_MODE mode;

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int suggest = 0;

//use minimax for the next move
	suggest = minimaxSuggestMove(game, game->difficulty, &i, &j, &k, &l);
	if (suggest == -2) {
		exceptionPrintAndExit(-2);
	}
	GameSetMove(game, i, j, k, l);
	printf("Computer: move %s at <%d,%c> to <%d,%c>\n",
			TransCharToString(game->gameBoard[k][l]), i + 1,
			convertIntToChar(j + 1), k + 1, convertIntToChar(l + 1));

	mode = getGameStatus(game);

//check if there is a winner
	if (mode == MATE) {
		*winner = 'f';
		printf("Checkmate! %s player wins the game\n",
				getOppositeStringCurrentPlayer(game->currentPlayer));
		//check if there is a tie
	} else if (mode == TIE) {
		*winner = 'f';
		printf("The game ends in a tie\n");
	} else if (mode == CHECK) {
		printf("Check!\n");
	}

	if (*winner == getOppositeCurrentPlayer(game->userColor)) {
		GamePrintBoard(game);
	}
}

//return winner to main function
// r- restart, e- error, f- quit
char gameProgress(Game* game) {
	char winner = '\0';
	winner = gamePlay(game);
	if (winner == 'r') {
		return winner;
	} else if (winner == 'e') {
		return 'e';
	} else if (winner == 'f') {
		return winner;
	}

	return winner;
}

//print exception and exit the game
void exceptionPrintAndExit(int functionType) {
	char* exceptionName = NULL;
	if (functionType == -2) {
		exceptionName = "malloc";
	} else if (functionType == -3) {
		exceptionName = "fgets";
	}
	perror_message(exceptionName);
	printf("Exiting...\n");
	exit(EXIT_SUCCESS);
}

void checkIfGameProgressReturnedError(Game* game, char errorCode) {
// Check for error code
	if (errorCode == 'e') {
		GameDestroy(game);
		exceptionPrintAndExit(-3);
	}
}

void checkIfFgetsFailed(Game* game, char* returnFgets) {
// Check if fgets failed
	if (NULL == returnFgets) {
		GameDestroy(game);
		exceptionPrintAndExit(-3);
	}
	return;
}

void checkIfGameCrateFailed(Game* game) {
// Check if create game failed
	if (NULL == game) {
		exceptionPrintAndExit(-2);
	}
	return;
}

//restart the game
char restartGame(Game* game) {

	settingsState(game);

	char winner = '\0';
	checkIfGameCrateFailed(game);

	winner = gameProgress(game);
	checkIfGameProgressReturnedError(game, winner);

	return winner;

}

//convert the game to default settings
void defaultSettingsGame(Game* game) {

	game->difficulty = DEFAULT_DIFFICULTY;
	game->gameMode = ONE_PLAYER_MODE;
	game->userColor = WHITE;

	return;

}

//print the settings of the current game
void printSettingsGame(Game* game) {
	printf("SETTINGS:\n");
	if (game->gameMode == TWO_PLAYER_MODE) {
		printf("GAME_MODE: 2\n");
	}
	if (game->gameMode == ONE_PLAYER_MODE) {
		printf("GAME_MODE: 1\n");
		printf("DIFFICULTY_LVL: %d\n", game->difficulty);
		if (game->userColor == 1) {
			printf("USER_CLR: WHITE\n");
		} else if (game->userColor == 0) {
			printf("USER_CLR: BLACK\n");
		}
	}

	return;

}

USER_COLOR getUserColorOfColor(char currentPlayer) {
	if (currentPlayer == 'W') {
		return WHITE;
	} else if (currentPlayer == 'B') {
		return BLACK;
	}

	return NO_COLOR;

}

char* getStringOfColor(char currentPlayer) {
	char* player;
	if (currentPlayer == 'W') {
		player = "white";
	} else if (currentPlayer == 'B') {
		player = "black";
	}

	return player;

}

//return the opposite color from imput
char* getOppositeStringOfColor(char currentPlayer) {
	char* player;
	if (currentPlayer == 'W') {
		player = "black";
	} else if (currentPlayer == 'B') {
		player = "white";
	}

	return player;
}

//return the current player color string
const char * getStringCurrentPlayer(char c) {
	char* player;
	if (c == GAME_PLAYER_1_SYMBOL) {
		player = "white";
	} else if (c == GAME_PLAYER_2_SYMBOL) {
		player = "black";
	}

	return player;

}
//return the current player opposite color string
const char * getOppositeStringCurrentPlayer(char c) {
	char* player;
	if (c == GAME_PLAYER_1_SYMBOL) {
		player = "black";
	} else if (c == GAME_PLAYER_2_SYMBOL) {
		player = "white";
	}

	return player;

}

char getOppositeCurrentPlayer(USER_COLOR userColor) {
	if (userColor == WHITE) {
		return GAME_PLAYER_2_SYMBOL;
	} else {
		return GAME_PLAYER_1_SYMBOL;
	}
}

int convertCharToInt(char c) {
	switch (c) {
	case 'A':
		return 1;
	case 'B':
		return 2;
	case 'C':
		return 3;
	case 'D':
		return 4;
	case 'E':
		return 5;
	case 'F':
		return 6;
	case 'G':
		return 7;
	case 'H':
		return 8;
	}
	return -1;

}

char convertIntToChar(int i) {
	switch (i) {
	case 1:
		return 'A';
	case 2:
		return 'B';
	case 3:
		return 'C';
	case 4:
		return 'D';
	case 5:
		return 'E';
	case 6:
		return 'F';
	case 7:
		return 'G';
	case 8:
		return 'H';

	}
//can't get here
	return 'O';
}

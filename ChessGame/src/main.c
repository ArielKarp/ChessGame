/*
 ============================================================================
 Name        : ChessGame.c
 Author      : Ariel Karpilovski 308552454,	Ron Tabibian 308472596
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include "GuiMode.h"
#include "ConsoleMode.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc == 2) {
		if (strcmp(argv[1], "-c") == 0) {
				ConsoleMode();
		}
		if (strcmp(argv[1], "-g") == 0) {
			startGuiMode();
		}
	} else { //Default operation
		ConsoleMode();
	}
	return 0;
}

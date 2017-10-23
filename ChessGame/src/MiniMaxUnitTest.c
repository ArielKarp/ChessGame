/*
 * MiniMaxUnitTest.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "unit_test_util.h"
#include "MiniMaxAlgorithm.h"


//
//static bool miniMaxCheck1(){
//	Game* game= GameCreate(3);
//	game->gameBoard[0][0]='_';
//	game->gameBoard[0][1]='_';
//	game->gameBoard[0][2]='k';
//	game->gameBoard[0][3]='r';
//	game->gameBoard[0][4]='_';
//	game->gameBoard[0][5]='b';
//	game->gameBoard[0][6]='_';
//	game->gameBoard[0][7]='r';
//	game->gameBoard[1][0]='m';
//	game->gameBoard[1][1]='m';
//	game->gameBoard[1][2]='m';
//	game->gameBoard[1][3]='_';
//	game->gameBoard[1][4]='_';
//	game->gameBoard[1][5]='m';
//	game->gameBoard[1][6]='m';
//	game->gameBoard[1][7]='m';
//	game->gameBoard[2][0]='_';
//	game->gameBoard[2][1]='_';
//	game->gameBoard[2][2]='n';
//	game->gameBoard[2][3]='_';
//	game->gameBoard[2][4]='_';
//	game->gameBoard[2][5]='_';
//	game->gameBoard[2][6]='_';
//	game->gameBoard[2][7]='_';
//	game->gameBoard[3][0]='_';
//	game->gameBoard[3][1]='_';
//	game->gameBoard[3][2]='_';
//	game->gameBoard[3][3]='_';
//	game->gameBoard[3][4]='_';
//	game->gameBoard[3][5]='_';
//	game->gameBoard[3][6]='_';
//	game->gameBoard[3][7]='_';
//	game->gameBoard[4][0]='_';
//	game->gameBoard[4][1]='_';
//	game->gameBoard[4][2]='_';
//	game->gameBoard[4][3]='_';
//	game->gameBoard[4][4]='Q';
//	game->gameBoard[4][5]='_';
//	game->gameBoard[4][6]='b';
//	game->gameBoard[4][7]='_';
//	game->gameBoard[5][0]='_';
//	game->gameBoard[5][1]='_';
//	game->gameBoard[5][2]='M';
//	game->gameBoard[5][3]='_';
//	game->gameBoard[5][4]='M';
//	game->gameBoard[5][5]='_';
//	game->gameBoard[5][6]='_';
//	game->gameBoard[5][7]='_';
//	game->gameBoard[6][0]='M';
//	game->gameBoard[6][1]='M';
//	game->gameBoard[6][2]='_';
//	game->gameBoard[6][3]='_';
//	game->gameBoard[6][4]='_';
//	game->gameBoard[6][5]='M';
//	game->gameBoard[6][6]='M';
//	game->gameBoard[6][7]='M';
//	game->gameBoard[7][0]='R';
//	game->gameBoard[7][1]='N';
//	game->gameBoard[7][2]='B';
//	game->gameBoard[7][3]='K';
//	game->gameBoard[7][4]='_';
//	game->gameBoard[7][5]='B';
//	game->gameBoard[7][6]='_';
//	game->gameBoard[7][7]='R';
//	game->blackKingLocation[0]=7;
//	game->blackKingLocation[1]=3;
//	game->whiteKingLocation[0]=0;
//	game->whiteKingLocation[1]=2;
//	game->currentPlayer = GAME_PLAYER_2_SYMBOL;
//	game->blackPieces[0]=7; game->blackPieces[1]=2; game->blackPieces[2]=2; game->blackPieces[3]=1; game->blackPieces[4]=1; game->blackPieces[5]=1;
//	game->whitePieces[0]=6; game->whitePieces[1]=1; game->whitePieces[2]=2; game->whitePieces[3]=1; game->whitePieces[4]=0; game->whitePieces[5]=1;
//	//game->game_status = updateStatus(game);
//	//int a = scoreFunction(game);
//	GamePrintBoard(game);
//	int i = 0, j = 0, k = 0, l = 0;
//	printf("difficulty: %d\n", game->difficulty);
//	int result = miniMaxAlgorithm(game, 2, &i, &j, &k, &l);
//	printf("Result: %d From: i: %d, j: %d To: k: %d l: %d\n", result, i, j, k, l);
//	//ASSERT_TRUE(best_move[2]==6 && best_move[3]==2);
//	GameDestroy(game);
//	printf("count is: %d\n", var);
//
//	//free(best_move);
//	return true;
//}
//
//static bool miniMaxCheck2(){
//	Game* game= GameCreate(3);
//
//	game->gameBoard[0][0]='r';
//	game->gameBoard[0][1]='_';
//	game->gameBoard[0][2]='_';
//	game->gameBoard[0][3]='_';
//	game->gameBoard[0][4]='_';
//	game->gameBoard[0][5]='_';
//	game->gameBoard[0][6]='_';
//	game->gameBoard[0][7]='_';
//	game->gameBoard[1][0]='_';
//	game->gameBoard[1][1]='_';
//	game->gameBoard[1][2]='_';
//	game->gameBoard[1][3]='_';
//	game->gameBoard[1][4]='_';
//	game->gameBoard[1][5]='_';
//	game->gameBoard[1][6]='_';
//	game->gameBoard[1][7]='_';
//	game->gameBoard[2][0]='_';
//	game->gameBoard[2][1]='_';
//	game->gameBoard[2][2]='_';
//	game->gameBoard[2][3]='_';
//	game->gameBoard[2][4]='_';
//	game->gameBoard[2][5]='_';
//	game->gameBoard[2][6]='_';
//	game->gameBoard[2][7]='_';
//	game->gameBoard[3][0]='_';
//	game->gameBoard[3][1]='_';
//	game->gameBoard[3][2]='_';
//	game->gameBoard[3][3]='_';
//	game->gameBoard[3][4]='_';
//	game->gameBoard[3][5]='_';
//	game->gameBoard[3][6]='_';
//	game->gameBoard[3][7]='_';
//	game->gameBoard[4][0]='_';
//	game->gameBoard[4][1]='k';
//	game->gameBoard[4][2]='_';
//	game->gameBoard[4][3]='_';
//	game->gameBoard[4][4]='_';
//	game->gameBoard[4][5]='_';
//	game->gameBoard[4][6]='_';
//	game->gameBoard[4][7]='_';
//	game->gameBoard[5][0]='_';
//	game->gameBoard[5][1]='_';
//	game->gameBoard[5][2]='m';
//	game->gameBoard[5][3]='_';
//	game->gameBoard[5][4]='_';
//	game->gameBoard[5][5]='_';
//	game->gameBoard[5][6]='_';
//	game->gameBoard[5][7]='_';
//	game->gameBoard[6][0]='_';
//	game->gameBoard[6][1]='_';
//	game->gameBoard[6][2]='_';
//	game->gameBoard[6][3]='_';
//	game->gameBoard[6][4]='_';
//	game->gameBoard[6][5]='_';
//	game->gameBoard[6][6]='_';
//	game->gameBoard[6][7]='_';
//	game->gameBoard[7][0]='_';
//	game->gameBoard[7][1]='K';
//	game->gameBoard[7][2]='_';
//	game->gameBoard[7][3]='_';
//	game->gameBoard[7][4]='_';
//	game->gameBoard[7][5]='_';
//	game->gameBoard[7][6]='_';
//	game->gameBoard[7][7]='q';
//	game->blackKingLocation[0]=7;
//	game->blackKingLocation[1]=1;
//	game->whiteKingLocation[0]=4;
//	game->whiteKingLocation[1]=1;
//	game->currentPlayer = GAME_PLAYER_2_SYMBOL;
//	game->blackPieces[0]=0; game->blackPieces[1]=0; game->blackPieces[2]=0; game->blackPieces[3]=0; game->blackPieces[4]=0; game->blackPieces[5]=1;
//	game->whitePieces[0]=1; game->whitePieces[1]=0; game->whitePieces[2]=1; game->whitePieces[3]=0; game->whitePieces[4]=1; game->whitePieces[5]=1;
//
//	GamePrintBoard(game);
//
//	int i = 0, j = 0, k = 0, l = 0;
//	printf("difficulty: %d\n", game->difficulty);
//	int result = miniMaxAlgorithm(game, 2, &i, &j, &k, &l);
//	printf("Result: %d From: i: %d, j: %d To: k: %d l: %d\n", result, i, j, k, l);
//	GameDestroy(game);
//	printf("count is: %d\n", var);
//
//	//ASSERT_TRUE(best_move[2]==7 && best_move[3]==3);
//	//free(best_move);
//	return true;
//}

static bool miniMaxCheck3(){
	Game* game= GameCreate(6);

	game->gameBoard[0][0]='_';
	game->gameBoard[0][1]='_';
	game->gameBoard[0][2]='_';
	game->gameBoard[0][3]='_';
	game->gameBoard[0][4]='Q';
	game->gameBoard[0][5]='_';
	game->gameBoard[0][6]='_';
	game->gameBoard[0][7]='_';
	game->gameBoard[1][0]='_';
	game->gameBoard[1][1]='_';
	game->gameBoard[1][2]='_';
	game->gameBoard[1][3]='_';
	game->gameBoard[1][4]='_';
	game->gameBoard[1][5]='_';
	game->gameBoard[1][6]='m';
	game->gameBoard[1][7]='k';
	game->gameBoard[2][0]='_';
	game->gameBoard[2][1]='_';
	game->gameBoard[2][2]='_';
	game->gameBoard[2][3]='_';
	game->gameBoard[2][4]='_';
	game->gameBoard[2][5]='_';
	game->gameBoard[2][6]='_';
	game->gameBoard[2][7]='m';
	game->gameBoard[3][0]='m';
	game->gameBoard[3][1]='_';
	game->gameBoard[3][2]='_';
	game->gameBoard[3][3]='_';
	game->gameBoard[3][4]='_';
	game->gameBoard[3][5]='_';
	game->gameBoard[3][6]='_';
	game->gameBoard[3][7]='_';
	game->gameBoard[4][0]='_';
	game->gameBoard[4][1]='m';
	game->gameBoard[4][2]='_';
	game->gameBoard[4][3]='_';
	game->gameBoard[4][4]='_';
	game->gameBoard[4][5]='_';
	game->gameBoard[4][6]='M';
	game->gameBoard[4][7]='_';
	game->gameBoard[5][0]='M';
	game->gameBoard[5][1]='m';
	game->gameBoard[5][2]='_';
	game->gameBoard[5][3]='M';
	game->gameBoard[5][4]='_';
	game->gameBoard[5][5]='_';
	game->gameBoard[5][6]='K';
	game->gameBoard[5][7]='M';
	game->gameBoard[6][0]='_';
	game->gameBoard[6][1]='M';
	game->gameBoard[6][2]='_';
	game->gameBoard[6][3]='_';
	game->gameBoard[6][4]='_';
	game->gameBoard[6][5]='R';
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
	game->blackKingLocation[1]=6;
	game->whiteKingLocation[0]=1;
	game->whiteKingLocation[1]=7;
	game->currentPlayer = GAME_PLAYER_2_SYMBOL;
	//game->blackPieces[0]=0; game->blackPieces[1]=0; game->blackPieces[2]=0; game->blackPieces[3]=0; game->blackPieces[4]=0; game->blackPieces[5]=1;
	//game->whitePieces[0]=1; game->whitePieces[1]=0; game->whitePieces[2]=1; game->whitePieces[3]=0; game->whitePieces[4]=1; game->whitePieces[5]=1;

	GamePrintBoard(game);

	int i = 0, j = 0, k = 0, l = 0;
	printf("difficulty: %d\n", game->difficulty);
	int result = miniMaxAlgorithm(game, 3, &i, &j, &k, &l);
	printf("Result: %d From: i: %d, j: %d To: k: %d l: %d\n", result, i, j, k, l);
	GameDestroy(game);
	//printf("count is: %d\n", var);

	//ASSERT_TRUE(best_move[2]==7 && best_move[3]==3);
	//free(best_move);
	return true;
}


int main() {
	//printf("kaki!\n");
	//RUN_TEST(miniMaxCheck1);
	//RUN_TEST(miniMaxCheck2);
	RUN_TEST(miniMaxCheck3);

}

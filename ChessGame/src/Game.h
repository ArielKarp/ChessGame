#define GAME_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "ArrayList.h"


/**
 * Game Summary:
 *
 * A container that represents a classic chess game
 * board game. The container supports the following functions.
 *
 * GameCreate           - Creates a new game board
 * GameCopy             - Copies a game board
 * GameDestroy          - Frees all memory resources associated with a game
 * GameSetMove          - Sets a move on a game board
 * GameIsValidMove      - Checks if a move is valid
 * GameUndoPrevMove     - Undoes previous move made by the last player
 * GamePrintBoard       - Prints the current board
 * GameGetCurrentPlayer - Returns the current player
 *
 */

//Definitions
#define GAME_N_ROWS 8
#define GAME_N_COLUMNS 8
#define GAME_PLAYER_1_SYMBOL 'W'
#define GAME_PLAYER_2_SYMBOL 'B'
#define WHITE_PAWN 'm'
#define BLACK_PAWN 'M'
#define WHITE_BISHOP 'b'
#define BLACK_BISHOP 'B'
#define WHITE_ROOK 'r'
#define BLACK_ROOK 'R'
#define WHITE_KNIGHT 'n'
#define BLACK_KNIGHT 'N'
#define WHITE_QUEEN 'q'
#define BLACK_QUEEN 'Q'
#define WHITE_KING 'k'
#define BLACK_KING 'K'
#define GAME_TIE_SYMBOL '-'
#define GAME_EMPTY_ENTRY '_'
#define KING_LOC 2
#define NUM_PIECES 6
#define DEFAULT_DIFFICULTY 2
#define PAWN_NUMS 8
#define BISHOP_NUMS 2
#define ROOK_NUMS 2
#define KNIGHT_NUMS 2
#define QUEEN_NUMS 1
#define KING_NUMS 1
#define WHITE_PIECES_BACK_LINE 0
#define WHITE_PIECES_FRONT_LINE 1
#define BLACK_PIECES_BACK_LINE 7
#define BLACK_PIECES_FRONT_LINE 6
#define KING_Y_LOCATION 4
#define NUM_OF_MOVES 4
#define NUM_OF_CORDS 2
#define HISTORY_SIZE 6
#define perror_message(func_name) (fprintf(stdout, "ERROR: standard function %s has failed\n", func_name))
#define perror_command(line) (fprintf(stdout, "ERROR: %s\n", line))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



typedef enum user_color_t {
	BLACK, WHITE, NO_COLOR,
} USER_COLOR;

typedef enum game_mode_t {
	ONE_PLAYER_MODE, TWO_PLAYER_MODE, NO_GAME_MODE,
} GAME_MODE;

typedef enum check_mode_t {
	CHECK, MATE, TIE, PASS, FAIL_MODE
} CHECK_MODE;

typedef struct game_t {
	char gameBoard[GAME_N_ROWS][GAME_N_COLUMNS];
	char currentPlayer;
	int whiteKingLocation[KING_LOC];
	int blackKingLocation[KING_LOC];
	int whitePieces[NUM_PIECES]; //[Pawn,Bishop,Rook,Knight,Queen,King]
	int blackPieces[NUM_PIECES];
	ArrayList* historyMoves;
	int historySize;
	int difficulty;
	GAME_MODE gameMode;
	USER_COLOR userColor;

} Game;

/**
 * Type used for returning error codes from game functions
 */
typedef enum game_message_t {
	GAME_INVALID_MOVE, GAME_INVALID_ARGUMENT, GAME_NO_HISTORY, GAME_SUCCESS,
} GAME_MESSAGE;

/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
Game* GameCreate(int historySize);

/**
 * Set GAME_EMPTY_ENTRY in every entry of the board
 * @param board- game board
 */
void initGameBoard(char board[GAME_N_ROWS][GAME_N_COLUMNS]);

/**
 * translate char to chess piece
 * @param board- game board
 * @return chess piece
 */
ChessPiece TransCharToPiece(char c);

/**
 * translate char to chess piece string
 * @param board- game board
 * @return char*
 */
char* TransCharToString(char c);

/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
Game* GameCopy(Game* src);

/**
 * Utility function, copy board from srcBoard to dstBoard, iterate over every entry
 */
void copyBoard(char destBoard[GAME_N_ROWS][GAME_N_COLUMNS],
		char srcBoard[GAME_N_ROWS][GAME_N_COLUMNS]);

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void GameDestroy(Game* src);

/**
 * Sets the next move in a given game by specifying column index. The
 * columns are 0-based and in the range [0,GAME_N_COLUMNS -1].
 *
 * @param src - The target game
 * @return
 * GAME_INVALID_MOVE 	 - invalid move by chess rules
 * GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
 * GAME_INVALID_MOVE - if the given move is invalid by chess rules.
 * GAME_SUCCESS - otherwise
 */
GAME_MESSAGE GameSetMove(Game* src, int row_source, int col_source,
		int row_dest, int col_dest);

/**
 * Checks if a disk can be put in the specified valid location.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool GameIsValidMovement(Game* src, int row_source, int col_source,
		int row_dest, int col_dest);

/**
 * Removes a disc that was put in the previous move and changes the current
 * player's turn. If the user invoked this command more than historySize times
 * in a row then an error occurs.
 *
 * @param src - The source game
 * @return
 * GAME_INVALID_MOVE 	 - invalid move by chess rules
 * GAME_INVALID_ARGUMENT - if src == NULL
 * GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * GAME_SUCCESS          - on success. The last disc that was put on the
 *                                 board is removed and the current player is changed
 */
GAME_MESSAGE GameUndoPrevMove(Game* src);

///**
// * Similar to GameUndoPrevMove function, but places move into collNum
// *
// * @param src- src Game
// * @param collNum- pointer to int parameter that indicates column number- 0-based
// * @return same as GameUndoPrevMove
// */
//GAME_MESSAGE GameUndoWithMove(Game* src, DataMember* collNum);

/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters 'X' and 'O' are used to represent
 * the discs of player 1 and player 2, respectively.
 *
 * @param src - the target game
 * @return
 * GAME_INVALID_MOVE 	 - invalid move by chess rules
 * GAME_INVALID_ARGUMENT - if src==NULL
 * GAME_SUCCESS - otherwise
 *
 */
GAME_MESSAGE GamePrintBoard(Game* src);

/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * GAME_INVALID_MOVE 	 - invalid move by chess rules
 * GAME_PLAYER_1_SYMBOL - if it's player one's turn
 * GAME_PLAYER_2_SYMBOL - if it's player two's turn
 * GAME_EMPTY_ENTRY     - otherwise
 */
char GameGetCurrentPlayer(Game* src);

/**
 * Checks if a disk can be put in the specified valid location for pawn chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */

bool PawnIsValidMove(Game* src, char current_player, int row_source,
		int col_source, int row_dest, int col_dest);

/**
 * Checks if a disk can be put in the specified valid location for bishop chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool BishopIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest);

/**
 * Checks if a disk can be put in the specified valid location for rook chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool RookIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest);

/**
 * Checks if a disk can be put in the specified valid location for knight chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool KnightIsValidMove(int row_source, int col_source, int row_dest,
		int col_dest);

/**
 * Checks if a disk can be put in the specified valid location for king chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool KingIsValidMove(int row_source, int col_source, int row_dest, int col_dest);

/**
 * Checks if a disk can be put in the specified valid location for queen chess piece.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool QueenIsValidMove(Game* src, int row_source, int col_source, int row_dest,
		int col_dest);

/**
 * Checks if a king is compromised by another chess piece enemy.
 *
 * @param src - The source game
 * @param col_source - The specified column source
 * @param row_source - The specified row source
 * @param col_dest - The specified column destination
 * @param row_dest - The specified row destination
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool IsKingCompromisedByMove(Game* src, int row_source, int col_source,
		int row_dest, int col_dest);

/**
 * Checks if a current position is lower or upper char which it means it belongs to player 1 or 2.
 *
 * @param src - The source game
 * @param current_position - The specified position of chess piece
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool LowerOrUpper(Game* src, char current_position);

/**
 * Checks if a current position is lower or upper reverse char which it means it belongs to player 1 or 2.
 *
 * @param src - The source game
 * @param current_position - The specified position of chess piece
 *
 * @return
 * true  - if the a disc can be put in the target columnc and row
 * false - otherwise.
 */
bool LowerOrUpperReverse(Game* src, char current_position);

/**
 * Checks if a the king is compromised in the input game
 * @param src - The source game
 *
 * @return
 * true false.
 */
bool IsKingCompromised(Game* src);

CHECK_MODE getGameStatus(Game* src);

/**
 * get all moves for specific game
 * @param src - The source game
 *
 * @return
 * int result
 */
int getAllMoves(Game* src);

/**
 * get all moves for specific game and piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int getAllPossibleMoves(Game* src, char piece, int row_source, int col_source,
		int*** movesArr, bool fillMoves);

bool isMoveAllowed(Game* src, int row_source, int col_source, int row_dest,
		int col_dest);

/**
 * get all moves for specific game and pawn chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetPawnMoves(Game* src, char piece, int row_source, int col_source,
		int*** movesArr, bool fillMoves);

/**
 * get all moves for specific game and Knight chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetKnightMoves(Game* src, int row_source, int col_source, int*** movesArr,
		bool fillMoves);
/**
 * get all moves for specific game and king chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetKingMoves(Game* src, int row_source, int col_source, int*** movesArr,
		bool fillMoves);
/**
 * get all moves for specific game and rook chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetRookMoves(Game* src, int row_source, int col_source, int*** movesArr,
		bool fillMoves);
/**
 * get all moves for specific game and bishop chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetBishopMoves(Game* src, int row_source, int col_source, int*** movesArr,
		bool fillMoves);
/**
 * get all moves for specific game and queen chess piece
 * @param src - The source game and coordinates ints
 *
 * @return
 * int result
 */
int GetQueenMoves(Game* src, int row_source, int col_source, int*** movesArr,
		bool fillMoves);

void fillMovesArray(int*** dst, int resultSize, int srcSize, int n,
		int (*src)[n]);
/**
 * check if coordinates is in the board
 * @coordinates ints
 *
 * @return
 * bool
 */
bool InBoardLimits(int row_source, int col_source);

void learnGameBoardAndFillPieces(Game* src);

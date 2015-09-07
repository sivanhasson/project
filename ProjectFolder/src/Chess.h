#ifndef CHESS_
#define CHESS_

#include<stdio.h>

#define WHITE_P 'm'  //HAYAL
#define WHITE_B 'b'  //RATZ
#define WHITE_N 'n'  //PARASH
#define WHITE_R 'r'  //TSARIACH
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'


/* TODO--------TO DELETE!!!!!!! ----------*/
#define BLACK_M 'A'
#define WHITE_M 'a'
/*--------TO DELETE!!!!!!! ----------*/

#define EMPTY ' '

#define BOARD_SIZE 8

#define INPUT_LEN 50

/*IMPORTANT!! WE DECLARATED 0,1,2,3 (right-up, left-up...etc) STEPS. NOW WE HAVE UP, LEFT, DOWN, RIGHT TOO.
 *  NUMBER OF THEIS WILL BE UP = 4, LEFT = 5, DOWN = 6, RIGHT = 7*/

// board initialization
#define ENTER_SETTINGS "Enter game settings:\n"
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define DOES_NOT_CONTAIN "The specified position does not contain your piece\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"

#define WRONG_ROOK_POSITION "Wrong position for a rook\n"
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"

#define WHITE_TURN "white player - enter your move:\n"
#define BLACK_TURN "black player - enter your move:\n"

#define CHECK "Check!\n"
#define WHITE_WIN "Mate! white player wins the game\n"
#define BLACK_WIN "Mate! black player wins the game\n"
#define TIE "The game ends in a tie\n"




#define perror_message(func_name) (fprintf(stderr, "Error: standard function %s has failed\n", func_name))
#define print_message(message) (printf("%s", message));


/*GLOBAL VARS*/											/*set in a c file extern veriable*/
extern int player; /*(0 = computer (first player) , 1 = user (second player))*/
extern int gameMode; /*1 = two players mode, 2 =player VS computer*/
extern int state; /*(0 = setting, 1 = game)*/
extern int currPlayer; /*(0 = computer (first player) , 1 = user (second player))*/
extern int whitePlayer; /*(0 = computer (first player), 1 = user (second player)))*/
extern int depth;
extern int gameIsOn; /*(1 = yes, 0 = no)*/
extern int SettingStateIsOn; /*(1 = yes, 0 = no)*/
extern int whiteKingThreatRecord; /* 0 = never been threten, 1 = has been threten*/
extern int blackKingThreatRecord; /* 0 = never been threten, 1 = has been threten*/
extern int whiteKingIsThreat; /* 0 = is not threten, 1 = is threten*/
extern int blackKingIsThreat; /* 0 = is not threten, 1 = is threten*/
extern int whiteKingMoved; /*0 = did not, 1= moved*/
extern int blackKingMoved; /*0 = did not, 1= moved*/
extern struct boardState GAME_BOARD;


/*DEFINE THE STRUCTS*/
typedef struct location loc_t;
typedef struct move move_t;
typedef struct possibleMove possibleM_t;
typedef struct boardState boardState_t;
typedef struct miniMaxGameState mmGS_t;


struct location{	/*add all structs in a c file*/
	char col;
	int row;
};

struct move{
	loc_t curr;
	move_t *next;
	int castling;
};


struct possibleMove{
	move_t move;
	int check; /* 0 = no check , 1 = check*/
	//int eatCnt;
	possibleM_t* next;    /**----------------------> RETURN THE FIELD!!!! CAUSE WE NEED IT WHEN WE BUILD THE "GET ALL POSSIBLE MOVES"**/
};

struct boardState{
	char board[BOARD_SIZE][BOARD_SIZE];
	int numberWM;
	int numberWB;
	int numberWN;
	int numberWR;
	int numberWQ;
	int numberWK;

	int numberBM;
	int numberBB;
	int numberBN;
	int numberBR;
	int numberBQ;
	int numberBK;
};

struct miniMaxGameState{	//------------------------->> check if need to be FIXED
	int score;
	boardState_t boardState;
	move_t move; /*(list of moves for a current player's turn*/
};

//To check for Castling : (white/blaclk)KingThreatRecord , (white/black)KingMoved and check for continuous empty squers between King and Rook
int canDoRightCastling(char board[BOARD_SIZE][BOARD_SIZE], int currPlayer);   //TODO
int canDoLeftCastling(char board[BOARD_SIZE][BOARD_SIZE], int currPlayer);   //TODO
void addCastlingMove(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //TODO
loc_t* getKingLoc(char board[BOARD_SIZE][BOARD_SIZE], int player);    //TODO
loc_t* getRightRootLoc(char board[BOARD_SIZE][BOARD_SIZE], int player);    //TODO
loc_t* getLeftRootLoc(char board[BOARD_SIZE][BOARD_SIZE], int player);    //TODO
void addOneCastling(possibleM_t* firstStep, loc_t kingLoc, loc_t rightRootLoc);  //TODO
int checkAfterCastling(char board[BOARD_SIZE][BOARD_SIZE], int player);  //TODO



/*DECLARE THE FUNCTIONS*/
void gameState();

/*COMMON FUNCTIONS*/

void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_line();
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);   //TODO------------------------------------------>> UPDATE
void copyGameBoard(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]);
int checkIfWin(boardState_t* board, int player);		 //TODO------------------------------------------>> UPDATE
int checkIfCanMove(char board[BOARD_SIZE][BOARD_SIZE], int player);	//TODO------------------------------------------>> UPDATE
int checkMoveDisc(char board[BOARD_SIZE][BOARD_SIZE],int i, int j, int color);	//TODO------------------------------------------>> UPDATE

possibleM_t* getAllPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], int player);		//MORIA CHANGED

struct possibleMove* copyPossibleMove(struct possibleMove* firstOld);		//TODO------------------------------------------>> CHECK FOR UPDATE
int beenBefore(move_t *move, struct location *result, int KingPlayer);		//TODO------------------------------------------>> DELETE? MAYBE UPDATE FOR KING
int locIsBetween(move_t *move, move_t *moveNext, struct location *result);	//TODO------------------------------------------>> UPDATE
void getRecMoves(struct possibleMove* firstEmptyNode, struct possibleMove* firstStep, struct move* lastMove, int kingPlayer, char player);	//TODO------------------------------------------>> DELETE?
struct move* setNewStep(struct move* move, struct location* loc);			//TODO------------------------------------------>> UPDATE?
void returnTheBiggest(struct possibleMove* first);							//TODO------------------------------------------>> DELETE


void getPawnMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED
void getBishopMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED
void getKnightMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED
void getRookMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED
void getQueenMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED
void getKingMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player);  //MORIA ADDED


//void getEatingMove(char board[BOARD_SIZE][BOARD_SIZE],struct possibleMove* firstStep, struct possibleMove* tmpMove, struct move* lastStep ,int kingPlayer, int player);
//void getRegularMove(char board[BOARD_SIZE][BOARD_SIZE], struct possibleMove* firstStep, int kingPlayer, int player);

void addNewStep(possibleM_t* firstStep, loc_t loc);	//MORIA CHANGED
struct location* manCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo); // DELETE
struct location* kingCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo);	//--------->> DELETE
int theSamePlayer(char board[BOARD_SIZE][BOARD_SIZE], struct location* nextLoc, int player);			//TODO --> UPDATE
void setLocDuringGame(int x, int y, char* color, char* type, boardState_t* boardState);			/*TODO New - use this to set location in Game*/   //---->>UPDATE
void removeLocDuringGame(int x, int y, boardState_t* boardState);	//TODO---->>UPDATE
int stopConditions(loc_t* result, move_t* currMove, int player);	//TODO---->>UPDATE



int isContainsCheck(move_t* newMove); //TODO

void freeMT(move_t* move);		//TODO--------------------------------------->>UPDATE
void freePM(struct possibleMove* possibleMove); //TODO--------------------------------------->>UPDATE
void free_mmGS(mmGS_t* mmGS); //TODO--------------------------------------->>UPDATE
void free_mmGSArray(mmGS_t** arrayOfmmGS_t, int arraySize); //TODO--------------------------------------->>UPDATE

int isPlayer(char piece, int playerColor);  //MORIA ADDED
int isOtherPlayer(char piece, int playerColor);  //MORIA ADDED
int isWhite(char piece);  //MORIA ADDED
int isBlack(char piece);  //MORIA ADDED
int isPawn(char piece);  //MORIA ADDED
int isBishop(char piece);  //MORIA ADDED
int isKnight(char piece);  //MORIA ADDED
int isRook(char piece);  //MORIA ADDED
int isQueen(char piece);  //MORIA ADDED
int isKing(char piece);  //MORIA ADDED

int getPlayerColor(int player);  //MORIA ADDED


/*SETTING FUNCTIONS*/

void setGameMode(int gameMode);		//TODO NEW
int miniDepth(int);	//TODO--------------------------------------->>UPDATE
void userColor(char*);//TODO--------------------------------------->>UPDATE
void SettingState(boardState_t* gameBoard);//TODO--------------------------------------->>UPDATE
void userSettingCommand(char* userInput);//TODO--------------------------------------->>UPDATE
void load(char* filePath); //TODO NEW
void clear();	//TODO--------------------------------------->>UPDATE
void firstPlayer(char* color); //TODO NEW (update currentPlayer)
void setLoc(int, int, char*, char*);//TODO--------------------------------------->>UPDATE
int whiteSquare(struct location);	//TODO--------------------------------------->>CHECK FOR UPDATE
void removeLoc(int x, int y);	//TODO--------------------------------------->>UPDATE
void quit();
void start();//TODO--------------------------------------->>UPDATE
int boardIsEmpty(struct boardState* GAME_BOARD); //TODO--------------------------------------->>CHECK FOR UPDATE
int onlyOneColorDiscks(struct boardState* GAME_BOARD); //TODO--------------------------------------->>CHECK FOR UPDATE
int moreThen20ColorDicks(struct boardState* GAME_BOARD);//TODO--------------------------------------->>UPDATE

/*USER'S TURN FUNCTIONS*/
void userTurn();									//TODO---------------------------------------->>UPDATE
char* getInput(FILE* fp, size_t strSize);//TODO---------------------------------------->>UPDATE
void userCommand(char* userInput);//TODO---------------------------------------->>UPDATE
void checkMoveAndSet(char* moveCommand);//TODO---------------------------------------->>UPDATE
move_t createMoveByCommand(char* moveCommand);//TODO---------------------------------------->>UPDATE
int checkPosition(move_t userMove);//TODO---------------------------------------->>UPDATE
int validLoc(char col, int row);   //MORIA CHANGED
int emptyOrEatLoc(char piece, int player);    //MORIA ADD

int checkContainTheColor(move_t userMove);//TODO---------------------------------------->>UPDATE
int checkIfLegalMove(move_t userMove);//TODO---------------------------------------->>UPDATE
int moveDiagonally(move_t* move);//TODO---------------------------------------->>UPDATE
int canMoveThatWay(move_t *move, int player);//TODO---------------------------------------->>UPDATE
int checkIfEmpty(loc_t location);//TODO---------------------------------------->>UPDATE
int containEat(loc_t currLoc, loc_t afterLoc);//TODO---------------------------------------->>UPDATE
int validEating(loc_t currLoc, loc_t afterLoc);//TODO---------------------------------------->>UPDATE
int containComputerDisc(loc_t currLoc, loc_t afterLoc);//TODO---------------------------------------->>UPDATE
int legalKingMove(move_t *move);//TODO---------------------------------------->>UPDATE
void changeBoardByMove(boardState_t* board, move_t move);//TODO---------------------------------------->>UPDATE
void changeSingleMove(boardState_t* board, loc_t currLoc, loc_t afterLoc);//TODO---------------------------------------->>UPDATE
void endTurn();										//TODO---------------------------------------->>UPDATE
char getDiscByLocationInGameBoard(loc_t loc);//TODO---------------------------------------->>UPDATE
char getDiscByLocation(char board[BOARD_SIZE][BOARD_SIZE], loc_t loc);//TODO---------------------------------------->>UPDATE
void getUserMoves();								//TODO---------------------------------------->>UPDATE
void printPossibleMoves(possibleM_t *possibleMoves);//TODO(update for castling)---------------------------->>UPDATE
void printMove(move_t *move);					//TODO(update for castling)------------------------------------>>UPDATE

/*COMPUTER'S TURN FUNCTIONS*/
void computerTurn();							//TODO---------------------------------------->>UPDATE
mmGS_t* minimax(mmGS_t* node, int depth, int maximizingPlayer);	//TODO---------------------------------------->>UPDATE
void getChildren(mmGS_t* fatherNode, possibleM_t* possibleMove, mmGS_t** array); //TODO---------------------------------------->>UPDATE
mmGS_t* scoreCalc(mmGS_t* node);							//TODO---------------------------------------->>UPDATE
mmGS_t* maxNode (mmGS_t* firstNode, mmGS_t* secondNode);	//TODO---------------------------------------->>UPDATE
mmGS_t* minNode (mmGS_t* firstNode, mmGS_t* secondNode);	//TODO---------------------------------------->>UPDATE



/*INITIATION FUNCTIONS*/
void initArrChar(char* charArray, int len);//---------------------------------------->>UPDATE
void moveInitiation(move_t* move);//---------------------------------------->>UPDATE
void locInitiation(loc_t* loc);//---------------------------------------->>UPDATE
void posMovInitiation(struct possibleMove* firstEmptyNode);//---------------------------------------->>UPDATE
void mmGSArrayInit(mmGS_t** array , int len);//---------------------------------------->>UPDATE
void mmGSInitiation(mmGS_t* node);//---------------------------------------->>UPDATE

#endif //CHESS_

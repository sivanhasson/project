#ifndef CHESS_
#define CHESS_

#include<stdio.h>

#define WHITE_P 'm'
#define WHITE_B 'b'
#define WHITE_N 'n'
#define WHITE_R 'r'
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'


#define EMPTY ' '

#define BOARD_SIZE 8

// board initialization
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"  
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
 
#define WRONG_ROOK_POSITION "Wrong position for a rook\n" 
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"  

#define TIE "The game ends in a tie\n"
 
#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));


/*GLOBAL VARS*/											/*set in a c file extern veriable*/
extern int player; /*(1 = user, 0 = computer)*/
extern int gameMode; /*1 = two players mode, 2 =player VS computer*/
extern int state; /*(0 = setting, 1 = game)*/
extern int currPlayer; /*(0 = compuer (first player) , 1 = user (second player))*/
extern int whitePlayer; /*(0 = computer (first player), 1 = user (second player)))*/
extern int depth;
extern int gameIsOn; /*(1 = yes, 0 = no)*/
extern int SettingStateIsOn; /*(1 = yes, 0 = no)*/
extern int whiteKingThreatRecord; /* 0 = nver been threten, 1 = has been threten*/
extern int blackKingThreatRecord; /* 0 = nver been threten, 1 = has been threten*/
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
	//possibleMove_t * next; ----------------------> FIX ON CODE!!!
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
int canDoCastling(boardState_t boardState, int currPlayer, int whitePlayer);




/*DECLARE THE FUNCTIONS*/
void gameState();

/*COMMON FUNCTIONS*/

void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void print_line();
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);   //------------------------------------------>> UPDATE
void copyGameBoard(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]);
int checkIfWin(boardState_t* board, int player);		 //------------------------------------------>> UPDATE
int checkIfCanMove(char board[BOARD_SIZE][BOARD_SIZE], int player);	//------------------------------------------>> UPDATE
int checkMoveDisc(char board[BOARD_SIZE][BOARD_SIZE],int i, int j, int color);	//------------------------------------------>> UPDATE

possibleM_t* getAllPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], int player);		//------------------------------------------>> UPDATE

struct possibleMove* copyPossibleMove(struct possibleMove* firstOld);		//------------------------------------------>> CHECK FOR UPDATE
int beenBefore(move_t *move, struct location *result, int KingPlayer);		//------------------------------------------>> DELETE? MAYBE UPDATE FOR KING
int locIsBetween(move_t *move, move_t *moveNext, struct location *result);	//------------------------------------------>> UPDATE
void getRecMoves(struct possibleMove* firstEmptyNode, struct possibleMove* firstStep, struct move* lastMove, int kingPlayer, char player);	//------------------------------------------>> DELETE?
struct move* setNewStep(struct move* move, struct location* loc);			//------------------------------------------>> UPDATE?
void returnTheBiggest(struct possibleMove* first);							//------------------------------------------>> DELETE

//--------------> BOTH FUNCTIONS NEEDED TO BE MERGED
void getEatingMove(char board[BOARD_SIZE][BOARD_SIZE],struct possibleMove* firstStep, struct possibleMove* tmpMove, struct move* lastStep ,int kingPlayer, int player);
void getRegularMove(char board[BOARD_SIZE][BOARD_SIZE], struct possibleMove* firstStep, int kingPlayer, int player);

void addNewRegularStep(struct possibleMove* firstStep, struct location loc);	//------------------------------------------>> CHECK HOW TO USE
struct location* manCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo); // CHANGE TO pieceCanEatFromLoc and send each piece to the relevent function
struct location* kingCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo);	//--------->> DELETE
int theSamePlayer(char board[BOARD_SIZE][BOARD_SIZE], struct location* nextLoc, int player);						// --> UPDATE
void setLocDuringGame(int x, int y, char* color, char* type, boardState_t* boardState);			/*New - use this to set location in Game*/   //---->>UPDATE
void removeLocDuringGame(int x, int y, boardState_t* boardState);	//---->>UPDATE
int stopConditions(loc_t* result, move_t* currMove, int player);	//---->>UPDATE
void freeMT(move_t* move);		//--------------------------------------->>UPDATE
void freePM(struct possibleMove* possibleMove); //--------------------------------------->>UPDATE
void free_mmGS(mmGS_t* mmGS); //--------------------------------------->>UPDATE
void free_mmGSArray(mmGS_t** arrayOfmmGS_t, int arraySize); //--------------------------------------->>UPDATE


/*SETTING FUNCTIONS*/

void gameMode (int gameMode);		//NEW
int miniDepth(int);	//--------------------------------------->>UPDATE
void userColor(char*);//--------------------------------------->>UPDATE
void SettingState(boardState_t* gameBoard);//--------------------------------------->>UPDATE
void userSettingCommand(char* userInput);//--------------------------------------->>UPDATE
void load(char* filePath); //NEW
void clear();	//--------------------------------------->>UPDATE
void firstPlayer(char* color); //NEW (update currentPlayer)
void setLoc(int, int, char*, char*);//--------------------------------------->>UPDATE
int whiteSquare(struct location);	//--------------------------------------->>CHECK FOR UPDATE
void removeLoc(int x, int y);	//--------------------------------------->>UPDATE
void quit();
void start();//--------------------------------------->>UPDATE
int boardIsEmpty(struct boardState* GAME_BOARD); //--------------------------------------->>CHECK FOR UPDATE
int onlyOneColorDiscks(struct boardState* GAME_BOARD); //--------------------------------------->>CHECK FOR UPDATE
int moreThen20ColorDicks(struct boardState* GAME_BOARD);//--------------------------------------->>UPDATE

/*USER'S TURN FUNCTIONS*/
void userTurn();									//---------------------------------------->>UPDATE
char* getInput(FILE* fp, size_t strSize);//---------------------------------------->>UPDATE
void userCommand(char* userInput);//---------------------------------------->>UPDATE
void checkMoveAndSet(char* moveCommand);//---------------------------------------->>UPDATE
move_t createMoveByCommand(char* moveCommand);//---------------------------------------->>UPDATE
int checkPosition(move_t userMove);//---------------------------------------->>UPDATE
int validLoc(char col, int row);//---------------------------------------->>UPDATE
int checkContainTheColor(move_t userMove);//---------------------------------------->>UPDATE
int checkIfLegalMove(move_t userMove);//---------------------------------------->>UPDATE
int moveDiagonally(move_t* move);//---------------------------------------->>UPDATE
int canMoveThatWay(move_t *move, int player);//---------------------------------------->>UPDATE
int checkIfEmpty(loc_t location);//---------------------------------------->>UPDATE
int containEat(loc_t currLoc, loc_t afterLoc);//---------------------------------------->>UPDATE
int validEating(loc_t currLoc, loc_t afterLoc);//---------------------------------------->>UPDATE
int containComputerDisc(loc_t currLoc, loc_t afterLoc);//---------------------------------------->>UPDATE
int legalKingMove(move_t *move);//---------------------------------------->>UPDATE
void changeBoardByMove(boardState_t* board, move_t move);//---------------------------------------->>UPDATE
void changeSingleMove(boardState_t* board, loc_t currLoc, loc_t afterLoc);//---------------------------------------->>UPDATE
void endTurn();										//---------------------------------------->>UPDATE
char getDiscByLocationInGameBoard(loc_t loc);//---------------------------------------->>UPDATE
char getDiscByLocation(char board[BOARD_SIZE][BOARD_SIZE], loc_t loc);//---------------------------------------->>UPDATE
void getUserMoves();								//---------------------------------------->>UPDATE
void printPossibleMoves(possibleM_t *possibleMoves);//---------------------------------------->>UPDATE
void printMove(move_t *move);					//---------------------------------------->>UPDATE

/*COMPUTER'S TURN FUNCTIONS*/
void computerTurn();							//---------------------------------------->>UPDATE
mmGS_t* minimax(mmGS_t* node, int depth, int maximizingPlayer);	//---------------------------------------->>UPDATE
void getChildren(mmGS_t* fatherNode, possibleM_t* possibleMove, mmGS_t** array); //---------------------------------------->>UPDATE
mmGS_t* scoreCalc(mmGS_t* node);							//---------------------------------------->>UPDATE
mmGS_t* maxNode (mmGS_t* firstNode, mmGS_t* secondNode);	//---------------------------------------->>UPDATE
mmGS_t* minNode (mmGS_t* firstNode, mmGS_t* secondNode);	//---------------------------------------->>UPDATE



/*INITIATION FUNCTIONS*/
void initArrChar(char* charArray, int len);//---------------------------------------->>UPDATE
void moveInitiation(move_t* move);//---------------------------------------->>UPDATE
void locInitiation(loc_t* loc);//---------------------------------------->>UPDATE
void posMovInitiation(struct possibleMove* firstEmptyNode);//---------------------------------------->>UPDATE
void mmGSArrayInit(mmGS_t** array , int len);//---------------------------------------->>UPDATE
void mmGSInitiation(mmGS_t* node);//---------------------------------------->>UPDATE
#endif CHESS_

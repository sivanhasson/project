#include "Chess.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>


int whitePlayer;
int currPlayer;
int SettingStateIsOn;
int gameIsOn;
struct boardState GAME_BOARD;
int depth;


int main(){
	init_board(GAME_BOARD.board);
	clear(GAME_BOARD);

	/*
	 * check the getAllPossibleMoves function:
	GAME_BOARD.board[0][7] = BLACK_R;
	GAME_BOARD.board[4][7] = BLACK_R;
	GAME_BOARD.board[6][7] = BLACK_K;
	GAME_BOARD.board[1][6] = BLACK_B;
	GAME_BOARD.board[2][6] = BLACK_Q;
	GAME_BOARD.board[3][6] = BLACK_N;
	GAME_BOARD.board[5][6] = BLACK_P;
	GAME_BOARD.board[7][6] = BLACK_P;
	GAME_BOARD.board[0][5] = BLACK_P;
	GAME_BOARD.board[1][5] = BLACK_P;
	GAME_BOARD.board[2][5] = BLACK_N;
	GAME_BOARD.board[3][5] = BLACK_P;
	GAME_BOARD.board[4][5] = BLACK_P;
	GAME_BOARD.board[6][5] = BLACK_P;

	GAME_BOARD.board[6][4] = WHITE_P;
	GAME_BOARD.board[0][3] = WHITE_P;
	GAME_BOARD.board[3][3] = WHITE_N;
	GAME_BOARD.board[4][3] = WHITE_P;
	GAME_BOARD.board[5][3] = WHITE_P;
	GAME_BOARD.board[2][2] = WHITE_N;
	GAME_BOARD.board[7][2] = WHITE_R;
	GAME_BOARD.board[1][1] = WHITE_P;
	GAME_BOARD.board[2][1] = WHITE_P;
	GAME_BOARD.board[5][1] = WHITE_Q;
	GAME_BOARD.board[6][1] = WHITE_B;
	GAME_BOARD.board[7][1] = WHITE_P;
	GAME_BOARD.board[5][0] = WHITE_R;
	GAME_BOARD.board[7][0] = WHITE_K;

	print_board(GAME_BOARD.board);

	printPossibleMoves(getAllPossibleMoves(GAME_BOARD.board, 0));
	*/
	//print_message(WELCOME_TO_DRAUGHTS);
	//SettingStateIsOn = 1;
	//SettingState(&GAME_BOARD);

	//if (gameIsOn){
	//	gameState();
	//}

	return 0;
}



void gameState(){

	/*put the default*/
	if (whitePlayer == 3){
		whitePlayer = 1;
	}
	if (depth == 10){
		depth = 1;
	}

	currPlayer = whitePlayer;

	/*start the game*/
	while(gameIsOn){
		if (currPlayer){
			userTurn();
		}
		else{
			computerTurn();
		}
	}
}


void computerTurn(){
	mmGS_t* nextCompTurn = NULL;
	mmGS_t root;
	mmGSInitiation(&root);

	root.boardState = GAME_BOARD;
	nextCompTurn = minimax(&root, depth, 0);
	changeBoardByMove(&GAME_BOARD,nextCompTurn->move);

	//print_message(COMPUTER_MOVE);  TODO
	printMove(&(nextCompTurn->move));
	print_board(GAME_BOARD.board);

	if (checkIfWin(&GAME_BOARD, 0)){  /*the computer win*/
		if (!whitePlayer){   /*computer is the white player*/
			print_message(WHITE_WIN);
		}
		else{
			print_message(BLACK_WIN);
		}
		gameIsOn = 0;
	}

	else {      /*continue the game, now the userTurn*/
		currPlayer = 1;
	}
}


void userTurn()	{			/*will print "enter your move", and will send to userCommand()*/

	char* userInput = 0;

	userInput = (char*)malloc(INPUT_LEN);
	if(!userInput){
		perror_message("userTurn");
		quit();
	}
	initArrChar(userInput, INPUT_LEN);
	//print_message(ENTER_YOUR_MOVE); TODO
	userInput = getInput(stdin, INPUT_LEN);
	userCommand(userInput);
	free(userInput);
}

void copyGameBoard(char board1[BOARD_SIZE][BOARD_SIZE], char board2[BOARD_SIZE][BOARD_SIZE]){
	int i, j;
	for(i = 0; i < BOARD_SIZE; ++i){
		for(j = 0; j < BOARD_SIZE; ++j){
			strncpy(&(board1[i][j]), &(board2[i][j]), 1);
		}
	}
}
/*SETTING STATE FUNCTIONS*/

void SettingState(boardState_t* gameBoard)
{
	char* userInput = 0;

	print_message(ENTER_SETTINGS);

	/*put non-valid value, so if the setting state will not change it, ww'll know how to change it*/
	whitePlayer = 3;
	depth = 10;

	while(SettingStateIsOn){
		userInput = getInput(stdin, INPUT_LEN);
		userSettingCommand(userInput);
	}
}

void userSettingCommand(char* userInput)		/*parsing user settings command and call functions*/
{
	int x, y;
	char color[8];
	char* yValue = 0;
	char* xValue = 0;
	char* type = 0;
	initArrChar(color, 8);

	if (memcmp(userInput, "_depth", strlen("minimax_depth")) == 0){
		x = userInput[strlen("minimax_depth")] - '0';
		miniDepth(x);
	}
	else if (memcmp(userInput, "user_color", strlen("user_color")) == 0){
		strncpy(color, strtok(userInput, " "),  8);
		userColor(color);
	}
	else if (memcmp(userInput, "clear", strlen("clear")) == 0){
		clear(&GAME_BOARD);
	}
	else if (memcmp(userInput, "rm", strlen("rm")) == 0){

		xValue= strtok(userInput, " <,>");   /*sivan - what happened if the row is 10?*/
		x = xValue[0] - '0';
		yValue = strtok(NULL, " <,>");
		y = yValue[0] - 1;

		removeLoc(x, y);
	}
	else if (memcmp(userInput, "set", strlen("set")) == 0){    /* - add the set parsing*/




			xValue= strtok(userInput, " <,>");  /*will take the "set"*/
			xValue= strtok(NULL, " <,>");     /*will take the col*/
			x = xValue[0] - 'a';
			yValue = strtok(NULL, " <,>");
			if(yValue[0] == '1' && yValue[1] == '0'){
				y = 10;
			}
			else{
				y = yValue[0] - '0'- 1;
			}

			strncpy(color,strtok(NULL, " <,>"), 8);   /*add the strtok to the color var*/

			type = strtok(NULL, " <,>");	/*enter b value to type*/

			setLoc(x, y, color, type);
		}
	else if (memcmp(userInput, "print", strlen("print")) == 0){
		print_board(GAME_BOARD.board);
	}
	else if (memcmp(userInput, "quit", strlen("quit")) == 0){
		quit();
	}
	else if (memcmp(userInput, "start", strlen("start")) == 0){
		start(&GAME_BOARD);
	}

}


int miniDepth(int x){
	if ((x < 1) || (x > 6)){
		printf(WRONG_MINIMAX_DEPTH);
		depth = 1;
	}
	else{
		depth = x;
	}
	return depth;
}

void userColor(char* tempColor){
	if (strcmp(tempColor,"black") == 0){
		whitePlayer = 0;
	}
}

void clear(boardState_t* boardState){
	int i,j;
	for(i = 0; i < BOARD_SIZE; ++i){
		for(j = 0; j < BOARD_SIZE; ++j){

			boardState->board[i][j] = EMPTY;
		}
	}
	boardState->numberWM = 0;
	boardState->numberWK = 0;
	boardState->numberBM = 0;
	boardState->numberBK = 0;
}

void removeLoc(int x, int y){   /*moria looking at the calling func- do y as x*/

	if(x < 0 || x > 9){
		printf(WRONG_POSITION);
	}
	else if(y < 0 || y > 9){
		printf(WRONG_POSITION);
	}
	else if((x+y)%2 != 0){
		printf(WRONG_POSITION);
	}
	else{
		if(GAME_BOARD.board[x][y] == WHITE_M){
			GAME_BOARD.numberWM -= 1;
		}
		else if(GAME_BOARD.board[x][y] == WHITE_K){
			GAME_BOARD.numberWK -= 1;
		}
		else if(GAME_BOARD.board[x][y] == BLACK_M){
			GAME_BOARD.numberBM -= 1;
		}
		else if(GAME_BOARD.board[x][y] == BLACK_K){
			GAME_BOARD.numberBK -= 1;
		}
		GAME_BOARD.board[x][y] = EMPTY;
	}
}

void setLoc(int x, int y, char* color, char* type){
	loc_t loc;
	locInitiation(&(loc));

	loc.col = x;
	loc.row = y;

	if(x < 0 || x > 9){
		printf(WRONG_POSITION);
	}
	else if(y < 0 || y > 9){
		printf(WRONG_POSITION);
	}
	else if(whiteSquare(loc)){
		printf(WRONG_POSITION);
	}
	else{
		if(memcmp(color, "white", strlen("white")) == 0){
			if (*type == 'm'){
				GAME_BOARD.board[x][y] = WHITE_M;
				GAME_BOARD.numberWM += 1;
			}
			else{
				GAME_BOARD.board[x][y] = WHITE_K;
				GAME_BOARD.numberWK += 1;
			}
		}
		else{					/*color entered is black*/
			if (*type == 'm'){
				GAME_BOARD.board[x][y] = BLACK_M;
				GAME_BOARD.numberBM += 1;
			}
			else{
				GAME_BOARD.board[x][y] = BLACK_K;
				GAME_BOARD.numberBK += 1;
			}
		}
	}
}

void setLocDuringGame(int x, int y, char* color, char* type, boardState_t* boardState){
	if(memcmp(color, "white", strlen("white")) == 0){
		if(y == 9){	/*white player reached to the end of board*/
			boardState->board[x][y] = WHITE_K;
			boardState->numberWK += 1;
		}
		else{			/*didn't reach to the end of board*/
			if (*type == 'm'){
				boardState->board[x][y] = WHITE_M;
				boardState->numberWM += 1;
			}
			else{
				boardState->board[x][y] = WHITE_K;
				boardState->numberWK += 1;
			}
		}
	}
	else{		/*color entered is black*/
		if(y == 0){	/*black player reached to the end of board*/
			boardState->board[x][y] = BLACK_K;
			boardState->numberBK += 1;
		}
		else{			/*didn't reach to the end of board*/
			if (*type == 'm'){
				boardState->board[x][y] = BLACK_M;
				boardState->numberBM += 1;
			}
			else{
				boardState->board[x][y] = BLACK_K;
				boardState->numberBK += 1;
			}
		}
	}
}

void removeLocDuringGame(int x, int y, boardState_t* boardState){
	if(boardState->board[x][y] == WHITE_M){
		boardState->numberWM -= 1;
	}
	else if(boardState->board[x][y] == WHITE_K){
		boardState->numberWK -= 1;
	}
	else if(boardState->board[x][y] == BLACK_M){
		boardState->numberBM -= 1;
	}
	else if(boardState->board[x][y] == BLACK_K){
		boardState->numberBK -= 1;
	}
	boardState->board[x][y] = EMPTY;
}
int whiteSquare(struct location loc){							/*returns 1 if white else 0*/
	if ((((int)loc.col - 97) + (loc.row - 1)) % 2 == 0){
		return 0;
	}
	else{
		return 1;
	}
}


void quit(){
	exit(0);
}

void start(struct boardState* gameBoard)
{
	int emptyBoard, oneColorDiscks, moreThen20;

	emptyBoard = boardIsEmpty(gameBoard);
	oneColorDiscks = onlyOneColorDiscks(gameBoard);
	moreThen20 = moreThen20ColorDicks(gameBoard);
	if (emptyBoard || oneColorDiscks || moreThen20)	/*initialization is NOT OK*/
	{
		printf(WROND_BOARD_INITIALIZATION);
	}
	else
	{																/*initialization is OK*/
		SettingStateIsOn = 0;
		gameIsOn = 1;
		gameState();
	}
}

int boardIsEmpty(struct boardState* gameBoard)			/*return 1 if empty and 0 otherwise*/
{
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (GAME_BOARD.board[j][i] != EMPTY)
			{
				return 0;
			}
		}
	}
	return 1;
}


int onlyOneColorDiscks(struct boardState* gameBoard){	/*return 0 if more then 2 colors, else 1*/
	char* color = "color";
	int i,j;
	for(i = 0; i < BOARD_SIZE; ++i){
		for(j = 0; j < BOARD_SIZE; ++j){
			if(gameBoard->board[j][i] == WHITE_M || gameBoard->board[j][i] == WHITE_K){	/*dicks are white*/
				if(strcmp(color, "BLACK")){
					return 0;
				}
				else{	/*If color== NULL or color == WHITE*/
					strcpy(color,"WHITE");
				}
			}
			else if(gameBoard->board[j][i] == BLACK_M || gameBoard->board[j][i] == BLACK_K){	/*dicks are black*/
				if(memcmp(color, "WHITE", strlen("WHITE"))){
					return 0;
				}
				else{	/*If color== NULL or color == BLACK*/
					strcpy(color,"BLACK");
				}
			}
		}
	}
	return 1;
}
int moreThen20ColorDicks(struct boardState* gameBoard){	/*return 1 if there are more then 20 dicks of the same color*/
	int i,j;
	int WD = 0, BD = 0;

	for(i = 0; i < BOARD_SIZE; ++i){
		for(j = 0; j < BOARD_SIZE; ++j){
			if(gameBoard->board[j][i] == WHITE_M || gameBoard->board[j][i] == WHITE_K){
				WD += 1;
				if (WD > 20){
					return 1;
				}
			}
			if(gameBoard->board[j][i] == BLACK_M || gameBoard->board[j][i] == BLACK_K){
				BD += 1;
				if (BD > 20){
					return 1;
				}
			}
		}
	}
	return 0;
}


/*GET THE USER'S INPUT*/

char* getInput(FILE* fp, size_t strSize){

	char *tmpStr = 0, *input = 0;
	char tmpChar;
	size_t len = 0;

	tmpStr = (char*) malloc(sizeof(char)*strSize);	/*v*/
	if (!tmpStr){
		perror_message("getInput");
		quit();
	}
	initArrChar(tmpStr, sizeof(char)*strSize);
	while (EOF != (tmpChar = fgetc(fp)) && tmpChar != '\n')
	{
		tmpStr[len++] = tmpChar;
		if (len == strSize)
		{
			tmpStr = (char*) realloc(tmpStr, sizeof(char)*(strSize + 10));
			if (!tmpStr){
				perror_message("getInput");
				quit();
			}
		}
	}
	tmpStr[len++] = '\0';
	input = (char*) (realloc(tmpStr, sizeof(char)*len));
	return input;
}



/*PARSE THE COMMAND*/

void userCommand(char* userInput){			/*parse the user command and send it to the relevand function*/

	char *pathIfMove = 0;

	if (memcmp(userInput, "move", 4) == 0){    /*the user's input is a move*/
		pathIfMove = strchr (userInput, '<');   /*will return from < and on*/
		if (!pathIfMove){
			print_message(ILLEGAL_COMMAND);
			userTurn(); /*back to the userTurn func*/
		}
		else{
			checkMoveAndSet(pathIfMove);
		}

	}

	else if (memcmp(userInput, "get_moves", 9) == 0){    /*the user asked to get his possible moves */
		getUserMoves();
		userTurn();
	}

	else if (memcmp(userInput, "quit", 4) == 0){   /*the user want to quit the game*/
		quit();
	}

	else{         /*the user input an illegal command*/
		print_message(ILLEGAL_COMMAND);
		userTurn(); /*back to the userTurn func*/
	}
}



/*CHECK IF THE MOVE VALID, set if is*/

void checkMoveAndSet(char* moveCommand){      /*will get the path, without "move". will check if the move is legal. if so- will set*/
	move_t userMove;
	int isValidPosition, theLocContainTheColor, isLegalMove;

	moveInitiation(&(userMove));
	userMove = createMoveByCommand(moveCommand);   /*the command become a move_t*/

	isValidPosition = checkPosition(userMove);    /*check if every position in the command is valid on the board*/

	if (!isValidPosition){        /*contain an un-valid position*/
		print_message(WRONG_POSITION);
		freeMT(userMove.next);
		userTurn();   /*go back to the userTurn function*/
	}

	else{    /*all the positions are valid*/

		theLocContainTheColor = checkContainTheColor(userMove);    /*check if position <x,y> (the first) contain a disc of the user's color */

		if (!theLocContainTheColor){                    /*<x,y> not contain user's disc*/
			print_message (DOES_NOT_CONTAIN);
			freeMT(userMove.next);
			userTurn();   /*go back to the userTurn function*/
		}

		else{                            /*<x,y> contain user's disc*/

			isLegalMove = checkIfLegalMove(userMove);    /*check if the move is legal*/

			if (!isLegalMove){         /*not legal move*/
				print_message(ILLEGAL_MOVE);
				freeMT(userMove.next);
				userTurn();   /*go back to the userTurn function*/
			}

			else{                                       /*the move is legal :)*/
				changeBoardByMove(&GAME_BOARD, userMove);
				freeMT(userMove.next);  /*moria*/
				endTurn();
			}
		}

	}
}



/*GET COMMAND STRING, RETURN MOVE_T*/

move_t createMoveByCommand(char* moveCommand){  /*will get the command without "move"*/

	const char startLoc[2] = "<";
	char *tmpLoc = NULL;
	int tmpRow;
	char tmpCol;

	move_t *beforeMove = NULL, *newMove = NULL;
	move_t firstMove;
	int thereIsAFirst = 0;

	moveInitiation(&(firstMove));
	tmpLoc = strtok(moveCommand, startLoc);

	while (tmpLoc != NULL){
		tmpCol = tmpLoc[0];
		tmpRow = tmpLoc[2] - 48;
		if (tmpLoc[3] == '0' && tmpLoc[2] == '1'){    /*if the row is 10*/
			tmpRow = 10;
		}

		newMove = (move_t*) malloc(sizeof(move_t));		/*V*/
		if(!newMove){
			perror_message("createMoveByCommand");
			quit();
		}

		moveInitiation(newMove);

		newMove->curr.col = tmpCol;
		newMove->curr.row = tmpRow;


		if (!thereIsAFirst){         /*this is the first move in the linked list*/
			firstMove = *newMove;
			beforeMove = &firstMove;
			free(newMove);
			thereIsAFirst = 1;
		}

		else{                                /*the movebefore's next will be the new move, and beforeMove will point now to the new */
			beforeMove->next = newMove;
			beforeMove = beforeMove->next;
		}

		tmpLoc = strtok(NULL, startLoc);
	}

	return firstMove;
}


/*ARE ALL THE POSITIONS IN THE MOVE_T VALID?*/

int checkPosition(move_t userMove){
	move_t* tmpMove = NULL;

	tmpMove = &userMove;

	while (tmpMove != NULL){
		if (!validLoc((char)(tmpMove->curr.col), tmpMove->curr.row)){
			return 0;
		}
		tmpMove = tmpMove->next;
	}

	return 1;
}

int validLoc(char col, int row){
	if ((row > 8) || (row < 1) || (col < 'a') || (col > 'h')){
				return 0;
			}
	return 1;
}


/*DOES THE <X,Y> LOC CONTAINS USER'S DISC?*/

int checkContainTheColor(move_t userMove){

	char charInPosition;

	charInPosition = GAME_BOARD.board[userMove.curr.col-97][userMove.curr.row -1];  /*cause 'a' is 97 value*/

	if (whitePlayer){    /*the user is the white player*/
		if ((charInPosition == WHITE_M) || (charInPosition == WHITE_K)){
			return 1;
		}
	}
	else {         /*the user is the black player*/
		if ((charInPosition == BLACK_M) || (charInPosition == BLACK_K)){
			return 1;
		}
	}
	return 0;
}


/*IS IT A LEGAL MOVE?*/

int checkIfLegalMove(move_t userMove){      /*(checked before if the position is valid and if there is a disc in the start position)*/
	move_t* tmpMove = NULL;

	tmpMove = &userMove;

	if ((GAME_BOARD.board[userMove.curr.col -97][userMove.curr.row -1] == WHITE_M) || (GAME_BOARD.board[userMove.curr.col -97][userMove.curr.row -1] == BLACK_M)){
		if (!containEat(tmpMove->curr, tmpMove->next->curr)){   /*a regular step. no eating*/

			if (!moveDiagonally(tmpMove)){      /*not go diagonally*/
				return 0;
			}
			else if (!canMoveThatWay(tmpMove, 1)){   /*this is a black (white) man and it move up (down), or a king */
				return 0;
			}
			else if ((checkIfEmpty(tmpMove->next->curr)) && (tmpMove->next->next == NULL)){  /*a valid, regular step*/
				return 1;
			}
			else {
				return 0;
				}
		}

		else {  /*probably contain an eating step(s)*/
			while (tmpMove->next != NULL){
				if (!validEating(tmpMove->curr, tmpMove->next->curr)){      /*the eating step is illegal*/
					return 0;
				}
				tmpMove = tmpMove->next;
			}
			return 1;    /*the step is legal*/
		}
	}

	else{  /*king*/
		if (legalKingMove(&userMove) != 0){   /*the first move is legal*/

			if (legalKingMove(&userMove) == 2){   /*the first move is an eating move*/
				if (userMove.next->next != NULL){   /*more than one eating*/
					while (tmpMove != NULL){
						if (!validEating(tmpMove->curr, tmpMove->next->curr)){      /*the eating step is illegal*/
							return 0;
						}
						tmpMove = tmpMove->next;
					}
				return 1;  /*the step is legal*/
				}
				else {
					return 1;
				}
			}
			else if (userMove.next->next == NULL){  /*after the non-eating step, no more step*/
				return 1;
			}
		}
	}
	return 0;
}


int containEat(loc_t currLoc, loc_t afterLoc){     /*get two location: the curr and the loc after the turn. check if eat while move*/
	if (abs(currLoc.row - afterLoc.row) != 1){   /*regular man step*/
		return 1;
	}
	return 0;
}


int moveDiagonally(move_t* move){
	if (abs(move->curr.row - move->next->curr.row) == 1){
		if (abs(move->curr.col - move->next->curr.col) == 1){
			return 1;
		}
		return 0;
	}
	return 0;
}


int canMoveThatWay(move_t *move, int player){   /*check if that player can move up/down. (the move DOES NOT contain an eating)*/

	char currDisc;

	currDisc =  GAME_BOARD.board[move->curr.col -97][move->curr.row -1];
	if ((currDisc == WHITE_K) || (currDisc == BLACK_K)){   /*this is a king, and it can move up and down*/
		return 1;
	}

	else if (player == whitePlayer){    /*this is the white. can move UP*/
		if ((move->curr.row - move->next->curr.row) == -1){ /*go up*/
			return 1;
		}
		return 0;
	}
	else{                           /*this is the black. can move DOWN*/
		if ((move->curr.row - move->next->curr.row) == 1){ /*go up*/
			return 1;
		}
		return 0;
	}

}

int checkIfEmpty(loc_t location){
	if (GAME_BOARD.board[location.col -97][location.row-1] == EMPTY){
		return 1;
	}
	return 0;
}





int validEating(loc_t currLoc, loc_t afterLoc){    /*will get 2 loc_t: before and after eating. will check if the eating step is valid*/
	if (abs(currLoc.row - afterLoc.row) != 2){  /*move more or less then 2 */
		return 0;
	}
	else if (abs(currLoc.col - afterLoc.col) != 2){
		return 0;
	}
	else if (!containComputerDisc(currLoc,afterLoc)){    /*the place not contain a computer disc to eat*/
		return 0;
	}
	return 1;    /*the eating move is valid*/
}


int containComputerDisc(loc_t currLoc, loc_t afterLoc){    /*check if there is a computer disc to eat*/
	int computerRow;
	char computerCol;
	char locDisc;
	char computerDiscMan, computerDiscKing;

	if (currLoc.row < afterLoc.row){          /*find out the location of the computer disc*/
		computerRow = afterLoc.row -1;
	}
	else{
		computerRow = currLoc.row -1;
	}

	if (currLoc.col < afterLoc.col){
		computerCol = afterLoc.col -1;
	}
	else{
		computerCol = currLoc.col -1;
	}

	/*find out what the computer disc is*/
	if (!whitePlayer){                  /*the computer is the white player*/
		computerDiscMan = WHITE_M;
		computerDiscKing = WHITE_K;
	}

	else{                               /*the computer is the black player*/
		computerDiscMan = BLACK_M;
		computerDiscKing = BLACK_K;
	}

	locDisc = GAME_BOARD.board[computerCol-97][computerRow-1];
	if ((locDisc == computerDiscMan) || (locDisc == computerDiscKing)){
		return 1;
	}
	return 0;
}

int legalKingMove(move_t *move){   /*will return 0 if not legal, 1 if legal but not eating, 2 if legal & contains eating*/

	int eat = 0;
	char otherMan, otherKing;
	int startCol;
	int startRow;
	int i, distance;
	loc_t currLoc, afterLoc;

	locInitiation(&(currLoc));
	locInitiation(&(afterLoc));

	currLoc = move->curr;
	afterLoc = move->next->curr;

	startCol = (int) currLoc.col -97;
	startRow = currLoc.row -1;

	distance = abs(currLoc.row - afterLoc.row);

	if ((GAME_BOARD.board[currLoc.col -97][currLoc.row -1] == WHITE_M) ||
		(GAME_BOARD.board[currLoc.col -97][currLoc.row -1] == WHITE_K)){
		otherMan = BLACK_M;
		otherKing = BLACK_K;
	}

	else {
		otherMan = WHITE_M;
		otherKing = WHITE_K;
	}



	if ((currLoc.col < afterLoc.col) && (currLoc.row < afterLoc.row)){   /*0*/
		for (i = 1; i < distance +1; ++i){

			if ((GAME_BOARD.board[startCol + i][startRow +i] == EMPTY) && (!eat)){  /*keep see only empty*/
				continue;
			}

			else if ((GAME_BOARD.board[startCol + i][startRow +i] == otherMan) ||
				(GAME_BOARD.board[startCol + i][startRow +i] == otherKing)){    /*this is an eating!*/
				eat = 1;
			}

			else if ((eat) && (i = distance) && (GAME_BOARD.board[startCol + i][startRow +i] == EMPTY)){  /*eat loop before and now the afterLoc is right after the eating*/
				return 2;
			}
			else {   /*if non of the previous condition is right then the move illegal*/
				return 0;
			}
		}
		return 1; /*regular king move*/
	}

	else if ((currLoc.col > afterLoc.col) && (currLoc.row < afterLoc.row)){   /*1*/

		for (i = 1; i < distance +1; ++i){

			if ((GAME_BOARD.board[startCol - i][startRow +i] == EMPTY) && (!eat)){  /*keep see only empty*/
				continue;
			}

			else if ((GAME_BOARD.board[startCol - i][startRow +i] == otherMan) ||
				(GAME_BOARD.board[startCol - i][startRow +i] == otherKing)){    /*this is an eating!*/
				eat = 1;
			}

			else if ((eat) && (i = distance) && ((GAME_BOARD.board[startCol - i][startRow +i] == EMPTY))){  /*eat loop before and now the afterLoc is right after the eating*/
				return 2;
			}
			else {   /*if non of the previous condition is right then the move illegal*/
				return 0;
			}
		}
		return 1; /*regular king move*/
	}

	else if ((currLoc.col < afterLoc.col) && (currLoc.row > afterLoc.row)){   /*2*/

		for (i = 1; i < distance +1; ++i){

			if ((GAME_BOARD.board[startCol + i][startRow -i] == EMPTY) && (!eat)){  /*keep see only empty*/
				continue;
			}

			else if ((GAME_BOARD.board[startCol + i][startRow -i] == otherMan) ||
				(GAME_BOARD.board[startCol + i][startRow -i] == otherKing)){    /*this is an eating!*/
				eat = 1;
			}

			else if ((eat) && (i = distance) && (GAME_BOARD.board[startCol + i][startRow -i] == EMPTY)){  /*eat loop before and now the afterLoc is right after the eating*/
				return 2;
			}
			else {   /*if non of the previous condition is right then the move illegal*/
				return 0;
			}
		}
		return 1; /*regular king move*/
	}

	else{   /*3*/

		for (i = 1; i < distance +1; ++i){

			if ((GAME_BOARD.board[startCol - i][startRow -i] == EMPTY) && (!eat)){  /*keep see only empty*/
				continue;
			}

			else if ((GAME_BOARD.board[startCol - i][startRow -i] == otherMan) ||
				(GAME_BOARD.board[startCol - i][startRow -i] == otherKing)){    /*this is an eating!*/
				eat = 1;
			}

			else if ((eat) && (i = distance) && (GAME_BOARD.board[startCol - i][startRow -i] == EMPTY)){  /*eat loop before and now the afterLoc is right after the eating*/
				return 2;
			}
			else {   /*if non of the previous condition is right then the move illegal*/
				return 0;
			}
		}
		return 1; /*regular king move*/
	}
}




/*CHANGE BOARD BY MOVE*/

void changeBoardByMove(boardState_t* board, move_t move){   /*will get a POINTER to a boardState and a *LEGAL* move, and change the board*/

	move_t* tmp_move = NULL;

	tmp_move = &move;

	while (tmp_move->next != NULL){

		changeSingleMove(board, tmp_move->curr, tmp_move->next->curr);

		tmp_move = tmp_move->next;
	}
}



void changeSingleMove(boardState_t* board, loc_t currLoc, loc_t afterLoc){

	char discToMove;
	int eatRow;
	int eatCol;

	int startCol;
	int startRow;
	int i;
	int distance;

	char otherMan;
	char otherKing;

	char type;
	char color[8];

	if ((board->board[currLoc.col -97][currLoc.row -1] == WHITE_M) ||
		(board->board[currLoc.col -97][currLoc.row -1] == WHITE_K)){
		otherMan = BLACK_M;
		otherKing = BLACK_K;
	}

	else {
		otherMan = WHITE_M;
		otherKing = WHITE_K;
	}

	distance = abs(currLoc.row - afterLoc.row);


	if (distance >= 2){    /*eat the other playerm. find out the location of the eaten disc*/

		if (((currLoc.col < afterLoc.col) && (currLoc.row < afterLoc.row)) ||
			((currLoc.col < afterLoc.col) && (currLoc.row > afterLoc.row))){   /*0, 2*/
			startCol = currLoc.col -97;
			startRow = currLoc.row -1;
		}

		else{  /*1,3*/
			startCol = afterLoc.col -97;
			startRow = afterLoc.row -1;
		}

		if (((currLoc.col < afterLoc.col) && (currLoc.row < afterLoc.row)) ||
			((currLoc.col > afterLoc.col) && (currLoc.row > afterLoc.row))){    /*0,3*/

			for (i = 1; i < distance; ++i){
				if ((board->board[startCol + i][startRow +i] == otherMan) ||
					(board->board[startCol + i][startRow +i] == otherKing)){
					eatCol  = startCol + i;
					eatRow = startRow +i;
					removeLocDuringGame(eatCol, eatRow, board);
					break;
				}
			}
		}

		else {       /*1,2*/
			for (i = 1; i < distance; ++i){
				if ((board->board[startCol + i][startRow -i] == otherMan) ||
					(board->board[startCol + i][startRow -i] == otherKing)){
					eatCol  = startCol + i;
					eatRow = startRow -i;
					removeLocDuringGame(eatCol, eatRow, board);
					break;
				}
			}
		}
	}


	discToMove = board->board[currLoc.col-97][currLoc.row-1];
	if (discToMove == WHITE_M){
		strncpy(color,"white", 8);
		type = 'm';
	}

	else if (discToMove == WHITE_K){
		strncpy(color,"white", 8);
		type = 'k';
	}

	else if (discToMove == BLACK_M){
		strncpy(color,"black", 8);
		type = 'm';
	}

	else {                        /*discToMove == BLACK_K*/
		strncpy(color,"black", 8);
		type = 'k';
	}

	/*delete from currLoc*/
	removeLocDuringGame(currLoc.col-97, currLoc.row-1, board);

	/*set to afterLoc;*/
	setLocDuringGame((int)afterLoc.col-97, afterLoc.row-1, color, &type, board);

}

/*END USER'S TURN*/

void endTurn(){
	int win;

	print_board(GAME_BOARD.board);
	win = checkIfWin(&GAME_BOARD,1);   /*check if the user win*/

	if (win){   /*there is a winning :)*/
		if (whitePlayer){          /*the user is white*/
			print_message(WHITE_WIN);
		}
		else{
			print_message(BLACK_WIN);
		}

		gameIsOn = 0;     /*end the game*/
		return;
	}

	else{         /*no winning. now the computer play*/
		currPlayer = 0;
		return;
	}
}


/*DO WE HAVE A WINNING?*/

int checkIfWin(boardState_t* board, int player){     /*player=1 -> user, player=0 -> computer. return 1: the player won*/

	int secondPlayer, canMove;

	secondPlayer = abs(player -1);

	if (whitePlayer == secondPlayer){     /*the otherPlayer is white*/
		if ((board->numberWM == 0) && ((board->numberWK  == 0))){   /*the otherPlayer have no discs*/
			return 1;             /*the player won :)*/
		}
	}

	else{                        /*the otherPlayer is black*/
		if ((board->numberWM  == 0) && ((board->numberBK  == 0))){   /*the otherPlayer have no discs*/
			return 1;             /*the player won :)*/
		}
	}

	canMove = checkIfCanMove(board->board, secondPlayer);

	if (!canMove){     /*other player can't do another step*/
		return 1;
	}



	return 0;    /*no winning*/
}


int checkIfCanMove(char board[BOARD_SIZE][BOARD_SIZE], int player){           /*check if the player we got can move. 1- can, 0- cant*/
	char playerMan, playerKing;
	int canMoveDisc = 0;
	int playerColor;
	int i,j;

	if (whitePlayer == player){    /*the player is white*/
		playerColor = 0;
		playerMan = WHITE_M;
		playerKing = WHITE_K;
	}
	else{                        /*the player is black*/
		playerColor = 1;
		playerMan = BLACK_M;
		playerKing = BLACK_K;
	}


	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if ((i + j) % 2 == 0){
				if ((board[i][j] == playerMan) || (board[i][j] == playerKing)){
					canMoveDisc = checkMoveDisc(board,i,j, playerColor);
					if (canMoveDisc){    /*there is at least one disc that can move*/
						return 1;
					}
				}
			}
		}
	}

	return 0;
}


int checkMoveDisc(char board[BOARD_SIZE][BOARD_SIZE],int i,int j, int color){ /*color 0-> white, 1-> black*/

	char otherMan, otherKing;

	if (!color){       /*will check for the white (can move UP)*/

		/*check if can do a regular non-eating move*/
		if ((validLoc((char)(i+98), j+1) && (board[i+1][j+1] == EMPTY)) ||
				(validLoc((char)(i+96), j+1) && (board[i-1][j+1] == EMPTY))){
			return 1;
		}
		else if (board[i][j] == WHITE_K){                               /*add more checking for the king: check also down */
			if ((validLoc((char)(i+96), j-1) && (board[i-1][j-1] == EMPTY)) ||
					(validLoc((char)(i+98), j-1) && (board[i+1][j-1] == EMPTY))){
				return 1;
			}
		}

		else {
			otherMan = BLACK_M;
			otherKing = BLACK_K;
		}
	}

	else{            /*will check for the black (can move DOWN)*/
		/*check if can do a regular not-eatting move*/
		if ((validLoc((char)(i+96), j-1) && (board[i-1][j-1] == EMPTY)) ||
				(validLoc((char)(i+98), j-1) &&(board[i+1][j-1] == EMPTY))){
			return 1;
		}

		else if (board[i][j] == BLACK_K){                      /*add more checking for the king: check also up */
			if ((validLoc((char)(i+98), j+1) && (board[i+1][j+1] == EMPTY)) ||
					(validLoc((char)(i+96), j+1) && (board[i-1][j+1] == EMPTY))){
				return 1;
			}
		}

		else {
			otherMan = WHITE_M;
			otherKing = WHITE_K;
		}
	}


	/*start check if can eat
	 * (the possibility for the king to eat anyone on his way has been checked while checking if the next loc is empty)*/

	/*0*/
	if (validLoc((char)(i+97+2),j+2+1)){   /*cause if the loc after eating is valid, so the eating place is valid too*/
		if (((board[i+1][j+1] == otherMan) || (board[i+1][j+1] == otherKing)) && (board[i+2][j+2] == EMPTY)){
				return 1;
			}
	}

	/*1*/
	else if (validLoc((char)(i+97-2),j+1+2)){
		if (((board[i-1][j+1] == otherMan) || (board[i-1][j+1] == otherKing)) && (board[i-2][j+2] == EMPTY)){
				return 1;
			}
	}

	/*2*/
	else if (validLoc((char)(i+97+2),j+1-2)){
		if (((board[i+1][j-1] == otherMan) || (board[i+1][j-1] == otherKing)) && (board[i+2][j-2] == EMPTY)){
				return 1;
			}
	}

	/*3*/
	else if (validLoc((char)(i+97-2),j+1-2)){
		if (((board[i-1][j-1] == otherMan) || (board[i-1][j-1] == otherKing)) && (board[i-2][j-2] == EMPTY)){
				return 1;
			}
	}
	return 0;

}



/*RETURN CHAR BY LOCATION*/

/*in GAME_BOARD*/
char getDiscByLocationInGameBoard(loc_t loc){
	int rowLoc, colLoc;
	char discInPlace;

	rowLoc = loc.row -1;
	colLoc = loc.col -97;

	discInPlace = GAME_BOARD.board[rowLoc][colLoc];

	return discInPlace;
}

/* in OTHER board*/
char getDiscByLocation(char board[BOARD_SIZE][BOARD_SIZE], loc_t loc){
	int rowLoc, colLoc;
	char discInPlace;

	rowLoc = loc.row -1;
	colLoc = loc.col -97;

	discInPlace = board[rowLoc][colLoc];

	return discInPlace;
}



/*PRINT TO THE USER ALL HIS POSSIBLE MOVES*/

void getUserMoves(){
	struct possibleMove *userPossibleMoves = NULL;
	userPossibleMoves = getAllPossibleMoves(GAME_BOARD.board,1);  /*get a linked list of the moves*/
	printPossibleMoves(userPossibleMoves);   /*print it*/
	freePM(userPossibleMoves);    /*: to check!!!!!*/
	return;
}


void printPossibleMoves(possibleM_t *possibleMoves){
	possibleM_t* currMove = NULL;

	currMove = possibleMoves;

	while (currMove != NULL){    /*go each move in the array, and sent it to the func that print a single move*/
		printMove(&(currMove->move));
		currMove = currMove->next;
	}
}


void printMove(move_t *move){               /*print a SINGLE move*/
	move_t* currStep = NULL;

	printf("<%c,%d> to ", move->curr.col, move->curr.row);

	currStep = move->next;

	while (currStep != NULL){
		printf("<%c,%d>", currStep->curr.col, currStep->curr.row);
		currStep = currStep->next;
	}
	printf("\n");
}





/*PRINT THE BOARD*/

void print_line(){
	int i;

	printf("  |");
	for (i = 1; i < BOARD_SIZE*4; i++){
		printf("-");
	}
	printf("|\n");
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i,j;
	print_line();
	for (j = BOARD_SIZE-1; j >= 0 ; j--)
	{
		printf((j < 9 ? " %d" : "%d"), j+1);
		for (i = 0; i < BOARD_SIZE; i++){
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++){
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
	return;
}


/*INIT A BOARD*/

void init_board(char board[BOARD_SIZE][BOARD_SIZE]){
	int i,j;
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if ((i + j) % 2 == 0){
				if (j <= 3){
					board[i][j] = WHITE_M;
				}
				else if (j >= 6){
					board[i][j] = BLACK_M;
				}
				else{
					board[i][j] = EMPTY;
				}
			}
			else{
				board[i][j] = EMPTY;
			}
		}
	}

}




struct possibleMove* getAllPossibleMoves(char board[BOARD_SIZE][BOARD_SIZE], int player){

	int i,j;
	int playerColor;

	struct location currLoc;
	struct possibleMove* firstEmptyNode = 0;
	struct possibleMove* pointTmpMove = 0;
	struct possibleMove* firstStep = 0;
	struct possibleMove* result = 0;

	locInitiation(&currLoc);

	firstEmptyNode = (struct possibleMove*)malloc(sizeof(struct possibleMove));	/*V*/
	if(!firstEmptyNode){
		perror_message("getAllPossibleMoves");
		quit();
	}
	posMovInitiation(firstEmptyNode);

	pointTmpMove = firstEmptyNode;				/*can Delete because initiation is doubled and used only at the end of func*/


	playerColor = getPlayerColor(player);


	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if (isPlayer(board[i][j], playerColor)){
				currLoc.col = (char) i +97;
				currLoc.row = j +1;

				/*Setting first position*/
				firstStep = (struct possibleMove*)malloc(sizeof(struct possibleMove)); /*in use in the linked list*/
				if(!firstStep){
					perror_message("getAllPossibleMoves");
					quit();
				}

				posMovInitiation(firstStep);
				firstStep->move.curr = currLoc;


				if (isPawn(board[i][j])){
					getPawnMoves(board, firstStep, player);
				}

				else if (isBishop(board[i][j])){
					getBishopMoves(board, firstStep, player);
				}

				else if (isKnight(board[i][j])){
					getKnightMoves(board, firstStep, player);
				}

				else if (isRook(board[i][j])){
					getRookMoves(board, firstStep, player);
				}

				else if (isQueen(board[i][j])){
					getQueenMoves(board, firstStep, player);
				}

				else {   //it's a king
					getKingMoves(board, firstStep, player);
				}


				if (firstStep->next != NULL){  /*there is at least one move*/
					if (firstEmptyNode->next == NULL){
						firstEmptyNode->next = firstStep->next;
					}
					else{                             /*add to the big moves linked-list*/
						pointTmpMove = firstStep;
						while (pointTmpMove->next != NULL){
							pointTmpMove = pointTmpMove->next;
						}
						pointTmpMove->next = firstEmptyNode->next;
						firstEmptyNode->next = firstStep->next;
					}
				}
			}
		}
	}

	//addCastlingMove(board,firstEmptyNode,player);  //TODO
	result = firstEmptyNode->next;
	firstEmptyNode->next = NULL;
	freePM(firstEmptyNode);
	return result;			 /*if there isn't a possible move, will return NULL*/ /*free result from the calling function*/

}


void getPawnMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){  //HAYAL
	int playerColor;
	loc_t tmpNewLoc;

	locInitiation(&(tmpNewLoc));

	playerColor = getPlayerColor(player);

	if (whitePlayer == player){ /*move UP. add only 0,1,4 steps*/
		tmpNewLoc.row = firstStep->move.curr.row +1;    /*+*/
	}
	else{                         /*black. move DOWN. add only 2,3,6 steps*/
		tmpNewLoc.row = firstStep->move.curr.row -1;    /*-*/
	}

	tmpNewLoc.col = (char) firstStep->move.curr.col; /*will go up or down -- regular step*/

	if ((validLoc((char)tmpNewLoc.col, tmpNewLoc.row)) && (board[tmpNewLoc.col-97][tmpNewLoc.row-1] == EMPTY)){   /*that step in the board and empty*/

		addNewStep(firstStep, tmpNewLoc);  /*add regular step*/
	}

	tmpNewLoc.col = (char) firstStep->move.curr.col +1; /*check if can eat right*/

	if ((validLoc((char)tmpNewLoc.col, tmpNewLoc.row)) && (isOtherPlayer(board[tmpNewLoc.col-97][tmpNewLoc.row-1], playerColor))){   /*that place in the board contains piece to eat*/

		addNewStep(firstStep, tmpNewLoc);   /*add right eat step*/
	}

	tmpNewLoc.col = (char) firstStep->move.curr.col - 1; /*check if can eat left*/
	if ((validLoc((char)tmpNewLoc.col, tmpNewLoc.row)) && (isOtherPlayer(board[tmpNewLoc.col-97][tmpNewLoc.row-1], playerColor))){   /*that place in the board contains piece to eat*/

		addNewStep(firstStep, tmpNewLoc);  /*add left eat step*/
	}
}


void getBishopMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){   //RATZ
	int i, j;
	int playerColor;
	loc_t tmpNewLoc;
	loc_t *currLoc = NULL;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);

	playerColor = getPlayerColor(player);

	/*add all the 4, with every possible length*/
	for (i=0; i<4; ++i){

		if (i == 0){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 1){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 2){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else{  /*i = 3*/
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}
	}
}


void getRookMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){   //TSARIACH
	int i, j;
	int playerColor;
	loc_t tmpNewLoc;
	loc_t *currLoc = NULL;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);

	playerColor = getPlayerColor(player);

	/*add all the 4, with every possible length*/
	for (i=4; i<8; ++i){

		if (i == 4){  //UP
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 5){   //LEFT
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 6){   //DOWN
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else{  /*i = 7. RIGHT*/
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}
	}
}


void getKnightMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){  //PARASH
	int i;
	loc_t tmpNewLoc;
	loc_t *currLoc = NULL;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);


	/*add all the 4, with every possible length*/
	for (i=0; i<4; ++i){

		if (i == 0){
			if (validLoc((char)(currLoc->col + 1), currLoc->row + 2)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 1 -97][currLoc->row + 2 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 1);
				tmpNewLoc.row = currLoc->row + 2;
				addNewStep(firstStep, tmpNewLoc);
			}
			if (validLoc((char)(currLoc->col + 2), currLoc->row + 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 2 -97][currLoc->row + 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 2);
				tmpNewLoc.row = currLoc->row + 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 1){
			if (validLoc((char)(currLoc->col - 1), currLoc->row + 2)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 1 -97][currLoc->row + 2 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 1);
				tmpNewLoc.row = currLoc->row + 2;
				addNewStep(firstStep, tmpNewLoc);
			}
			if (validLoc((char)(currLoc->col - 2), currLoc->row + 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 2 -97][currLoc->row + 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 2);
				tmpNewLoc.row = currLoc->row + 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 2){
			if (validLoc((char)(currLoc->col + 1), currLoc->row - 2)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 1 -97][currLoc->row - 2 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 1);
				tmpNewLoc.row = currLoc->row - 2;
				addNewStep(firstStep, tmpNewLoc);
			}
			if (validLoc((char)(currLoc->col + 2), currLoc->row - 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 2 -97][currLoc->row - 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 2);
				tmpNewLoc.row = currLoc->row - 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else{  /*i = 3*/
			if (validLoc((char)(currLoc->col - 1), currLoc->row - 2)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 1 -97][currLoc->row - 2 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 1);
				tmpNewLoc.row = currLoc->row - 2;
				addNewStep(firstStep, tmpNewLoc);
			}
			if (validLoc((char)(currLoc->col - 2), currLoc->row - 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 2 -97][currLoc->row - 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 2);
				tmpNewLoc.row = currLoc->row - 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}
	}
}

void getQueenMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){   //QUEEN
	int i, j;
	int playerColor;
	loc_t tmpNewLoc;
	loc_t *currLoc = NULL;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);

	playerColor = getPlayerColor(player);

	/*add all the 4, with every possible length*/
	for (i=0; i<8; ++i){

		if (i == 0){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 1){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 2){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i==3){
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 4){  //UP
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col), currLoc->row + j)
						&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row + j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col);
					tmpNewLoc.row = currLoc->row + j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col -97][currLoc->row + j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 5){   //LEFT
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col - j), currLoc->row)
						&& (emptyOrEatLoc(board[(int)currLoc->col - j -97][currLoc->row -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col - j);
					tmpNewLoc.row = currLoc->row;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col - j -97][currLoc->row -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else if (i == 6){   //DOWN
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col), currLoc->row - j)
						&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row - j -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col);
					tmpNewLoc.row = currLoc->row - j;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col -97][currLoc->row - j -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}

		else{  /*i = 7. RIGHT*/
			for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

				if (validLoc((char)(currLoc->col + j), currLoc->row)
						&& (emptyOrEatLoc(board[(int)currLoc->col + j -97][currLoc->row -1], player))){  /*check validation of the loc*/

					tmpNewLoc.col = (char)(currLoc->col + j);
					tmpNewLoc.row = currLoc->row;
					addNewStep(firstStep, tmpNewLoc);
				}
				else{  /*do not continue to add new move from that loc*/
					break;
				}
				if (isOtherPlayer(board[(int)currLoc->col + j -97][currLoc->row -1], playerColor)){  //because we got to otherPlayer and it can't jump
					break;
				}
			}
		}
	}
}


void getKingMoves(char board[BOARD_SIZE][BOARD_SIZE],possibleM_t* firstStep, int player){   //KING
	int i;
	loc_t tmpNewLoc;
	loc_t *currLoc = NULL;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);


	/*add all the 4, with every possible length*/
	for (i=0; i<8; ++i){

		if (i == 0){
			if (validLoc((char)(currLoc->col + 1), currLoc->row + 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 1 -97][currLoc->row + 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 1);
				tmpNewLoc.row = currLoc->row + 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 1){
			if (validLoc((char)(currLoc->col - 1), currLoc->row + 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 1 -97][currLoc->row + 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 1);
				tmpNewLoc.row = currLoc->row + 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 2){
			if (validLoc((char)(currLoc->col + 1), currLoc->row - 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 1 -97][currLoc->row - 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 1);
				tmpNewLoc.row = currLoc->row - 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i==3){
			if (validLoc((char)(currLoc->col - 1), currLoc->row - 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 1 -97][currLoc->row - 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 1);
				tmpNewLoc.row = currLoc->row - 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 4){  //UP
			if (validLoc((char)(currLoc->col), currLoc->row + 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row + 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col);
				tmpNewLoc.row = currLoc->row + 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 5){   //LEFT
			if (validLoc((char)(currLoc->col - 1), currLoc->row)
					&& (emptyOrEatLoc(board[(int)currLoc->col - 1 -97][currLoc->row -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col - 1);
				tmpNewLoc.row = currLoc->row;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else if (i == 6){   //DOWN
			if (validLoc((char)(currLoc->col), currLoc->row - 1)
					&& (emptyOrEatLoc(board[(int)currLoc->col -97][currLoc->row - 1 -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col);
				tmpNewLoc.row = currLoc->row - 1;
				addNewStep(firstStep, tmpNewLoc);
			}
		}

		else{  /*i = 7. RIGHT*/
			if (validLoc((char)(currLoc->col + 1), currLoc->row)
					&& (emptyOrEatLoc(board[(int)currLoc->col + 1 -97][currLoc->row -1], player))){  /*check validation of the loc*/

				tmpNewLoc.col = (char)(currLoc->col + 1);
				tmpNewLoc.row = currLoc->row;
				addNewStep(firstStep, tmpNewLoc);
			}
		}
	}
}


int emptyOrEatLoc(char piece, int player){
	int playerColor;

	playerColor = getPlayerColor(player);

	if (piece == EMPTY){     //the square is empty
		return 1;
	}

	else if (isOtherPlayer(piece, playerColor)){   //cat eat
		return 1;
	}

	return 0;
}


void addNewStep(possibleM_t* firstStep, loc_t loc){

	possibleM_t* newStep = NULL;
	move_t* newMove = NULL;

	newStep = (possibleM_t*)malloc(sizeof(possibleM_t));	/*in use with the linked list*/
	if(!newStep){
		perror_message("addNewStep");
		quit();
	}
	posMovInitiation(newStep);

	newStep = copyPossibleMove(firstStep);
	newMove = (struct move*)malloc(sizeof(struct move));					/*in use with the linked list*/
	if(!newMove){
		perror_message("addNewStep");
		quit();
	}

	moveInitiation(newMove);
	newMove->curr = loc;   /*new move have the new Loc*/
	newMove->castling = 0;   /*a castling move won't be added here*/

	newStep->move.next = newMove;   /*newStep have the new move*/

	//newStep->check = isContainsCheck(newMove);                            /*TODO: WRITE THAT FUNCTION*/

	newStep->next = firstStep->next;  /*connect the newStep to the list*/
	firstStep->next = newStep;
}



/*BEEN BEFORE*/

int beenBefore(move_t *move, struct location *result, int kingPlayer){   /*get move_t and loc_t and check if move_t already contain the specific loc_t*/
	move_t* tmpMove = NULL;
	move_t* tmpMoveNext = NULL;

	tmpMove = move;
	tmpMoveNext = move->next;

	while(tmpMoveNext != NULL){   /*cause only if so we can do the checking 'between'*/
		if ((tmpMove->curr.col == result->col) && (tmpMove->curr.row == result->row)){
			return 1;
		}
		else if(locIsBetween(tmpMove, tmpMoveNext, result)){   /*go to 'between' check - check the possibily of a king that eat in a long length*/
			return 1;
		}
		else{
			tmpMove = tmpMove->next;
			tmpMoveNext = tmpMoveNext->next;
		}
	}

	return 0;
}


int locIsBetween(move_t *move, move_t *moveNext, struct location *result){

	char startCol;
	int startRow;

	int i, distance;

	distance = abs(move->curr.row - moveNext->curr.row);

	/*find the start loc (0&3 will be checked together. if 0- the start will be move, if 3- the start will be moveNext.
			      1&2 will be checked together. if 2- the start will be move, if 1- the start will be moveNext.)*/

	if (((move->curr.col < moveNext->curr.col) && (move->curr.row < moveNext->curr.row)) ||
		((move->curr.col > moveNext->curr.col) && (move->curr.row > moveNext->curr.row))){  /*0 or 3*/

		if (move->curr.col < moveNext->curr.col){  /*0*/
			startCol = move->curr.col;
			startRow = move->curr.row;
		}
		else {                  /*3*/
			startCol = moveNext->curr.col;
			startRow = moveNext->curr.row;
		}

		for (i = 0; i < distance +1; ++i){
			if ((startCol + i == result->col) && (startRow + i == result->row)){
				return 1;
			}
		}
		return 0;

	}

	else {     /*1 or 2*/
		if (move->curr.col < moveNext->curr.col){  /*2*/
			startCol = move->curr.col;
			startRow = move->curr.row;
		}
		else {                  /*1*/
			startCol = moveNext->curr.col;
			startRow = moveNext->curr.row;
		}

		for (i = 0; i < distance +1; ++i){
			if ((startCol + i == result->col) && (startRow - i == result->row)){
				return 1;
			}
		}
		return 0;
	}
}


struct possibleMove* copyPossibleMove(struct possibleMove* old)	/*copy the sub-linked list*/
{
	struct possibleMove* newPossibleMove = NULL;   /*NEW possibleM*/

	struct move* tmpMoveOld = NULL;    /*pointer to tmp move in the OLD */
	struct move* tmpMoveNew = NULL;    /*pointer to tmp move in the NEW */


	newPossibleMove = (struct possibleMove*)malloc(sizeof(struct possibleMove));	/*in use in the linked list*/

	if(!newPossibleMove){
		perror_message("copyPossibleMove");
		quit();
	}
	posMovInitiation(newPossibleMove);

	/*start copy the old to the new*/
	//newPossibleMove->eatCnt = old->eatCnt;
	newPossibleMove->move = old->move;

	/*declare the pointers*/
	tmpMoveOld = old->move.next;
	tmpMoveNew = newPossibleMove->move.next;

	while (tmpMoveOld != NULL){  /*there is still some node that needed to be copied*/

		tmpMoveNew = (struct move*)malloc(sizeof(struct move));	/*in use in the linked list*/

		if(!(tmpMoveNew)){
			perror_message("copyPossibleMove");
			quit();
		}
		moveInitiation(tmpMoveNew);

		tmpMoveNew->curr.col = tmpMoveOld->curr.col;
		tmpMoveNew->curr.row = tmpMoveOld->curr.row;

		tmpMoveNew = tmpMoveNew->next;   /*update the new pointer*/

		tmpMoveOld = tmpMoveOld->next;   /*update the old pointer*/
	}
	return newPossibleMove;
}

struct move* setNewStep(struct move* move, struct location* loc){  /*will get a move_t and put the loc at the last move_t, and return the *last* move*/

	struct move* tmpMove = 0;
	struct move* newMove = 0;

	newMove = (struct move*)malloc(sizeof(struct move)); /*in use with the linked list*/
	if(!newMove){
		perror_message("setNewStep");
		quit();
	}
	moveInitiation(newMove);
	newMove->curr = *loc;

	tmpMove = move;

	while (tmpMove->next != NULL){
		tmpMove = tmpMove->next;
	}
	tmpMove->next = newMove;

	return newMove;
}






/*REGULAR MOVE*/

void getRegularMove(char board[BOARD_SIZE][BOARD_SIZE], struct possibleMove* firstStep, int kingPlayer, int player){

	int i, j;
	struct location tmpNewLoc;
	struct location *currLoc;

	locInitiation(&(tmpNewLoc));

	currLoc = &(firstStep->move.curr);
	if (kingPlayer){   /*add all the 4, with every possible length*/
		for (i=0; i<4; ++i){

			if (i == 0){
				for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

					if (validLoc((char)(currLoc->col + j), currLoc->row + j)
							&& (board[(int)currLoc->col + j -97][currLoc->row + j -1] == EMPTY)){  /*check validation of the loc*/

						tmpNewLoc.col = (char)(currLoc->col + j);
						tmpNewLoc.row = currLoc->row + j;
						addNewStep(firstStep, tmpNewLoc);
					}
					else{  /*do not continue to add new move from that loc*/
						break;
					}
				}
			}

			else if (i == 1){
				for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

					if (validLoc((char)(currLoc->col - j), currLoc->row + j)
							&& (board[(int)currLoc->col - j -97][currLoc->row + j -1] == EMPTY)){  /*check validation of the loc*/

						tmpNewLoc.col = (char)(currLoc->col - j);
						tmpNewLoc.row = currLoc->row + j;
						addNewStep(firstStep, tmpNewLoc);
					}
					else{  /*do not continue to add new move from that loc*/
						break;
					}
				}
			}

			else if (i == 2){
				for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

					if (validLoc((char)(currLoc->col + j), currLoc->row - j)
							&& (board[(int)currLoc->col + j -97][currLoc->row - j -1] == EMPTY)){  /*check validation of the loc*/

						tmpNewLoc.col = (char)(currLoc->col + j);
						tmpNewLoc.row = currLoc->row - j;
						addNewStep(firstStep, tmpNewLoc);
					}
					else{  /*do not continue to add new move from that loc*/
						break;
					}
				}
			}

			else{  /*i = 3*/
				for(j = 1; j < BOARD_SIZE; ++j){    	/*check syntax and initiation*/

					if (validLoc((char)(currLoc->col - j), currLoc->row - j)
							&& (board[(int)currLoc->col - j -97][currLoc->row - j -1] == EMPTY)){  /*check validation of the loc*/

						tmpNewLoc.col = (char)(currLoc->col - j);
						tmpNewLoc.row = currLoc->row - j;
						addNewStep(firstStep, tmpNewLoc);
					}
					else{  /*do not continue to add new move from that loc*/
						break;
					}
				}
			}
		}
	}

	else{           /*man*/
		if (whitePlayer == player){ /*move UP. add only 0,1 steps*/
			tmpNewLoc.row = firstStep->move.curr.row +1;    /*+*/
		}
		else{                         /*black. move DOWN. add only 2,3, steps*/
			tmpNewLoc.row = firstStep->move.curr.row -1;    /*-*/
		}

		tmpNewLoc.col = (char) firstStep->move.curr.col +1; /*+*/

		if ((validLoc((char)tmpNewLoc.col, tmpNewLoc.row)) && (board[tmpNewLoc.col-97][tmpNewLoc.row-1] == EMPTY)){   /*that step in the board and empty*/

			addNewStep(firstStep, tmpNewLoc);
		}

		tmpNewLoc.col = (char) firstStep->move.curr.col - 1; /*-*/
		if ((validLoc((char)tmpNewLoc.col, tmpNewLoc.row)) && (board[tmpNewLoc.col-97][tmpNewLoc.row-1] == EMPTY)){   /*that step in the board and empty*/
			addNewStep(firstStep, tmpNewLoc);
		}
	}
}








/*check if the specific man can eat in the specific goTo*/
struct location* manCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo)
{
	char otherMan, otherKing;
	int i,j;
	struct location *nextLoc = NULL;

	nextLoc = (struct location*)malloc(sizeof(struct location));
	if(!nextLoc){
		perror_message("manCanEatFromLoc");
		quit();
	}
	locInitiation(nextLoc);
	if (player == whitePlayer){
		/*we'll check if can eat:*/
		otherMan = BLACK_M;
		otherKing = BLACK_K;
	}

	else{    /*player is black*/
		otherMan = WHITE_M;
		otherKing = WHITE_K;
	}

	i = (int) loc->col -97;
	j = loc->row - 1;

	if (goTo == 0){
		/*0*/
		if (validLoc((char)(i+97+2), j+1+2)){
			if (((board[i+1][j+1] == otherMan) || (board[i+1][j+1] == otherKing)) && (board[i+2][j+2] == EMPTY)){
				nextLoc->col = (char) loc->col +2;
				nextLoc->row = loc->row +2;
				return nextLoc;
			}
		}
	}
	else if (goTo == 1){
		/*1*/
		if (validLoc((char)(i+97-2), j+1+2)){
			if (((board[i-1][j+1] == otherMan) || (board[i-1][j+1] == otherKing)) && (board[i-2][j+2] == EMPTY)){
				nextLoc->col = (char) loc->col -2;
				nextLoc->row = loc->row +2;
				return nextLoc;
			}
		}
	}
	else if (goTo == 2){
		/*2*/
		if (validLoc((char)(i+97+2), j+1-2)){
			if (((board[i+1][j-1] == otherMan) || (board[i+1][j-1] == otherKing)) && (board[i+2][j-2] == EMPTY)){
				nextLoc->col = (char) loc->col +2;
				nextLoc->row = loc->row -2;
				return nextLoc;
			}
		}
	}
	else{   /*goTo == 3*/
		/*3*/
		if(validLoc((char)(i+97-2), j+1-2)){
			if (((board[i-1][j-1] == otherMan) || (board[i-1][j-1] == otherKing)) && (board[i-2][j-2] == EMPTY)){
				nextLoc->col = (char) loc->col -2;
				nextLoc->row = loc->row -2;
				return nextLoc;
			}
		}
	}
	free(nextLoc);
	return NULL;
}



/*check if the specific king can eat in the specific goTo*/

struct location* kingCanEatFromLoc(char board[BOARD_SIZE][BOARD_SIZE], struct location *loc, int player, int goTo)		/*change return type and input is a king*/
{

	int i;
	char otherMan, otherKing;
	int colIndex = loc->col-97;
	int rowIndex = loc->row -1;
	struct location *nextLoc = 0;

	nextLoc = (struct location*)malloc(sizeof(struct location));		/*V*/
	if(!nextLoc){
		perror_message("kingCanEatFromLoc");
		quit();
	}
	locInitiation(nextLoc);
	if (player == whitePlayer){
		/*we'll check if can eat:*/
		otherMan = BLACK_M;
		otherKing = BLACK_K;
	}

	else{    /*player is black*/
		otherMan = WHITE_M;
		otherKing = WHITE_K;
	}

	if(goTo == 0)
	{
		for(i = 0; i < BOARD_SIZE; ++i){    	/*check syntax and initiation*/

			if (validLoc((char)(loc->col + (i +1)), loc->row +(i+1))){  /*check validation of the loc*/

				if(((board[colIndex + i][rowIndex +i] == otherMan) || (board[colIndex + i][rowIndex + i] == otherKing))
						&& (board[colIndex + (i+1)][rowIndex +(i+1)] == EMPTY)){

					nextLoc->col = (char) colIndex +(i + 1) +97;
					nextLoc->row = rowIndex +(i +1) +1;
					return nextLoc;
				}
			}
		}
		/*we're here cause we didn't find a valid eating*/
		free(nextLoc);
		return NULL;
	}

	else if(goTo == 1)
	{
		for(i = 0; i < BOARD_SIZE; ++i){    	/*check syntax and initiation*/

			if (validLoc((char)(loc->col -(i +1)), loc->row +(i+1))){  /*check validation of the loc*/

				if(((board[colIndex - i][rowIndex +i] == otherMan) || (board[colIndex - i][rowIndex + i] == otherKing))
						&& (board[colIndex - (i +1)][rowIndex + i+1] == EMPTY)){

					nextLoc->col = (char) colIndex -(i + 1) +97;
					nextLoc->row = rowIndex +(i +1) +1;
					return nextLoc;
				}
			}
		}
		/*we're here cause we didn't find a valid eating in the loop before*/
		free(nextLoc);
		return NULL;
	}

	else if(goTo == 2)
	{
		for(i = 0; i < BOARD_SIZE; ++i){    	/*check syntax and initiation*/

			if (validLoc((char)(loc->col +(i +1)), loc->row -(i+1))){  /*check validation of the loc*/

				if(((board[colIndex + i][rowIndex -i] == otherMan) || (board[colIndex + i][rowIndex - i] == otherKing))
						&& (board[colIndex +(i +1)][rowIndex -(i+1)] == EMPTY)){

					nextLoc->col = (char) colIndex +(i + 1) +97;
					nextLoc->row = rowIndex -(i +1) +1;
					return nextLoc;
				}
			}
		}
		/*we're here cause we didn't find a valid eating in the loop before*/
		free(nextLoc);
		return NULL;
	}
	else 	/*goTo=3*/
	{
		for(i = 0; i < BOARD_SIZE; ++i){    	/*check syntax and initiation*/

			if (validLoc((char)(loc->col -(i +1)), loc->row -(i+1))){  /*check validation of the loc*/

				if(((board[colIndex - i][rowIndex -i] == otherMan) || (board[colIndex - i][rowIndex - i] == otherKing))
						&& (board[colIndex -(i +1)][rowIndex -(i+1)] == EMPTY)){

					nextLoc->col = (char) colIndex -(i + 1) +97;
					nextLoc->row = rowIndex -(i +1) +1;
					return nextLoc;
				}
			}
		}
		/*we're here cause we didn't find a valid eating in the loop before*/
		free(nextLoc);
		return NULL;
	}
}



int theSamePlayer(char board[BOARD_SIZE][BOARD_SIZE], struct location* nextLoc, int player)
{
	int j = nextLoc->row -1;
	int i = nextLoc->col -97;

	if (player == whitePlayer){
		if ((board[i][j] == WHITE_K) || (board[i][j]== WHITE_M) ){
			return 1;
		}
	}
	else{
		if ((board[i][j] == BLACK_K) || (board[i][j]== BLACK_M) ){
			return 1;
		}
	}
	return 0;
}

int stopConditions(loc_t* result ,move_t* currMove, int player){
	move_t* tmpMove = 0;
	tmpMove = currMove;


	if(result == NULL){	/*no eating move that way, last step of that recursion*/ /*no 1 happened*/
		return 1;
	}

	else if (tmpMove->next == NULL){   /*this is the currLoc. no check if in the end of the board*/
		return 0;
	}

	while(tmpMove->next != NULL){
		tmpMove = tmpMove->next;
	}

	if((player == whitePlayer) && (tmpMove->curr.row == 10)){	/*white player reached to the end of board*/
		return 1;
	}
	else if((player != whitePlayer) && (tmpMove->curr.row == 1)){	/*black player reached to the end of board*/
		return 1;
	}

	return 0;
}



/*THE ONE AND ONLY: OUR SWEET DEAR MINIMAX !!!!!*/


mmGS_t* minimax(mmGS_t* node, int depth, int maximizingPlayer){   /*1-> the maxi player (the computer))*/

	int i;
	int numberOfChildren = 0;

	mmGS_t** children = NULL;
	mmGS_t* currChild = NULL;
	mmGS_t* curNode = NULL;
	mmGS_t* bestNode = NULL;


	possibleM_t* childrenMoves = NULL;
	possibleM_t* tmpMove = NULL;

	childrenMoves = getAllPossibleMoves(node->boardState.board, maximizingPlayer);
	tmpMove = childrenMoves;

	while (tmpMove != NULL){   /*how many possible moves (children)*/
		numberOfChildren += 1;
		tmpMove = tmpMove->next;
	}

	children = (mmGS_t**)malloc(numberOfChildren * sizeof(possibleM_t*));	/*an empty array of mmGS_t pointers*/
	if(!children){
		perror_message("minimax");
		quit();
	}
	mmGSArrayInit(children, numberOfChildren);

	getChildren(node, childrenMoves, children);   /*we convert the childrensMoves to an array of mmGS_t pointers*/


	if ((depth == 0) || (numberOfChildren == 0)){
		scoreCalc(node);
		return node;
	}

	if (maximizingPlayer){

		bestNode = (mmGS_t*) malloc(sizeof (mmGS_t));   /*init to -infinity*/
		if(!bestNode){
			perror_message("minimax");
			quit();
		}
		mmGSInitiation(bestNode);
		bestNode->score = INT_MIN;


		for (i = 0; i < numberOfChildren; ++i){
			currChild = children[i];
			curNode = minimax(currChild, depth - 1, 0);     /*recursion call*/
			bestNode = maxNode(curNode, bestNode);       /*find the max between the two*/
		}
		free_mmGSArray(children, numberOfChildren);
		return bestNode;
	}

	else{

		bestNode = (mmGS_t*) malloc(sizeof (mmGS_t));
		if(!bestNode){
			perror_message("minimax");
			quit();
		}
		mmGSInitiation(bestNode);
		bestNode->score = INT_MAX;						/*init to infinity*/


		for (i = 0; i < numberOfChildren; ++i){
			currChild = children[i];
			curNode = minimax(currChild, depth - 1, 1);     /*recursion call*/
			bestNode = minNode(curNode, bestNode);       /*find the min between the two*/
		}

		return bestNode;
	}
}





mmGS_t* minNode (mmGS_t* firstNode, mmGS_t* secondNode){

	if (firstNode->score < secondNode->score){
		return firstNode;
	}

	return secondNode; /*if '=' will return the second */
}


mmGS_t* maxNode (mmGS_t* firstNode, mmGS_t* secondNode){

	if (firstNode->score < secondNode->score){
		return firstNode;
	}

	return secondNode; /*if '=' will return the second */
}



mmGS_t* scoreCalc(mmGS_t* node){

	int score = 0;
	int whiteDiscs;
	int blackDiscs;

	whiteDiscs = node->boardState.numberWM +3*(node->boardState.numberWK);
	blackDiscs = node->boardState.numberBM +3*(node->boardState.numberBK);

	if (checkIfWin(&(node->boardState), 0)){   /*did the computer win?*/
		score = 100;
	}

	else if (checkIfWin(&(node->boardState), 1)){   /*did the user win?*/
		score = -100;
	}

	else if (!whitePlayer){/*the computer is the white player (and not win, cause if so, it was entered in the loop before) */
		score = whiteDiscs - blackDiscs;
	}

	else{                         /*/*the computer is the black player (and not win)*/
		score = blackDiscs - whiteDiscs;
	}

	node->score = score;

	return node;
}


void getChildren(mmGS_t* fatherNode, possibleM_t* possibleMove, mmGS_t** array){		/*casting a list of possibleM_t to an array of mmGS_t*/

	possibleM_t* tmpPossibleMove = NULL;
	mmGS_t* newMmGS = NULL;
	int i = 0;

	tmpPossibleMove = possibleMove;

	while (tmpPossibleMove != NULL){
		newMmGS  = (mmGS_t*) malloc (sizeof (mmGS_t));   /*place for the new mmGS_t (new node)*/
		if(!newMmGS){
			perror_message("getChildren");
			quit();
		}
		mmGSInitiation(newMmGS);
		newMmGS->boardState = fatherNode->boardState;       /*copy the game state from the father node*/

		changeBoardByMove(&(newMmGS->boardState), tmpPossibleMove->move); /*change the board we copied by the tmp possible move*/

		if (!(fatherNode->move.curr.row)){   /*mean: the father is the root. we'll save the move from tmpPossibleMove */
			newMmGS->move = tmpPossibleMove->move;
		}

		else{
			newMmGS->move = fatherNode->move;        /*copy the move from the *father node**/
		}

		array[i] = newMmGS;                /*put the new mmGS_t in the array*/

		i += 1;

		tmpPossibleMove = tmpPossibleMove->next;
	}
}


int isPlayer(char piece, int playerColor){  //return 1 if the piece belong to the player. playerColor 0 -> white, 1 -> black
	int res;

	switch (playerColor){
		case 0:    /*white*/
			switch(piece){
			case WHITE_P :
			case WHITE_B :
			case WHITE_N :
			case WHITE_R :
			case WHITE_Q :
			case WHITE_K :
				res = 1;
				break;
			default:
					res = 0;
					break;
			}
			break;

		case 1:    /*black*/
			switch(piece){
			case BLACK_P :
			case BLACK_B :
			case BLACK_N :
			case BLACK_R :
			case BLACK_Q :
			case BLACK_K :
				res = 1;
				break;
			default:
					res = 0;
					break;
			}
			break;

		default:
			res  = -1; //if we got here, something went wrong
			break;
	}
	return res;
}

int isOtherPlayer(char piece, int playerColor){  //return 1 if the piece belong to the *other player*. playerColor 0 -> white, 1 -> black
	int res;

	switch (playerColor){
		case 0:    /*white*/
			switch(piece){
				case BLACK_P :
				case BLACK_B :
				case BLACK_N :
				case BLACK_R :
				case BLACK_Q :
				case BLACK_K :
					res = 1;
					break;
				default:
					res = 0;
					break;
			}
			break;

		case 1:    /*black*/
			switch(piece){
				case WHITE_P :
				case WHITE_B :
				case WHITE_N :
				case WHITE_R :
				case WHITE_Q :
				case WHITE_K :
					res = 1;
					break;
				default:
					res = 0;
					break;
			}
			break;

		default:
			res  = -1; //if we got here, something went wrong
			break;
	}
	return res;
}



int isWhite(char piece){

	int res;

	switch(piece){

		case WHITE_P :
		case WHITE_B :
		case WHITE_N :
		case WHITE_R :
		case WHITE_Q :
		case WHITE_K :
			res = 1;
			break;

		default:
			res = 0;
			break;
	}

	return res;

}



int isBlack(char piece){

	int res;

	switch(piece){

		case BLACK_P :
		case BLACK_B :
		case BLACK_N :
		case BLACK_R :
		case BLACK_Q :
		case BLACK_K :
			res = 1;
			break;

		default:
			res = 0;
			break;
	}

	return res;
}


int isPawn(char piece){

	int res;

	switch(piece){

		case WHITE_P :
		case BLACK_P :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}


int isBishop(char piece){

	int res;

	switch(piece){

		case WHITE_B :
		case BLACK_B :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}



int isRook(char piece){

	int res;

	switch(piece){

		case WHITE_R :
		case BLACK_R :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}



int isKnight(char piece){

	int res;

	switch(piece){

		case WHITE_N :
		case BLACK_N :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}



int isQueen(char piece){

	int res;

	switch(piece){

		case WHITE_Q :
		case BLACK_Q :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}



int isKing(char piece){

	int res;

	switch(piece){

		case WHITE_K :
		case BLACK_K :
			res = 1;
			break;

		default :
			res = 0;
			break;
	}

	return res;
}

int getPlayerColor(int player){ /*if white - will return 0. black - 1*/

	if (player == whitePlayer){
		return 0;
	}

	return 1;
}

void freeMT(move_t* move){
	move_t* tmpMove = 0;

	tmpMove = move->next;
	if (tmpMove == NULL){
		free(move);
	}
	while(tmpMove != NULL){
		free(move);
		move = tmpMove;
		tmpMove = tmpMove->next;
	}
}

void freePM(struct possibleMove* possibleMove){
	possibleM_t* tmpPM = 0;

	tmpPM = possibleMove->next;
	while(tmpPM != NULL){
		freeMT(possibleMove->move.next);
		free(possibleMove);
		possibleMove = tmpPM;
		tmpPM = tmpPM->next;
	}
}

void free_mmGS(mmGS_t* mmGS){
	freeMT(mmGS->move.next);
	free(mmGS);
}

void free_mmGSArray(mmGS_t** arrayOfmmGS_t, int arraySize){
	int i;

	for(i = 0; i < arraySize; ++i){
		free_mmGS(arrayOfmmGS_t[i]);			/*~~~~~~check if ok~~~~~~~~*/
		arrayOfmmGS_t++;
	}
}

void initArrChar(char* charArray, int len){
	int i;

	for(i = 0; i < len; ++i){
		charArray[i]= 0;
	}
}

void moveInitiation(move_t* move){
	move->next = NULL;
	locInitiation(&(move->curr));
	move->castling = 0;
}

void locInitiation(loc_t* loc){
	loc->col = 0;
	loc->row = 0;
}

void posMovInitiation(struct possibleMove* firstEmptyNode){
	moveInitiation(&(firstEmptyNode->move));
	firstEmptyNode->check = 0;
	firstEmptyNode->next = NULL;
}
void mmGSArrayInit(mmGS_t** array , int len){
	int i;

	for(i = 0; i< len; ++i){
		array[i] = (mmGS_t*)malloc(sizeof(mmGS_t));
		mmGSInitiation(array[i]);
	}
}

void mmGSInitiation(mmGS_t* node){
	node->score = 0;
	clear(&(node->boardState));
	moveInitiation(&(node->move));
}


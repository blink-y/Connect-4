#include <stdio.h>
/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2



/* Initialize the game board by setting all squares to EMPTY */
void initGameBoard(int gameBoard[6][7]) {


    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameBoard[i][j] = EMPTY;
        }
    }

}



/* Display the game board on the screen.*/
void printGameBoard(int gameBoard[6][7]) {

    for (int i=0; i<6; i++){
        printf("|");
        for (int j=0; j<7; j++){
            if (gameBoard[i][j] == EMPTY){
                printf(" |");
            } else if (gameBoard[i][j] == CIRCLE){
                printf("O|");
            } else if (gameBoard[i][j] == CROSS){
                printf("X|");
            }
        }
        printf("\n");
    }
    printf(" ");
    for (int i=1; i<8; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

int getTop(int gameBoard[6][7], int column){
    for (int i=5; i>=0; i--){
        if (gameBoard[i][column]==EMPTY){
            return i;
        }
    }
    return -1;
}

/* Ask the human player to place the mark.*/
void placeMarkByHumanPlayer(int gameBoard[6][7], int mark) {
    int flag=0, col=0;
    printf("Player %d's turn:\n", mark);
    while (1){
        scanf("%d", &col);
        if (col>=1 && col<=7){
            if (gameBoard[0][col-1]==EMPTY){
                gameBoard[getTop(gameBoard, col-1)][col-1] = mark;
                break;
            }
            else{
                printf("Column is full. Please input again: \n");
            }
        }
        else{
            printf("Input out of range. Please input again:\n");
        }
    }
}



/* Return 1 if there is a winner in the game, otherwise return 0.*/
int whoWon(int gameBoard[6][7]){
    int mark;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            mark = gameBoard[i][j];
            if (mark == EMPTY){
                continue;
            }
            // rows
            if (j<4){
                if (gameBoard[i][j+1]==mark &&
                 gameBoard[i][j+2]==mark &&
                 gameBoard[i][j+3]==mark){
                    return mark;
                }
            }
            // columns
            if(i>2){
                if (gameBoard[i-1][j]==mark &&
                 gameBoard[i-2][j]==mark &&
                 gameBoard[i-3][j]==mark){
                    return mark;
                }
            }
            // diagonal 1
            if(i>2 && j<4){
                if (gameBoard[i-1][j+1]==mark &&
                 gameBoard[i-2][j+2]==mark &&
                 gameBoard[i-3][j+3]==mark){
                    return mark;
                }
            }
            // diagonal 2
            if(i>2 && j>2){
                if (gameBoard[i-1][j-1]==mark &&
                 gameBoard[i-2][j-2]==mark &&
                 gameBoard[i-3][j-3]==mark){
                    return mark;
                }
            }
        }
    }
    return -1;
}

int hasWinner(int gameBoard[6][7], int numOfHumanPlayers){
    int winningPlayer = whoWon(gameBoard);
    if (winningPlayer != -1){
        printGameBoard(gameBoard);
        if (numOfHumanPlayers == 1 && winningPlayer == 2){
            printf("Congratulations! Computer wins!\n");
            return 1;
        }
        else {
            printf("Congratulations! Player %d wins!\n", winningPlayer);
            return 1;
        }
    }
    return -1;


}

/* Return 1 if the game board is full, otherwise return 0. */
int isFull(int gameBoard[6][7]) {

    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            if (gameBoard[i][j] == EMPTY){
                return 0;
            }
        }
    }
    if (whoWon(gameBoard) == -1){
        printGameBoard(gameBoard);
        printf("Game draw!\n");
    }
    return 1;
}


/* Determine the next move of the computer player.*/
void placeMarkByComputerPlayer(int gameBoard[6][7]){
    int mostSlotsLeft=-1, minColumn=0, slotsLeft=0, target=0;
    printf("Computer's turn: \n");
    for (int j=6; j>=0; j--){
        target = getTop(gameBoard, j);
        gameBoard[target][j] = CROSS;
        if (whoWon(gameBoard) == CROSS){
            //printf("%d\n", j+1);
            return;
        }
        gameBoard[target][j] = EMPTY;
    }

    for (int j=6; j>=0; j--){
        target = getTop(gameBoard, j);
        gameBoard[target][j] = CIRCLE;
        if (whoWon(gameBoard) == CIRCLE){
            gameBoard[target][j] = CROSS;
            //printf("%d\n", j+1);
            return;
        }
        gameBoard[target][j] = EMPTY;
    }

    for (int i=6; i>=0; i--){
        slotsLeft = 1+getTop(gameBoard, i);
        if (slotsLeft != -1 && slotsLeft > mostSlotsLeft) {
            mostSlotsLeft = slotsLeft;
            minColumn = i;
        }
    }

    gameBoard[getTop(gameBoard, minColumn)][minColumn] = CROSS;
    //printf("%d\n", minColumn+1);
}

int togglePlayer(int player){
    if (player == 1) {
            return 2;
    }
    return 1;
}

/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[6][7];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1             2: Player 2
    int gameContinue;       // 1: The game continues   0: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameContinue = 1;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);    // You can assume that the user input must be valid

    while(hasWinner(gameBoard, numOfHumanPlayers) == -1 && !isFull(gameBoard)==1 ){
        printGameBoard(gameBoard);
        if (currentPlayer == 1){
            placeMarkByHumanPlayer(gameBoard, CIRCLE);
        }
        else {
            if (numOfHumanPlayers == 2){
                placeMarkByHumanPlayer(gameBoard, CROSS);
            }
            else{
                placeMarkByComputerPlayer(gameBoard);
            }
        }
        currentPlayer = togglePlayer(currentPlayer);
    }
    return 0;
}

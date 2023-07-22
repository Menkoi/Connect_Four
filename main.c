#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define COL  7
#define ROW  6

int box = 0;
char playerOne[15];
char playerTwo[15];
char playerX = 'X';
char playerO = 'O';
char scores[ROW][COL];

int readFileLine();

 typedef struct {
    int id;
    char playerOneName[15];
    char playerTwoName[15];
    char gameBoard[42];
    int spaceLeft;
} Profile;

int amountSpaceLeft;

// Prototype
void gameFunction();
void layout();
void init_scores();
void choice();
void fill_box();
int check(char disc);
void playerName();

void save();
void saveId();
void saveBoard();

void loadId();
void loadAllGames();
void loadGame();
void loadFromPlayer();
void loadBoard();
void returnGame();

int main()
{
     int menuSelect;
        printf("\n\n");
        printf("CONNECT FOUR\n");
        printf("\n\n");
        printf(" 1  Play New Game\n");
        printf(" 2  Load Already Saved Game\n");
        printf(" 3  Exit Game\n");

        printf("\n");
        printf("Enter selection\n");
        scanf("%d", &menuSelect);


    switch (menuSelect) {
        case 1:
        playerName();
        newGame();
        break;

        case 2:
          printf("\n");
          loadGame();
        break;

        case 3:
          printf("Exited Game\n");
          exit(0);
        break;

        default:
          printf("input only numbers 1, 2, or 3\n");
          main();
        break;
    }
    return 0;
}

/* Create new game */
 void newGame() {
     init_scores();
     layout();
     gameFunction();
 }

 void gameFunction() {

      while (true){
        printf("Player %c, your turn!\n", playerX);
        choice();
        printf("\n\n");
        layout();
        if (check('X')){
            printf("\n\nPlayer %s wins!\n\n", playerOne);
            gameEnd();
        }
        if (check('O')){
            printf("\n\nPlayer %s wins!\n\n", playerTwo);
            gameEnd();
        }

    }

    return 0;
 }

 void gameEnd() {

    int k;

    printf(" 1 Start new game\n");
    printf(" 2 Back to main menu\n");
    scanf("%d", &k);

    switch(k) {
        case 1:
        playerName();
        newGame();
        break;

        case 2:
        main();
        break;

        default:
        printf("Choose either 1 or 2");
        break;
    }
}


// Players input name
void playerName() {

    printf("Enter Player 1 Name\n");
    scanf("%s", &playerOne);

    printf("Enter Player 2 Name\n");
    scanf("%s", &playerTwo);

    printf("\n\n");
    printf("Welcome %s, and %s\n", playerOne, playerTwo);
    printf("\n\n");

}

void layout() {
    char header[] = "   1   2   3   4   5   6   7";
    char body[] = " |---|---|---|---|---|---|---|";
    printf("%s\n", header);
    printf("%s\n", body);

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("   %c", scores[i][j]);
        }
        printf("\n");
        printf("%s\n", body);
    }
    printf("\n");
}

 // fill layout with empty space
 void init_scores(){
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            scores[i][j] = ' ';
        }
    }
}

/* user input into box */
void choice(){
    int input;

    while (true){
        printf("\nChoose box or press 0 to save: ");
        scanf("%i", &input);

        if(input == 0){
            save();
            main();
        }

        switch(input)
        {
            case 1:
                playerO = 0;
                break;
            case 2:
                playerO = 1;
                break;
            case 3:
                playerO = 2;
                break;
            case 4:
                playerO = 3;
                break;
            case 5:
                playerO = 4;
                break;
            case 6:
                playerO = 5;
                break;
            case 7:
                playerO = 6;
                break;

            default:
                playerO = 666;
                printf("\nWrong number!\n");
        }
        if ((playerO >= 0 && playerO <= 6) && (scores[0][playerO] == ' ')){
            fill_box();
            playerX = (playerX == 'X') ? 'O' : 'X';
            break;
        }
    }
}

void save()
{
    int b;

    printf("\n");
    printf(" Press 1 to save\n");
    printf("        OR\n");
    printf(" 2 Return to main menu\n");
    printf("\n-------------------------------------------\n");
    printf("*Going to main menu will lose all progress*\n");
    printf("-------------------------------------------");
    printf("\n\n");

    scanf("%d", &b);

    switch(b) {

        case 1:
         saveId();
         saveBoard();
        break;

        case 2:
            main();
        break;
    }

}

/* Get the numbers of lines in a file for the ID */
int readFileLine(const char *filename) {
    int lines = 1;
    char ch;
    FILE *file = fopen(filename, "r");
    while ((ch = fgetc(file)) != EOF) { if (ch == '\n') { lines++; }}
    fclose(file);
    return lines;
}

/* saves id, players, and spaces */
void saveId() {
    FILE *file;
    file = fopen("saveGame.txt", "a+");
    int id = readFileLine("saveGame.txt");

    int emptySpace;

    printf("\n");
    printf("Your save ID is %d\n", id);
    printf("---------------------------------------\n");

    fprintf(file, "%d  %s  %s  %d", id, &playerOne, &playerTwo, &emptySpace);

    fprintf(file, "\n");
    fclose(file);

}

/* saves current layout */
void saveBoard() {
    FILE *file;
    file = fopen("history.txt", "a+");
    int id = readFileLine("history.txt");
    for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
            fprintf(file,"%c", scores[i][j]);
            }
        }
        fprintf(file, "\n");
        fclose(file);
}

void loadGame() {
    int k;

    printf(" 1 List all saved games\n");
    printf(" 2 List all saved games for particular player\n");
    printf(" 3 Show the board of one of the saved games\n");
    printf(" 4 Load a game\n");
    printf(" 5 Return to main menu\n");

    scanf("%d", &k);

    switch(k) {

        case 1:
          loadAllGames();
          printf("\n");
          loadGame();
        break;

        case 2:
            loadFromPlayer();
            printf("\n");
            loadGame();
        break;

        case 3:
            loadBoard();
            loadGame();
        break;

        case 4:
            loadId();
            printf("\n");
        break;

        case 5:
            main();
        break;

        default:
        printf("\nChoose either 1, 2, 3, 4, or 5\n\n");
        loadGame();
        break;
    }
}

/* Show list of all saved games */
void loadAllGames() {

    FILE *file;
    file = fopen("saveGame.txt", "r");
    int read = readFileLine("saveGame.txt");

    Profile user[read];
    printf("\n\n---------SAVED GAMES----------\n\n");

    for (int i = 0; i < read - 1; i++) {
        fscanf(file, "%d %s %s %d\n", &user[read].id, &user[read].playerOneName, &user[read].playerTwoName, &user[read].spaceLeft);
        printf("id-%d P1-%s P2-%s Space-%d\n", user[read].id, user[read].playerOneName, user[read].playerTwoName, user[read].spaceLeft);
    }

    printf("\n\n-----------------------------\n\n");
    fclose(file);

}

/* List all saved games from player name */
void loadFromPlayer(){

    int playerName[15];
    int firstPlayer;
    int secondPlayer;

    printf("Enter player name\n");
    scanf("%s", &playerName);

    FILE *file;
    file = fopen("saveGame.txt", "r");
    int read = readFileLine("saveGame.txt");

    Profile user[read];

    for (int i = 0; i < read - 1; i++) {
        fscanf(file, "%d %s %s %d\n", &user[read].id, &user[read].playerOneName, &user[read].playerTwoName, &user[read].spaceLeft);

        firstPlayer = strcmp(user[read].playerOneName, playerName);
        secondPlayer = strcmp(user[read].playerTwoName, playerName);

        if (firstPlayer == 0 || secondPlayer == 0) {
            printf("\n");
            printf("id-%d P1-%s P2-%s Space-%d\n", user[read].id, user[read].playerOneName, user[read].playerTwoName, user[read].spaceLeft);
        }

      }

    fclose(file);
    printf("\n\n");
}

/* Print out board from saved game*/
void loadBoard() {

    int idNum;

    FILE *file;
    file = fopen("saveGame.txt", "r");
    int read = readFileLine("saveGame.txt");

    FILE *file2;
    file2 = fopen("history.txt", "r");
    int check = readFileLine("history.txt");

    int k = 0;
    char c;

    printf("Enter Id\n");
    scanf("%d", &idNum);

    Profile user[read];

    if (idNum > read - 1) {
        printf("\nError, cant find ID number\n");
        printf("\n\n");
        main();
    } else {
        for (int i = 0; i < read - 1; i++) {
            fscanf(file, "%d %s %s %d\n", &user[read].id, &user[read].playerOneName, &user[read].playerTwoName, &user[read].spaceLeft);
            if (idNum == user[read].id) {
                printf("\n\n------------------------------\n\n");
                printf("id-%d P1-%s P2-%s Space-%d\n", user[read].id, user[read].playerOneName, user[read].playerTwoName, user[read].spaceLeft);
            }
        }
    }

    fclose(file);
    printf("\n\n");

    do {
        fscanf(file2, "%c", &c);
        if (c == '\n' ) {
            k++;
        }
    } while (k < (idNum - 1));

     for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
            fscanf(file2, "%c", &c);
            scores[i][j] = c;
            }
        }
        fclose(file2);
        layout();
        printf("\n\n------------------------------\n\n");

}

/* Load from saved game */
void loadId() {

    int idNum;

    FILE *file;
    file = fopen("saveGame.txt", "r");
    int read = readFileLine("saveGame.txt");

    FILE *file2;
    file2 = fopen("history.txt", "r");
    int check = readFileLine("history.txt");

    int k = 0;
    char c;

    printf("Enter Id\n");
    scanf("%d", &idNum);

    Profile user[read];

    if (idNum > read - 1) {
        printf("\nError, cant find ID number\n");
        printf("\n\n");
        loadGame();
    } else {
        for (int i = 0; i < read - 1; i++) {
            fscanf(file, "%d %s %s %d\n", &user[read].id, &user[read].playerOneName, &user[read].playerTwoName, &user[read].spaceLeft);
            if (idNum == user[read].id) {
                printf("id-%d P1-%s P2-%s Space-%d\n", user[read].id, user[read].playerOneName, user[read].playerTwoName, user[read].spaceLeft);
            }
        }
    }

    fclose(file);
    printf("\n\n");

    do {
        fscanf(file2, "%c", &c);
        if (c == '\n' ) {
            k++;
        }
    } while (k < (idNum - 1));

     for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
            fscanf(file2, "%c", &c);
            scores[i][j] = c;
            }
        }
        fclose(file2);
        layout();
        gameFunction();

}



void fill_box()
{
    // fill the boxes
    int level ;

    for (level = ROW-1; level >= 0; level--){
        if (scores[level][playerO] == ' '){
            scores[level][playerO] = playerX;

            break;
        }
    }
}

int check(char playerX)
{
    // check vertical
    int i, j, k;
    int count;
    int ways = 4;

    for (i = 0; i < ROW; ++i){
        for (j = 0; j < ways; ++j){
            count = 0;
            for (k = 0; k < 4; ++k){
                if (scores[i][j + k] == playerX) count++;
            }
            if (count == 4) return 1;
        }
    }


    /* check horizontal*/

    ways = 3;

    for (j = 0; j < COL; ++j){
        for (i = 0; i < ways; ++i){
            count = 0;
            for (k = 0; k < 4; ++k){
                if (scores[i + k][j] == playerX) count++;
            }
            if (count == 4) return 1;
        }
    }

    /* check diagonals*/

    int ii, jj;
    for (i = 1; i < ROW-1; i++){
        for (j = 1; j < COL-1; j++){
            count = 0;

            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--){
                if (scores[ii][jj] == playerX){
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i+1, jj = j+1; (ii <= ROW-1) || (jj <= COL-1); ii++, jj++){
                if (scores[ii][jj] == playerX){
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            /* right-tilted diagonals */
            count = 0;

            for (ii = i, jj = j; (ii <= ROW-1) || (jj >= 0); ii++, jj--){
                if (scores[ii][jj] == playerX){
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COL-1); ii--, j++){
                if (scores[ii][jj] == playerX){
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

        }
    }

    return 0;
}









#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COL  7
#define ROW  6

int box = 0;
char playerOne[15];
char playerTwo[15];
char playerX = 'X';
char playerO = 'O';
char scores[ROW][COL];
char save1[ROW][COL];
char save2[ROW][COL];
char save3[ROW][COL];
char save4[ROW][COL];



// Prototype
void playerName();
void save();
void layout();
void init_scores();
void choice();
void fill_box();
void loadGame();
int check(char disc);


int main()
{
     int menuSelect;

        printf("CONNECT FOUR\n");
        printf("\n");
        printf(" 1  Play New Game\n");
        printf(" 2  Load Already Saved Game\n");
        printf(" 3  Exit Game\n");

        printf("\n");
        printf("Enter selection\n");
        scanf("%d", &menuSelect);


    switch (menuSelect) {
        case 1:
          newGame();
        break;

        case 2:
          printf("Loaded game\n");
          printf("\n");
          loadGame();
        break;

        case 3:
          printf("Exited Game\n");
          exit(0);
        break;

        default:
          printf("input only numbers 1, 2, or 3\n");
        break;
    }
    return 0;
}

// create new game
 void newGame() {
     playerName();
     init_scores();
     layout();

     while (1)
    {
        printf("Player %c, your turn!\n", playerX);
        choice();
        printf("\n\n");
        layout();
        if (check('X'))
        {
            printf("\n\nPlayer %s wins!\n\n", playerOne);
            gameEnd();
        }
        if (check('O'))
        {
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
        newGame();
        break;

        case 2:
        main();
        break;

        default:
        printf("Choose either 1 or 2");
        // program ends if not 1 or 2 were chosen
        break;
    }
}

void loadGame() {
    int k;

    printf(" Press 1 to load save1\n");
    printf(" Press 2 to load save2\n");
    printf(" Press 3 to load save3\n");
    printf(" Press 4 to load save4\n");

    printf(" 5 Return to main menu\n");

    scanf("%d", &k);

    switch(k) {
        case 1:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                scores[i][j] = save1[i][j];
            }
        }
        layout();
        choice();
        break;

        case 2:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                scores[i][j] = save2[i][j];
            }
        }
        layout();
        choice();
        break;

        case 3:
            for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                scores[i][j] = save3[i][j];
            }
        }
        layout();
        choice();
        break;

        case 4:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                scores[i][j] = save4[i][j];
            }
        }
        layout();
        choice();
        break;

        case 5:
            main();
        break;

        default:
        printf("Choose either 1 or 2");
        // program ends if not 1 or 2 were chosen
        break;
    }
}

// Players input name
void playerName() {

    printf("Enter Player 1 Name\n");
    scanf("%s", &playerOne);

    printf("Enter Player 2 Name\n");
    scanf("%s", &playerTwo);

    printf("\n");
    printf("Welcome %s, and %s\n", playerOne, playerTwo);
    printf("\n");

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
        printf(" |\n");
        printf("%s\n", body);
    }
}

 // fill layout with empty space
 void init_scores()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            scores[i][j] = ' ';
        }
    }
}

// user input choice into box
void choice()
{
    int input;

    while (true)
    {
        printf("\nChoose box or press 8 to save: ");
        scanf("%i", &input);

        if (input == 8) 
        {
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
                printf("\nWrong number! \n\n");
                //layout();
        }
        if ((playerO >= 0 && playerO <= 6) && (scores[0][playerO] == ' '))
        {
            fill_box();
            playerX = (playerX == 'X') ? 'O' : 'X';
            break;
        }
    }
}

void save()
{
    int b;
    printf(" Press 1 to save save1\n");
    printf(" Press 2 to save save2\n");
    printf(" Press 3 to save save3\n");
    printf(" Press 4 to save save4\n");

    printf(" 5 Return to main menu\n");

    scanf("%d", &b);

    switch(b) {

        case 1:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                save1[i][j] = scores[i][j];
            }
        }
        break;

        case 2:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                save2[i][j] = scores[i][j];
            }
        }
        break;

        case 3:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                save3[i][j] = scores[i][j];
            }
        }
        break;

        case 4:
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                save4[i][j] = scores[i][j];
            }
        }
        break;
    }

}

void fill_box()
{
    // fill the boxes
    int level ;

    for (level = ROW-1; level >= 0; level--)
    {
        if (scores[level][playerO] == ' ')
        {
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

    for (i = 0; i < ROW; ++i)
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < 4; ++k)
            {
                if (scores[i][j + k] == playerX) count++;
            }
            if (count == 4) return 1;
        }
    }


    /* check horizontal*/

    ways = 3;

    for (j = 0; j < COL; ++j)
    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < 4; ++k)
            {
                if (scores[i + k][j] == playerX) count++;
            }
            if (count == 4) return 1;
        }
    }

    /* check diagonals*/

    int ii, jj;
    for (i = 1; i < ROW-1; i++)
    {
        for (j = 1; j < COL-1; j++)
        {
            count = 0;

            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == playerX)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i+1, jj = j+1; (ii <= ROW-1) || (jj <= COL-1); ii++, jj++)
            {
                if (scores[ii][jj] == playerX)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            /* right-tilted diagonals */
            count = 0;

            for (ii = i, jj = j; (ii <= ROW-1) || (jj >= 0); ii++, jj--)
            {
                if (scores[ii][jj] == playerX)
                {
                    count++;
                    if (count == 4) return 1;
                }
                else
                    break;
            }

            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COL-1); ii--, j++)
            {
                if (scores[ii][jj] == playerX)
                {
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









#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

//       index ->  0  1  2  3  4  5  6  7  8  9   10  11  12  13  14  15     
//int board[4][4] = {3, 2, 4, 1, 7, 5, 6, 8, 14, 12, 13, 15, 9, 10, 11, 0 };
int board[4][4] = { [3][3]= 0 };
// to match if player wins
int WinningBoard[4][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

short int PlayerMove = 0;
int moves = 400;
char playerName[10] = {0};


//Board display
void Display();
// player input to manipulate board
void Input(); // ASCII CODE OF ARROW KEYS: down - 80    up - 72    left - 75   right - 77
// to check if move is valid or not
int ValidMove();
//winnig checking
int CheckWin();
void PlayerNameInput();
void RuleDisplay();
//This function will assign non - repeating random values between range [1-15] in board 
void RandomGen();


int main()
{
    int isWin = 0;

    RandomGen();

    RuleDisplay();
    PlayerNameInput();

    //setup the game
    do
    {
        Display();
        Input();
        isWin = CheckWin();
        if(isWin)
        {  
            break;
        }
    } while (moves);
    
    //win or lose
    if(isWin)
    {
        Display();
        printf("\n\n\t\t\e[1;92m ----- HURRAY YOU WON -------- \e[0m\n");
    }
    else
    {
        Display();
        printf("\n\n\t\t\e[1;91m ----- YOU LOSE! TRY AGAIN :-( -------- \e[0m\n");
    }
     printf("\n\n\n\n");
     printf("\t\t\e[1;93m \2 \2 thank you for playing....  \2 \2 \e[0m\n\n\n");
     Sleep(8000);
     return 0;
}

void Display()
{
    system("cls");
    printf("\n\n\tHello :\e[0;93m %s \2 \2 \e[0m \n", playerName);
    if(moves > 100)
    {
        printf("\n\t\e[1;92mYour remaining moves : %d\e[0m\n\n", moves);
    }
    else
    {
        printf("\n\t\e[1;91mYour remaining moves : %d\e[0m\n\n", moves);
    }
    // printf("\t\e[4;32mRemaing Moves:\e[0m \e[1;92m%d\e[0m\n\n", moves);
    printf("  \e[0;35m__________________________________________\e[0m \n");
    printf("  \e[0;35m|          |         |         |         |\e[0m \n");
    printf("  \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m \n",board[0][0], board[0][1],board[0][2], board[0][3]);
    printf("  \e[0;35m|__________|_________|_________|_________|\n");
    printf("  \e[0;35m|          |         |         |         |\n");
    printf("  \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m \n", board[1][0], board[1][1],board[1][2], board[1][3]);
    printf("  \e[0;35m|__________|_________|_________|_________|\n");
    printf("  \e[0;35m|          |         |         |         |\n");
    printf("  \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m \n", board[2][0], board[2][1],board[2][2], board[2][3]);
    printf("  \e[0;35m|__________|_________|_________|_________|\n");
    printf("  \e[0;35m|          |         |         |         |\n");
    printf("  \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m \n", board[3][0], board[3][1],board[3][2], board[3][3]);
    printf("  \e[0;35m|__________|_________|_________|_________|\e[0m \n");

    printf("\n");
}

void Input()
{
    while(1)
    {
        fflush(stdin);
        printf("\n  \e[1;94mPress \30  to move Blank-Tile \e[1;96m'UP'\n");
        printf("  \e[1;94mPress \31  to move Blank-Tile \e[1;96m'DOWN'\n");
        printf("  \e[1;94mPress <- to move Blank-Tile \e[1;96m'LEFT'\n");
        printf("  \e[1;94mPress \32  to move Blank-Tile \e[1;96m'RIGHT'\n\n");
        printf("  \e[1;95mPress 'e' or 'E' to exit the game any time.\n");
        int exitButton = 0;
        exitButton = getch();
        if(exitButton == 69 || exitButton == 101)
        {
            system("cls");
            printf("\n\n\n\tThank You For Playing This Game, I Hope You Enjoyed It .......\n");
            printf("\n\n\n\tSee ya' Later .......\n");
            printf("\n\n\t\e[1;93mExiting The Game .......\e[0m\n\n\n");
            Sleep(7000);
            exit(EXIT_SUCCESS);
        }
        PlayerMove = getch(); // there are 2 getch() because arrow keys are special it sends 2 signals
        int isValid = ValidMove();
        if(isValid)
        {
            // 'i' and 'j' will contain indexed position of blanktile and 'temp' is used in swap of tiles
            int i, j, temp = 0;

            for (int ti = 0; ti < 4; ti++)
            {
                for (int tj = 0; tj < 4; tj++)
                {
                    if(board[ti][tj] == 0)
                    {
                        i = ti;  // ith index of BlankTile
                        j = tj; //  jth index of BlankTile
                        break;
                    }
                }
            }

            //if player press the 'UP' key swap the position of blank tile with its upper tile
            if (PlayerMove == 72)
            {
                int tempi = i, tempj = j;
                // tempi--;
                tempi++;
                temp = board[tempi][tempj];
                board[tempi][tempj] = board[i][j];
                board[i][j] = temp;
                
            }  //if player press the 'DOWN' key swap the position of blank tile with its below tile
            else if(PlayerMove == 80)
            {

                int tempi = i, tempj = j;
                tempi--;
                // tempi++;
                temp = board[tempi][tempj];
                board[tempi][tempj] = board[i][j];
                board[i][j] = temp;

            }  //if player press the 'LEFT' key swap the position of blank tile with its left tile
            else if(PlayerMove == 75)
            {

                int tempi = i, tempj = j;
                tempj++;
                // tempj--;
                temp = board[tempi][tempj];
                board[tempi][tempj] = board[i][j];
                board[i][j] = temp;

            }  //if player press the 'RIGHT' key swap the position of blank tile with its right tile
            else if(PlayerMove == 77)
            {

                int tempi = i, tempj = j;
                tempj--;
                // tempj++;
                temp = board[tempi][tempj];
                board[tempi][tempj] = board[i][j];
                board[i][j] = temp;

            }
            moves--;
            return;
        }
        else //if pressed for invalid location
        {
            Display();
            printf("     \e[1;91mInvalid Move!!\e[0m\n");
        }
    }  
}


int ValidMove()
{
    int i= 0, j = 0;

    for (int ti = 0; ti < 4; ti++)
    {
        for (int tj = 0; tj < 4; tj++)
        {
            if(board[ti][tj] == 0)
            {
                i = ti;
                j = tj;
                break;
            }
        }
    }    

    //checking for player input if valid or not based on manipulating the index of tile
    if (PlayerMove == 72)
    {

        i++;
        // i--;
    }
    else if(PlayerMove == 80)
    {
        i--;
        // i++;
    }
    else if(PlayerMove == 75)
    {
        j++;
        // j--;
    }
    else if(PlayerMove == 77)
    {
        j--;
        // j++;
    }


    if((i >= 0 && i <= 3) && (j >= 0 && j <= 3))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CheckWin()
{
    int notWin = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(WinningBoard[i][j] != board[i][j])
            {
                notWin = 1;
                break;
            }
        }
        if(notWin)
        {
            break;
        }
    }

    if(!notWin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void RuleDisplay()
{
    system("cls");
    printf("\n\n\t\t\t\t___________________________________________\n");
    printf("\t\t\t\t|\e[0;106m                                         \e[0m|\n");
    printf("\t\t\t\t|\e[0;106m                                         \e[0m|\n");
    printf("\t\t\t\t|\e[0;106m          \e[0m \e[1;93m RULE OF THIS GAME \e[0m \e[0;106m          \e[0m|\n");
    printf("\t\t\t\t|\e[0;106m                                         \e[0m|\n");
    printf("\t\t\t\t|\e[0;106m                                         \e[0m|\n");
    printf("\t\t\t\t-------------------------------------------\n");

    printf("\t________________________________________________________________________________________\n");
    printf("\t|\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("\t|   \e[4;35m\e[4;32m1. You can move only 1 step at a time by ARROW key\e[0m\t\t\t\t        |\n");
    printf("\t|\t    \e[1;94mPress \30  to move Blank-Tile \e[1;96m'UP'\e[0m\t\t\t\t\t\t|\n");
    printf("\t|\t    \e[1;94mPress \31  to move Blank-Tile \e[1;96m'DOWN'\e[0m\t\t\t\t\t\t|\n");
    printf("\t|\t    \e[1;94mPress <- to move Blank-Tile \e[1;96m'LEFT'\e[0m\t\t\t\t\t\t|\n");
    printf("\t|\t    \e[1;94mPress \32  to move Blank-Tile \e[1;96m'RIGHT'\e[0m\t\t\t\t\t\t|\n\t|\t\t\t\t\t\t\t\t\t\t\t|");
    printf("\n\t|    \e[4;32m2. You can move number at empty position only\e[0m\t\t\t\t\t|\n");
    printf("\t|    \e[4;32m3. For each valid move : you total number of move will decreased by 1\e[0m\t        |\n");
    printf("\t|    \e[4;32m4. Winning situation : number in a 4x4 matrix should be in order from 1 to 15\e[0m      |\n");
    printf("\t|   \t\t\t\t\t\t\t\t\t\t\t|\n\t|\t\e[1;36mWinning Situation: \e[0m                                                             |\n");
    printf("\t|   \e[0;35m__________________________________________\e[0m                             \t\t|\n");
    printf("\t|   \e[0;35m|          |         |         |         |\e[0m                             \t\t|\n");
    printf("\t|   \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m                              \t\t|\n",1, 2, 3, 4);
    printf("\t|   \e[0;35m|__________|_________|_________|_________|                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|          |         |         |         |                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m                              \t\t|\n", 5, 6, 7, 8);
    printf("\t|   \e[0;35m|__________|_________|_________|_________|                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|          |         |         |         |                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m                              \t\t|\n", 9, 10, 11, 12);
    printf("\t|   \e[0;35m|__________|_________|_________|_________|                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|          |         |         |         |                             \e[0m\t\t|\n");
    printf("\t|   \e[0;35m|    \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|   \e[1;93m%2d\e[0m    \e[0;35m|\e[0m                              \t\t|\n", 13, 14, 15, 0);
    printf("\t|   \e[0;35m|__________|_________|_________|_________|\e[0m                              \t\t|\n");
    printf("\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t|    \e[4;32m5. You can exit the game at any time by pressing 'E' or 'e' \e[0m        \t\t|\n");
    printf("\t|    \t\t\e[0;95mSo Try to win in minimum number of moves\e[0m\t\t\t\t|\n\t|                             \t\t\t\t\t\t\t\t|\n");
    printf("\t|   \t\t\t\e[0;95mHappy Gaming , Good Luck \e[0m                            \t\t|\n");
    printf("\t|\t\t\t\t\t\t\t\t\t\t\t|\n\t|   \e[1;93m Press any key to start \2 \2 \2 \2 \e[0m                           \t\t\t\t|\n");
    printf("\t|_______________________________________________________________________________________|\n");
    getch();
}

void PlayerNameInput()
{
    system("cls");
    printf("\n\n\n");
    printf("\t  \e[1;96mPlease Enter Your Name :\e[1;93m ");
    //fgets(playerName, 8, stdin);
    scanf("%9s", playerName);
    fflush(stdin);
    printf("\n\n\n\t\t   \e[0m\e[1;94m*********************   \e[4;32mT H A N K Y O U !!!!\e[0m  \e[1;94m*************************\e[0m\n");
    printf("\t \e[1;94m*********************   \e[1;91m\2  \2  Now, Let's Begin The Game  \2  \2 \e[0m  \e[1;94m*************************\e[0m\n");
    printf("\n\n\n\n \t\e[0;96m Press Any Key To Start The Game ..... ");
    getch();
}


void RandomGen()
{
    int randArray[15] = {0};
    int x, p;
    int count;
    int i=0;
    int upper = 15, lower = 1; //range [1-15]
    srand(time(NULL));

    for(count = 0; count < 15; count++)
    {
        randArray[count] = (rand() % (upper - lower + 1)) + lower;
    }

    while(i < 15)
    {
        int r = (rand() % (upper - lower + 1)) + lower;

        for (x = 0; x < i; x++)
        {
            if(randArray[x] == r){
                break;
            }
        }
        if(x==i)
        {
            randArray[i++]=r;
        }
    }

    int flag = 0, k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == 3 && j == 3)
            {
                flag = 1;
                break;
            }
            else
            {
                board[i][j] = randArray[k++];
            }
        }   
        if(flag) break;
    }  
}
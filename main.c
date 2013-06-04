/*
* Author SJ Zhu @ USTC
*/
#include<stdio.h>
#define LEN 8
/*
 *global variables
 */
int Direct[8][2] = {{0, -1}, {0, 1}, { -1, 0}, {1, 0}, { -1, -1}, {1, -1}, { -1, 1}, {1, 1}};
//left,right,up,down,up-left,down-left,up-right,down-right
int pointValue[8][8] =
{
    {1000, -150, 30, 10, 10, 30, -150, 1000},
    { -150, -250, 0, 0, 0, 0, -250, -150},
    {30, 0, 1, 2, 2, 1, 0, 30},
    {10, 0, 2, 16, 16, 2, 0, 10},
    {10, 0, 2, 16, 16, 2, 0, 10},
    {30, 0, 1, 2, 2, 1, 0, 30},
    { -150, -250, 0, 0, 0, 0, -250, -150},
    {1000, -150, 30, 10, 10, 30, -150, 1000}
};
int originBoard[8][8] =
{
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1,  1,  0, -1, -1, -1},
    { -1, -1, -1,  0,  1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1, -1},
};
int colorComputer = 0;
int colorPerson = 1;
/*
 *function declare
 */
void guess(int board[][LEN], int ans[][LEN], int color);
int isCapable(int board[][LEN], int i, int j, int color);
void allDirection(int board[][LEN], int i, int j, int color, int direction[8]);
void change(int board[][LEN], int i, int j, int color);
int count(int array[][LEN], int thing);
void printBoard(int board[][LEN]);
void cpBoard(int boardA[][LEN], int boardB[][LEN]);
int boardValue(int board[][LEN], int color);
void AI(int board[][LEN], int depth, int steptogo[2]);
int alphaBeta(int board[LEN][LEN], int alpha, int beta, int color, int depth);

/*
 * main code
 */

//main to play
/*
int main(void)
{
    int board[LEN][LEN], ans[LEN][LEN];
    int colorCurrent, colorWinner, countComputer, countPerson, countStep;
    //    int i, j;
    //    for(i = 0; i < LEN; i++)
    //        for(j = 0; j < LEN; j++)
    //            scanf("%d", &board[i][j]);
    cpBoard(board, originBoard);

    printf("++++\n");
    printf("color for Person %d\ncolor for Computer %d\n", colorPerson, colorComputer);
    colorCurrent = colorComputer;

    int flag=0;
    while (1)
    {
        int p, q;

        printBoard(board);
        printf("++++\n");

        if (colorCurrent == 1) printf("Person\n");
        else printf("Computer\n");

        guess(board, ans, colorCurrent);
        countStep = count(ans, 1);
        printf("available step counts:%d\n", countStep);

        if (countStep == 0)
        {
            if(flag=0)
            {
                flag++;
                colorCurrent = colorCurrent ^ 1;
                continue;
            }
            else
                {
                    break;
                }
        }
        else
        {
            flag=0;
        }

        //printBoard(ans);
        printf("input step\n");

        if (colorCurrent == 0)
            //That colorCurrent is 0 means it's Computer's turn.
        {
            int steptogo[2];
            AI(board, 4, steptogo);
            p = steptogo[0]; q = steptogo[1];
            printf("%d %d\n", p, q);
        }
        else
            //It's Person's turn
        {
            //int i,j;
            //for(i=0; i<8; i++)
            //    for(j=0; j<8; j++)
            //        if(ans[i][j]==1)
            //            printf("%d %d %d\n",i,j,pointValue[i][j]);
            while (1)
            {
                scanf("%d%d", &p, &q);
                if (ans[p][q] != 1) printf("False,again\n");
                else break;
            }
        }

        printf("++++\n");
        board[p][q] = colorCurrent;
        change(board, p, q, colorCurrent);
        countComputer = count(board, colorComputer);
        countPerson = count(board, colorPerson);


        //Judge who is winner
        
        if (countComputer + countPerson == LEN * LEN)
        {
            break;
        }

        //Change the current player
        colorCurrent = !colorCurrent;
    }
    colorWinner = (countComputer > countPerson ? countComputer : countPerson);
    if (countComputer == countPerson)colorWinner = -2;
    if (colorWinner == -2)printf("Draw\n");
    
    else printf("Winner : %s\n", (colorWinner == colorPerson ? "Person" : "Computer"));
    return 0;
}
*/

void guess(int board[][LEN], int ans[][LEN], int color)
//list all the capble place to put
{
    int i, j;
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if (isCapable(board, i, j, color) == 1) ans[i][j] = 1;
            else ans[i][j] = 0;
        }
    }
}

int isCapable(int board[][LEN], int i, int j, int color)
//is capable to place the chess
{
    int k, p;

    if (board[i][j] != -1)
        return 0;

    for (p = 0; p < 8; p++)
    {
        if (i + Direct[p][0] >= LEN || i + Direct[p][0] < 0 || j + Direct[p][1] >= LEN || j + Direct[p][1] < 0) continue;
        if (board[i + Direct[p][0]][j + Direct[p][1]] != (!color)) continue;
        for (k = 2; (i + Direct[p][0] * k < LEN) && (i + Direct[p][0] * k >= 0) &&
                (j + Direct[p][1] * k < LEN) && (j + Direct[p][1] * k >= 0); k++)
        {
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == -1) break;
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == color) return 1;
        }
    }

    return 0;
}

void allDirection(int board[][LEN], int i, int j, int color, int direction[8])
//list all the direction that can change color,similar to function isCapable()
{
    int k, p;

    for (p = 0; p < 8; p++) direction[p] = 0;

    for (p = 0; p < 8; p++)
    {
        if (i + Direct[p][0] >= LEN || i + Direct[p][0] < 0 || j + Direct[p][1] >= LEN || j + Direct[p][1] < 0) continue;
        if (board[i + Direct[p][0]][j + Direct[p][1]] != (!color)) continue;
        for (k = 2; (i + Direct[p][0] * k < LEN) && (i + Direct[p][0] * k >= 0) &&
                (j + Direct[p][1] * k < LEN) && (j + Direct[p][1] * k >= 0); k++)
        {
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == -1) break;
            if (board[i + Direct[p][0] * k][j + Direct[p][1] * k] == color) direction[p] = 1;
        }
    }
}

void change(int board[][LEN], int i, int j, int color)
//change the color
{
    int p, k, direction[8];
    board[i][j] = color;
    allDirection(board, i, j, color, direction);
    for (p = 0; p < 8; p++)
    {
        if (direction[p])
        {
            for (k = 1; board[i + Direct[p][0] * k][j + Direct[p][1] * k] != color; k++)
                board[i + Direct[p][0] * k][j + Direct[p][1] * k] = color;
        }
    }
}

int count(int array[][LEN], int thing)
//count how many 'thing' in the 'array'
{
    int i, j, sum;
    for (i = 0, sum = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
            if (array[i][j] == thing)
                sum++;
    return sum;
}

void printBoard(int board[][LEN])
{
    int i, j;
    for (i = 1; i >= 0; i--)
    {
        printf("   ");
        for (j = 0; j < LEN; j++) printf("%2c", i ? '0' + j : '-');
        printf("\n");
    }

    for (i = 0; i < LEN; i++)
    {
        printf("%2d|", i);
        for (j = 0; j < LEN; j++)
            if (board[i][j] == -1)printf("  ");
            else printf("%2d", board[i][j]);
        printf("\n");
    }
}

void cpBoard(int boardA[][LEN], int boardB[][LEN])
//copy boradB to boardA
{
    int i, j;
    for (i = 0; i < LEN; i++)
        for (j = 0; j < LEN; j++)
            boardA[i][j] = boardB[i][j];
}

int boardValue(int board[][LEN], int color)
{
    int i, j, sum = 0;
    int ans[LEN][LEN],sign[2];
    sign[colorComputer] = 1; sign[colorPerson] = -1;
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if(board[i][j]!=color && board[i][j]!=(!color))continue;
            sum += pointValue[i][j] * sign[board[i][j]] * 3;
        }
    }
    // guess(board, ans, color);
    // for (i = 0; i < LEN; i++)
    // {
    //     for (j = 0; j < LEN; j++)
    //     {
    //         if (ans[i][j] == 0)continue;
    //         else sum+= pointValue[i][j];
    //         }
    // }
    guess(board, ans, !color);
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if (ans[i][j] == 0)continue;
            else sum -= pointValue[i][j] * 3;
            }
    }
    return sum;
}


void AI(int board[][LEN], int depth, int steptogo[2])
{
    int ans[LEN][LEN];
    int i, j, val;
    int max = -9999;
    guess(board, ans, colorComputer);
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if (ans[i][j] == 1)
            {
                int board2[LEN][LEN];
                cpBoard(board2, board);
                change(board2, i, j, colorComputer);
                val = -1*alphaBeta(board2, -9999, 9999, !colorComputer, depth);
                //printf("%d %d %d\n", val, i, j);
                if (val > max)
                {
                    max = val;
                    steptogo[0] = i;
                    steptogo[1] = j;
                }
            }
        }
    }
}

int alphaBeta(int board[LEN][LEN], int alpha, int beta, int color, int depth)
{
    int max, val, i, j;
    int sign[2], ans[LEN][LEN];
    max = -9999;
    sign[colorComputer] = 1; sign[colorPerson] = -1;

    if (depth <= 0) return sign[color] * boardValue(board, colorComputer);

    guess(board, ans, color);
    //printBoard(board);
    //printf("%d %d\n",count(ans,1),color);
    if (count(ans, 1) == 0)
    {
        guess(board, ans, !color);
        if (count(ans, 1) == 0) return sign[color] * boardValue(board, colorComputer);
        else return -1 * alphaBeta(board, -1 * beta, -1 * alpha, !color, depth);
    }
    for (i = 0; i < LEN; i++)
    {
        for (j = 0; j < LEN; j++)
        {
            if (ans[i][j] == 1)
            {
                int board2[LEN][LEN];
                cpBoard(board2, board);
                change(board2, i, j, color);
                val = -1 * alphaBeta(board2, -1 * beta, -1 * alpha, !color, depth - 1);
                //printf("+++%d %d\n", val, depth);
                if (val > alpha)
                {
                    if (val >= beta)return val;
                    alpha = val;
                }
                if (val > max)max = val;
            }
        }
    }
    return max;
}

// main to contest
int main(void)
{
    int board[LEN][LEN];//, ans[LEN][LEN], computerStep[2];
    int i, j, p, q, temp;
    for(i = 0; i < LEN; i++)
        for(j = 0; j < LEN; j++)
        {
            scanf("%d", &temp);
            board[i][j] = temp - 1; //now -1 means no chess; 0 means mine; 1 means opponent;
        }
    int steptogo[2];
    AI(board, 4, steptogo);
    p = steptogo[0]; q = steptogo[1];
    printf("%d %d\n", p, q);
    return 0;
}

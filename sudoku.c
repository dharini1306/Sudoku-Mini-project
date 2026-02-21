#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define HINT_LIMIT 3

// Easy Puzzle
int easy[9][9] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

// Solution for easy
int solution[9][9] = {
    {5,3,4,6,7,8,9,1,2},
    {6,7,2,1,9,5,3,4,8},
    {1,9,8,3,4,2,5,6,7},
    {8,5,9,7,6,1,4,2,3},
    {4,2,6,8,5,3,7,9,1},
    {7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},
    {2,8,7,4,1,9,6,3,5},
    {3,4,5,2,8,6,1,7,9}
};

void printBoard(int board[9][9]) {
    printf("\n");
    for(int i=0;i<9;i++) {
        if(i%3==0 && i!=0)
            printf("---------------------\n");
        for(int j=0;j<9;j++) {
            if(j%3==0 && j!=0)
                printf("| ");
            if(board[i][j]==0)
                printf(". ");
            else
                printf("%d ",board[i][j]);
        }
        printf("\n");
    }
}

int isValid(int board[9][9], int row, int col, int num) {

    for(int i=0;i<9;i++)
        if(board[row][i]==num)
            return 0;

    for(int i=0;i<9;i++)
        if(board[i][col]==num)
            return 0;

    int startRow = row - row%3;
    int startCol = col - col%3;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[startRow+i][startCol+j]==num)
                return 0;

    return 1;
}

int isComplete(int board[9][9]) {
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(board[i][j]==0)
                return 0;
    return 1;
}

int main() {

    int board[9][9];
    int row,col,num;
    int wrong_attempts=0;
    int hints_used=0;

    time_t start,end;
    start = time(NULL);

    // Copy puzzle to board
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            board[i][j]=easy[i][j];

    printf("==== SUDOKU GAME ====\n");
    printf("You have %d hints\n",HINT_LIMIT);

    while(!isComplete(board)) {

        printBoard(board);

        printf("\nEnter row (1-9) col (1-9) num (1-9)\n");
        printf("Enter 0 0 0 for hint\n");
        scanf("%d %d %d",&row,&col,&num);

        if(row==0 && col==0 && num==0) {
            if(hints_used < HINT_LIMIT) {
                for(int i=0;i<9;i++) {
                    for(int j=0;j<9;j++) {
                        if(board[i][j]==0) {
                            board[i][j]=solution[i][j];
                            hints_used++;
                            printf("Hint used! Remaining: %d\n",HINT_LIMIT-hints_used);
                            goto next;
                        }
                    }
                }
            } else {
                printf("No hints left!\n");
            }
        }
        else {
            row--; col--;

            if(row>=0 && row<9 && col>=0 && col<9 && num>=1 && num<=9) {

                if(easy[row][col]!=0) {
                    printf("Cannot change fixed cell!\n");
                }
                else if(solution[row][col]==num) {
                    board[row][col]=num;
                }
                else {
                    printf("Wrong move!\n");
                    wrong_attempts++;
                }
            }
            else {
                printf("Invalid input!\n");
            }
        }

        next:;
    }

    end = time(NULL);
    double time_taken = difftime(end,start);

    printf("\n🎉 Congratulations! You solved it!\n");
    printf("Time Taken: %.2f seconds\n",time_taken);
    printf("Wrong Attempts: %d\n",wrong_attempts);

    int score = 1000 - (int)time_taken - (wrong_attempts*10) - (hints_used*20);
    if(score<0) score=0;

    printf("Your Score: %d\n",score);

    if(time_taken < 300)
        printf("Performance: Excellent!\n");
    else if(time_taken < 600)
        printf("Performance: Good!\n");
    else
        printf("Performance: Practice More!\n");

    return 0;
}

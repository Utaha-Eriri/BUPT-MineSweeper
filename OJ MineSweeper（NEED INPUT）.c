#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int open;
    int mine;
    int mark;
    int count;
} Cell;

int ROWS, COLS, MINES,di;
Cell board[100][100];
int opened_count, count;

void init_board() 
{
    int i, j, k;
    int di, ni, dj, nj;
    memset(board, 0, sizeof(board));
    for (k = 0; k < MINES; k++) {
        do {
            i = rand() % ROWS;
            j = rand() % COLS;
        } while (board[i][j].mine); 
        board[i][j].mine = 1;
        
        for (di = -1; di <= 1; di++) {
            for (dj = -1; dj <= 1; dj++) {
                ni = i + di, nj = j + dj;
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                    board[ni][nj].count++;
                }
            }
        }
    }
    opened_count = 0; 
count = 0;

}

int open_cell(int i, int j) {
    int di, dj ;
    if (board[i][j].open || (board[i][j].mark == 2))
{
return 0;
}

    board[i][j].open = 1;

    if (board[i][j].mine) 
{
return 1;
}

opened_count ++;

    if (board[i][j].count == 0) {
        
        for (di = -1; di <= 1; di++) {
            for (dj = -1; dj <= 1; dj++) {
                int ni = i + di, nj = j + dj;
                if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                    (void)open_cell(ni, nj);
                }
            }
        }
    }

return 0;
}

void mark_cell(int i, int j, int mark) {

if (mark == 2)
{
if ((board[i][j].mark == 3) || (board[i][j].open == 0))
{
board[i][j].mark = mark;
} 

MINES --;

}
else if (mark == 3)
{
if ((board[i][j].mark == 2))
{
board[i][j].mark = mark;
MINES ++;
} 
else if ((board[i][j].open == 0))
{
board[i][j].mark = mark;
} 

}
else if (mark == 4)
{
board[i][j].mark = 0;
if (board[i][j].mark == 2)
{
MINES ++;
} 
}
}

int double_click(int i, int j) {
    int ni,di,  dj, nj;
    if (!board[i][j].open) return 0;
    if (board[i][j].mark) return 0;
    int mine_count = 0, mark_count = 0, ret = 0;

    for (di = -1; di <= 1; di++) {
        for (dj = -1; dj <= 1; dj++) {
            ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                if (board[ni][nj].mark == 2) 
{
mark_count++;
if (board[ni][nj].mine)
{
mine_count++;
}
else
{
return 1;
}

             }
            }
        }
    }

    if (mine_count != board[i][j].count) return 0;

    for (di = -1; di <= 1; di++) {
        for (dj = -1; dj <= 1; dj++) {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && (board[ni][nj].open == 0 && board[ni][nj].mark == 0)) {
                ret = open_cell(ni, nj);
if (ret == 1)
{
return ret;
}
            }
        }
    }
    return 0;
}

void print_norm_board() {
    int i, j;
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                if (board[i][j].open)
                    printf("%d", board[i][j].count);
                else if (board[i][j].mark == 2)
                    printf("!");
                else if (board[i][j].mark == 3)
                    printf("?");
                else
                    printf(".");
            }
            printf("\n");
        }
}
void print_board() {
    int i, j;

    for (i = 0; i < ROWS; i++) 
{
        for (j = 0; j < COLS; j++) 
{
if (board[i][j].mine)
                printf("*");
else if (board[i][j].open)
                printf("%d", board[i][j].count);
            else if (board[i][j].mark == 2)
                printf("!");
            else if (board[i][j].mark == 3)
                printf("?");
            else
                printf(".");
        }
        printf("\n");
    }
}

int main() {
    int level, x, y, op, i, j;
    int di, ni, dj, nj, minecount;
int ret = 0;
    char c[50] = {0};
    scanf("%d", &level);
    switch (level) {
        case 1:
     {
            ROWS = 9; COLS = 9; MINES = 10; 
break;
     }
        case 2:
     {
            ROWS = 16; COLS = 16; MINES = 40; 
break;
     }
        case 3:
            ROWS = 16; COLS = 30; MINES = 99; 
break;
        case 4:
            scanf("%d %d %d", &ROWS, &COLS, &MINES); break;
    }

    minecount = MINES;
    memset(board, 0, sizeof(board));
    getchar();

    for (i = 0; i < ROWS; i++) 
{
    memset(c, 0, sizeof(c));
scanf("%s", c);
        for (j = 0; j < COLS; j++) 
{
            if (c[j] == '*') 
{
                board[i][j].mine = 1;
                for (di = -1; di <= 1; di++) {
                    for (dj = -1; dj <= 1; dj++) {
                        ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                            board[ni][nj].count++;
                        }
                    }
                }
            }
        }
        getchar();
    }

opened_count = 0;
    
    while (1) 
{
count++;
scanf("%d %d %d", &op, &x, &y);

        switch (op) {
            case 1:
                ret = open_cell(x-1, y-1); 
break;
            case 2:
                mark_cell(x-1, y-1, 2); break;
            case 3:
                mark_cell(x-1, y-1, 3); break;
            case 4:
                mark_cell(x-1, y-1, 4); break;
            case 9:
                ret = double_click(x-1, y-1); break;
            default:
                break;
        }

        if (opened_count + minecount >= ROWS * COLS || ret == 1) {
            
            break;
        }
        printf("Game in progress\n");
        printf("%d %d\n", count, MINES);
        print_norm_board();
    }

    if (opened_count + minecount >= ROWS * COLS)
{
        printf("Game over, you win\n");
    }
else
{
        printf("Hit mine, you lose\n");
    } 
    printf("%d %d\n", count, MINES);
    print_board();
    
    return 0;
}

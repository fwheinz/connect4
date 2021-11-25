#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"

/* Canvas dimensions */
#define WIDTH 800
#define HEIGHT 650
#define MARGIN 10

/* Board dimensions */
#define XSIZE 7
#define YSIZE 6

/* Number of pieces in a row for winning condition */
#define WINCOUNT 4

/* The calculated tilesize (performed in createCanvas) */
int tilesize;

int clickedColumn (void);
void drawBoard (GWindow gw);
void announceWinner (GWindow gw, int winner);

int board[XSIZE][YSIZE];

/*
 * A player drops a single piece into a specific column
 * Parameters: player - Number of player (1 or 2)
 *             column - Column index (starting with 0)
 * Returns: 1, if the move was valid
 *          0, if the move was invalid (column index invalid
 *             or column already full)
 */
int playerMove (int player, int column) {
    if (column < 0 || column >= YSIZE)
        return 0;
    for (int i = YSIZE-1; i >= 0; i--) {
        if (board[column][i] == 0) {
            board[column][i] = player;
            return 1;
        }
    }


    return 0;
}


/*
 * Checks the board if a winning condition is fulfilled.
 * Parameters: none
 * Returns: 1 if player 1 has won
 *          2 if player 2 has won
 *          3 on draw
 *          0 if no ending condition is reached
 */
int checkWinner (void) {
    for (int x = 0; x < XSIZE; x++) {
        int count = 0, lastPlayer = 0;
        for (int y = 0; y < YSIZE; y++) {
            int player = board[x][y];
            if (player == lastPlayer) {
                count++;
            } else {
                count = 1;
                lastPlayer = player;
            }
            if (count >= WINCOUNT && player > 0) {
                return player;
            }
        }
    }

    for (int y = 0; y < YSIZE; y++) {
        int count = 0, lastPlayer = 0;
        for (int x = 0; x < XSIZE; x++) {
            int player = board[x][y];
            if (player == lastPlayer) {
                count++;
            } else {
                count = 1;
                lastPlayer = player;
            }
            if (count >= WINCOUNT && player > 0) {
                return player;
            }
        }
    }

    for (int x = -YSIZE+1; x < XSIZE; x++) {
        int count = 0, lastPlayer = 0;
        for (int y = 0; y < YSIZE; y++) {
            if ((x+y) < 0 || (x+y) >= XSIZE)
                continue;
            int player = board[x+y][y];
            if (player == lastPlayer) {
                count++;
            } else {
                count = 1;
                lastPlayer = player;
            }
            if (count >= WINCOUNT && player > 0) {
                return player;
            }
        }
    }


    return 0;
}


/*
 * Main game loop.
 * Parameters: gw - The canvas of the board
 */
void play (GWindow gw) {
    int winner = 0, player = 1;

    while (!winner) {
        int column = clickedColumn();
        int legal = playerMove(player, column);
        if (legal) {
            player = (player == 1) ? 2 : 1;
            drawBoard(gw);
            winner = checkWinner();
        }
    }
    announceWinner(gw, winner);
}


/*
 * Waits for a mouse click into a column.
 * Parameters: none
 * Returns: Number of column
 */
int clickedColumn (void) {
    int column = -1;
    do {
        // Wait for a mouse click event
        GEvent e = waitForEvent(MOUSE_CLICKED);
        if (e != NULL && getEventType(e) == MOUSE_CLICKED) {
            // Calculate the column index from the x coordinate of the click
            double x = getX(e);
            int col = (x - MARGIN)/tilesize;
            if (col >= 0 && col < XSIZE)
                column = col;
        }
    } while (column < 0 || column >= XSIZE);

    return column;
}

/*
 * Draws the board on the given canvas.
 * Parameter: gw - the canvas
 */
void drawBoard (GWindow gw) {
    // Always redraw the whole board from scratch
    clearGWindow(gw);

    // Draw the vertical lines of the board
    for (int x = 0; x <= XSIZE; x++) {
        drawLine(gw, x*tilesize+MARGIN, MARGIN, x*tilesize+MARGIN, YSIZE*tilesize+MARGIN);
    }

    // Draw the horizontal lines of the board
    for (int y = 0; y <= YSIZE; y++) {
        drawLine(gw, MARGIN, y*tilesize+MARGIN, XSIZE*tilesize+MARGIN, y*tilesize+MARGIN);
    }

    // Set each stone here
    for (int x = 0; x < XSIZE; x++) {
        for (int y = 0; y < YSIZE; y++) {
            int stone = board[x][y]; // TODO: Get actual board value here
            if (stone == 1) {
                setColor(gw, "RED");
            } else if (stone == 2) {
                setColor(gw, "BLUE");
            }
            if (stone > 0) {
                fillOval(gw, x * tilesize + MARGIN, y * tilesize + MARGIN, tilesize, tilesize);
            }
        }
    }
}

/*
 * Announce the winner of the game.
 * Parameters: gw     - The canvas to announce the winner
 *             winner - The number of the player who won
 * Returns: nothing
 */
void announceWinner (GWindow gw, int winner) {
    GLabel win;
    if (winner == 1) {
        win = newGLabel("Red has won!");
    } else if (winner == 2) {
        win = newGLabel("Blue has won!");
    } else {
        win = newGLabel("The game ends in a draw");
    }
    setColor(win, "BLACK");
    setFont(win, "ARIAL-30");

    int x = (WIDTH-getWidth(win))/2;
    int y = HEIGHT - getHeight(win) - MARGIN;
    addAt(gw, win, x, y);
}

GWindow createCanvas (void) {
    GWindow gw = newGWindow(WIDTH, HEIGHT);
    requestFocus(gw);
    int t1 = (WIDTH-2*MARGIN)/(XSIZE);
    int t2 = (HEIGHT-2*MARGIN)/YSIZE;
    tilesize = (t1 > t2) ? t2 : t1;

    return gw;
}

int main (void) {
    GWindow gw = createCanvas();
    drawBoard(gw);
    play(gw);

    pause(5000);
    closeGWindow(gw);

    return 0;
}

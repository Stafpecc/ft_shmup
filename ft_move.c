#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>

/*Movement function*/
void mvup(Player *myPlayer) {
    if (myPlayer->yLoc > 2)
        myPlayer->yLoc -= 2;
}

void mvdown(Player *myPlayer) {
    if (myPlayer->yLoc < myPlayer->yMax - 3)
        myPlayer->yLoc += 2;
}

void mvleft(Player *myPlayer) {
    if (myPlayer->xLoc > 2)
        myPlayer->xLoc -= 2;
}

void mvright(Player *myPlayer) {
    if (myPlayer->xLoc < myPlayer->xMax - 3)
        myPlayer->xLoc += 2;
}

/*Movement player input function*/
void getmv(Player *myPlayer, int xMax, int yMax, int choice, WINDOW *playwin, Player *allEnemies) {
    flushinp();
    static time_t lastShotTime = 0;
    time_t currentTime = time(NULL);
    char c = '|';
    if (choice != ' ' && choice != 'x')
        mvwaddch(playwin, myPlayer->yLoc, myPlayer->xLoc, ' ');

    switch (choice) {
        case (int)'w':
            mvup(myPlayer);
            break;
        case (int)'s':
            mvdown(myPlayer);
            break;
        case (int)'a':
            mvleft(myPlayer);
            break;
        case (int)'d':
            mvright(myPlayer);
            break;
        case (int)' ':
            if (difftime(currentTime, lastShotTime) >= 1.5) {
                shoot(myPlayer, xMax, yMax, '|', playwin, allEnemies);
                lastShotTime = currentTime;
            }
            break;
        case (int)'x':
            endwin();
            exit(0);
        default:
            break;
    }
    display(myPlayer);
}

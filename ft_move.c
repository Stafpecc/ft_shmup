#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>

/*Movement function*/
void mvup(Player *myPlayer) {
    if (myPlayer->yLoc > 2)
        myPlayer->yLoc -= 2;
}

void mvdown(Player *myPlayer) {
    if (myPlayer->yLoc < myPlayer->yMax - 14)
        myPlayer->yLoc += 2;
}

void mvleft(Player *myPlayer) {
    if (myPlayer->xLoc > 2)
        myPlayer->xLoc -= 2;
}

void mvright(Player *myPlayer) {
    if (myPlayer->xLoc < myPlayer->xMax - 15)
        myPlayer->xLoc += 2;
}

/*Movement player input function*/
void getmv(Player *myPlayer, int xMax, int yMax, int choice, WINDOW *playwin, Player *allEnemies) {
    flushinp();
    static time_t lastShotTime = 0;
    static time_t lastBallTime = 0;
    static time_t lastFireTime = 0;
    static time_t lastRotatifTime = 0;
    static time_t lastDiagTime = 0;
     time_t currentDiagTime = time(NULL);
    time_t currentRotatifTime = time(NULL);
    time_t currentFireTime = time(NULL);
    time_t currentTime = time(NULL);
    time_t currentBallTime = time(NULL);
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
        case (int)'g':
            if (difftime(currentBallTime, lastBallTime) >= 5) {
                fireBigBall(myPlayer, playwin, allEnemies, NUM_ENEMIES, xMax, yMax);
                lastBallTime = currentBallTime;
            }
            break;
        case (int)'q':
            if (difftime(currentFireTime, lastFireTime) >= 10) {
                firePowerfulShot(myPlayer, playwin, xMax, yMax, allEnemies, NUM_ENEMIES);
                lastFireTime = currentFireTime;
            }
            break;
        case (int)'e':
            if (difftime(currentRotatifTime, lastRotatifTime) >= 3) {
                fireRotatingLaser(myPlayer, playwin, xMax, yMax, allEnemies, NUM_ENEMIES);
                lastRotatifTime = currentRotatifTime;
            }
            break;
        case (int)' ':
            if (difftime(currentTime, lastShotTime) >= 1) {
                shoot(myPlayer, xMax, yMax, '|', playwin, allEnemies);
                lastShotTime = currentTime;
            }
            break;
        case (int)'c':
            if (difftime(currentDiagTime, lastDiagTime) >= 5) {
                fireDiagonalStars(myPlayer, playwin, xMax, yMax, allEnemies, NUM_ENEMIES);
                lastDiagTime = currentDiagTime;
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

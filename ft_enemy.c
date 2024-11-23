#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_ENEMIES 5
#define MIN_TIR_INTERVAL 142
#define MAX_TIR_INTERVAL 1000

/*Shoot enemy function*/
void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin) {
    Player s = newplayer(enemy->xLoc, enemy->yLoc + 1, xMax, yMax, c, playwin);
    while (s.yLoc < yMax) {
        mvwaddch(playwin, s.yLoc, s.xLoc, s.character);
        wrefresh(playwin);
        napms(50);
        mvwaddch(playwin, s.yLoc, s.xLoc, ' ');
        s.yLoc++;
    }
}

void *enemyThread(void *arg) {
    Player *enemy = (Player *)arg;
    int xMax = enemy->xMax;
    int yMax = enemy->yMax;
    WINDOW *playwin = enemy->currWindow;

    while (1) {
        enemyShootRandomly(enemy, xMax, yMax, '|', playwin);
    }
    return NULL;
}

/*Shoot randomly function*/
void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin) {
    int delay = rand() % MAX_TIR_INTERVAL + MIN_TIR_INTERVAL;
    napms(delay);
    shootEnemy(enemy, xMax, yMax, c, playwin);
}

/*Movement enemy function*/
void moveEnemy(Player *enemy, int xMax) {

}

/*Enemy function*/
void enemy(WINDOW *playwin, int xMax, int yMax) {
	mvwaddch(playwin, 5, 25, 'Y');
    wrefresh(playwin);
}


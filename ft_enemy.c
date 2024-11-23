#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_ENEMIES 5
#define MAX_TIR_INTERVAL 1042
#define MIN_TIR_INTERVAL 142

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

void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin, clock_t *lastShotTime) {
    clock_t currentTime = clock();
    if (((double)(currentTime - *lastShotTime) / CLOCKS_PER_SEC) < 1)
        return;
    *lastShotTime = currentTime;
    int shotX = rand() % xMax; 
    Player s = newplayer(shotX, enemy->yLoc + 1, xMax, yMax, c, playwin);
    while (s.yLoc < yMax) {
        mvwaddch(playwin, s.yLoc, s.xLoc, s.character);
        wrefresh(playwin);
        napms(50);
        mvwaddch(playwin, s.yLoc, s.xLoc, ' ');
        s.yLoc++;
    }
}

void moveEnemy(Player *enemy, int xMax, int yMax, WINDOW *playwin) {
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, ' ');
    int direction = (rand() % 2 == 0) ? -1 : 1;
    int newX = enemy->xLoc + direction;
    if (newX >= enemy->xLoc - 3 && newX <= enemy->xLoc + 3 && newX > 0 && newX < xMax - 1) {
        enemy->xLoc = newX;
    }
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, enemy->character);
}

void displayEnemy(Player *myEnemy, WINDOW *playwin) {
    mvwaddch(playwin, myEnemy->yLoc, myEnemy->xLoc, myEnemy->character);
}

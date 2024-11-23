#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_ENEMIES 5
#define MIN_TIR_INTERVAL 1
#define MAX_TIR_INTERVAL 3

/*Shoot enemy function*/
void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin) {
	int currentTime = time(NULL);
	Player s = newplayer(enemy->xLoc, enemy->yLoc - 1, xMax, yMax, c, playwin);
	if (currentTime - enemy->lastShotTime >= MIN_TIR_INTERVAL + rand() % (MAX_TIR_INTERVAL - MIN_TIR_INTERVAL + 1))
	{
		while (s.yLoc <= 0) {
			mvwaddch(playwin, s.yLoc, s.xLoc, s.character);
			wrefresh(playwin);
			napms(20);
			mvwaddch(playwin, s.yLoc, s.xLoc, ' ');
			s.yLoc++;
			enemy->lastShotTime = currentTime;
		}
	}
}

/*Movement enemy function*/
void moveEnemy(Player *enemy, int xMax) {
    if (enemy->xLoc > 0)
        enemy->xLoc--;
}

/*Print enemy function*/
void displayEnemy(Player *enemy, WINDOW *playwin, int xMax, int yMax) {
    if (enemy->yLoc >= 0 && enemy->yLoc < yMax && enemy->xLoc >= 0 && enemy->xLoc < xMax) {
        mvwaddch(playwin, enemy->yLoc, enemy->xLoc, 'Y');
        wrefresh(playwin);
    }
}

/*Enemy function*/
void enemy(WINDOW *playwin, int xMax, int yMax) {
    srand(time(NULL));
    Player enemies[MAX_ENEMIES];
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].xLoc = rand() % xMax;
        enemies[i].yLoc = rand() % (yMax / 2);
        enemies[i].lastShotTime = time(NULL);
    }

    while (1) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            moveEnemy(&enemies[i], yMax);
            displayEnemy(&enemies[i], playwin, xMax, yMax);
            shootEnemy(&enemies[i], xMax, yMax, '|', playwin);
        }
        wrefresh(playwin);
        usleep(50000);
    }
}

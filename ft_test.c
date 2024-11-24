#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int specialShotCounter = 0;

int main(void) {
    srand(time(NULL));
    initscr();
    raw();
    curs_set(0);
    timeout(10);
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    if (xMax == 0 || yMax == 0) {
        endwin();
        exit(1);
    }

    WINDOW *win = newwin((yMax - 10), (xMax - 10), 5, 5);
    WINDOW *playwin = newwin((yMax - 10), (xMax - 10), 5, 5);
    WINDOW *scorewin = newwin((yMax / 18), xMax - 10, yMax - 5, 5);

    start_color();
    assume_default_colors(COLOR_RED, COLOR_BLACK);
    wborder(win, '{', '}', '*', '*', '#', '#', '#', '#');
    wrefresh(win);
    wborder(playwin, '{', '}', '*', '*', '#', '#', '#', '#');
    wrefresh(playwin);
    wborder(scorewin, '{', '}', '*', '*', '#', '#', '#', '#');
    wrefresh(scorewin);

    Player p = newplayer(10, 10, xMax, yMax, '@', playwin, 1);
    display(&p);
    wrefresh(playwin);
    nodelay(playwin, TRUE);

    EnemyMovement enemyMovements[NUM_ENEMIES];
    Player enemies[NUM_ENEMIES];
    clock_t lastEnemyShotTimes[NUM_ENEMIES];
    time_t startSpecialShotTimes[NUM_ENEMIES];

    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i] = newplayer(rand() % xMax, rand() % (yMax / 3), xMax, yMax, 'Y', playwin, 1);
        lastEnemyShotTimes[i] = clock();
        enemyMovements[i].lastMoveTime = clock();
        enemyMovements[i].direction = 1;
        display(&enemies[i]);
    }

    GameTimer gameTimer = initTimer();

    startSpecialShotForEnemies(enemies, NUM_ENEMIES, startSpecialShotTimes);

    int seconds = 0, minutes = 0;

    while (1) 
	{
        clear();
		for (int i = 0; i < NUM_ENEMIES; i++) 
		{
    		if (enemies[i].alive == 1) {
        		moveEnemy(&enemies[i], xMax, yMax, playwin, &enemyMovements[i]);
        		enemyShootRandomly(&enemies[i], xMax, yMax, '|', playwin, &lastEnemyShotTimes[i], &startSpecialShotTimes[i]);
        		displayEnemy(&enemies[i], playwin);
				if (rand() % 100 < 1) 
					fireSpecialLaser(&enemies[i], xMax, yMax, playwin);
        	}
			int ch = wgetch(playwin);
			if (ch != ERR)
				if (ch == 'x')
					break; 
			getmv(&p, xMax, yMax, ch, playwin, enemies);
		}
        napms(16);
		updateBullets(playwin, yMax);
		updateGameTimer(&seconds, &minutes, scorewin, yMax);
        display(&p);
	}
       
    getch();
    endwin();

    return 0;
}

#include "ft_shmup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void asteroid(int xMax, int yMax, WINDOW *playwin) {
    Asteroid asteroid;
  	asteroid.xLoc = rand() % xMax;
	asteroid.yLoc = rand() % yMax; 

    asteroid.character = '#';

    for (int i = 0; i < 7; i++) {
        if (i == 0 || i == 1) {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, asteroid.character);
        } else if (i == 2 || i == 3) {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 1, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 1, asteroid.character);
        } else {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 2, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 1, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 1, asteroid.character);
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 2, asteroid.character);
        }
        wrefresh(playwin);
        napms(2);

        if (i == 0 || i == 1) {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, ' ');
        } else if (i == 2 || i == 3) {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 1, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 1, ' ');
        } else {
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 2, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc - 1, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 1, ' ');
            mvwaddch(playwin, asteroid.yLoc + i, asteroid.xLoc + 2, ' ');
        }
        wrefresh(playwin);
    }
}

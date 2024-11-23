#include "ft_shmup.h"
#include <ncurses.h>

/*Movement function*/
void mvup(Player *myPlayer) {
	if (myPlayer->yLoc > 1)
		myPlayer->yLoc--;
}

void mvdown(Player *myPlayer) {
	if (myPlayer->yLoc < myPlayer->yMax - 2)
		myPlayer->yLoc++;
}

void mvleft(Player *myPlayer) {
	if (myPlayer->xLoc > 1)
		myPlayer->xLoc--;
}

void mvright(Player *myPlayer) {
	if (myPlayer->xLoc < myPlayer->xMax - 2)
		myPlayer->xLoc++;
}

/*Shooting function*/
void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin) {
	Player s = newplayer(myPlayer->xLoc, myPlayer->yLoc - 1, xMax, yMax, c, playwin);
	while (s.yLoc >= 0) {
		mvwaddch(playwin, s.yLoc, s.xLoc, s.character);
		wrefresh(playwin);
		napms(20);
		mvwaddch(playwin, s.yLoc, s.xLoc, ' ');
		s.yLoc--;
	}
}
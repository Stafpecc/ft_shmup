#include "ft_shmup.h"
#include <ncurses.h>

/*Movement function*/
void mvup(Player *myPlayer) {
    if (myPlayer->yLoc > 1)
        myPlayer->yLoc--;
}

void mvdown(Player *myPlayer, int yMax) {
    myPlayer->yLoc++;
    if (myPlayer->yLoc > yMax - 2)
        myPlayer->yLoc = yMax--;
}

void mvleft(Player *myPlayer) {
    if (myPlayer->xLoc > 1)
        myPlayer->xLoc--;
}

void mvright(Player *myPlayer, int xMax) {
    myPlayer->xLoc++;
    if (myPlayer->xLoc > xMax - 2)
        myPlayer->xLoc = xMax--;
}

void validatePosition(Player *myPlayer, int xMax, int yMax) {

    if (myPlayer->yLoc < 1) myPlayer->yLoc = 1;

    if (myPlayer->yLoc > yMax - 2) myPlayer->yLoc = yMax - 2;

    if (myPlayer->xLoc < 1) myPlayer->xLoc = 1;

    if (myPlayer->xLoc > xMax - 2) myPlayer->xLoc = xMax - 2;

    printf("Validated Position: xLoc=%d, yLoc=%d, xMax=%d, yMax=%d\n", 
           myPlayer->xLoc, myPlayer->yLoc, xMax, yMax);
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
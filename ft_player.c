#include "ft_shmup.h"
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

/*Create new player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow) {
	Player thePlayer = {xLoc,yLoc, xMax,yMax, character, currWindow};
	return thePlayer;
}

/*Movement player input function*/
int getmv(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin) {
	flushinp();
	int choice = wgetch(myPlayer->currWindow);
	static time_t lastShotTime = 0;
	time_t currentTime = time(NULL);
	
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
			if (difftime(currentTime, lastShotTime) >= 1/5) {
				shoot(myPlayer, xMax, yMax, '|', playwin);
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
	return choice;
}

/*Print player function*/
void display(Player *myPlayer) {
	werase(myPlayer->currWindow);
	box(myPlayer->currWindow, 0, 0);
	mvwaddch(myPlayer->currWindow, myPlayer->yLoc, myPlayer->xLoc, myPlayer->character);
	wrefresh(myPlayer->currWindow);
}
#include "ft_shmup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/*Create new player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow, int alive) {
        Player thePlayer = {xLoc,yLoc, xMax,yMax, character, currWindow, alive};
        return thePlayer;
}

/*Print player function*/
void display(Player *myPlayer) {
    box(myPlayer->currWindow, 0, 0);
    mvwaddch(myPlayer->currWindow, myPlayer->yLoc, myPlayer->xLoc, myPlayer->character);
}


void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin, Player *enemies) {
    Player s = newplayer(myPlayer->xLoc, myPlayer->yLoc - 1, xMax, yMax, c, playwin, 1);
    while (s.yLoc >= 0) {
        mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", "|||");
        wrefresh(playwin);
		if (s.yLoc == 1) {
			s.yLoc = yMax - 14;
			while (s.yLoc >= 0) {
        		mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", "   ");
        		if (isEnemyonBullet(s.xLoc, s.yLoc, enemies) == 1 || 
            		isEnemyonBullet(s.xLoc - 1, s.yLoc, enemies) == 1 || 
            		isEnemyonBullet(s.xLoc + 1, s.yLoc, enemies) == 1) {
						
            			mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", " ");
						mvwprintw(playwin, s.yLoc, s.xLoc, "%s", " ");
						mvwprintw(playwin, s.yLoc, s.xLoc + 1, "%s", " ");
            			wrefresh(playwin);
            			removeEnemy(playwin, s.xLoc, s.yLoc, enemies);
						currentScore += 4200;
				}
			napms(2);
			s.yLoc--;
			wrefresh(playwin);
			}
    	}
		s.yLoc--;
	}
}

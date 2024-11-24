#include "ft_shmup.h"
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

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

void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin, Player *allEnemies)
{
    Player s = newplayer(myPlayer->xLoc, myPlayer->yLoc - 1, xMax, yMax, c, playwin, 1);
    while (s.yLoc >= 0) 
    {
        mvwprintw(playwin, s.yLoc , s.xLoc - 1, "%s", "|||");
        wrefresh(playwin);
        mvwprintw(playwin, yMax - 11 , s.xLoc - 3, "%s", "PEW PEW");
        if (s.yLoc == 1)
        {
            s.yLoc = yMax - 11;
            mvwprintw(playwin, s.yLoc , s.xLoc - 1, "%s", "NO!");
            while (s.yLoc >= 0)
            {
                if (s.yLoc == 'Y')
                {
                    mvwprintw(playwin, s.yLoc - 1 , s.xLoc - 1, "%s", "*");
                    mvwprintw(playwin, s.yLoc , s.xLoc - 1, "%s", "*");
                    napms(1);
                    mvwprintw(playwin, s.yLoc - 1 , s.xLoc - 1, "%s", " ");
                    mvwprintw(playwin, s.yLoc , s.xLoc - 1, "%s", "");
                }
                mvwprintw(playwin, s.yLoc , s.xLoc - 1, "%s", " ");
                s.yLoc--;
                wrefresh(playwin);
            }

        }
	if (isEnemyonBullet(playwin, s.xLoc, s.yLoc) == 1 || 
    	isEnemyonBullet(playwin, s.xLoc - 1, s.yLoc) == 1 || 
    	isEnemyonBullet(playwin, s.xLoc + 1, s.yLoc) == 1) 
	{
    	mvwprintw(playwin, s.yLoc - 1, s.xLoc - 1, "%s", "*");
    	mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", "*");
    	wrefresh(playwin);
    	napms(16);
    	mvwprintw(playwin, s.yLoc - 1, s.xLoc - 1, "%s", " ");
    	mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", " ");
    	wrefresh(playwin);
    	removeEnemy(playwin, s.xLoc, s.yLoc, allEnemies);
	}
        napms(3);
        s.yLoc--;
	}
}

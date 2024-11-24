#include "ft_shmup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BULLETS 4200000
Bullet bullets[MAX_BULLETS];

int updateBullets(WINDOW *playwin, int yMax, int xMax, int life, WINDOW *scorewin, Player player)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            if (bullets[i].yLoc == player.yLoc && bullets[i].xLoc == player.xLoc)
            {
                life--;
                if (life == 0)
                    return 0;

                mvwprintw(scorewin, yMax/18 - 2, xMax - 13 - life, "%s", "#");
                mvwprintw(scorewin, yMax/18 - 3, xMax - 12 - 3, " %01d", life);
                wrefresh(scorewin);

                mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, ' ');
                bullets[i].active = false;
                bullets[i].xLoc = 0;
                bullets[i].yLoc = 0;
            }
        }

        if (bullets[i].active)
        {
            mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, ' ');
            bullets[i].yLoc++;

            if (bullets[i].yLoc >= yMax)
                bullets[i].active = false;
            else
                mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, bullets[i].character);
        }
    }

    return life;
}


Bullet bullets[MAX_BULLETS];

void  initBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
    }
}

void    createShot(int x, int y, char c)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].xLoc = x;
            bullets[i].yLoc = y;
            bullets[i].character = c;
            bullets[i].active = true;
            break;
        }
    }
}
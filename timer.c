#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static clock_t lastUpdate = 0;

GameTimer initTimer() 
{
    GameTimer timer;
    timer.startTime = time(NULL);
    timer.minutes = 0;
    timer.seconds = 0;
    return timer;
}

void updateGameTimer(int *seconds, int *minutes, WINDOW *scorewin, int yMax) 
{
    clock_t currentTime = time(NULL);
    double elapsedSeconds = (double)(currentTime - lastUpdate) / CLOCKS_PER_SEC;

   if (currentTime > lastUpdate) 
	{ 
        (*seconds)++;
        if (*seconds >= 60) 
		{
            *minutes += 1;
            *seconds = 0;
        }
        lastUpdate = currentTime;
		mvwprintw(scorewin, yMax/18 - 3, 1, "%s", "Time :");
        mvwprintw(scorewin, yMax/18 - 2, 1, "%02d:%02d", *minutes, *seconds);
        wrefresh(scorewin);
  }
}

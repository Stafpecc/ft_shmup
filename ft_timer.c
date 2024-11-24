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

void updateGameTimer(int *seconds, int *minutes, WINDOW *scorewin, int yMax, int xMax) 
{
    clock_t currentTime = time(NULL);

    if (currentTime > lastUpdate) 
	{ 
        (*seconds)++;
        if (*seconds >= 60) 
		{
            *minutes += 1;
            *seconds = 0;
			currentScore += 4200;
        }
		currentScore += 42;
        lastUpdate = currentTime;
		mvwprintw(scorewin, yMax/18 - 3, xMax/2 - 10, "%s", "Score :");
		mvwprintw(scorewin, yMax/18 - 2, xMax/2 - 10, "%010d", currentScore);
		wrefresh(scorewin);
		mvwprintw(scorewin, yMax/18 - 3, 1, "%s", "Time :");
        mvwprintw(scorewin, yMax/18 - 2, 1, "%02d:%02d", *minutes, *seconds);
        wrefresh(scorewin);
  }
}

void init_score(WINDOW *scorewin, int yMax, int xMax)
{
	char life_point[] = "++++";
    mvwprintw(scorewin, yMax/18 - 3, xMax - 12 - (int)strlen("Life Point : 10 "), "%s", "Life Point :");	
	mvwprintw(scorewin, yMax/18 - 3, xMax - 12 - 3, "%d", 4);
    mvwprintw(scorewin, yMax/18 - 2, xMax - 12 - (int)strlen(life_point), "%s", life_point);
	wrefresh(scorewin);
}

void end(WINDOW *playwin)
{
            wclear(playwin);
			wrefresh(playwin);
			printw("......RIP....  Score : %d", currentScore);
			refresh();
			napms(1500);
			endwin();
			exit (1);
}

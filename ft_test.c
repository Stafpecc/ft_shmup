#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int specialShotCounter = 0;
int currentScore = 0;
int NUM_ENEMIES = 0;

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
    start_color();
    assume_default_colors(COLOR_RED, COLOR_BLACK);
    wborder(win, '{', '}', '*', '*', '#', '#', '#', '#');
    refresh();
	int choice = start_display(win, yMax, xMax);
	float speed =  check_level(win, xMax, yMax, choice);
    wrefresh(win);
	
    endwin();

    WINDOW *playwin = newwin((yMax - 10), (xMax - 10), 5, 5);
	WINDOW *scorewin = newwin((yMax / 18), xMax - 10 , yMax - 5, 5);
    start_color();
    assume_default_colors(COLOR_RED, COLOR_BLACK);
	wborder(scorewin, '{', '}', '*', '*', '#', '#', '#', '#');
	wrefresh(scorewin);
	
    struct Player p = newplayer(10, 10, xMax, yMax, '@', playwin, 1);
    display(&p);
    wrefresh(playwin);
	nodelay(playwin, TRUE);
	EnemyMovement	enemyMovements[NUM_ENEMIES];
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
	int seconds = 0;
	int minutes = 0;
	GameTimer gameTimer = initTimer();
	init_score(scorewin, yMax, xMax);
	int life = 4;
	startSpecialShotForEnemies(enemies, NUM_ENEMIES, startSpecialShotTimes);
    while (1) 
	{
        clear();
		for (int i = 0; i < NUM_ENEMIES; i++) 
		{
			if (enemies[i].alive == 1) {
            	moveEnemy(&enemies[i], xMax, yMax, playwin, &enemyMovements[i]);
          		enemyShootRandomly(&enemies[i], xMax, yMax, '|', playwin, &lastEnemyShotTimes[i], &startSpecialShotTimes[i]);
				if (rand() % 100 < 1) 
					fireSpecialLaser(&enemies[i], xMax, yMax, playwin);
				displayEnemy(&enemies[i], playwin);
			}
        	int ch = wgetch(playwin);
			if (ch != ERR)
				if (ch == 'x')
					break; 
			getmv(&p, xMax, yMax, ch, playwin, &enemies[i]);
		}
		life = updateBullets(playwin, yMax, xMax, life, scorewin, p);
		if (life == 0)
		{
			wclear(playwin);
			wrefresh(playwin);
			mvwprintw(win, yMax/2, xMax/2 - (int)strlen("You loose....")/2, "%s", "You loose....");
			wrefresh(playwin);
			napms(1500);
			break;
		}
        napms(16);
		updateBullets(playwin, yMax, xMax, life, scorewin, p);
		updateGameTimer(&seconds, &minutes, scorewin, yMax, xMax);
        display(&p);
        wrefresh(playwin);
    	
	}
    getch();
    endwin();

    return 0;
}

int	start_display(WINDOW *playwin, int yMax, int xMax)
{
	curs_set(0);
	char	title[] = "@robase -- Versus -- Y";
	int center = (int)strlen(title);
	const char selection[] = "Select the level:";
	const char *choices[] = {
		"+---------------+",
        "|   Easy Mode   |",
		"+---------------+",
        "|  Medium Mode  |",
		"+---------------+",
        "|   Hard Mode   |",
		"+---------------+",
        "| Ticasali Mode |",
		"+---------------+"
    };
	keypad(playwin, true);
	int n_choices = sizeof(choices) / sizeof(choices[0]);
	int choice;
	int	highlight = 1;
	wattron(playwin, A_BOLD);
	const char *p = title;
	float	size_char = 1;
	const char ur_name[] = "By: Tarini and Samaouch";
	const char *ptr = ur_name;
	while (*p)
	{
		mvwaddch(playwin, yMax/7, xMax/2 - (center + 0.5 - size_char), *p);
		wrefresh(playwin);
		p++;
		napms(100);
		size_char++;
	}
	size_char = 1;
	wattron(playwin, A_BLINK);
	mvwaddstr(playwin, yMax/3, xMax/2 - (center- 2.5), selection);
	wattroff(playwin, A_BLINK);
	while (*ptr)
	{
		mvwaddch(playwin, yMax - yMax/4, xMax/2 - (center - size_char), *ptr);
		wrefresh(playwin);
		ptr++;
		size_char++;
		napms(100);
	}
	refresh();
	while (1)
	{
		for (int i = 0; i < n_choices; i++)
		{
			if (i == highlight)
				wattron(playwin, A_REVERSE);
			mvwprintw(playwin, yMax/2.5 + (i), xMax/2 - (center - 2), "%s", choices[i]);
			wattroff(playwin, A_REVERSE);
		}
		choice = wgetch(playwin);
		switch (choice)
		{
			case KEY_UP:
				if (highlight == 1)
					highlight = 2;
				if (highlight % 2 == 1)
					highlight -= 2;
				else
					highlight--;
				break;
			case KEY_DOWN:
				if (highlight == n_choices - 2)
					highlight -= 1;
				if (highlight % 2 == 1)
					highlight += 2;
				else
					highlight++;
				break;
			default:
				break;
		}
		if (choice == 10)
			break;
	}
	clear();
	wrefresh(playwin);
	wattroff(playwin, A_BOLD);
	refresh();
	return (highlight);
}

float check_level(WINDOW *win, int xMax, int yMax, int choice)
{
	float speed = 0;
	char Ticasali[] = "Ticasali Mode!... good luck";
	if (choice == 1)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Easy Mode"), "%s", "Easy Mode");
		speed = 1;
		NUM_ENEMIES = 20;

	}
	else if (choice == 3)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Medium Mode"), "%s", "Medium Mode");
		speed = 1;
		NUM_ENEMIES = 30;

	}
	else if (choice == 5)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Hard Mode"), "%s", "Hard Mode");
		speed = 0.5;
		NUM_ENEMIES = 40;

	}
	else if (choice == 7)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen(Ticasali), "%s", Ticasali);
		speed = 0;
		NUM_ENEMIES = 45;
	}
    wrefresh(win);
	int i = 10;
	mvwprintw(win, yMax/2, xMax/2 - 2, "%d", i);
	wrefresh(win);
	mvwprintw(win, yMax/2, xMax/2 - 2	, "%s", "   ");
	i--;
	while (i > 0)
	{
		mvwprintw(win, yMax/2, xMax/2 - 1, "%d", i);
		i--;
		if (i == 0)
			mvwprintw(win, yMax/2, xMax/2 - strlen("Go !"), "%s", "Go !");
		wrefresh(win);
		napms(500);
	}
	return (speed);
}


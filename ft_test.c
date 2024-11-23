#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM_ENEMIES 20

void	start_display(WINDOW *playwin, int yMax, int xMax);

int main(void) {
    srand(time(NULL));
    initscr();
    raw();
    curs_set(0);
    timeout(100);
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
    wrefresh(win);
    start_display(win, yMax, xMax);
    wrefresh(win);

    endwin();

    WINDOW *playwin = newwin((yMax - 10), (xMax - 10), 5, 5);
    start_color();
    assume_default_colors(COLOR_RED, COLOR_BLACK);
    wborder(playwin, '{', '}', '*', '*', '#', '#', '#', '#');

    struct Player p = newplayer(10, 10, xMax, yMax, '@', playwin);
    display(&p);
    wrefresh(playwin);

    Player enemies[NUM_ENEMIES];
    clock_t lastEnemyShotTimes[NUM_ENEMIES];
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i] = newplayer(rand() % xMax, rand() % (yMax / 3), xMax, yMax, 'Y', playwin);
        lastEnemyShotTimes[i] = clock();
        display(&enemies[i]);
    }

    while (1) {
        clear();

        int ch = getmv(&p, xMax, yMax, '|', playwin);
        if (ch == 'x') 
            break;

        for (int i = 0; i < NUM_ENEMIES; i++) {
            moveEnemy(&enemies[i], xMax, yMax, playwin);
            enemyShootRandomly(&enemies[i], xMax, yMax, '|', playwin, &lastEnemyShotTimes[i]);
            displayEnemy(&enemies[i], playwin);
        }

        display(&p);
        wrefresh(playwin);
        napms(100);
    }

    getch();
    endwin();

    return 0;
}

void	start_display(WINDOW *playwin, int yMax, int xMax)
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
		mvwaddch(playwin, yMax/2.5 - 40, xMax/2 - (center - size_char), *p);
		wrefresh(playwin);
		p++;
		napms(100);
		size_char++;
	}
	size_char = 1;
	wattron(playwin, A_BLINK);
	mvwaddstr(playwin, yMax/2 - 25, xMax/2 - (center- 2.5), selection);
	wattroff(playwin, A_BLINK);
	while (*ptr)
	{
		mvwaddch(playwin, yMax/2 + 25, xMax/2 - (center - size_char), *ptr);
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
			mvwprintw(playwin, yMax/4 + (i), xMax/2 - (center - 2), "%s", choices[i]);
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
	refresh();
	wattroff(playwin, A_BOLD);
	refresh();
}

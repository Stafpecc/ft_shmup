#include "ft_shmup.h"

int main(int ac, char **av) {	
	initscr();
	noecho();
	cbreak();

	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW *playwin = newwin(20, 50, (yMax/2)-10, 10);
	box(playwin, 0, 0);
	wrefresh(playwin);

	struct Player p = newplayer(1, 1, xMax, yMax, '@', playwin);
	while (getmv(&p, xMax, yMax, '|', playwin) != 'x') {
		display(&p);
		wrefresh(playwin);
	}

	getch();
	endwin();
	
	return 0;
}
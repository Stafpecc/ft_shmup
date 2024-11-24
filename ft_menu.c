#include "ft_shmup.h"

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
	char Ticasali[] = "You selected Ticasali, Hmm good luck";
	if (choice == 1)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Easy Mode"), "%s", "Easy Mode");
		speed = 1;
		NUM_ENEMIES = 10;
	}
	else if (choice == 3)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Medium Mode"), "%s", "Medium Mode");
		speed = 1;
		NUM_ENEMIES = 20;
	}
	else if (choice == 5)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen("Hard Mode"), "%s", "Hard Mode");
		speed = 0.5;
		NUM_ENEMIES = 30;
	}
	else if (choice == 7)
	{
		mvwprintw(win, yMax/3, xMax/2 - (int)strlen(Ticasali), "%s", Ticasali);
		speed = 0;
		NUM_ENEMIES = 50;
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
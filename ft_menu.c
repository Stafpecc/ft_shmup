#include "ft_shmup.h"
#include <string.h>

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
	refresh();
	wattroff(playwin, A_BOLD);
	refresh();
}
#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void) {    
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

    WINDOW *playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    wrefresh(playwin);

    struct Player p = newplayer(10, 10, xMax, yMax, '@', playwin);
    display(&p);
    wrefresh(playwin);

    enemy(playwin, xMax, yMax);

    while (1) {
        int ch = getmv(&p, xMax, yMax, '|', playwin);
        if (ch == 'x')
            break;
        display(&p);
        enemy(playwin, xMax, yMax);
        wrefresh(playwin);
    }  
    getch();
    endwin();
    
    return 0;
}

#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void) {    
    initscr();
    raw();
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
    pthread_t enemy_thread;
    pthread_create(&enemy_thread, NULL, (void *)enemy, (void *)playwin);

    while (1) {
        int ch = getmv(&p, xMax, yMax, '|', playwin);
        if (ch == 'x')
            break;
        display(&p);
        wrefresh(playwin);
    }  
    pthread_cancel(enemy_thread);
    getch();
    endwin();
    
    return 0;
}

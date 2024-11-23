#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ENEMIES 5

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

    WINDOW *playwin = newwin(20, 50, (yMax / 2) - 10, 10);
    box(playwin, 0, 0);
    wrefresh(playwin);

    struct Player p = newplayer(10, 10, xMax, yMax, '@', playwin);
    display(&p);

    struct Player enemies[NUM_ENEMIES];
    pthread_t enemy_threads[NUM_ENEMIES];

    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemies[i] = newplayer(5 + i * 10, 5, xMax, yMax, 'Y', playwin);
        pthread_create(&enemy_threads[i], NULL, enemyThread, (void *)&enemies[i]);
    }

    while (1) {
        int ch = getmv(&p, xMax, yMax, '|', playwin);
        display(&p);

        for (int i = 0; i < NUM_ENEMIES; i++) {
            display(&enemies[i]);
        }

        wrefresh(playwin);

        usleep(50000);
    }

    for (int i = 0; i < NUM_ENEMIES; i++) {
        pthread_join(enemy_threads[i], NULL);
    }

    endwin();
    return 0;
}


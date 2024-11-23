#include "ft_shmup.h"
#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>

/*
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

    WINDOW *playwin = newwin(20, 50, (yMax / 2) - 10, 10);
    box(playwin, 0, 0);
    wrefresh(playwin);

    struct Player p = newplayer(10, 10, xMax, yMax, '@', playwin);
    display(&p);
    wrefresh(playwin);

    struct Player enemyPlayer = newplayer(20, 5, xMax, yMax, 'Y', playwin);

    pthread_t enemy_thread;
    pthread_create(&enemy_thread, NULL, enemyThread, &enemyPlayer);

    while (1) {
        int ch = getmv(&p, xMax, yMax, '|', playwin);
        display(&p);
        enemy(playwin, xMax, yMax);
        wrefresh(playwin);
    }

    pthread_join(enemy_thread, NULL);

    getch();
    endwin();

    return 0;
}
*/
#define NUM_ENEMIES 3

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

    pthread_mutex_lock(&display_mutex);
    werase(playwin);
    box(playwin, 0, 0);

    // Afficher le joueur
    display(&p);

    // Afficher tous les ennemis
    for (int i = 0; i < NUM_ENEMIES; i++) {
        display(&enemies[i]);
    }

    wrefresh(playwin);
    pthread_mutex_unlock(&display_mutex);
}


    for (int i = 0; i < NUM_ENEMIES; i++) {
        pthread_join(enemy_threads[i], NULL);
    }

    endwin();
    return 0;
}

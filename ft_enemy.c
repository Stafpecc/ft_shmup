#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_ENEMIES 5
#define MIN_TIR_INTERVAL 1
#define MAX_TIR_INTERVAL 3

/*Shoot enemy function*/
void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin) {

}

/*Movement enemy function*/
void moveEnemy(Player *enemy, int xMax) {

}

/*Print enemy function*/
void displayEnemy(Player *enemy, WINDOW *playwin, int xMax, int yMax) {
}

/*Enemy function*/
void enemy(WINDOW *playwin, int xMax, int yMax) {
	mvwaddch(playwin, 5, 25, 'Y');  // Position de l'ennemi
    wrefresh(playwin);
}


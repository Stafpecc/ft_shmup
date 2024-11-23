#ifndef FT_SHMUP_H
#define FT_SHMUP_H

#include <ncurses.h>
#include <stdint.h>
#include <time.h>

typedef struct Player {
    int xLoc;
    int yLoc;
    int xMax;
    int yMax;
    char character;
    WINDOW* currWindow;
}	Player;

/*Player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow);
void display(Player *myPlayer);

/*Movement function*/
void mvup(Player *myPlayer);
void mvdown(Player *myPlayer);
void mvleft(Player *myPlayer);
void mvright(Player *myPlayer);
int getmv(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin);
void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin);

/*Enemy function*/
void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin);
void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin);
void enemy(WINDOW *playwin, int xMax, int yMax);
void *enemyThread(void *arg);
void *moveEnemyThread(void *arg);

#endif

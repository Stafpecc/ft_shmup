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

Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow);
void mvup(Player *myPlayer);
void mvdown(Player *myPlayer);
void mvleft(Player *myPlayer);
void mvright(Player *myPlayer);
int getmv(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin);
void display(Player *myPlayer);
void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin);

#endif

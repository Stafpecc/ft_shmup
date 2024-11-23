#ifndef FT_SHMUP_H
#define FT_SHMUP_H

#include <ncurses.h>
#include <stdint.h>
#include <time.h>

typedef struct Player {
    int xLoc;
    int yLoc;
    int xMax;
    int Ymax;
    char character;
    WINDOW* currWindow;
}	Player;

Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow);
void mvup(Player *myPlayer);
void mvdown(Player *myPlayer);
void voidmvleft(Player *myPlayer);
void mvright(Player *myPlayer);
int getmv(Player *myPlayer);
void display(Player *myPlayer);
void shoot(Player *myPlayer);

#endif

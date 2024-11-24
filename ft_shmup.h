#ifndef FT_SHMUP_H
#define FT_SHMUP_H

#include <ncurses.h>
#include <stdint.h>
#include <time.h>

static int NUM_ENEMIES = 20;

typedef struct Player 
{
    int xLoc;
    int yLoc;
    int xMax;
    int yMax;
    char character;
    WINDOW* currWindow;
    int alive;
}	Player;

typedef struct Enemy 
{
    clock_t lastMoveTime;
    int direction;
    
} EnemyMovement;

typedef struct Bullet
{
    int xLoc;
    int yLoc;
    char character;
    bool active;
} Bullet;

typedef struct GameTimer {
    time_t startTime;
    int minutes;
    int seconds;
} GameTimer;

/*Menu*/
void	start_display(WINDOW *playwin, int yMax, int xMax);

/*Player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow, int alive);
void display(Player *myPlayer);
void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin, Player *allEnemies);

/*Movement function*/
void mvup(Player *myPlayer);
void mvdown(Player *myPlayer);
void mvleft(Player *myPlayer);
void mvright(Player *myPlayer);
void getmv(Player *myPlayer, int xMax, int yMax, int choice, WINDOW *playwin, Player *allEnemies);

/*Enemy function*/
void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin);
void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin, time_t *lastShotTime);
void moveEnemy(Player *enemy, int xMax, int yMax, WINDOW *playwin, EnemyMovement *movement);
void displayEnemy(Player *myEnemy, WINDOW *playwin);
bool    isEnemyAtposition (Player *enemy, int x);
void    updateBullets(WINDOW *playwin, int yMax);
void    createShot(int x, int y, char c);
void removeEnemy(WINDOW *playwin, int x, int y, Player *myEnemy);
int isEnemyonBullet(WINDOW *playwin, int x, int y);
void enemyLogic(Player *enemies, int xMax, int yMax, WINDOW *playwin, clock_t *lastEnemyShotTimes);

/*Time function*/
GameTimer initTimer();
void updateGameTimer(int *seconds, int *minutes, WINDOW *scorewin, int yMax);

#endif

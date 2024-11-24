#ifndef FT_SHMUP_H
#define FT_SHMUP_H

#include <ncurses.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

extern int specialShotCounter;
extern int NUM_ENEMIES;
extern	int	currentScore;

#define MAX_TIR_INTERVAL 442
#define MIN_TIR_INTERVAL 142

#define SPE_MAX_TIR_INTERVAL 142
#define SPE_MIN_TIR_INTERVAL 42

#define LASER_DURATION yMax - 13

#define SPECIAL_SHOT_DURATION 5
#define NORMAL_SHOT_DURATION 40

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

typedef struct Asteroid {
    int xLoc;
    int yLoc;
    char character;
} Asteroid;

/*Menu*/
int	start_display(WINDOW *playwin, int yMax, int xMax);
void check_level(WINDOW *win, int xMax, int yMax, int choice);

/*Player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow, int alive);
void display(Player *myPlayer);
void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin, Player *allEnemies);
void fireBigBall(Player *p, WINDOW *playwin, Player *enemies, int numEnemies, int xMax, int yMax);
void firePowerfulShot(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies);
void fireRotatingLaser(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies);
void fireDiagonalStars(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies);

/*Movement function*/
void mvup(Player *myPlayer, Player *allEnemies, WINDOW *playwin);
void mvdown(Player *myPlayer, Player *allEnemies, WINDOW *playwin);
void mvleft(Player *myPlayer, Player *allEnemies, WINDOW *playwin);
void mvright(Player *myPlayer, Player *allEnemies, WINDOW *playwin);
void getmv(Player *myPlayer, int xMax, int yMax, int choice, WINDOW *playwin, Player *allEnemies);


/*Enemy function*/
void enemyShootRandomly(Player *enemy, time_t *lastShotTime, time_t *startSpecialShotTime);
void moveEnemy(Player *enemy, int xMax, WINDOW *playwin);
void displayEnemy(Player *myEnemy, WINDOW *playwin);
bool    isEnemyAtposition (Player *enemy, int x);
int    updateBullets(WINDOW *playwin, int yMax, int xMax, int life, WINDOW *scorewin, Player player);
void    createShot(int x, int y, char c);
void removeEnemy(WINDOW *playwin, int x, int y, Player *allEnemies);
int isEnemyonBullet(int x, int y, Player *enemies);
void startSpecialShotForEnemies(int numEnemies, time_t *startSpecialShotTime);
void    createShot(int x, int y, char c);
void asteroid(int xMax, int yMax, WINDOW *playwin) ;


/*Time function*/
GameTimer initTimer();
void updateGameTimer(int *seconds, int *minutes, WINDOW *scorewin, int yMax, int);

/*Life and Score Function*/
void init_score(WINDOW *scorewin, int yMax, int xMax);
void end(WINDOW *playwin);



#endif


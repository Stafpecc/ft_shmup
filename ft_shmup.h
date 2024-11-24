#ifndef FT_SHMUP_H
#define FT_SHMUP_H

#include <ncurses.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

extern int specialShotCounter;
static int NUM_ENEMIES = 0;

#define MAX_TIR_INTERVAL 3042
#define MIN_TIR_INTERVAL 1042

#define SPE_MAX_TIR_INTERVAL 5042
#define SPE_MIN_TIR_INTERVAL 442

#define LASER_DURATION 7

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

/*Menu*/
int	start_display(WINDOW *playwin, int yMax, int xMax);
float check_level(WINDOW *win, int xMax, int yMax, int choice);

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
void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin, time_t *lastShotTime, time_t *startSpecialShotTime);
void moveEnemy(Player *enemy, int xMax, int yMax, WINDOW *playwin, EnemyMovement *movement);
void displayEnemy(Player *myEnemy, WINDOW *playwin);
bool    isEnemyAtposition (Player *enemy, int x);
int    updateBullets(WINDOW *playwin, int yMax, int xMax, int life, WINDOW *scorewin, Player player);
void    createShot(int x, int y, char c);
void removeEnemy(WINDOW *playwin, int x, int y, Player *allEnemies);
int isEnemyonBullet(WINDOW *playwin, int x, int y, Player *enemies);
void startSpecialShotForEnemies(Player *enemies, int numEnemies, time_t *startSpecialShotTime);
void    createShot(int x, int y, char c);
void fireSpecialLaser(Player *enemy, int xMax, int yMax, WINDOW *playwin) ;



/*Time function*/
GameTimer initTimer();
void updateGameTimer(int *seconds, int *minutes, WINDOW *scorewin, int yMax, int xMax);
void init_score(WINDOW *scorewin, int yMax, int xMax);

#endif

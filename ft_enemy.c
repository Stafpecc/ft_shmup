#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_TIR_INTERVAL 542
#define MIN_TIR_INTERVAL 142
#define MAX_BULLETS 50

Bullet bullets[MAX_BULLETS];

void  initBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
    }
}

void    createShot(int x, int y, char c)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].xLoc = x;
            bullets[i].yLoc = y;
            bullets[i].character = c;
            bullets[i].active = true;
            break;
        }
    }
}

void    updateBullets(WINDOW *playwin, int yMax)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, ' ');
            bullets[i].yLoc++;
            if (bullets[i].yLoc >= yMax)
                bullets[i].active = false;
            else
                mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, bullets[i].character);
        }
    }
}

void shootEnemy(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin) 
{
    clock_t currentTime = clock();
    double timeSinceLastShot = (double)clock() / CLOCKS_PER_SEC;
    Player s = newplayer(enemy->xLoc, enemy->yLoc + 1, xMax, yMax, c, playwin, 1);
    if (timeSinceLastShot >= 0.5)
   {
        while (s.yLoc < yMax) {
         mvwaddch(playwin, s.yLoc, s.xLoc, s.character);
            wrefresh(playwin);
            mvwaddch(playwin, s.yLoc, s.xLoc, ' ');
            s.yLoc++;
    }
    }
}

void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin, time_t *lastShotTime) 
{
    time_t currentTime = time(NULL);
    double timeElapsed = difftime(currentTime, *lastShotTime);
    if (timeElapsed >= (rand() % (MAX_TIR_INTERVAL - MIN_TIR_INTERVAL) + MIN_TIR_INTERVAL) / 100.0) 
    {
        *lastShotTime = currentTime;
        createShot(enemy->xLoc, enemy->yLoc + 1, '|');
    }
}

void moveEnemy(Player *enemy, int xMax, int yMax, WINDOW *playwin, EnemyMovement *movement) 
{
    clock_t currentTime = clock();
    double timeSinceLastMove = (double)clock() / CLOCKS_PER_SEC;
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, ' ');
    int direction = (rand() % 2 == 0) ? -1 : 1;
    int newX = enemy->xLoc + direction;
    if (newX >= enemy->xLoc - 20 && newX <= enemy->xLoc + 20 && newX > 0 && newX < xMax - 1) {
        if (isEnemyAtposition(enemy, newX) == false)
            enemy->xLoc = newX;
    }
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, enemy->character);
    napms(5);
}

void displayEnemy(Player *myEnemy, WINDOW *playwin) {
    mvwaddch(playwin, myEnemy->yLoc, myEnemy->xLoc, myEnemy->character);
}

bool    isEnemyAtposition (Player *enemy, int x)
{
    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        if (enemy[i].xLoc == x) 
            return (true);
    }
    return (false);
}

int isEnemyonBullet(WINDOW *playwin, int x, int y) 
{
    return (mvwinch(playwin, y, x) == 'Y');
}

void removeEnemy(WINDOW *playwin, int x, int y, Player *myEnemy) 
{
    mvwaddch(playwin, y, x, ' ');
    myEnemy->alive = 0;
    wrefresh(playwin);
}

void enemyLogic(Player *enemies, int xMax, int yMax, WINDOW *playwin, clock_t *lastEnemyShotTimes) 
{
	EnemyMovement	enemyMovements[NUM_ENEMIES];
    for (int i = 0; i < NUM_ENEMIES; i++) {
        moveEnemy(&enemies[i], xMax, yMax, playwin, &enemyMovements[i]);
        enemyShootRandomly(&enemies[i], xMax, yMax, '|', playwin, &lastEnemyShotTimes[i]);
        displayEnemy(&enemies[i], playwin);
    }
}

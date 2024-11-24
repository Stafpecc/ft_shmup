#include "ft_shmup.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_BULLETS 4200

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

int    updateBullets(WINDOW *playwin, int yMax, int xMax, int life, WINDOW *scorewin, Player player)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            if (bullets[i].yLoc == player.yLoc && bullets[i].xLoc == player.xLoc)
            {
                life--;
                  if (life == 0)
                    return (0);
                mvwprintw(scorewin, yMax/18 - 2, xMax - 13 - life, "%s", "#");
                mvwprintw(scorewin, yMax/18 - 3, xMax - 12 - 3, " %01d", life);
                wrefresh(scorewin);
                bullets[i].yLoc = ' ';
                bullets[i].xLoc = ' ';
                bullets[i].active = false;
                bullets->xLoc = 0;
                bullets->yLoc = 0;
            }
        }     
            mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, ' ');
            bullets[i].yLoc++;
            if (bullets[i].yLoc >= yMax)
                bullets[i].active = false;
            else
                mvwaddch(playwin, bullets[i].yLoc, bullets[i].xLoc, bullets[i].character);
    }

    return (life);
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


void enemyShootRandomly(Player *enemy, int xMax, int yMax, char c, WINDOW *playwin, time_t *lastShotTime, time_t *startSpecialShotTime) 
{
    time_t currentTime = time(NULL);
    double timeElapsed = difftime(currentTime, *lastShotTime);
    double specialShotElapsed = difftime(currentTime, *startSpecialShotTime);

    if (specialShotElapsed <= SPECIAL_SHOT_DURATION) {
        if (specialShotCounter < 2) {
            if (timeElapsed >= (rand() % (SPE_MAX_TIR_INTERVAL - SPE_MIN_TIR_INTERVAL) + SPE_MIN_TIR_INTERVAL) / 1000.0) {
                *lastShotTime = currentTime;
                createShot(enemy->xLoc, enemy->yLoc + 1, '|');
                specialShotCounter++;
            }
        }
    } 
    else if (specialShotElapsed <= (SPECIAL_SHOT_DURATION + NORMAL_SHOT_DURATION)) {
        if (timeElapsed >= (rand() % (MAX_TIR_INTERVAL - MIN_TIR_INTERVAL) + MIN_TIR_INTERVAL) / 1000.0) {
            *lastShotTime = currentTime;
            createShot(enemy->xLoc, enemy->yLoc + 1, '|');
        }
    }


    if (specialShotElapsed >= (SPECIAL_SHOT_DURATION + NORMAL_SHOT_DURATION)) {
        *startSpecialShotTime = currentTime;
        specialShotCounter = 0;
    }
}

void fireSpecialLaser(Player *enemy, int xMax, int yMax, WINDOW *playwin) {
    Bullet bullet;
    bullet.xLoc = enemy->xLoc;
    bullet.yLoc = enemy->yLoc + 1;
    bullet.character = '#';

    for (int i = 0; i < LASER_DURATION; i++) {
        if (i == 0 || i == 1) {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, bullet.character);
        } else if (i == 2 || i == 3) {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 1, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 1, bullet.character);
        } else {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 2, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 1, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 1, bullet.character);
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 2, bullet.character);
        }
        wrefresh(playwin);
        usleep(100000);

        if (i == 0 || i == 1) {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, ' ');
        } else if (i == 2 || i == 3) {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 1, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 1, ' ');
        } else {
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 2, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc - 1, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 1, ' ');
            mvwaddch(playwin, bullet.yLoc + i, bullet.xLoc + 2, ' ');
        }
        wrefresh(playwin);
    }
}


void startSpecialShotForEnemies(Player *enemies, int numEnemies, time_t *startSpecialShotTimes)
{
    for (int i = 0; i < numEnemies; i++) {
        startSpecialShotTimes[i] = time(NULL);
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
    napms(12);
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

int isEnemyonBullet(WINDOW *playwin, int x, int y, Player *enemies) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].xLoc == x && enemies[i].yLoc == y && enemies[i].alive == 1) {
            return 1;
        }
    }
    return 0;
}

void removeEnemy(WINDOW *playwin, int x, int y, Player *enemies) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (enemies[i].xLoc == x && enemies[i].yLoc == y && enemies[i].alive == 1) {
            mvwaddch(playwin, y, x, ' '); 
            enemies[i].alive = 0;
            NUM_ENEMIES--;
            wrefresh(playwin);
            break;
        }
    }
}
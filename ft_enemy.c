#include "ft_shmup.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

void enemyShootRandomly(Player *enemy, time_t *lastShotTime, time_t *startSpecialShotTime) 
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
                napms(1);
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

void startSpecialShotForEnemies(int numEnemies, time_t *startSpecialShotTimes)
{
    for (int i = 0; i < numEnemies; i++) {
        startSpecialShotTimes[i] = time(NULL);
    }
}

void moveEnemy(Player *enemy, int xMax, WINDOW *playwin) 
{
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, ' ');
    int direction = (rand() % 2 == 0) ? -1 : 1;
    int newX = enemy->xLoc + direction;
    if (newX >= enemy->xLoc - 20 && newX <= enemy->xLoc + 20 && newX > 0 && newX < xMax - 1) {
        if (isEnemyAtposition(enemy, newX) == false)
            enemy->xLoc = newX;
    }
    mvwaddch(playwin, enemy->yLoc, enemy->xLoc, enemy->character);
    napms(3);
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

int isEnemyonBullet(int x, int y, Player *enemies) {
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

#include "ft_shmup.h"

#define RADIUS 7
#define LASER_RADIUS 12
#define LASER_LENGTH 15
#define ROTATE_SPEED 5
#define MAX_ROTATIONS 20

#include <ncurses.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void fireBigBall(Player *p, WINDOW *playwin, Player *enemies, int numEnemies, int xMax, int yMax) {
    int centerX = p->xLoc;
    int centerY = p->yLoc;

    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {
            if (x * x + y * y <= RADIUS * RADIUS) {
                int posX = centerX + x;
                int posY = centerY + y;
                
                
                if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                    mvwaddch(playwin, posY, posX, '#');
                }

                
                for (int i = 0; i < numEnemies; i++) {
                    if (enemies[i].alive == 1 && 
                        (posX == enemies[i].xLoc && posY == enemies[i].yLoc)) {
                        enemies[i].alive = 0;
						currentScore += 4200;
                    }
					
                }
            }
        }
    }

    wrefresh(playwin);
    napms(100);
    for (int y = -RADIUS; y <= RADIUS; y++) {
        for (int x = -RADIUS; x <= RADIUS; x++) {
            if (x * x + y * y <= RADIUS * RADIUS) {
                int posX = centerX + x;
                int posY = centerY + y;
                
                
                if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                    mvwaddch(playwin, posY, posX, ' ');
                }
            }
        }
    }

    wrefresh(playwin);
}

void fireRotatingLaser(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies) {
    int centerX = p->xLoc;
    int centerY = p->yLoc - 1;
    int angle = 0;

    for (int rotation = 0; rotation < MAX_ROTATIONS; rotation++) {
        for (int i = 0; i < LASER_LENGTH; i++) {
            int xOffset = (int)(cos(angle * M_PI / 180.0) * i);
            int yOffset = (int)(sin(angle * M_PI / 180.0) * i);

            int posX = centerX + xOffset;
            int posY = centerY + yOffset;

            if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                mvwaddch(playwin, posY, posX, '#');
            }

            for (int i = 0; i < numEnemies; i++) {
                if (enemies[i].alive == 1 && enemies[i].xLoc == posX && enemies[i].yLoc == posY) {
                    enemies[i].alive = 0;
                    currentScore += 4200;
                }
            }
        }

        wrefresh(playwin);
        napms(50);
        for (int i = 0; i < LASER_LENGTH; i++) {
            int xOffset = (int)(cos(angle * M_PI / 180.0) * i);
            int yOffset = (int)(sin(angle * M_PI / 180.0) * i);

            int posX = centerX + xOffset;
            int posY = centerY + yOffset;

            if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                mvwaddch(playwin, posY, posX, ' ');
            }
        }

        angle += ROTATE_SPEED;
        if (angle >= 360) {
            angle = 0;
        }
    }
    for (int i = 0; i < LASER_LENGTH; i++) {
        int xOffset = (int)(cos(angle * M_PI / 180.0) * i);
        int yOffset = (int)(sin(angle * M_PI / 180.0) * i);

        int posX = centerX + xOffset;
        int posY = centerY + yOffset;

        if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
            mvwaddch(playwin, posY, posX, ' ');
        }
    }

    wrefresh(playwin);
}


void firePowerfulShot(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies) {
    int centerX = p->xLoc;
    int centerY = p->yLoc - 1;
    int moveDistance = 1;
    int maxDistance = 15;
    int radius = 5;

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int posX = centerX + x;
                int posY = centerY + y;

                if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                    mvwaddch(playwin, posY, posX, 'O');
                }
            }
        }
    }

    wrefresh(playwin);
    napms(100);

    for (int step = 1; step <= maxDistance; step++) {
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    int posX = centerX + x;
                    int posY = centerY + y + 1;

                    if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                        mvwaddch(playwin, posY, posX, ' ');
                    }
                }
            }
        }

        centerY -= moveDistance;

        if (centerY - radius < 0) {
            break;
        }

        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    int posX = centerX + x;
                    int posY = centerY + y;

                    if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                        mvwaddch(playwin, posY, posX, 'O');
                    }
                }
            }
        }

        for (int i = 0; i < numEnemies; i++) {
            if (enemies[i].alive == 1) {
                for (int y = -radius; y <= radius; y++) {
                    for (int x = -radius; x <= radius; x++) {
                        if (x * x + y * y <= radius * radius) {
                            int posX = centerX + x;
                            int posY = centerY + y;

                            if (enemies[i].xLoc == posX && enemies[i].yLoc == posY) {
                                enemies[i].alive = 0;
                                currentScore += 4200;
                            }
                        }
                    }
                }
            }
        }

        wrefresh(playwin);
        napms(50);
    }

    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int posX = centerX + x;
                int posY = centerY + y;

                if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                    mvwaddch(playwin, posY, posX, ' ');
                }
            }
        }
    }

    wrefresh(playwin);
}


void fireDiagonalStars(Player *p, WINDOW *playwin, int xMax, int yMax, Player *enemies, int numEnemies) {
    int centerX = p->xLoc;
    int centerY = p->yLoc - 1;

    int numDirections = 8;
    int maxSteps = 15;

    int directions[8][2] = {
        {1, 0},    
        {-1, 0},   
        {0, 1},    
        {0, -1},  
        {1, 1},    
        {-1, 1},   
        {1, -1},   
        {-1, -1}  
    };
    for (int i = 0; i < numDirections; i++) {
        int offsetX = directions[i][0];
        int offsetY = directions[i][1]; 
        for (int step = 0; step < maxSteps; step++) {
            int posX = centerX + offsetX * step; 
            int posY = centerY + offsetY * step;  
            if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                mvwaddch(playwin, posY - 1, posX - 1, ' ');
            }  
            for (int j = 0; j < numEnemies; j++) {
                if (enemies[j].alive == 1 && enemies[j].xLoc == posX && enemies[j].yLoc == posY) {
                    enemies[j].alive = 0;
                    currentScore += 4200;
                }
			}
            if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax)
                mvwaddch(playwin, posY, posX, '*');
            wrefresh(playwin);
            napms(5);
        }
    }
    for (int i = 0; i < numDirections; i++) {
        int offsetX = directions[i][0]; 
        int offsetY = directions[i][1];
        for (int step = 0; step < maxSteps; step++) {
            int posX = centerX + offsetX * step;
            int posY = centerY + offsetY * step;
            if (posX >= 0 && posX < xMax && posY >= 0 && posY < yMax) {
                mvwaddch(playwin, posY, posX, ' ');
            }
        }
    }

    wrefresh(playwin);
}


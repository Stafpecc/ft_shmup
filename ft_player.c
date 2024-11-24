#include "ft_shmup.h"
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

#include <math.h>
#define RADIUS 7
#define LASER_RADIUS 12
#define LASER_LENGTH 15
#define ROTATE_SPEED 5
#define MAX_ROTATIONS 20

/*Create new player function*/
Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow, int alive) {
        Player thePlayer = {xLoc,yLoc, xMax,yMax, character, currWindow, alive};
        return thePlayer;
}

/*Print player function*/
void display(Player *myPlayer) {
    box(myPlayer->currWindow, 0, 0);
    mvwaddch(myPlayer->currWindow, myPlayer->yLoc, myPlayer->xLoc, myPlayer->character);
}


void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin, Player *enemies) {
    Player s = newplayer(myPlayer->xLoc, myPlayer->yLoc - 1, xMax, yMax, c, playwin, 1);
    while (s.yLoc >= 0) {
        mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", "|||");
        wrefresh(playwin);
		if (s.yLoc == 1) {
			s.yLoc = yMax - 14;
			while (s.yLoc >= 0) {
        		mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", "   ");
        		if (isEnemyonBullet(playwin, s.xLoc, s.yLoc, enemies) == 1 || 
            		isEnemyonBullet(playwin, s.xLoc - 1, s.yLoc, enemies) == 1 || 
            		isEnemyonBullet(playwin, s.xLoc + 1, s.yLoc, enemies) == 1) {
						
            			mvwprintw(playwin, s.yLoc, s.xLoc - 1, "%s", " ");
						mvwprintw(playwin, s.yLoc, s.xLoc, "%s", " ");
						mvwprintw(playwin, s.yLoc, s.xLoc + 1, "%s", " ");
            			wrefresh(playwin);
            			removeEnemy(playwin, s.xLoc, s.yLoc, enemies);
						currentScore += 4200;
				}
			napms(2);
			s.yLoc--;
			wrefresh(playwin);
			}
    	}
		s.yLoc--;
	}
}


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
    int moveDistance = 1;
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


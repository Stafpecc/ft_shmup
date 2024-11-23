#include "ft_shmup.h"

Player newplayer(int xLoc,int yLoc, int xMax, int yMax, char character, WINDOW* currWindow) {
    Player thePlayer = {xLoc,yLoc, xMax,yMax, character, currWindow};
   
    return thePlayer;
}

void mvup(Player *myPlayer) {
    myPlayer->yLoc = myPlayer->yLoc - 1;
}

void mvdown(Player *myPlayer) {
    myPlayer->yLoc = myPlayer->yLoc + 1;
}

void mvleft(Player *myPlayer) {
    myPlayer->xLoc = myPlayer->xLoc - 1;
}

void mvright(Player *myPlayer) {
    myPlayer->xLoc = myPlayer->xLoc + 1;
}

void shoot(Player *myPlayer, int xMax, int yMax, char c, WINDOW *playwin) {
	struct Player s = newplayer(myPlayer->xLoc, myPlayer->yLoc - 1, xMax, yMax, c, playwin);
}

int getmv(Player *myPlayer) {
    int choice = wgetch(myPlayer->currWindow);
    switch(choice) {
        case (int)'w':
            mvup(myPlayer);
            break;
        case (int)'s':
            mvdown(myPlayer);
            break;
        case (int)'a':
            mvleft(myPlayer);
            break;
        case (int)'d':
            mvright(myPlayer);
            break;
		case (int)' ':
			shoot(myPlayer, '|');
			break;
        default:
            break;
    }
    return choice;
}

void display(Player *myPlayer) {
    mvwaddch(myPlayer->currWindow, myPlayer->yLoc, myPlayer->xLoc, myPlayer->character);
}
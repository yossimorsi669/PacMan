#pragma once
#include <iostream>
using namespace std;
#include "General.h"
#include "Fruit.h"
#include "PacMan.h"
#include "Board.h"
#include "Ghost.h"

class Game
{
private:
	int gameNum = 0;/* counter the games of the player*/
	Board* pBoard;
	Fruit* fruit;
	PacMan* pac;
	General* color, point;
	Ghost* gst1, * gst2;
	char menu();
	void intreduction();
public:
	Game(Board* pBoard, Fruit* fruit, PacMan* pac, Ghost* gst1, Ghost* gst2, General* color);
	void loser();
	void winner();
	void printFullScreen();
	void pacmanMoveItsClear(bool* nextMoveIsGhost, char* key, int* pacManMoveTwice);/*check if ghost is not in the next step so move*/
	void setStaringPosition();
	bool inputRightForPlay(char direction);
	void updatePacmanGhosts();
	void pacmanLoseLife(bool* gameOver, char* key);
	void playerMove();
	void playingGame();
	void startingGame();
};
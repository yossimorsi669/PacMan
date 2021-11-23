#pragma once
#include <iostream>
using namespace std;
#include "General.h"
#include "Board.h"
#include "Fruit.h"

class Ghost
{
private:
	Board* pBoard;
	General* color, point;
	Fruit* fruit;
	bool isFruit = true;
	int ghost_X, ghost_Y;
public:
	Ghost(Board* pBoard, Fruit* fruit, General* color);
	void setGhost(int x, int y); /*set ghost position*/
	bool getIsFruit() const;
	void setIsFruit();
	int getX() const;
	int getY() const;
	bool isNextMoveIsPacman(int x, int y, char dir); /*check if the next move is pacman*/
	void isGhostOnFruit();/*if the ghost stand on fruit*/
	void setAfterGhost(int x, int y);
	bool ghostStuckWall(int ghost_X, int ghost_Y);
	void setXY(int X, int Y);
	void ghostMove(char* direction);
	char randGhostMove(); /*change direction ghost move random*/

};
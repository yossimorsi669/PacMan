#pragma once
#include <iostream>
#include "General.h"
#include "Board.h"
#include "Fruit.h"
using namespace std;

class PacMan
{
private:
	Board* pBoard;
	General* color, point;
	Fruit* fruit;
	int x = 15, y = 2;
public:
	PacMan(Board* pBoard, Fruit* fruit, General* color);
	const int getX();
	const int getY();
	void setXY(int x, int y);
	int getKey();
	void setPacMan(int x, int y);
	void pacmanMove(char dir);
	bool isNextMoveIsGhost(int x, int y, char key);
	bool crushGhost(int x, int y);
};
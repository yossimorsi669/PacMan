#include "Ghost.h"

Ghost::Ghost(Board* pBoard, Fruit* fruit, General* color)
{
	this->pBoard = pBoard;
	this->fruit = fruit;
	this->color = color;
}
void Ghost::setGhost(int x, int y)
/*set ghost in the board and print it on the screen*/
{
	pBoard->setXY(x, y, GHOST);
}

bool Ghost::getIsFruit() const
{
	return isFruit;
}

void Ghost::setIsFruit()
{
	this->isFruit = true;
}

int Ghost::getX() const
{
	return ghost_X;
}

int Ghost::getY() const
{
	return ghost_Y;
}
void Ghost::setXY(int x, int y)
{
	this->ghost_X = x;
	this->ghost_Y = y;
}

void Ghost::ghostMove(char* dir)
{
	if (color->getColor())
		color->setTextColor(Color::BROWN);
	setAfterGhost(ghost_X, ghost_Y);

	switch (*dir)
	{
	case 'w': // UP
		ghost_Y--;
		if (ghostStuckWall(ghost_X, ghost_Y))
		{
			*dir = randGhostMove();
			ghost_Y++;
		}
		break;
	case 'x': // DOWN
		ghost_Y++;
		if (ghostStuckWall(ghost_X, ghost_Y))
		{
			*dir = randGhostMove();
			ghost_Y--;
		}
		break;
	case 'a': // LEFT
		ghost_X--;
		if (ghostStuckWall(ghost_X, ghost_Y))
		{
			*dir = randGhostMove();
			ghost_X++;
		}
		break;
	case 'd': // RIGHT
		ghost_X++;
		if (ghostStuckWall(ghost_X, ghost_Y))
		{
			*dir = randGhostMove();
			ghost_X--;
		}
		break;
	}
	isGhostOnFruit();
	if (color->getColor())
		color->setTextColor(Color::RED);
	setGhost(ghost_X, ghost_Y);
	point.gotoxy(0, 26);
}
bool Ghost::ghostStuckWall(int x, int y)
/*when one of the ghost stuck a wall or tunnel so the change to randome position*/
{
	return(pBoard->getXY(x, y) == WALLS || pBoard->tunnels(x, y));
}
char Ghost::randGhostMove()
{
	char diractions[4] = { 'w','d','x','a' };
	char dir = diractions[rand() % 4];
	return dir;
}
void Ghost::setAfterGhost(int x, int y)
{
	if (isFruit)
		pBoard->setXY(x, y, FRUIT);
	else
		pBoard->setXY(x, y, EMPTY);
}
void Ghost::isGhostOnFruit()
{
	if (fruit->isFruit(ghost_X, ghost_Y))
		isFruit = true;
	else
		isFruit = false;
}
bool Ghost::isNextMoveIsPacman(int x, int y, char key)
{
	switch (key)
	{
	case 'w':
		y--;
		break;
	case 'x':
		y++;
		break;
	case 'a':
		x--;
		break;
	case 'd':
		x++;
		break;
	}
	return (pBoard->getXY(x, y) == PACMAN);
}


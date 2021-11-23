#include "pacman.h"

PacMan::PacMan(Board* pBoard, Fruit* fruit, General* color)
{
	this->pBoard = pBoard;
	this->fruit = fruit;
	this->color = color;
}

const int PacMan::getX()
{
	return x;
}

const int PacMan::getY()
{
	return y;
}
void PacMan::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}
void PacMan::setPacMan(int x, int y)
{
	pBoard->setXY(x, y, PACMAN);
}
void PacMan::pacmanMove(char dir)
{
	switch (dir)
	{
	case 'w': // UP
	case 'W':
		if (pBoard->getXY(x, y - 1) != WALLS) /*if it not a wall*/
		{
			if (pBoard->getXY(x, y - 1) == FRUIT)
				fruit->addCounter();
			pBoard->setXY(x, y, EMPTY); /*we delete by EMPTY the last char*/
			--y;
		}
		if (pBoard->tunnels(x, y))/*if is the tunnels coords */
		{
			pBoard->setXY(x, y, EMPTY);
			y = 19;
			if (pBoard->getXY(x, y) == FRUIT)
				fruit->addCounter();
		}

		break;
	case 'x': // DOWN
	case 'X':
		if (pBoard->getXY(x, y + 1) != WALLS)
		{
			if (pBoard->getXY(x, y + 1) == FRUIT)
				fruit->addCounter();
			pBoard->setXY(x, y, EMPTY);
			++y;
		}
		if (pBoard->tunnels(x, y))
		{
			pBoard->setXY(x, y, EMPTY);
			y = 1;
			if (pBoard->getXY(x, y) == FRUIT)
				fruit->addCounter();
		}
		break;
	case 'a': // LEFT
	case 'A':
		if (pBoard->getXY(x - 1, y) != WALLS)
		{
			if (pBoard->getXY(x - 1, y) == FRUIT)
			{
				fruit->addCounter();
			}
			pBoard->setXY(x, y, EMPTY);
			--x;
		}
		if (pBoard->tunnels(x, y))
		{
			pBoard->setXY(x, y, EMPTY);
			x = 73;
			if (pBoard->getXY(x, y) == FRUIT)
				fruit->addCounter();
		}
		break;
	case 'd': // RIGHT
	case 'D':
		if (pBoard->getXY(x + 1, y) != WALLS)
		{
			if (pBoard->getXY(x + 1, y) == FRUIT)
			{
				fruit->addCounter();
			}
			pBoard->setXY(x, y, EMPTY);
			++x;
		}
		if (pBoard->tunnels(x, y))
		{
			pBoard->setXY(x, y, EMPTY);
			x = 1;
			if(pBoard->getXY(x, y) == FRUIT)
			   fruit->addCounter();
		}
		break;
	case 's':
	case 'S':
		break;
	}
	if (color->getColor())
		color->setTextColor(Color::LIGHTCYAN);
	setPacMan(x, y); /*and printing the pacman on the new coord*/
	point.gotoxy(0, 26);
}

int PacMan::getKey()
{
	char key = _getch();
	return (key);
}
bool PacMan::isNextMoveIsGhost(int pacman_x, int pacman_y, char key)
{
	switch (key)
	{
	case 'W':
	case 'w':
		pacman_y--;
		break;
	case 'X':
	case 'x':
		pacman_y++;
		break;
	case 'A':
	case 'a':
		pacman_x--;
		break;
	case 'D':
	case 'd':
		pacman_x++;
		break;
	}
	return crushGhost(pacman_x, pacman_y); /*if pcamn crush into ghost*/
}

bool PacMan::crushGhost(int x, int y)
{
	return pBoard->getXY(x, y) == GHOST;
}


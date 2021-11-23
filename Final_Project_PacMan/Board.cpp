#include "Board.h"

Board::Board(General* color)
{
	this->color = color;
}
void Board::printGameBoard()
{
	for (char* board : gameBoard)
	{
		if (color->getColor())
			point.setTextColor(Color::BROWN);
		cout << board << endl;
	}
}
const char Board::getXY(int x, int y)
{
	return gameBoard[y][x];
}
void Board::setXY(int x, int y, char ch)
{
	gameBoard[y][x] = ch;
	point.gotoxy(x, y);
	cout << gameBoard[y][x];
}
const int Board::getLives()
{
	return lives;
}
void Board::printLives()
{
	if (color->getColor())
		color->setTextColor(Color::LIGHTCYAN);
	point.gotoxy(49, 22);
	cout << lives;
}
void Board::setLives()
{
	lives--;
}
void Board::printScoreBoard()
{
	point.gotoxy(18, 21);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	point.gotoxy(18, 22);
	cout << "~~     Points:         Lives:       ~~";
	point.gotoxy(18, 23);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
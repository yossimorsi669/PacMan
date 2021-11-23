#include "Fruit.h"

Fruit::Fruit(Board* pBoard, General* color)
{
	this->pBoard = pBoard;
	this->color = color;
}
void Fruit::addCounter()
{
	counter++;
	point.gotoxy(33, 22); /*the position where we want to print the points*/
	if (color->getColor())
		point.setTextColor(Color::LIGHTCYAN);
	cout << counter;
}
void Fruit::setCounter(int counter)
{
	this->counter = 0;
}
const int Fruit::getCounter()
{
	return counter;
}
bool Fruit::isAllFoodDone()
{
	return(counter == TotalFood);
}
bool Fruit::isFruit(int x, int y)
{
	return pBoard->getXY(x, y) == FRUIT;
}
#pragma once
#include <iostream>
using namespace std;
#include "General.h"
#include "Board.h"
class Fruit
{
private:
	int TotalFood = 1110;
	int counter = 0; /*how many food was eaten*/
	Board* pBoard;
	General* color, point;
public:
	Fruit(Board* pBoard, General* color);
	void addCounter(); /*add one to counter*/
	void setCounter(int counter);/*set the counter to 0 (for new game)*/
	const int getCounter();
	bool isAllFoodDone();/*return true if all the food are eaten*/
	bool isFruit(int x, int y);
};


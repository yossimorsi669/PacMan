#pragma once
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <process.h>
#include "color.h"

#define ROWS 21
#define COLS 76
#define ESC 27  // Escape Key
#define FRUIT '.'
#define PACMAN '@'
#define WALLS '#'
#define GHOST '$'
#define EMPTY ' '

class General
{
private:
	bool withColors;
public:
	/*set the "withColors" if yes or not*/
	void setColor(bool color)
	{
		this->withColors = color;
	}
	const int getColor()
	{
		return withColors;
	}
	void gotoxy(int x, int y);
	void clearSceen();
	void setTextColor(Color colorToSet);

};
#include "General.h"

/************************************* gotoxy ************************************************
This function moves the cursor to the line y and column x.
(0,0) is the upper left corner of the screen.
Parameters: x - the column in the board.
			y - the line in the board.
**********************************************************************************************/
void General::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void General::clearSceen()
{
	system("cls");
}
void General::setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}
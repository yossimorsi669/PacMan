#include <iostream>
using namespace std;
#include <windows.h>
#include <process.h>
#include "Game.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Board.h"
#include "Fruit.h"
#include "General.h"

void main()
{
	General* color = new General();
	Board* pBoard = new Board(color);
	Fruit* fruit = new Fruit(pBoard, color);
	PacMan* pac = new PacMan(pBoard, fruit, color);
	Ghost* gst1 = new Ghost(pBoard, fruit, color);
	Ghost* gst2 = new Ghost(pBoard, fruit, color);
	Game* game = new Game(pBoard, fruit, pac, gst1, gst2, color);
	game->startingGame();

	delete(game);
	delete(gst1);
	delete(gst2);
	delete(pac);
	delete(fruit);

}

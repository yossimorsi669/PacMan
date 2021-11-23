#include "Game.h"

char Game::menu()
{
	char number;
	cout << "*******************************************" << endl;
	cout << " Welcome to the PacMan Game!" << endl;
	cout << " press 1 - to start a new game with colors" << endl;
	cout << " press 2 - to start a new game without colors" << endl;
	cout << " press 8 - to instructions" << endl;
	cout << " press 9 - EXIT" << endl;
	cout << "*******************************************" << endl;
	cin >> number;
	return number;
}
bool Game::inputRightForPlay(char direction)
{
	return (direction == 'w' || direction == 'W' || direction == 'A' || direction == 'a' || direction == 's' || direction == 'S'
		|| direction == 'x' || direction == 'X' || direction == 'd' || direction == 'D');
}
Game::Game(Board* pBoard, Fruit* fruit, PacMan* pac, Ghost* gst1, Ghost* gst2, General* color)
{
	this->pBoard = pBoard;
	this->fruit = fruit;
	this->pac = pac;
	this->gst1 = gst1;
	this->gst2 = gst2;
	this->color = color;
}
void Game::loser() /*print the massage for the game over*/
{
	point.clearSceen();
	if (color->getColor())
		color->setTextColor(Color::RED);
	cout << "            Game Over" << endl << endl;
	cout << "Please enter any key to go back to the menu" << endl;
	_getch();
	point.clearSceen();
}
void Game::pacmanLoseLife(bool* gameOver, char* key)
/*pacman lose one life and if there is no more lives the game is over*/
{
	pBoard->setLives();
	pBoard->printLives();
	if (pBoard->getLives() == 0)
	{
		loser();
		*gameOver = true;
	}
	else
	{
		if (color->getColor())
			color->setTextColor(Color::BROWN);
		updatePacmanGhosts();
		*key = 's';
	}
}
void Game::winner() /*print the massage for the winner*/
{
	point.clearSceen();
	if (color->getColor())
		color->setTextColor(Color::LIGHTGREEN);
	cout << "             YOU    ARE    THE    WINNER ! ! !" << endl << endl;
	cout << "Please enter any key to go back to the menu" << endl;
	_getch();
	point.clearSceen();

}
void Game::updatePacmanGhosts() /* update the pacman and the ghosts after crushing*/
{
	pBoard->setXY(pac->getX(), pac->getY(), EMPTY);
	gst1->setAfterGhost(gst1->getX(), gst1->getY());
	gst2->setAfterGhost(gst2->getX(), gst2->getY());
	setStaringPosition();
}
void Game::playingGame() /*set previous things and print all screen before player move and than start to play*/
{
	gameNum++;
	if (gameNum > 1) /* if the player in the secend game or more*/
		Board* pBoard = new Board(color);/*we create original board for new game*/
	fruit->setCounter(0);
	if (color->getColor())
		color->setTextColor(Color::BROWN);
	gst1->setIsFruit();
	gst2->setIsFruit();
	printFullScreen();
	playerMove();
	delete(pBoard);
}
void Game::pacmanMoveItsClear(bool* nextMoveIsGhost, char* key, int* pacManMoveTwice)
/*here we check if there are no ghost in the next step so the pacman move normaly*/
{
	*nextMoveIsGhost = pac->isNextMoveIsGhost(pac->getX(), pac->getY(), *key);
	if (!*nextMoveIsGhost) /*if the next move of the pacman is not ghost than:*/
	{
		pac->pacmanMove(*key); /*pacman move*/
		*pacManMoveTwice += 1;
	}
}
void Game::playerMove()/*the main function to control the stages of the game */
{
	char key = 's', dirGhost = 'w'; /*the first pcaman key - s*//*the first ghost direction is up*/
	char* directionGhost = &dirGhost;
	bool nextMoveIsGhost = false, nextMoveIsPacman = false;
	char tmpDirection = key;
	int pacManMoveTwice = 0;/*for update every two steps of pacman, the ghost move */
	bool checkEsc = false, /* will be true if the player press esc one time*/
		gameOver = false;
	setStaringPosition();

	while (!gameOver)
	{
		Sleep(50);
		if (_kbhit())// if any key was hit
		{
			if (checkEsc)/*if the player press esc before*/
			{
				key = pac->getKey();
				while (key != ESC)
					key = pac->getKey();
				checkEsc = false;
				point.gotoxy(10, 25);
				cout << "                                                                           ";
				key = tmpDirection;
			}
			else
				key = pac->getKey(); /*here we get the key from the player*/

			if (inputRightForPlay(key))
			{
				pacmanMoveItsClear(&nextMoveIsGhost, &key, &pacManMoveTwice);
				tmpDirection = key;
			}
			else /*if the player didnt press any key*/
			{
				if (key == ESC)
				{
					checkEsc = true;
					key = *directionGhost = 's';
					point.gotoxy(10, 25);
					cout << " The game is pause, please enter Esc again to continue the game";
					continue;
				}
				else
				{
					key = tmpDirection;
					pacmanMoveItsClear(&nextMoveIsGhost, &key, &pacManMoveTwice);
				}
			}
		}
		else
			pacmanMoveItsClear(&nextMoveIsGhost, &key, &pacManMoveTwice);

		if (nextMoveIsGhost) /*if pcaman crush into ghost*/
			pacmanLoseLife(&gameOver, &key);
		
		if (pacManMoveTwice == 2) /*every 2 moves of Pacman the Ghosts moves 1*/
		{
			/*check if the next move of the ghost is pacman*/
			nextMoveIsPacman = gst1->isNextMoveIsPacman(gst1->getX(), gst1->getY(), *directionGhost) || gst2->isNextMoveIsPacman(gst2->getX(), gst2->getY(), *directionGhost);
			if (!nextMoveIsPacman)/*if the next move is not pacman*/
			{
				if (*directionGhost == 's' && !checkEsc)/* case after esc*/
					*directionGhost = gst1->randGhostMove();
				gst1->ghostMove(directionGhost);
				gst2->ghostMove(directionGhost);
			}
			else
				pacmanLoseLife(&gameOver, &key);
	
			pacManMoveTwice = 0;
		}
		if (fruit->isAllFoodDone())/*if the pacman eats all the fruits*/
		{
			winner();
			gameOver = true;
			break;
		}
	}
}
void Game::printFullScreen()
{
	pBoard->printGameBoard();
	if (color->getColor())
		color->setTextColor(Color::LIGHTBLUE);
	pBoard->printScoreBoard();
	pBoard->printLives();
}
void Game::setStaringPosition() /*every starting game we set the pacman and the ghosts on staring position*/
{
	if (color->getColor())
		color->setTextColor(Color::LIGHTBLUE);
	pac->setPacMan(15, 2); /*printing the pacman on the starting coord*/
	pac->setXY(15, 2);
	if (color->getColor())
		color->setTextColor(Color::RED);
	gst1->setXY(3, 17);
	gst1->isGhostOnFruit();
	gst1->setGhost(3, 17);/*printing the ghost 1 on the starting coord*/
	gst2->setXY(70, 7);
	gst2->isGhostOnFruit();
	gst2->setGhost(70, 7);/*printing the ghost 2 on the starting coord*/
}
void Game::intreduction() /* print the intreduction: */
{
	cout << "***************************************************************************************" << endl;
	cout << "                               the instructions:" << endl;
	cout << "the pacman is '@' and to move it, here is the keys for:" << endl;
	cout << "press 'W' / 'w' - to move up" << endl;
	cout << "press 'D' / 'd' - to move right" << endl;
	cout << "press 'X' / 'x' - to move down" << endl;
	cout << "press 'A' / 'a' - to move left" << endl;
	cout << "press 'S' / 's' - to stay" << endl;
	cout << "press ESC - to pause the game and ESC again to continue" << endl;
	cout << "the pacman has 3 lives, he can lose a life if a ghost ($) will crash into him," << endl;
	cout << "after 3 lives lost, the game is over and you go to the menu again." << endl;
	cout << "To win : you need to eat all the food on the board - '.'" << endl;
	cout << "press any key to go back to the menu" << endl;
	cout << "***************************************************************************************" << endl;
	_getch();
}
/*here we are printing the menu and the player the choose the following cases.*/
void Game::startingGame()
{
	char number;
	bool endGame = false;
	while (!endGame)
	{
		if (color->getColor())
			color->setTextColor(Color::WHITE);
		number = menu();
		point.clearSceen();
		switch (number)
		{
		case '1':/*start the game with colors*/
			color->setColor(true);
			playingGame();
			break;
		case '2': /*start the game without colors*/
			color->setColor(false);
			playingGame();
			break;
		case '8':/*printing the intreduction*/
			intreduction();
			point.clearSceen();
			break;
		case '9':/*EXIT*/
			endGame = true;
			cout << "Thank you for playing bye bye" << endl;
			break;
		default: /*if the player choose illegal number*/
			cout << "Please enter a right value for menu" << endl;
			break;
		}
	}
}
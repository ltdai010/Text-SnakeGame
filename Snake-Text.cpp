#include<iostream>
#include<conio.h>
#include<Windows.h>

using namespace std;
bool gameOver;
const int length = 30;
const int height = 20;
int tailX[100]; //save position of snake's tail
int tailY[100];
int snakeHeadX, snakeHeadY; //position of Snake's head
int fruitX, fruitY; //position of fruit
int nTail; //length of snake's tail
int score; //the score
enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT }; //movement's command
eDirection direc;

void setup();
void draw();
void control();
void logic();

int main()
{
	setup();
	while (!gameOver)
	{
		draw();
		control();
		logic();
		Sleep(100); //10 frame per second
	}
	cout << "Game Over!" << endl;
	system("pause");
	return 0;
}

void setup() //default setting
{
	gameOver = false;
	snakeHeadX = length / 2;
	snakeHeadY = height / 2;
	direc = STOP;
	fruitX = rand() % (length + 1) + 1;
	fruitY = rand() % (height + 1) + 1;
	score = 0;
	nTail = 0;
}

void draw() //draw the frame
{
	system("cls");
	for (int mapX = 0; mapX < length + 2; ++mapX)
	{
		cout << "#";
	}
	cout << endl;
	for (int mapY = 1; mapY < height + 1; ++mapY)
	{
		for (int mapX = 0; mapX < length + 2; ++mapX)
		{
			bool print = false; //to print the tail
			for (int i = 0; i < nTail; ++i)
			{
				if (tailX[i] == mapX && tailY[i] == mapY)
				{
					print = true;
				}
			}
			if (mapX == 0 || mapX == length + 1)
			{
				cout << "#";
			}
			else if (print)
			{
				cout << "o";
			}
			else if (mapX == snakeHeadX && mapY == snakeHeadY)
			{
				cout << "O";
			}
			else if (mapX == fruitX && mapY == fruitY)
			{
				cout << "+";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	for (int mapX = 0; mapX < length + 2; ++mapX)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << "  press \"x\" to exit" << endl;
}

void control()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (direc == RIGHT) direc = RIGHT;
			else direc = LEFT;
			break;
		case 'd':
			if (direc == LEFT) direc = LEFT;
			else direc = RIGHT;
			break;
		case 's':
			if (direc == UP) direc = UP;
			else direc = DOWN;
			break;
		case 'w':
			if (direc == DOWN) direc = DOWN;
			else direc = UP;
			break;
		case 'A':
			if (direc == RIGHT) direc = RIGHT;
			else direc = LEFT;
			break;
		case 'D':
			if (direc == LEFT) direc = LEFT;
			else direc = RIGHT;
			break;
		case 'S':
			if (direc == UP) direc = UP;
			else direc = DOWN;
			break;
		case 'W':
			if (direc == DOWN) direc = DOWN;
			else direc = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		case 'X':
			gameOver = true;
			break;
		}
	}
}
void logic()
{
	int prevSHX, prevSHY; //save position of snake head;
	prevSHX = snakeHeadX;
	prevSHY = snakeHeadY;
	switch (direc) //move the snake's head
	{
	case LEFT:
		snakeHeadX--;
		break;
	case RIGHT:
		snakeHeadX++;
		break;
	case DOWN:
		snakeHeadY++;
		break;
	case UP:
		snakeHeadY--;
		break;
	}
	if (snakeHeadX == fruitX && snakeHeadY == fruitY) //eat fruit
	{
		bool spawn;
		do
		{
			spawn = true;
			fruitX = rand() % (length - 1 + 1) + 1; // new fruit
			fruitY = rand() % (height - 1 + 1) + 1;
			for (int i = 0; i < nTail; ++i) //fruit can't spawn in snake's tail
			{
				if (tailX[i] == fruitX && tailY[i] == fruitY) spawn = false;
			}
		}
		while (!spawn);
		++nTail;
		score = score + 10;
	}
	if (snakeHeadX == 0 || snakeHeadY == 0 || snakeHeadX == length + 1 || snakeHeadY == height + 1) //hit the wall
	{
		gameOver = true;
	}
	else
	{
		for (int i = 0; i < nTail; ++i) //hit itself
		{
			if (tailX[i] == snakeHeadX && tailY[i] == snakeHeadY)
			{
				gameOver = true;
			}
		}
	}
	for (int i = nTail - 1; i > 0; --i) //move the tail
	{
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = prevSHX;
	tailY[0] = prevSHY;
}

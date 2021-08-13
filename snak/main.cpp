#include <iostream>
#include "Snake.h"

int main(int argc, char** argv)
{
	Snake snake;
	snake.LoadPlayDataFromFile("data.txt");
	snake.Play();

	return 0;
}


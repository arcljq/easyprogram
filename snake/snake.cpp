#include <iostream>
#include "Snake.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>	// 随机数
#include <chrono>	// 日期时间
#include <stdlib.h> 


Snake::Snake(void)
{

}

bool Snake::LoadPlayDataFromFile(const std::string& file)
{
	std::ifstream fin(file);
	if (!fin)
	{
		return false;
	}
	std::string line;
	std::getline(fin, line);
	std::istringstream iss(line);
	int row, column;
	iss >> row >> column;
	for (size_t i = 0; i < row; i++)
	{
		std::vector<char>	lineData;
		std::getline(fin, line);
		std::istringstream issLineData(line);
		for (size_t j = 0; j < column; j++)
		{
			char data;
			issLineData >> data;
			lineData.push_back(data);
			if (data == '#')
			{
				m_snakeBody.push_back(std::make_pair(i, j));
			}
		}
		m_playMatrix.push_back(lineData);
	}
	if (m_snakeBody.size() != 1)
	{
		return false;
	}
	return true;
}

bool Snake::IsGameOver(int x, int y) const {
	return	(x < 0 || y<0 || x>m_playMatrix.size() || y >= m_playMatrix[0].size() || (m_playMatrix[x][y] == static_cast<int>(MatrixValueEnum::SNAKE_BODY)));
}

std::pair<int, int> Snake::GetCurrentPosition(void) const
{
	auto front = m_snakeBody.front();
	return front;
}

	std::pair<int, int> Snake::GetNextPosition(int i, int j) const
	{
		auto old = GetCurrentPosition();
		auto x = old.first += i;
		auto y = old.second += j;
		return std::make_pair(x, y);
	}

	bool Snake::ExistFood(int i, int j) const
	{
		return m_playMatrix[i][j] == static_cast<int>(MatrixValueEnum::FOOD);
	}

	void Snake::CreateFood(void)
	{
		do
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 g(seed);	// mt19937 is a standard mersenne_twister_engine
			int x = g() % m_playMatrix.size();
			int y = g() % m_playMatrix[0].size();
			if (m_playMatrix[x][y] == static_cast<char>(MatrixValueEnum::NOTHING))
			{
				m_playMatrix[x][y] = static_cast<char>(MatrixValueEnum::FOOD);
				break;
			}
		} while (true);
	}

	bool Snake::GoAhead(int i, int j)
	{
		auto nextPosition = GetNextPosition(i, j);	// 垂直方向不变
		if (IsGameOver(nextPosition.first, nextPosition.second))
		{
			return false;
		}
		if (ExistFood(nextPosition.first, nextPosition.second))
		{
			m_snakeBody.push_front(nextPosition);
			// 直接吃掉，尾巴不用移动
			m_playMatrix[nextPosition.first][nextPosition.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY);
			CreateFood();	// 随机生成一个食物
		}
		else
		{
			m_snakeBody.push_front(nextPosition);	// PUSH HEAD==PUSH_BACK
			m_playMatrix[nextPosition.first][nextPosition.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY);
			// 尾巴移动
			auto tail = m_snakeBody.back();
			m_playMatrix[tail.first][tail.second] = static_cast<char>(MatrixValueEnum::NOTHING);
			m_snakeBody.pop_back();

		}
	}

	bool Snake::GoAhead(char directoin)
	{
		switch (directoin)
		{
		case'W':
		case'w':
			return GoAhead(-1, 0);	// up
		case'a':
		case'A':
			return GoAhead(0, -1);	// left
		case'd':
		case'D':
			return GoAhead(0, 1);	// right
		case's':
		case'S':
			return GoAhead(1, 0);	// down
		default:
			return true;

		}
	}

	void Snake::Play(void)
	{
		CreateFood();	// 随机生成一个食物
		while (true)
		{
			system("cls");	// 清屏， 这不是C++的一部分，是系统调用。
			// clear();
			// ClearSreen();
			PrintMatrix();

			std::cout << "w s a d\n";
			char directoin;
			std::cin >> directoin;
			if (!GoAhead(directoin))
			{
				std::cout << "Game Over!" << std::endl;
				break;
			}
		}
	}

	void Snake::PrintMatrix(void) const
	{
		auto headPosition = m_snakeBody.front();
		for (size_t i = 0; i < m_playMatrix.size(); i++)
		{
			for (size_t j = 0; j < m_playMatrix.size(); j++)
			{
				if (i == headPosition.first && j == headPosition.second)
				{
					std::cout << "@" << "";
				}
				else if (m_playMatrix[i][j] == '2')
				{
					std::cout << "$" << " ";
				}
				else if (m_playMatrix[i][j] == '0')
				{
					std::cout << "_" << " ";
				}
				else
				{
					std::cout << m_playMatrix[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}

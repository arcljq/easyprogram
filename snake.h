#include <list>
#include <utility>
#include <vector>

class Snake
{
	enum class MatrixValueEnum	// enum is enumerator
	{
		NOTHING = '0', SNAKE_BODY = '#', FOOD = '2'

	};

public:
	Snake(void);
	bool LoadPlayDataFromFile(const std:: string& file);
	void Play(void);
private:
	bool GoAhead(char direction);
	bool GoAhead(int, int);
	bool IsGameOver(int, int) const;	// 撞到墙壁就结束游戏
	// const 修饰类成员函数代表该函数不改变调用参数的值
	std::pair<int,int> GetCurrentPosition(void) const;
	std::pair<int,int> GetNextPosition(int, int) const;
	void PrintMatrix(void) const;
	bool ExistFood(int,int) const;
	void CreateFood(void);
private:
	std::vector<std::vector<char>> m_playMatrix;
	std::list<std::pair<int,int>> m_snakeBody;
};

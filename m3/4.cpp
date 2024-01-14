#include <array>
#include <cassert>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using std::array;
using std::ostream;
using std::priority_queue;
using std::queue;
using std::string;
using std::swap;
using std::unordered_map;
using std::vector;

const int LINE_SIZE = 4;
const int FIELD_SIZE = LINE_SIZE * LINE_SIZE;
const array<uint16_t, FIELD_SIZE> FINISH_FIELD({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0});

class GameState
{
public:
	GameState(const array<uint16_t, FIELD_SIZE> &_field);

	bool CanMoveLeft() const;
	bool CanMoveUp() const;
	bool CanMoveRight() const;
	bool CanMoveDown() const;

	GameState MoveLeft() const;
	GameState MoveUp() const;
	GameState MoveRight() const;
	GameState MoveDown() const;

	bool IsFinish() const;
	bool CheckPosition() const;
	int ManhattanDistance() const;

	uint16_t GetFieldValue(size_t pos) const;

	bool operator==(const GameState &state) const { return field == state.field; }
	bool operator!=(const GameState &state) const { return !(*this == state); }

private:
	array<uint16_t, FIELD_SIZE> field;
	size_t zeroPos;
};

GameState::GameState(const array<uint16_t, FIELD_SIZE> &_field) : field(_field), zeroPos(-1)
{
	for (size_t i = 0; i < field.size(); ++i)
	{
		if (field[i] == 0)
		{
			zeroPos = i;
			break;
		}
	}
	assert(zeroPos != -1);
}

bool GameState::CanMoveLeft() const { return (zeroPos + 1) % LINE_SIZE != 0; }

bool GameState::CanMoveUp() const { return zeroPos < FIELD_SIZE - LINE_SIZE; }

bool GameState::CanMoveRight() const { return zeroPos % LINE_SIZE != 0; }

bool GameState::CanMoveDown() const { return zeroPos >= LINE_SIZE; }

GameState GameState::MoveRight() const
{
	assert(CanMoveRight());
	GameState newState(*this);
	swap(newState.field[zeroPos], newState.field[zeroPos - 1]);
	--newState.zeroPos;
	return newState;
}

GameState GameState::MoveDown() const
{
	assert(CanMoveDown());
	GameState newState(*this);
	swap(newState.field[zeroPos], newState.field[zeroPos - LINE_SIZE]);
	newState.zeroPos -= LINE_SIZE;
	return newState;
}

GameState GameState::MoveLeft() const
{
	assert(CanMoveLeft());
	GameState newState(*this);
	swap(newState.field[zeroPos], newState.field[zeroPos + 1]);
	++newState.zeroPos;
	return newState;
}

GameState GameState::MoveUp() const
{
	assert(CanMoveUp());
	GameState newState(*this);
	swap(newState.field[zeroPos], newState.field[zeroPos + LINE_SIZE]);
	newState.zeroPos += LINE_SIZE;
	return newState;
}

bool GameState::IsFinish() const { return field == FINISH_FIELD; }

uint16_t GameState::GetFieldValue(size_t pos) const
{
	assert(pos >= 0 && pos < FIELD_SIZE);
	return field[pos];
}

struct StateHasher
{
	size_t operator()(const GameState &state) const
	{
		size_t hash = 0, p = 1;
		for (int i = 0; i < FIELD_SIZE; ++i)
		{
			p *= 137;
			hash += state.GetFieldValue(i) * p;
		}
		return hash;
	}
};

int GameState::ManhattanDistance() const
{
	int distance = 0;

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		if (field[i] == 0)
		{
			continue;
		}
		int row = i / LINE_SIZE, col = i % LINE_SIZE;
		int targetRow = (field[i] - 1) / LINE_SIZE, targetCol = (field[i] - 1) % LINE_SIZE;

		distance += abs(row - targetRow) + abs(col - targetCol);

		// горизонтальный конфликт
		if (row == targetRow) 
		{
			for (int j = i + 1; j < (row + 1) * LINE_SIZE; ++j)
			{
				int next = (field[j] - 1) % LINE_SIZE;
				if (col < next && next < targetCol)
				{
					distance += 2;
				}
			}
		}

		// вертикальный конфликт
		if (col == targetCol)
		{
			for (int j = i + LINE_SIZE; j < FIELD_SIZE; j += LINE_SIZE)
			{
				int next = (field[j] - 1) / LINE_SIZE;
				if (row < next && next < targetRow)
				{
					distance += 2;
				}
			}
		}
	}

	return distance;
}

bool GameState::CheckPosition() const
{
	int nversion = 0;
	for (int i = 0; i < FIELD_SIZE; ++i)
		if (field[i])
			for (int j = 0; j < i; ++j)
				if (field[i] < field[j])
					++nversion;

	nversion += 1 + zeroPos / LINE_SIZE;
	return nversion & 1;
}

struct StateCompare
{
	bool operator()(const GameState &state1, const GameState &state2)
	{
		return state1.ManhattanDistance() > state2.ManhattanDistance();
	}
};

string Get16thSolution(const GameState &state)
{
	if( state.CheckPosition() ) {
	    return "-1";
	}
	priority_queue<GameState, vector<GameState>, StateCompare> bfsQueue;
	bfsQueue.push(state);
	unordered_map<GameState, char, StateHasher> visited;
	visited[state] = 'S';

	while (!bfsQueue.empty())
	{
		GameState current = bfsQueue.top();
		bfsQueue.pop();
		if (current.IsFinish())
		{
			break;
		}
		if (current.CanMoveLeft())
		{
			GameState newState = current.MoveLeft();
			if (visited.find(newState) == visited.end())
			{
				visited[newState] = 'L';
				bfsQueue.push(newState);
			}
		}
		if (current.CanMoveUp())
		{
			GameState newState = current.MoveUp();
			if (visited.find(newState) == visited.end())
			{
				visited[newState] = 'U';
				bfsQueue.push(newState);
			}
		}
		if (current.CanMoveRight())
		{
			GameState newState = current.MoveRight();
			if (visited.find(newState) == visited.end())
			{
				visited[newState] = 'R';
				bfsQueue.push(newState);
			}
		}
		if (current.CanMoveDown())
		{
			GameState newState = current.MoveDown();
			if (visited.find(newState) == visited.end())
			{
				visited[newState] = 'D';
				bfsQueue.push(newState);
			}
		}
	}

	string result;
	GameState current(FINISH_FIELD);
	uint16_t move = visited[current];
	while (move != 'S')
	{
		result += move;
		switch (move)
		{
		case 'L':
			current = current.MoveRight();
			break;
		case 'U':
			current = current.MoveDown();
			break;
		case 'R':
			current = current.MoveLeft();
			break;
		case 'D':
			current = current.MoveUp();
			break;
		}
		move = visited[current];
	}

	std::reverse(result.begin(), result.end());
	return result;
}

int main()
{
	array<uint16_t, FIELD_SIZE> field;

	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		std::cin >> field[i];
	}
	GameState state(field);
	string result = Get16thSolution(state);
	if (result == "-1")
	{
		std::cout << result << std::endl;
	}
	else
	{
		std::cout << result.size() << std::endl;
		std::cout << result << std::endl;
	}
	return 0;
}
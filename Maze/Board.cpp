#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"
#include "DisjointSet.h"

const char* TILE = "��";

Board::Board()
{

}

Board::~Board()
{

}

void Board::Init(int32 size, Player* player)
{
	_size = size;
	_player = player;

	GenerateMap();
}

void Board::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowConsoleCursor(false);

	for (int32 y = 0; y < 25; y++)
	{
		for (int32 x = 0; x < 25; x++)
		{	
			ConsoleColor color = GetTileColor(Pos { y, x } );
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}

		cout << endl;
	}
}

//Binary Tree �̷� ���� �˰���
// -Mazes For Programmers
void Board::GenerateMap()
{
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}
	
	vector<CostEdge> edges;

	// edges �ĺ��� ���� cost�� ����Ѵ�
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				continue;
			}

			// ���� �����ϴ� ���� �ĺ�
			if (x < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge{ randValue, Pos{y,x}, Pos{y, x+2} });
			}

			// �Ʒ��� �����ϴ� ���� �ĺ�
			if (y < _size - 2)
			{
				const int32 randValue = ::rand() % 100;
				edges.push_back(CostEdge { randValue, Pos{y,x}, Pos{y + 2, x} });
			}
		}
	}

	std::sort(edges.begin(), edges.end());

	DisjointSet sets(_size * _size);

	for (CostEdge& edge : edges)
	{
		int u = edge.u.y * _size + edge.u.x;
		int v = edge.v.y * _size + edge.v.x;

		// ���� �׷��̸� ��ŵ (�� �׷��� ����Ŭ �߻�)
		if (sets.Find(u) == sets.Find(v))
		{
			continue;
		}

		// �� �׷��� ��ģ��
		sets.Merge(u, v);

		// �ʿ� ����
		int y = (edge.u.y + edge.v.y) / 2;
		int x = (edge.u.x + edge.v.x) / 2;
		_tile[y][x] = TileType::EMPTY;
	}
}

TileType Board::GetTileType(Pos pos)
{
	if (pos.x < 0 || pos.x >= _size)
		return TileType::NONE; 

		if (pos.y < 0 || pos.y >= _size)
		return TileType::NONE;
		
	return _tile[pos.y][pos.x];

}

ConsoleColor Board::GetTileColor(Pos pos)
{
	if (_player && _player->GetPos() == pos)
		return ConsoleColor::YELLOW;

	if (GetExitPos() == pos)
		return ConsoleColor::BLUE;

	TileType tileType = GetTileType(pos);

	switch (tileType)
	{
	case TileType::EMPTY:
		return ConsoleColor::GREEN;
	case TileType::WALL:
		return ConsoleColor::RED;
	}
	
	return ConsoleColor::WHITE;
}


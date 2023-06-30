#pragma once

#include "Types.h"
#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

struct Pos
{
	int32 x = 0;
	int32 y = 0;

	bool operator==(Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		
		return ret;
	}

	Pos& operator+=(Pos& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,

	DIR_COUNT = 4
};

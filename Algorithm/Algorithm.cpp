﻿
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "BinarySearchTree.h"
#include <thread>
#include <windows.h>

using namespace std;

// LIS (Longest Increasing Sequence)

// Seq : 1 9 2 5 7
// 부분 수열 : 일부(0개 이상) 숫자를 지우고 남은 수열
// ex) 1 2 5
// ex) 1 9 5 7
// 순 증가 부분 수열
// ex) 1 2 5

// LIS : 제일 긴 [순 증가 부분 수열]의 길이
// 1 2 5 7 길이 = 4


int cache[100];
vector<int> seq;

int Lis(int pos)
{
	// 기저 사항
	/*if (pos == seq.size() - 1)
	{
		return 1;
	}*/

	// 캐시 확인
	int& ret = cache[pos];
	if (ret != -1)
	{
		return ret;
	}

	// 구현
	ret = 1;

	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] < seq[next])
		{
			ret = max(ret, 1 + Lis(next));
		}
	}

	return ret;
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	seq = vector<int>{10, 1, 9, 2, 5, 7};

	int ret = 0;
	for (int pos = 0; pos < seq.size(); pos++)
	{
		ret = max(ret, Lis(pos));
	}
}	


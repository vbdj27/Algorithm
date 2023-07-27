
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "BinarySearchTree.h"
#include <thread>
#include <windows.h>

using namespace std;

// ENCHANT

// +9 집행검 뜨는 경우의 수는?

int N;
int cache[100];

// [+Num]에서 시작해서, [+N]까지 가는 경우의 수
int Enchant(int num)
{
	// 기저 사례
	if (num > N)
	{
		return 0;
	}

	if (num == N)
	{
		 return 1;
	}

	// 캐시
	int& ret = cache[num];
	if (ret != -1)
	{
		return ret;
	}

	// 구현
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);

}

int main()
{
	N = 9;

	memset(cache, -1, sizeof(cache));

	int ret = Enchant(0);

	cout << ret << endl;
}	


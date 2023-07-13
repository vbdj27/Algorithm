// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

vector<int> numbers;

void BinarySearch(int N)
{
	int left = 0;
	int right = numbers.size() -1 ;

	while (left <= right)
	{
		cout << "탐색 범위:" << left << "~" << right <<endl;

		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			cout << N << "<" << numbers[mid] << endl;
			right = mid - 1;
		}

		else if (N > numbers[mid])
		{
			cout << N << ">" << numbers[mid] << endl;
			left = mid + 1;
		}

		else
		{
			cout << "찾음" << endl;
			break;
		}
	}
}

int main()
{
	numbers = vector<int>{1, 8, 15, 23, 32, 44, 56, 63, 81, 91};
	BinarySearch(82);
}


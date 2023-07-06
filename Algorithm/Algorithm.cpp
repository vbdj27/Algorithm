// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;


template <typename T, typename Container = vector<T>>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}

	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}

	bool empty() { return _container.empty(); }
	int size(){ return _container.size(); }

private:
	vector<T> _container;
};

int main()
{
	Stack<int, list<int>> s;

	//삽입
	s.push(1);
	s.push(2);
	s.push(3);

	//최상위 원소
	while(s.empty() == false)
	{ 
		int data = s.top();

		//최상위 원소 삭제
		s.pop();
	}

	int size = s.size();

}


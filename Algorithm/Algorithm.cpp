
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "BinarySearchTree.h"
#include <thread>

using namespace std;

// 상호 배타적 집합 (Disjoint Set)
// -> 유니온-파인드 Union-Find(합치기-찾기)

// 트리 구조를 이용한 상호 배타적 집합의 표현
struct Node
{
	Node* leader;
};

class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		if (u == _parent[u])
		{
			return u;
		}

		return Find(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
		{
			return;
		}

		_parent[u] = v;
	}

private:
	vector<int> _parent;
};

// 트리가 한쪽으로 기우는 문제를 해결 => 트리를 합칠 때, 항상 '높이가 낮은 트리를'
// '높이가 높은 트리' 밑으로 => Union by Rank 랭크에 의한 합치기 최적화
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int Find(int u)
	{
		if (u == _parent[u])
		{
			return u;
		}

		return _parent[u]  = Find(_parent[u]);
	}

	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
		{
			return;
		}

		if (_rank[u] > _rank[v])
		{
			swap(u, v);
		}

		// rank[u] <= rank[v] 보장됨
		_parent[u] = v;

		if (_rank[u] == _rank[v])
		{
			_rank[v]++;
		}
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{
	
}	


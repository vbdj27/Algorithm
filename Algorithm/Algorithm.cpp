// Algorithm.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

struct Vertex
{

};

vector <Vertex> vertices;
vector<vector<int>> adjacent; // 인접행렬

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6, vector<int>(6, -1));

	adjacent[0][1] = 15;
	adjacent[0][1] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered; // 발견목록
	vector<int> best(6, INT32_MAX); //각 정점별로 지금까지 발견한 최소 거리
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost {here, 0});
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		//제일 좋은 후보를 찾는다
		list<VertexCost>::iterator bestlt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			if (it->cost < bestCost)
			{
				bestCost = it->cost;
				bestlt = it;
			}
		}

		int cost = bestlt->cost;
		here = bestlt->vertex;
		discovered.erase(bestlt);

		//방문? 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[here] < cost)
		{
			continue;
		}

		//방문
		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵
			if (adjacent[here][there] == -1)
			{
				continue;
			}

			//더 좋은 경로를 과거에 찾았으면 스킵
			int nextCost = best[here] + adjacent[here][there];
			
			if (nextCost >= best[there])
			{
				continue;
			}

			discovered.push_back(VertexCost{ there, nextCost });
			best[there] = nextCost;
			parent[there] = here;
		}
	}
}

int main()
{
	CreateGraph();
}


#pragma once
#define OUT

#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <numeric>
#include <set>

using namespace std;
/*--------------------
* QBase
--------------------*/
class QBase
{
public:
	QBase() = default;
	virtual ~QBase() = default;

	virtual void Init()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
	}
	virtual void Input() {}
	virtual void Solution() {}
	virtual void Delete() {}
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
};

/*--------------------
* Q1916
--------------------*/
class Q1916 : public QBase
{
private:
	enum Parameter
	{
		INF = 0x3fffffff
	};
public:
	Q1916();
	virtual ~Q1916() = default;

	virtual void Input();
	void FloydInput();
	void DijkstraInput();
	virtual void Solution();
	void DijkstraSolution();
	void FloydSolution();

private:
	int _N;
	int _M;
	int _from;
	int _to;
	// Dijkstra
	vector<vector<pair<int, int>>> _data;
	// Floyd
	vector<vector<int>> _dist;
};

Q1916::Q1916()
	: _N(0)
	, _M(0)
	, _from(0)
	, _to(0)
{
}
void Q1916::Input()
{
	DijkstraInput();
}
void Q1916::FloydInput()
{
	cin >> _N >> _M;
	_dist.resize(_N, vector<int>(_N, INF));
	for (int i = 0; i < _N; ++i)
		_dist[i][i] = 0;

	int begin, end, dist;
	for (int i = 0; i < _M; ++i)
	{
		cin >> begin >> end >> dist;
		_dist[begin - 1][end - 1] = _dist[begin - 1][end - 1] < dist ? _dist[begin - 1][end - 1] : dist;
	}

	cin >> _from >> _to;
}
void Q1916::DijkstraInput()
{
	cin >> _N >> _M;
	_data.resize(_N + 1);

	int begin, end, dist;
	for (int i = 0; i < _M; ++i)
	{
		cin >> begin >> end >> dist;
		_data[begin].push_back({ dist, end });
	}

	cin >> _from >> _to;
}

void Q1916::Solution()
{
	DijkstraSolution();
}

void Q1916::DijkstraSolution()
{
	vector<int> dist(_N + 1, INF);
	dist[_from] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push({ 0, _from });
	while (!pq.empty())
	{
		int cost = pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (dist[cur] < cost)
			continue;

		for (int i = 0; i < _data[cur].size(); ++i)
		{
			int nxtCost = cost + _data[cur][i].first;
			int nxt = _data[cur][i].second;

			if (dist[nxt] > nxtCost)
			{
				pq.push({ nxtCost, nxt });
				dist[nxt] = nxtCost;
			}
		}
	}

	cout << dist[_to] << endl;
}

void Q1916::FloydSolution()
{
	for (int trans = 0; trans < _N; ++trans)
		for (int begin = 0; begin < _N; ++begin)
			for (int end = 0; end < _N; ++end)
			{
				_dist[begin][end] = _dist[begin][end] < _dist[begin][trans] + _dist[trans][end] ? _dist[begin][end] : _dist[begin][trans] + _dist[trans][end];
			}
	cout << _dist[_from - 1][_to - 1] << endl;
}

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1916>();
//	q->Init();
//	q->Solve();
//
//
//	return 0;
//}
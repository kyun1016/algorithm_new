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
	virtual void Input() {};
	virtual void Solution() {};
	virtual void Delete() {};
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
};
class Q15686 : public QBase
{
public:
	enum Parameter
	{
		MAX_CNT = 6,
		INF = 0x7fffffff,
	};

	Q15686()
		: _N(0)
		, _M(0)
	{};
	virtual ~Q15686() = default;

	virtual void Input()
	{
		int temp;
		cin >> _N >> _M;
		for (int y = 0; y < _N; ++y)
			for (int x = 0; x < _N; ++x)
			{
				cin >> temp;
				if (temp == 1)
					_home.push_back({ y,x });
				else if (temp == 2)
					_chicken.push_back({ y, x });
			}

		// dist √ ±‚»≠
		_dist.resize(_chicken.size(), vector<int>(_home.size()));
		for (int i = 0; i < _chicken.size(); ++i)
		{
			pair<int, int>& pos1 = _chicken[i];
			for (int j = 0; j < _home.size(); ++j)
			{
				pair<int, int>& pos2 = _home[j];
				_dist[i][j] = abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
			}
		}
	};

	int CalcDist(const vector<bool>& visited)
	{
		vector<int> minDist(_dist[0].size(), INF);

		for (int i = 0; i < _dist.size(); ++i)
		{
			if (!visited[i])
				continue;
			for (int j = 0; j < _dist[i].size(); ++j)
				minDist[j] = minDist[j] < _dist[i][j] ? minDist[j] : _dist[i][j];
		}

		return accumulate(minDist.begin(), minDist.end(), 0);
	}

	int DFS(vector<bool>& visited, const int& pos, const int& depth)
	{
		int ret = INF;
		if (_dist.size() - pos < _M - depth)
			return INF;

		if (depth == _M)
			return CalcDist(visited);
		for (int nxtPos = pos + 1; nxtPos < _dist.size(); ++nxtPos)
		{
			visited[nxtPos] = true;
			int temp = DFS(visited, nxtPos, depth + 1);
			visited[nxtPos] = false;
			ret = ret < temp ? ret : temp;
		}
		return ret;
	}

	virtual void Solution()
	{
		vector<bool> visited(_dist.size(), false);
		cout << DFS(visited, -1, 0) << endl;
	};

private:
	int _N;
	int _M;
	vector<pair<int, int>> _home;
	vector<pair<int, int>> _chicken;
	vector<vector<int>> _dist;
};

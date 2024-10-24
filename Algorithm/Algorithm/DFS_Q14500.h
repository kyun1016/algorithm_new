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
class Q14500 : public QBase
{
public:
	enum Parameter
	{
		INF = -0x7fff,
	};
	struct Pos
	{
		int y;
		int x;
	};
	Q14500()
		: _N(0)
		, _M(0)
	{
		_dir[0] = { 0, -1 };
		_dir[1] = { 0, 1 };
		_dir[2] = { -1, 0 };
		_dir[3] = { 1, 0 };

		_arr.resize(4);
		_arr[0].resize(2, vector<bool>(3, true));
		_arr[0][0][0] = false;
		_arr[0][0][2] = false;
		_arr[1].resize(2, vector<bool>(3, true));
		_arr[1][1][0] = false;
		_arr[1][1][2] = false;
		_arr[2].resize(3, vector<bool>(2, true));
		_arr[2][0][0] = false;
		_arr[2][2][0] = false;
		_arr[3].resize(3, vector<bool>(2, true));
		_arr[3][0][1] = false;
		_arr[3][2][1] = false;
	}

	virtual void Input()
	{
		cin >> _N >> _M;
		_map.resize(_N, vector<int>(_M));
		_visited.resize(_N, vector<bool>(_M, false));

		for (int y = 0; y < _N; ++y)
			for (int x = 0; x < _M; ++x)
				cin >> _map[y][x];
	}


	int CheckUnique(const Pos& pos)
	{
		int ret = INF;
		for (int i = 0; i < _arr.size(); ++i)
		{
			if (_arr[i].size() + pos.y > _N)
				continue;
			if (_arr[i][0].size() + pos.x > _M)
				continue;

			int sum = 0;
			for (int dy = 0; dy < _arr[i].size(); ++dy)
			{
				for (int dx = 0; dx < _arr[i][0].size(); ++dx)
				{
					if (_arr[i][dy][dx])
						sum += _map[pos.y + dy][pos.x + dx];
				}
			}
			ret = ret > sum ? ret : sum;
		}

		return ret;
	}

	int DFS(const Pos& pos, const int& depth, const int& sum)
	{
		if (depth == 4)
			return sum;

		int ret = sum;
		if (depth == 0)
		{
			for (int y = 0; y < _N; ++y)
			{
				for (int x = 0; x < _M; ++x)
				{
					_visited[y][x] = true;
					ret = max(ret, DFS({ y,x }, 1, _map[y][x]));
					ret = max(ret, CheckUnique({ y, x }));
					_visited[y][x] = false;
				}
			}
		}
		else
		{
			Pos nPos;
			for (int i = 0; i < 4; ++i)
			{
				nPos.x = pos.x + _dir[i].x;
				nPos.y = pos.y + _dir[i].y;
				if (nPos.y < 0)
					continue;
				if (nPos.y >= _N)
					continue;
				if (nPos.x < 0)
					continue;
				if (nPos.x >= _M)
					continue;

				if (_visited[nPos.y][nPos.x] == true)
					continue;

				_visited[nPos.y][nPos.x] = true;
				ret = max(ret, DFS(nPos, depth + 1, sum + _map[nPos.y][nPos.x]));
				_visited[nPos.y][nPos.x] = false;
			}
		}

		return ret;
	}


	virtual void Solution()
	{
		int ret = DFS({ -1, 0 }, 0, 0);
		cout << ret << endl;
	}
private:
	int _N;
	int _M;
	Pos _dir[4];
	vector<vector<vector<bool>>> _arr;
	vector<vector<bool>> _visited;
	vector<vector<int>> _map;
};
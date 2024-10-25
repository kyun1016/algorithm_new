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
* Q1987
--------------------*/
class Q1987 : public QBase
{
private:
	struct Pos
	{
		int y;
		int x;
	};
public:
	Q1987()
		: _R(0)
		, _C(0)
	{
		_dir[0] = { 1,0 };
		_dir[1] = { -1,0 };
		_dir[2] = { 0, 1 };
		_dir[3] = { 0, -1 };
	};

	virtual ~Q1987() = default;

	virtual void Input()
	{
		cin >> _R >> _C;
		char c;
		_map.resize(_R, vector<int>(_C));
		_visited.resize(26, false);
		for (int y = 0; y < _R; ++y)
			for (int x = 0; x < _C; ++x)
			{
				cin >> c;
				_map[y][x] = c - 'A';
			}
	}
	int DFS(const Pos& pos, const int& depth)
	{
		int ret = depth;
		for (int i = 0; i < 4; ++i)
		{
			Pos nPos = { pos.y + _dir[i].y, pos.x + _dir[i].x };
			if (nPos.y < 0 || nPos.y >= _R || nPos.x < 0 || nPos.x >= _C || _visited[_map[nPos.y][nPos.x]])
				continue;
			_visited[_map[nPos.y][nPos.x]] = true;
			ret = max(ret, DFS(nPos, depth + 1));
			_visited[_map[nPos.y][nPos.x]] = false;
		}
		return ret;
	}
	virtual void Solution()
	{
		_visited[_map[0][0]] = true;
		cout << DFS({ 0,0 }, 1) << endl;
	}

private:
	vector<bool> _visited;
	vector<vector<int>> _map;
	Pos _dir[4];
	int _R;
	int _C;
};


/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1987>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
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
* Q4963
--------------------*/
class Q4963 : public QBase
{
public:
	Q4963()
		: _W(0)
		, _H(0)
	{
		_dir[0] = { 1,0 };
		_dir[1] = { -1,0 };
		_dir[2] = { 0, 1 };
		_dir[3] = { 0, -1 };
		_dir[4] = { 1,-1 };
		_dir[5] = { -1,-1 };
		_dir[6] = { -1, 1 };
		_dir[7] = { 1, 1 };
	};

	virtual ~Q4963() = default;

	virtual void Input()
	{
		cin >> _W >> _H;
		_map.resize(_H, vector<int>(_W));
		for (int y = 0; y < _H; ++y)
			for (int x = 0; x < _W; ++x)
				cin >> _map[y][x];
	}
	virtual void Solution()
	{
		queue<Pos> q;
		int ret = 0;
		for (int y = 0; y < _H; ++y)
			for (int x = 0; x < _W; ++x)
			{
				if (_map[y][x] == 0)
					continue;
				if (_map[y][x] == 1)
				{
					_map[y][x] = ++ret + 1;
					q.push({ y, x });
				}
				while (!q.empty())
				{
					Pos pos = q.front();
					q.pop();
					for (int i = 0; i < 8; ++i)
					{
						int ny = pos.y + _dir[i].y;
						int nx = pos.x + _dir[i].x;
						if (ny < 0 || ny >= _H || nx < 0 || nx >= _W || _map[ny][nx] != 1)
							continue;

						_map[ny][nx] = ret + 1;
						q.push({ ny, nx });
					}
				}
			}

		//for (int y = 0; y < _H; ++y)
		//{
		//	for (int x = 0; x < _W; ++x)
		//		cout << _map[y][x];

		//	cout << endl;
		//}

		cout << ret << endl;
	}
	virtual void Delete()
	{
		_map.clear();
	}
	virtual void Solve()
	{
		while (true)
		{
			Input();
			if (_W == 0 && _H == 0)
				break;
			Solution();
			Delete();
		}
	}
private:
	struct Pos
	{
		int y;
		int x;
	};

	vector<vector<int>> _map;
	Pos _dir[8];
	int _W;
	int _H;
};


/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q4963>();
//	q->Init();
//	q->Solve();
//
//
//	return 0;
//}
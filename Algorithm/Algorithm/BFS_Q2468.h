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
class Q2468 : public QBase
{
public:
	Q2468()
		: _N(0)
		, _maxHeight(0)
	{
		_dir[0].y = 1;
		_dir[0].x = 0;
		_dir[1].y = -1;
		_dir[1].x = 0;
		_dir[2].y = 0;
		_dir[2].x = 1;
		_dir[3].y = 0;
		_dir[3].x = -1;
	}
	virtual ~Q2468() = default;

	virtual void Input()
	{
		cin >> _N;
		_arr.resize(_N, vector<int>(_N));

		for (auto& arr : _arr)
			for (auto& a : arr)
			{
				cin >> a;
				_maxHeight = _maxHeight > a ? _maxHeight : a;
			}
	}

	virtual void Solution()
	{
		int ret = 0;
		for (int h = 0; h < _maxHeight; ++h)
		{
			queue<Pos> qu;
			vector<vector<bool>> visited(_N, vector<bool>(_N, false));
			int chunk = 0;
			for (int x = 0; x < _N; ++x)
				for (int y = 0; y < _N; ++y)
				{
					if (_arr[y][x] <= h)
						continue;
					if (!visited[y][x])
					{
						visited[y][x] = true;
						qu.push({ y,x });
						++chunk;
					}
					while (!qu.empty())
					{
						Pos curPos = qu.front();
						qu.pop();
						for (int dir = 0; dir < 4; ++dir)
						{
							Pos nxtPos = { curPos.y + _dir[dir].y, curPos.x + _dir[dir].x };

							if (nxtPos.x < 0 || nxtPos.x >= _N)
								continue;
							if (nxtPos.y < 0 || nxtPos.y >= _N)
								continue;

							if (_arr[nxtPos.y][nxtPos.x] <= h)
								continue;

							if (!visited[nxtPos.y][nxtPos.x])
							{
								visited[nxtPos.y][nxtPos.x] = true;
								qu.push({ nxtPos.y,nxtPos.x });
							}
						}
					}
				}
			// cout << "[" << h << "]height: " << chunk << endl;
			ret = ret > chunk ? ret : chunk;
		}
		cout << ret << endl;
	}
private:
	struct Pos
	{
		int y;
		int x;
	};
	Pos _dir[4];
	int _N;
	int _maxHeight;
	vector<vector<int>> _arr;
};

//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q2468>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
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
class Q16029 : public QBase
{
public:
	Q16029()
		: _N(0)
	{
		_dir.x = 1;
		_dir.y = 0;
		_snake.push_back({ 0, 0 });
	}
	virtual ~Q3190() = default;

	virtual void Input()
	{
		cin >> _N;
		_arr.resize(_N, vector<int>(_N, 0));
		_arr[0][0] = 1;
		int temp, y, x;
		cin >> temp;
		for (int i = 0; i < temp; ++i)
		{
			cin >> y >> x;
			_arr[y - 1][x - 1] = 2;
		}

		cin >> temp;
		char c;
		for (int i = 0; i < temp; ++i)
		{
			cin >> y >> c;
			_TimeTable.push({ y, c });
		}
	}

	void Rot(const char& dir)
	{
		if (dir == 'L')
		{
			int temp = _dir.y;
			_dir.y = _dir.x * -1;
			_dir.x = temp;
		}
		else // if(dir == 'D')
		{
			int temp = _dir.x;
			_dir.x = _dir.y * -1;
			_dir.y = temp;
		}
	}

	virtual void Solution()
	{
		int ret = 0;
		Pos nPos;
		Data data = _TimeTable.front();
		_TimeTable.pop();
		while (true)
		{
			//cout << "[" << ret << "]: " << endl;
			//for (int y = 0; y < _N; ++y)
			//{
			//	for (int x = 0; x < _N; ++x)
			//	{
			//		cout << _arr[y][x];
			//	}
			//	cout << endl;
			//}
			++ret;

			nPos.x = _snake.back().x + _dir.x;
			nPos.y = _snake.back().y + _dir.y;
			// 1. 경계 체크
			if (nPos.x >= _N)
				break;
			if (nPos.x < 0)
				break;
			if (nPos.y >= _N)
				break;
			if (nPos.y < 0)
				break;

			// 2. 뱀 검사
			if (_arr[nPos.y][nPos.x] == 1)
				break;

			// 3. 사과 검사
			if (_arr[nPos.y][nPos.x] == 2)
			{
				_arr[nPos.y][nPos.x] = 1;
				_snake.push_back(nPos);
			}
			else {
				_arr[nPos.y][nPos.x] = 1;
				_arr[_snake.front().y][_snake.front().x] = 0;
				_snake.push_back(nPos);
				_snake.pop_front();
			}

			// 4. 회전
			if (ret == data.t)
			{
				Rot(data.dir);
				if (!_TimeTable.empty())
				{
					data = _TimeTable.front();
					_TimeTable.pop();
				}
			}
		}

		cout << ret << endl;
	}


private:
	struct Pos
	{
		int y;
		int x;
	};
	struct Data
	{
		int t;
		char dir;
	};
	int _N;
	vector<vector<int>> _arr;	// 0: 빈 공간, 1: 뱀, 2: 사과
	Pos _dir;
	deque<Pos> _snake;
	queue<Data> _TimeTable;
};

//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q3190>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
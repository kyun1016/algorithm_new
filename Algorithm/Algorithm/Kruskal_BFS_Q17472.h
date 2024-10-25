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
class Q17472 : public QBase
{
public:
	struct Pos
	{
		int y;
		int x;
	};
	class Edge
	{
	public:
		Edge()
			: _begin(0)
			, _end(0)
			, _dist(0)
		{}
		Edge(int begin, int end, int dist)
			: _begin(begin)
			, _end(end)
			, _dist(dist)
		{}

		bool operator< (Edge& rhs)
		{
			return this->_dist < rhs._dist;
		}
	public:
		int _begin;
		int _end;
		int _dist;
	};
public:
	Q17472()
		: _N(0)
		, _M(0)
	{
		_dir[0] = { 1, 0 };
		_dir[1] = { -1, 0 };
		_dir[2] = { 0, 1 };
		_dir[3] = { 0, -1 };
	}
	virtual ~Q17472() = default;

	void BFSFindIsland();
	vector<Edge> FindBridge();
	int GetParent(const int& a);
	void UnionParent(int a, int b);
	virtual void Input();
	virtual void Solution();

private:
	int _N;
	int _M;
	Pos _dir[4];
	vector<vector<int>> _arr;
	vector<int> _parent;
};

void Q17472::BFSFindIsland()
{
	vector<vector<bool>> visited(_N, vector<bool>(_M, false));
	queue<Pos> q;

	int num = 0;
	for (int y = 0; y < _N; ++y)
	{
		for (int x = 0; x < _M; ++x)
		{
			if (visited[y][x])
				continue;
			if (_arr[y][x] == 1)
			{
				_arr[y][x] = ++num;
				visited[y][x] = true;
				q.push({ y, x });
			}
			while (!q.empty())
			{
				Pos curPos = q.front();
				q.pop();
				for (int i = 0; i < 4; ++i)
				{
					Pos nxtPos = { curPos.y + _dir[i].y, curPos.x + _dir[i].x };
					if (nxtPos.x < 0 || nxtPos.x >= _M || nxtPos.y < 0 || nxtPos.y >= _N)
						continue;
					if (visited[nxtPos.y][nxtPos.x])
						continue;
					if (_arr[nxtPos.y][nxtPos.x] == 1)
					{
						_arr[nxtPos.y][nxtPos.x] = num;
						visited[nxtPos.y][nxtPos.x] = true;
						q.push({ nxtPos.y, nxtPos.x });
					}
				}
			}
		}
	}
	_parent.resize(num + 1);
	for (int i = 0; i < num + 1; ++i)
	{
		_parent[i] = i;
	}
}

vector<Q17472::Edge> Q17472::FindBridge()
{
	vector<Edge> ret;
	for (int y = 0; y < _N; ++y)
	{
		for (int x = 0; x < _M; ++x)
		{
			if (_arr[y][x] == 0)
				continue;
			for (int i = 0; i < 4; ++i)
			{
				int ny = y;
				int nx = x;
				int dist = 0;
				while (true)
				{
					ny += _dir[i].y;
					nx += _dir[i].x;
					if (nx < 0 || nx >= _M || ny < 0 || ny >= _N || _arr[y][x] == _arr[ny][nx])
						break;
					if (_arr[ny][nx] == 0)
						++dist;
					else
					{
						if (dist >= 2 && _arr[y][x] != _arr[ny][nx])
							ret.push_back(Edge(_arr[y][x], _arr[ny][nx], dist));
						break;
					}
				}
			}
		}
	}

	sort(ret.begin(), ret.end());
	return ret;
}

int Q17472::GetParent(const int& a)
{
	if (_parent[a] == a)
		return a;
	else
		return _parent[a] = GetParent(_parent[a]);
}

void Q17472::UnionParent(int a, int b)
{
	a = GetParent(a);
	b = GetParent(b);
	if (a < b)
		_parent[b] = a;
	else
		_parent[a] = b;
}

void Q17472::Input()
{
	cin >> _N >> _M;
	_arr.resize(_N, vector<int>(_M));

	for (auto& arr : _arr)
		for (auto& a : arr)
		{
			cin >> a;
		}
}

void Q17472::Solution()
{
	BFSFindIsland();
	vector<Edge> bridgeList = FindBridge();
	int ret = 0;
	for (const auto& bridge : bridgeList)
	{
		if (GetParent(bridge._begin) != GetParent(bridge._end))
		{
			ret += bridge._dist;
			UnionParent(bridge._begin, bridge._end);
		}
	}

	for (int i = 2; i < _parent.size(); ++i)
	{
		if (1 != GetParent(i))
			ret = -1;
	}

	cout << ret << endl;
}

//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q17472>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
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
* Q1922
--------------------*/
class Q1922 : public QBase
{
public:
	class Edge
	{
	public:
		Edge()
			: _begin(0)
			, _end(0)
			, _cost(0)
		{}
		Edge(int begin, int end, int cost)
			: _begin(begin)
			, _end(end)
			, _cost(cost)
		{}

		bool operator< (Edge& rhs)
		{
			return this->_cost < rhs._cost;
		}
	public:
		int _begin;
		int _end;
		int _cost;
	};
public:
	Q1922() = default;
	virtual ~Q1922() = default;

	virtual void Input()
	{
		cin >> _N >> _M;
		_edge.resize(_M);
		for (auto& e : _edge)
			cin >> e._begin >> e._end >> e._cost;
	}

	virtual void Solution()
	{
		sort(_edge.begin(), _edge.end());

		_parent.resize(_N + 1);
		for (int i = 0; i <= _N; ++i)
			_parent[i] = i;

		int totalCost = 0;
		for (int i = 0; i < _M; ++i)
		{
			if (!CheckParent(_edge[i]._begin, _edge[i]._end))
			{
				UnionParent(_edge[i]._begin, _edge[i]._end);
				totalCost += _edge[i]._cost;
			}
		}

		cout << totalCost;
	}

	int GetParent(const int& a)
	{
		if (_parent[a] == a)
			return a;

		return _parent[a] = GetParent(_parent[a]);
	}
	void UnionParent(int a, int b)
	{
		a = GetParent(a);
		b = GetParent(b);
		if (a < b)
			_parent[b] = a;
		else
			_parent[a] = b;
	}
	bool CheckParent(int a, int b)
	{
		a = GetParent(a);
		b = GetParent(b);

		return a == b;
	}
private:
	int _N;
	int _M;
	vector<Edge> _edge;
	vector<int> _parent;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1922>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
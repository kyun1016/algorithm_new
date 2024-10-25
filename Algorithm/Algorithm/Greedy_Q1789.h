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
* Q1789
--------------------*/
class Q1789 : public QBase
{
public:
	Q1789()
		: INF(4'294'967'295u)
		, _N(0)
	{
		unsigned long long diff = 0;
		_arr.push_back(diff++);
		_arr.push_back(diff++);
		while (true)
		{
			// cout <<idx << ":" << _arr[idx] << endl;
			_arr.push_back(diff++ + _arr[_arr.size() - 1]);

			if (_arr[_arr.size() - 1] >= INF)
				break;
		}
	}
	virtual ~Q1789() = default;

	virtual void Input()
	{
		cin >> _N;
	}

	virtual void Solution()
	{
		for (int i = 0; i < _arr.size(); ++i)
		{
			if (_N == _arr[i])
			{
				cout << i << endl;
				return;
			}
			else if (_N < _arr[i])
			{
				cout << i - 1 << endl;
				return;
			}
		}
	}

private:
	const unsigned long long INF;
	unsigned long long _N;
	vector<unsigned long long> _arr;
};


/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1789>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
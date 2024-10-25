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
* Q1715
--------------------*/
class Q1715 : public QBase
{
public:
	Q1715()
	{

	}
	virtual ~Q1715() = default;

	virtual void Input()
	{
		cin >> _N;
		int temp;
		for (int i = 0; i < _N; ++i)
		{
			cin >> temp;
			pq.push(temp);
		}
	}

	virtual void Solution()
	{
		int ret = 0;
		int data = 0;
		while (!pq.empty())
		{
			data = pq.top();
			pq.pop();
			if (!pq.empty())
			{
				data += pq.top();
				pq.pop();
				ret += data;
				// cout << ret << endl;
				pq.push(data);
			}
		}

		cout << ret << endl;
	}
private:
	int _N;
	priority_queue<int, vector<int>, greater<int>> pq;
};


/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1715>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
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
class Q14501 : public QBase
{
public:
	Q14501() : _N(0) {}
	virtual ~Q14501() {}

	virtual void Input()
	{
		cin >> _N;
		_arr.resize(_N);
		for (int i = 0; i < _N; ++i)
		{
			cin >> _arr[i].T >> _arr[i].P;
		}
	}

	int DP(const int& t, const int& sum)
	{
		int ret = sum;
		if (t >= _N)
			return ret;
		int nxtT = t + _arr[t].T;
		if (nxtT > _N)
			ret = DP(t + 1, sum);
		else
			ret = max(DP(t + 1, sum), DP(nxtT, sum + _arr[t].P));

		return ret;
	}

	virtual void Solution()
	{
		cout << DP(0, 0) << endl;
	}


private:
	int _N;
	struct Query
	{
		int T;
		int P;
	};
	vector<Query> _arr;
};
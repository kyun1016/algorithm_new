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
* Q18185
--------------------*/
class Q18185 : public QBase
{
public:
	Q18185() = default;
	virtual ~Q18185() = default;

	virtual void Input()
	{
		cin >> _N;
		_arr.resize(_N + 2, 0);
		for (int i = 0; i < _N; ++i)
			cin >> _arr[i];
	}

	virtual void Solution()
	{
		int ret = 0;
		for (int i = 0; i < _N; ++i)
		{
			if (_arr[i + 1] > _arr[i + 2])
			{
				int cnt = min(_arr[i], _arr[i + 1] - _arr[i + 2]);
				_arr[i] -= cnt;
				_arr[i + 1] -= cnt;
				ret += 5 * cnt;

				cnt = min(_arr[i], min(_arr[i + 1], _arr[i + 2]));
				_arr[i] -= cnt;
				_arr[i + 1] -= cnt;
				_arr[i + 2] -= cnt;
				ret += 7 * cnt;
			}
			else
			{
				int cnt = min(_arr[i], min(_arr[i + 1], _arr[i + 2]));
				_arr[i] -= cnt;
				_arr[i + 1] -= cnt;
				_arr[i + 2] -= cnt;
				ret += 7 * cnt;

				cnt = min(_arr[i], _arr[i + 1]);
				_arr[i] -= cnt;
				_arr[i + 1] -= cnt;
				ret += 5 * cnt;
			}
			ret += 3 * _arr[i];
			_arr[i] = 0;
		}

		cout << ret << endl;
	}
private:
	int _N;
	vector<int> _arr;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q18185>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
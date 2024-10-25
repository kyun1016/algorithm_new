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
* Q16496
--------------------*/
bool compare(string a, string b)
{
	string ab = a + b;
	string ba = b + a;
	for (int i = 0; i < ab.size(); ++i)
	{
		if (ab[i] > ba[i])
			return true;
		else if (ba[i] > ab[i])
			return false;
	}
	return false;
}
class Q16496 : public QBase
{
public:
	Q16496() = default;
	virtual ~Q16496() = default;

	virtual void Input()
	{
		cin >> _N;
		_arr.resize(_N);
		_flag = true;
		for (auto& a : _arr)
		{
			cin >> a;
			if (a != "0")
				_flag = false;
		}
	}

	virtual void Solution()
	{
		sort(_arr.begin(), _arr.end(), compare);

		if (_flag)
			cout << 0;
		else
			for (auto& a : _arr)
				cout << a;
	}
private:
	int _N;
	bool _flag;
	vector<string> _arr;
};


/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q16496>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
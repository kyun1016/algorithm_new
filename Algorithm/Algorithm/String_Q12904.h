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
* Q12904
--------------------*/
class Q12904 : public QBase
{
public:
	Q12904() = default;
	virtual ~Q12904() = default;

	virtual void Input()
	{
		cin >> _S >> _T;
	}

	virtual void Solution()
	{
		while (_T.size() != _S.size())
		{
			if (_T.back() == 'A')
				_T.pop_back();
			else
			{
				_T.pop_back();
				reverse(_T.begin(), _T.end());
			}
		}
		if (_S == _T)
			cout << 1;
		else
			cout << 0;
	}
private:
	string _S;
	string _T;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q12904>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
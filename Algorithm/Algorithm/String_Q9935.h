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
* Q9935
--------------------*/
class Q9935 : public QBase
{
public:
	Q9935() = default;
	virtual ~Q9935() = default;

	virtual void Input()
	{
		cin >> _str >> _bomb;
	}

	virtual void Solution()
	{
		string str;
		int len = _bomb.length();
		for (int i = 0; i < _str.length(); ++i)
		{
			str += _str[i];
			if (str.length() >= len)
			{
				bool flag = true;
				for (int j = 0; j < len; ++j)
				{
					if (str[str.length() + j - len] != _bomb[j])
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					// str.erase(str.end() - len, str.end());
					str.resize(str.length() - len);
				}
			}
		}
		if (str.length() == 0)
			cout << "FRULA";
		else
			cout << str;
	}
private:
	string _str;
	string _bomb;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q9935>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
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
	virtual void Input() {};
	virtual void Solution() {};
	virtual void Delete() {};
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
};
class Q6603 : public QBase
{
public:
	enum Parameter
	{
		MAX_CNT = 6,
	};
	Q6603()
		: _k(0)
		, _ret()
	{};
	virtual ~Q6603() = default;

	virtual void Input()
	{
		for (auto& k : _arr)
			cin >> k;
	};

	void DP(const int& pos, const int& idx)
	{
		if (_k - pos + idx < MAX_CNT)	// 기저 조건: 남은 숫자의 조합이 6보다 적은 경우 탈출
			return;
		_ret[idx] = _arr[pos];
		for (int nxtPos = pos + 1; nxtPos < _k; ++nxtPos)
		{
			if (idx == MAX_CNT - 2) {
				_ret[MAX_CNT - 1] = _arr[nxtPos];
				for (const auto& a : _ret)
					cout << a << " ";
				cout << "\n";
				continue;
			}
			DP(nxtPos, idx + 1);
		}
	}

	virtual void Solution()
	{
		for (int i = 0; i < _k; ++i)
		{
			DP(i, 0);
		}
	};

	virtual void Delete()
	{
		_arr.clear();
	}

	virtual void Solve()
	{
		while (true)
		{
			cin >> _k;
			if (_k == 0)
				break;
			_arr.resize(_k);
			Input();
			Solution();
			cout << "\n";
			Delete();
		}
	}

private:
	int _k;
	vector<int> _arr;
	int _ret[MAX_CNT];
};
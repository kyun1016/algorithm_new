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
* Q2143
--------------------*/
class Q2143 : public QBase
{
public:
	Q2143() = default;
	virtual ~Q2143() = default;

	virtual void Input()
	{
		cin >> _T >> _N;
		_A.resize(_N + 1);
		_A[0] = 0;
		for (int i = 1; i < _N + 1; ++i)
		{
			cin >> _A[i];
			_A[i] += _A[i - 1];	// 누적합
		}

		cin >> _M;
		_B.resize(_M + 1);
		_B[0] = 0;
		for (int i = 1; i < _M + 1; ++i)
		{
			cin >> _B[i];
			_B[i] += _B[i - 1];
		}
	}

	virtual void Solution()
	{
		vector<long long> sumA;
		vector<long long> sumB;
		// 부분 누적합 계산
		for (int i = 0; i < _N + 1; ++i)
			for (int j = 0; j < i; ++j)
				sumA.push_back(_A[i] - _A[j]);

		for (int i = 0; i < _M + 1; ++i)
			for (int j = 0; j < i; ++j)
				sumB.push_back(_B[i] - _B[j]);

		// 정렬
		sort(sumA.begin(), sumA.end());
		sort(sumB.begin(), sumB.end());

		// 이분탐색
		long long ret = 0;
		for (auto A : sumA)
		{
			int lowerBound;
			int upperBound;
			int lo;
			int hi;
			int mid;
			{
				lo = 0;
				hi = sumB.size() - 1;
				while (lo <= hi)
				{
					mid = (lo + hi) / 2;
					if (_T - A <= sumB[mid])
						hi = mid - 1;
					else
						lo = mid + 1;
				}
				lowerBound = lo;
			}
			{
				lo = 0;
				hi = sumB.size() - 1;
				while (lo <= hi)
				{
					mid = (lo + hi) / 2;
					if (_T - A < sumB[mid])
						hi = mid - 1;
					else
						lo = mid + 1;
				}
				upperBound = lo;
			}

			ret += upperBound - lowerBound;
		}

		cout << ret;
	}
private:
	int _T;
	int _N;
	int _M;
	vector<long long> _A;
	vector<long long> _B;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q2143>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
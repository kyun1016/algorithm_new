#pragma once
#define OUT

#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <stdint.h>

#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <limits>
#include <vector>
#include <climits>

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

class QHelper
{
public:
	static inline void Init() {
		std::ios_base::sync_with_stdio(false);
		std::cin.tie(NULL);
		std::cout.tie(NULL);
	}
};

class QBase
{
public:
	QBase() = default;
	QBase(const QBase& rhs) = default;
	QBase& operator=(const QBase& rhs)
	{
		return *this;
	}
	virtual ~QBase() = default;

public:
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
private:
	virtual void Input() = 0;
	virtual void Solution() = 0;
	virtual void Delete() = 0;

};

/*--------------------
* Q25314
--------------------*/
class Q25314 : public QBase
{
public:
	Q25314()
		: QBase()
		, _A(4)
	{}
	Q25314(const Q25314& rhs)
		: QBase(rhs)
		, _A(rhs._A)
	{}
	Q25314& operator=(const Q25314& rhs)
	{
		if (&rhs == this) return *this;
		QBase::operator=(rhs);

		_A = rhs._A;

		return *this;
	}
	virtual ~Q25314() = default;

private:
	virtual void Input()
	{
		std::cin >> _A;
		assert(_A >= 4 && _A <= 1000);
	}
	virtual void Solution()
	{
		for (uint16_t i = 0; i < _A / 4; ++i) std::cout << "long ";
		std::cout << "int\n";
	}
	virtual void Delete()
	{
	}

private:
	uint16_t _A;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	QHelper::Init();
//
//	std::unique_ptr<QBase> q = std::make_unique<Q25314>();
//
//	q->Solve();
//	return 0;
//}
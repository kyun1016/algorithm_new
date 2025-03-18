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
* Q11382
--------------------*/
class Q11382 : public QBase
{
public:
	Q11382()
		: QBase()
		, _A(0)
		, _B(0)
		, _C(0)
	{}
	Q11382(const Q11382& rhs)
		: QBase(rhs)
		, _A(rhs._A)
		, _B(rhs._B)
		, _C(rhs._C)
	{}
	Q11382& operator=(const Q11382& rhs)
	{
		if (&rhs == this) return *this;
		QBase::operator=(rhs);

		_A = rhs._A;
		_B = rhs._B;
		_C = rhs._C;

		return *this;
	}
	virtual ~Q11382() = default;

private:
	virtual void Input()
	{
		std::cin >> _A >> _B >> _C;
		assert(_A >= 1 && _A <= 1000000000000);
		assert(_B >= 1 && _B <= 1000000000000);
		assert(_C >= 1 && _C <= 1000000000000);
	}
	virtual void Solution()
	{
		std::cout << _A + _B + _C << std::endl;
	}
	virtual void Delete()
	{
	}

private:
	uint64_t _A;
	uint64_t _B;
	uint64_t _C;
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();

	std::unique_ptr<QBase> q = std::make_unique<Q11382>();

	q->Solve();
	return 0;
}

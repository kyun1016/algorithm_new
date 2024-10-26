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
* Q10158
--------------------*/
class Q10158 : public QBase
{
public:
	struct Pos
	{
		int x;
		int y;
	};
public:
	Q10158()
		:_dir({ 1,1 })
	{}
	virtual ~Q10158() = default;

	virtual void Input()
	{
		cin >> _maxPos.x >> _maxPos.y;
		cin >> _pos.x >> _pos.y;
		cin >> _t;
	}

	virtual void Solution()
	{
		_pos.x += _t;
		_pos.x %= _maxPos.x * 2;
		_pos.y += _t;
		_pos.y %= _maxPos.y * 2;

		if (_pos.x >= _maxPos.x)
			_pos.x = 2 * _maxPos.x - _pos.x;
		if (_pos.y >= _maxPos.y)
			_pos.y = 2 * _maxPos.y - _pos.y;

		cout << _pos.x << " " << _pos.y;
	}
private:
	Pos _maxPos;
	Pos _pos;
	Pos _dir;
	int _t;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q10158>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
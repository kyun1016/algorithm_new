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
* Q1034
--------------------*/
class Q1034 : public QBase
{
public:
	Q1034() = default;
	virtual ~Q1034() = default;

	virtual void Input()
	{
		cin >> _N >> _M;
		_arr.resize(_N);
		for (int y = 0; y < _N; ++y)
			cin >> _arr[y];
		cin >> _K;
	}

	virtual void Solution()
	{
		unordered_map<string, int> table;
		for (const auto& str : _arr)
		{
			int cntZero = 0;
			for (const auto& c : str)
				if (c == '0')
					++cntZero;

			if (cntZero > _K || cntZero % 2 != _K % 2)
				continue;

			if (table.find(str) == table.end())
				table.insert({ str, 1 });
			else
				table[str]++;
		}

		int ret = 0;
		for (const auto& i : table)
			ret = ret > i.second ? ret : i.second;

		cout << ret;
	}
private:
	int _N;
	int _M;
	int _K;
	vector<string> _arr;
};

/*--------------------
* main
--------------------*/
//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1034>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
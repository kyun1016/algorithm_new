#pragma once
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
* Q1922
--------------------*/
class Q5419 : public QBase
{
public:
	Q5419() = default;
	virtual ~Q5419() = default;

	virtual void Input()
	{
		cin >> _N;
		_map.resize(_N);
		for (auto& island : _map)
			cin >> island.first >> island.second;
	}

	virtual void Solution()
	{

	}

	virtual void Delete()
	{
		_map.clear();
	}

	virtual void Solve()
	{
		int TestCase;
		cin >> TestCase;
		while (TestCase--)
		{
			Input();
			Solution();
			Delete();
		}
	}
private:
	int _N;
	vector<pair<int, int>> _map;
};
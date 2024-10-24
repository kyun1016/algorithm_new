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
private:
	int _N = 10;
};
class Q1764 : public QBase
{
public:
	Q1764() {}
	virtual ~Q1764() {}

	virtual void Input()
	{
		//int N, M;
		//cin >> N >> M;

		//set<string> s1;
		//vector<string> ret;
		//ret.reserve(min(N, M));
		//string name;
		//for (int i = 0; i < N; ++i)
		//{
		//	cin >> name;
		//	s1.insert(name);
		//}

		//for (int i = 0; i < M; ++i)
		//{
		//	cin >> name;
		//	if (s1.find(name) != s1.end())
		//		ret.push_back(name);
		//}

		//sort(ret.begin(), ret.end());
		//cout << ret.size() << endl;
		//for (const auto& str : ret)
		//	cout << str << endl;

		int N, M;
		cin >> N >> M;

		unordered_map<string, int> map;
		vector<string> ret;
		ret.reserve(min(N, M));
		string name;
		for (int i = 0; i < N; ++i)
		{
			cin >> name;
			map.insert({ name, i });
		}

		for (int i = 0; i < M; ++i)
		{
			cin >> name;
			if (map.find(name) != map.end())
				ret.push_back(name);
		}

		sort(ret.begin(), ret.end());
		cout << ret.size() << endl;
		for (const auto& str : ret)
			cout << str << endl;
	}

};

//int main()
//{
//	unique_ptr<QBase> q = make_unique<Q1764>();
//	q->Init();
//	q->Solve();
//
//	return 0;
//}
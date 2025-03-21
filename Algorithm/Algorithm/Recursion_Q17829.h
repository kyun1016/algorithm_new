#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<stdint.h>
#include<algorithm>

using namespace std;

class QBase
{
public:
	QBase() = default;
	virtual ~QBase() = default;
	QBase(const QBase& rhs) = delete;
	QBase operator=(const QBase& rhs) = delete;

	void Run()
	{
		Input();
		Solve();
		Clear();
	}
private:
	virtual void Input() = 0;
	virtual void Solve() = 0;
	virtual void Clear() = 0;
};

class Q17829 final : public QBase
{
public:
	Q17829() = default;
	~Q17829() = default;

private:
	virtual void Input() override
	{
		cin >> _N;
		_arr.resize(_N, vector<int16_t>(_N));
		for (auto& r : _arr)
			for (auto& c : r)
				cin >> c;
	}
	virtual void Solve() override
	{
		while (_arr.size() > 1)
		{
			_arr = Polling();
		}

		cout << _arr[0][0];
	}
	virtual void Clear() override
	{}

	vector<vector<int16_t>> Polling()
	{
		vector<vector<int16_t>> ret;
		ret.resize(_arr.size() / 2, vector<int16_t>(_arr.size() / 2));

		for (size_t y = 0; y < ret.size(); ++y)
			for (size_t x = 0; x < ret.size(); ++x)
			{
				int a[4];
				a[0] = _arr[y * 2][x * 2];
				a[1] = _arr[y * 2][x * 2 + 1];
				a[2] = _arr[y * 2 + 1][x * 2];
				a[3] = _arr[y * 2 + 1][x * 2 + 1];
				sort(a, a + 4);
				ret[y][x] = a[2];
			}

		return ret;
	}

	int16_t _N;
	vector<vector<int16_t>> _arr;
};

int main()
{
	unique_ptr<QBase> q = make_unique<Q17829>();
	q->Run();

	return 0;
}
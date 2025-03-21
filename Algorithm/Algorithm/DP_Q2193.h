#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<cstdint>

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

class Q2193 final : public QBase
{
public:
	Q2193() = default;
	virtual ~Q2193() = default;

private:
	virtual void Input() override
	{
		std::cin >> _N;
	}
	virtual void Solve() override
	{
		_dp.resize(_N + 1, std::vector<uint64_t>(2, 0));
		_dp[1][1] = 1;
		for (int i = 2; i <= _N; ++i)
		{
			_dp[i][0] = _dp[i - 1][0] + _dp[i - 1][1];
			_dp[i][1] = _dp[i - 1][0];
		}

		std::cout << _dp[_N][0] + _dp[_N][1];
	}
	virtual void Clear() override
	{

	}
private:
	uint64_t _N;
	std::vector<std::vector<uint64_t>> _dp;
};

int main()
{
	std::unique_ptr<QBase> q = std::make_unique<Q2193>();
	q->Run();
	return 0;
}
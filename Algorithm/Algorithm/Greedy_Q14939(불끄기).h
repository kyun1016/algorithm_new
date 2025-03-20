#pragma once
#define OUT

#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <stdint.h>

#include <filesystem>

#include <fstream>
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

	static inline void mkdir(const std::string& path)
	{
		std::filesystem::path p(path);

		if (std::filesystem::is_directory(p))
			return;

		std::filesystem::create_directories(p);
	}
	static inline void SaveTestFile(const std::string& dir = "./TestData/Q1/", const std::string& filename = "Input1.txt")
	{
		mkdir(dir);
		std::string line;
		std::ofstream ofp(dir + filename);

		assert(ofp.is_open());

		while (std::getline(std::cin, line)) {
			if (line == ";;") break;
			ofp << line << std::endl;
		}

		ofp.close();
	}

	static inline std::ifstream LoadROFile(const std::string& dir = "./TestData/Q1/", const std::string& filename = "Input1.txt")
	{
		std::ifstream fp(dir + filename);
		assert(fp.is_open());
		return fp;
	}

	static inline std::ofstream LoadWOFile(const std::string& dir = "./TestData/Q1/", const std::string& filename = "Input1.txt")
	{
		std::ofstream fp(dir + filename);
		assert(fp.is_open());
		return fp;
	}

	static inline void SaveTest(const std::string& dir = "./TestData/Q1/", const int& num = 1)
	{
		std::string temp;
		// std::cin >> temp;

		for (int i = 1; i <= num; ++i)
		{
			std::string inputFileName = "Input" + std::to_string(i) + ".txt";
			std::string outputFileName = "Output" + std::to_string(i) + ".txt";

			std::cout << "*Info, Start Input file: " << dir + inputFileName << " (last line: ;;)\n";
			SaveTestFile(dir, inputFileName);
			std::cout << "*Info, Finish Input file: " << dir + inputFileName << "\n";

			std::cout << "*Info, Start Onput file: " << dir + outputFileName << " (last line: ;;)\n";
			SaveTestFile(dir, outputFileName);
			std::cout << "*Info, Finish Onput file: " << dir + outputFileName << "\n";
		}
	}

	static inline std::ifstream LoadTestInput(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::string filename = "Input" + std::to_string(testCase) + ".txt";
		return LoadROFile(dir, filename);
	}

	static inline std::ifstream LoadTestOutput(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::string filename = "Output" + std::to_string(testCase) + ".txt";
		return LoadROFile(dir, filename);
	}
	static inline std::ifstream LoadTestAnswer(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::string filename = "Ans" + std::to_string(testCase) + ".txt";
		return LoadROFile(dir, filename);
	}

	static inline std::ofstream PrintTestAnswer(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::string filename = "Ans" + std::to_string(testCase) + ".txt";
		return LoadWOFile(dir, filename);
	}

	static inline void Score(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::ifstream ifp = LoadTestOutput(dir, testCase);
		std::ifstream ifp2 = LoadTestAnswer(dir, testCase);

		std::string line;
		std::string line2;
		uint32_t i = 0;
		while (getline(ifp, line)) {
			assert(getline(ifp2, line2));
			if (line2.back() == ' ')
				line2.pop_back();
			else if (line2.back() == '\n')
				line2.pop_back();

			std::cout << line2 << std::endl;
			// assert(line.compare(line2) == 0);
			if (line.compare(line2) == 0)
				std::cout << "*Info, [" << i++ << " Line] Test Pass\n";
			else
				std::cout << "*Info, [" << i++ << " Line] Test Fail\n";
		}
	}
};

class QBase
{
public:
	QBase() = default;
	QBase(const QBase& rhs) = delete;
	QBase& operator=(const QBase& rhs) = delete;
	virtual ~QBase() = default;

public:
	virtual void Solve(const int& testCase = 1)
	{
		Input(testCase);
		Solution(testCase);
		Delete();
	}
private:
	virtual void Input(const int& testCase) = 0;
	virtual void Solution(const int& testCase) = 0;
	virtual void Delete() = 0;

};

/*--------------------
* Q14939
--------------------*/
class Q14939 final : public QBase
{
public:
	Q14939() = default;
	virtual ~Q14939() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		_arr.resize(10);
		std::string line;
		for (uint16_t y = 0; y < 10; ++y)
		{
			cin >> line;
			for (uint16_t x = 0; x < 10; ++x)
				if (line[x] == 'O')
					bitsum(y, x);
		}
	}
	virtual void Solution(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ofstream cout = QHelper::PrintTestAnswer(_dir, testCase);
#else
		using namespace std;
#endif
		/*--------------------
		* Solution
		--------------------*/
		{
			int ret = 1000000007;
			int cnt = 0;
			std::vector<uint16_t> map(_arr);
			for (uint16_t k = 0; k < (1 << 10); ++k)
			{
				// 1. Initial
				{
					for (uint16_t y = 0; y < 10; ++y)
						_arr[y] = map[y];
					cnt = 0;
				}
				// 2. Pre Setting
				for (int x = 0; x < 10; ++x)
				{
					if (k & (1 << x))
					{
						++cnt;
						pushBtn(0, x);
					}
				}

				// 3. Btn Chk
				for (uint16_t y = 1; y < 10; ++y)
				{
					for (uint16_t x = 0; x < 10; ++x)
					{
						if (bitchk(y - 1, x))
						{
							pushBtn(y, x);
							++cnt;
						}
					}
				}
				if (!_arr[9])
					ret = ret < cnt ? ret : cnt;
			}

			if (ret == 1000000007)
				cout << -1;
			else
				cout << ret;
		}

#if defined(DEBUG) || defined(_DEBUG)
		cout << std::endl;
		cout.close();
		QHelper::Score(_dir, testCase);
#endif
	}
	virtual void Delete() override
	{
	}
private:
	std::string _dir = "./TestData/Q14939/";
private:
	std::vector<uint16_t> _arr;

	inline void bitsum(const int& y, const int& x)
	{
		if (y < 0 || y > 9)
			return;
		if (x < 0 || x > 9)
			return;

		_arr[y] ^= (1 << x);
	}

	inline bool bitchk(const int& y, const int& x)
	{
		if (y < 0 || y > 9)
			return false;
		if (x < 0 || x > 9)
			return false;

		return _arr[y] & (1 << x);
	}

	inline void pushBtn(const int& y, const int& x)
	{
		if (y < 0 || y > 9)
			return;
		if (x < 0 || x > 9)
			return;

		bitsum(y - 1, x);
		bitsum(y, x - 1);
		bitsum(y, x);
		bitsum(y, x + 1);
		bitsum(y + 1, x);
	}
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 1;
	// QHelper::SaveTest("./TestData/Q14939/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q14939>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q14939>();
	q->Solve();
#endif
	return 0;
}
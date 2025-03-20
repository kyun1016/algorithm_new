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
* Q2873
--------------------*/
class Q2873 final : public QBase
{
public:
	Q2873() = default;
	virtual ~Q2873() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		cin >> _R >> _C;
		_arr.resize(_R, std::vector<int16_t>(_C));
		for (auto& r : _arr)
			for (auto& c : r)
				cin >> c;
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

			if (_R % 2)
			{
				for (int16_t r = 0; r < _R; ++r)
				{
					char d = r % 2 ? 'L' : 'R';
					for (int16_t c = 1; c < _C; ++c)
						cout << d;
					if (r == _R - 1)
						break;
					cout << 'D';
				}
			}
			else if (_C % 2)
			{
				for (int16_t c = 0; c < _C; ++c)
				{
					char d = c % 2 ? 'U' : 'D';
					for (int16_t r = 1; r < _R; ++r)
						cout << d;
					if (c == _C - 1)
						break;
					cout << 'R';
				}
			}
			else
			{
				pos target = findMin();
				// 전반부
				for (int16_t c = 0; c <= (target.x - 1 - target.x % 2); ++c)
				{
					char d = c % 2 ? 'U' : 'D';
					for (int16_t r = 1; r < _R; ++r)
						cout << d;
					cout << 'R';
				}

				// 중간
				{
					// 위쪽
					int16_t r = 0;
					for (; r <= (target.y - 1 - target.y % 2); ++r)
						cout << (r % 2 ? "LD" : "RD");
					// 타겟
					for (int i = 0; i < 2; ++r, i++)
					{
						if (target.y % 2 == r % 2)
						{
							if (r != _R - 1)
								cout << 'D';
							continue;
						}
						cout << 'R';
						if (r != _R - 1)
							cout << 'D';
						else if ((target.x + 2 - target.x % 2) != _C)
							cout << 'R';
					}
					// 아래쪽
					for (; r < _R; ++r)
					{
						cout << (r % 2 ? 'R' : 'L');
						if (r != _R - 1)
							cout << 'D';
						else if ((target.x + 2 - target.x % 2) != _C)
							cout << 'R';
					}

				}

				// 후반부
				for (int16_t c = (target.x + 2 - target.x % 2); c < _C; ++c)
				{
					char d = c % 2 ? 'D' : 'U';
					for (int16_t r = 1; r < _R; ++r)
						cout << d;
					if (c == _C - 1)
						break;
					cout << 'R';
				}
			}
		}

#if defined(DEBUG) || defined(_DEBUG)
		cout << std::endl;
		cout.close();
		QHelper::Score(_dir, testCase);
#endif
	}
	virtual void Delete() override
	{
		_arr.clear();
	}
private:
	std::string _dir = "./TestData/Q2873/";
private:
	int16_t _R;
	int16_t _C;
	std::vector<std::vector<int16_t>> _arr;

	struct pos
	{
		int16_t x;
		int16_t y;
	};

	inline pos findMin()
	{
		int16_t val = INF;
		pos ret = { 0,1 };
		for (int16_t r = 0; r < _R; ++r)
			for (int16_t c = 0; c < _C; ++c)
				if ((r + c) % 2)
					if (val > _arr[r][c])
					{
						val = _arr[r][c];
						ret.x = c;
						ret.y = r;
					}

		return ret;
	}
	static constexpr int16_t INF = 1001;
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 3;
	//QHelper::SaveTest("./TestData/Q2873/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q2873>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q2873>();
	q->Solve();
#endif
	return 0;
}
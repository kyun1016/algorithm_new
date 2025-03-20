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
* Q25682
--------------------*/
class Q25682 final : public QBase
{
public:
	Q25682() = default;
	virtual ~Q25682() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		cin >> _N >> _M >> _K;
		_board.resize(_N, std::vector<bool>(_M));
		char c;
		for (uint16_t y = 0; y < _N; ++y)
			for (uint16_t x = 0; x < _M; ++x)
			{
				cin >> c;
				if (c == 'B')
					_board[y][x] = false;
				else
					_board[y][x] = true;
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
			std::vector<std::vector<uint32_t>> wbw;
			std::vector<std::vector<uint32_t>> bwb;
			wbw.resize(_N + 1, std::vector<uint32_t>(_M + 1));
			bwb.resize(_N + 1, std::vector<uint32_t>(_M + 1));

			// 1.1. WBWB 구간 합 [l,r]
			for (uint16_t y = 0; y < _N; ++y)
				for (uint16_t x = 0; x < _M; ++x)
				{
					wbw[y + 1][x + 1] = wbw[y + 1][x] + wbw[y][x + 1] - wbw[y][x];
					if ((y + x) % 2 == 0 && !_board[y][x] || (y + x) % 2 == 1 && _board[y][x])
						wbw[y + 1][x + 1]++;
				}

			// 1.2. BWBW 구간 합 [l,r]
			for (uint16_t y = 0; y < _N; ++y)
				for (uint16_t x = 0; x < _M; ++x)
				{
					bwb[y + 1][x + 1] = bwb[y + 1][x] + bwb[y][x + 1] - bwb[y][x];
					if ((y + x) % 2 == 0 && _board[y][x] || (y + x) % 2 == 1 && !_board[y][x])
						bwb[y + 1][x + 1]++;
				}

			uint32_t ret = 4000000;
			for (uint16_t y = _K; y <= _N; ++y)
				for (uint16_t x = _K; x <= _M; ++x)
				{
					// 2.1. WBW[0][l,r] / BWB / WBW ... 중 최소값
					uint32_t sum = wbw[y][x] - wbw[y][x - _K] - wbw[y - _K][x] + wbw[y - _K][x - _K];
					ret = ret < sum ? ret : sum;

					sum = bwb[y][x] - bwb[y][x - _K] - bwb[y - _K][x] + bwb[y - _K][x - _K];
					// 2.2. BWB[0][l,r] / WBW / BWB ... 중 최소값
					ret = ret < sum ? ret : sum;
				}
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
		for (auto& d : _board)
			d.clear();
		_board.clear();
	}

private:
	std::string _dir = "./TestData/Q25682/";
private:
	uint16_t _N;
	uint16_t _M;
	uint16_t _K;
	std::vector<std::vector<bool>> _board;
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 4;
	// QHelper::SaveTest("./TestData/Q25682/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q25682>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q25682>();
	q->Solve();
#endif
	return 0;
}
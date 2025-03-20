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
* Q1700
--------------------*/
class Q1700 final : public QBase
{
public:
	Q1700() = default;
	virtual ~Q1700() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		cin >> _N >> _K;
		_arr.resize(_K);
		for (auto& d : _arr)
			cin >> d;
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
			int ret = 0;
			std::unordered_map<uint16_t, uint16_t> tap;
			for (int i = 0; i < _K; ++i) {
				if (tap.find(_arr[i]) != tap.end())
					continue;
				if (tap.size() < _N)
				{
					tap[_arr[i]] = _arr[i];
					continue;
				}

				if (_N == 1)
					tap.erase(tap.begin()->first);
				else
				{
					std::unordered_map<uint16_t, uint16_t> target(tap);
					for (int j = i + 1; j < _K; ++j) {
						if (target.find(_arr[j]) != target.end())
							target.erase(_arr[j]);
						if (target.size() <= 1)
							break;
					}
					tap.erase(target.begin()->first);
				}

				++ret;
				tap[_arr[i]] = _arr[i];
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
	}

private:
	std::string _dir = "./TestData/Q1700/";
private:
	uint16_t _N;
	uint16_t _K;
	std::vector<uint16_t> _arr;
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 1;
	// QHelper::SaveTest("./TestData/Q1700/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q1700>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q1700>();
	q->Solve();
#endif
	return 0;
}
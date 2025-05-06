#pragma once
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

#define OUT
constexpr int Q_NAME = 5073;

#if defined(DEBUG) || defined(_DEBUG)
#define Q_INPUT_INIT() std::ifstream cin = QHelper::LoadTestInput(_dir, _testCase);
#define Q_SOLUTION_INIT() std::ofstream cout = QHelper::PrintTestAnswer(_dir, _testCase);
#define Q_SOLUTION_END() cout << std::endl; cout.close(); QHelper::Score(_dir, _testCase);
#else
#define Q_INPUT_INIT() using namespace std;
#define Q_SOLUTION_INIT() using namespace std;
#define Q_SOLUTION_END() 
#endif
#define Q_CLASS_BEGIN(ID) class Q##ID : public QBase	\
{														\
public:													\
	Q##ID()	: QBase(##ID) {};							\
	virtual ~Q##ID() = default;							\

#define Q_PTR(ID) std::make_unique<Q##ID>()


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
		uint16_t i = 0;
		while (getline(ifp, line)) {
			assert(getline(ifp2, line2));
			if (line2.back() == ' ')
				line2.pop_back();
			else if (line2.back() == '\n')
				line2.pop_back();

			std::cout << line2 << std::endl;
			assert(line == line2);
			std::cout << "*Info, [" << i++ << " Line] Test Pass\n";
		}
	}
};

class QBase
{
public:
	QBase() = default;
	QBase(std::string num)
		: _dir("./TestData/Q" + num + "/")
	{

	}
	QBase(int num)
		: _dir("./TestData/Q" + std::to_string(num) + "/")
	{

	}
	virtual ~QBase() = default;
	QBase(const QBase& rhs) = delete;
	QBase& operator=(const QBase& rhs) = delete;

public:
	virtual void Solve(const int& testCase = 1)
	{
		_testCase = testCase;
		Input();
		Solution();
		Delete();
	}
private:
	virtual void Input() = 0;
	virtual void Solution() = 0;
	virtual void Delete() = 0;
protected:
	int _testCase = 1;
	std::string _dir = "./TestData/Q99999/";
};

class QSolve : public QBase
{
public:
	QSolve() : QBase(Q_NAME) {};
	virtual ~QSolve() = default;
private:
	virtual void Input()
	{
		Q_INPUT_INIT();
		int a = 1, b = 1, c = 1;
		while (true)
		{
			cin >> a >> b >> c;
			if (a == 0 && b == 0 && c == 0) break;
			_arr.push_back(a);
			_arr.push_back(b);
			_arr.push_back(c);
		}
	}
	virtual void Solution()
	{
		Q_SOLUTION_INIT();

		for (int i = 0; i < _arr.size(); i += 3)
		{
			int a = _arr[i];
			int b = _arr[i + 1];
			int c = _arr[i + 2];
			if (a == 0 && b == 0 && c == 0) break;

			if (a + b <= c || a + c <= b || b + c <= a)
			{
				cout << "Invalid\n";
				continue;
			}
			if (a == b && a == c)
				cout << "Equilateral\n";
			else if (a == b || b == c || a == c)
				cout << "Isosceles\n";
			else
				cout << "Scalene\n";
		}

		Q_SOLUTION_END();
	}
	virtual void Delete()
	{

	}
private:
	std::vector<int> _arr;
};
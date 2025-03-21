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
* Q13976
--------------------*/
class Q13976 final : public QBase
{
public:
	Q13976() = default;
	virtual ~Q13976() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		cin >> _N;
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
		if (_N & 1)
			cout << 0;
		else
		{
			Mat2x1 ret = { 3, 1 };
			Mat rootMat = { 4, -1, 1, 0 };

			_N >>= 1;
			_N--;
			while (_N)
			{
				if (_N & 1)
					ret = mul(rootMat, ret);

				rootMat = mul(rootMat, rootMat);

				_N >>= 1;
			}
			if (ret.a0 < 0) ret.a0 += INF;
			cout << ret.a0;
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
	std::string _dir = "./TestData/Q13976/";
private:
	static constexpr int64_t INF = 1000000007;
	int64_t _N;

	struct Mat2x1
	{
		int64_t a0 = 1;
		int64_t a1 = 0;
	};

	struct Mat
	{
		int64_t a00 = 1;
		int64_t a01 = 0;
		int64_t a10 = 0;
		int64_t a11 = 1;
	};

	static Mat mul(const Mat& a, const Mat& b)
	{
		Mat ret;
		ret.a00 = ((a.a00 * b.a00) % INF + (a.a01 * b.a10) % INF) % INF;
		ret.a01 = ((a.a00 * b.a01) % INF + (a.a01 * b.a11) % INF) % INF;
		ret.a10 = ((a.a10 * b.a00) % INF + (a.a11 * b.a10) % INF) % INF;
		ret.a11 = ((a.a10 * b.a01) % INF + (a.a11 * b.a11) % INF) % INF;

		return ret;
	}
	static Mat2x1 mul(const Mat& a, const Mat2x1& b)
	{
		Mat2x1 ret;
		ret.a0 = ((a.a00 * b.a0) % INF + (a.a01 * b.a1) % INF) % INF;
		ret.a1 = ((a.a10 * b.a0) % INF + (a.a11 * b.a1) % INF) % INF;

		return ret;
	}

	// static Mat operator+(const Mat& a, const Mat& b)
	// {
	// 	Mat ret;
	// 	ret.a00 = (a.a00 + b.a00) % INF;
	// 	ret.a01 = (a.a01 + b.a01) % INF;
	// 	ret.a10 = (a.a10 + b.a10) % INF;
	// 	ret.a11 = (a.a11 + b.a11) % INF;
	// 
	// 	return ret;
	// }

};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 3;
	// QHelper::SaveTest("./TestData/Q13976/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q13976>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q13976>();
	q->Solve();
#endif
	return 0;
}
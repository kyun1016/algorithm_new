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
#include <map>
#include <unordered_set>
#include <iomanip>
#include <numeric>
#include <set>

#pragma region BOJHelper
#define OUT

#if defined(DEBUG) || defined(_DEBUG)
#define Q_INPUT_BEGIN() std::ifstream cin = QHelper::LoadTestInput(_dir, _testCase);
#define Q_SOLUTION_BEGIN() std::ofstream cout = QHelper::PrintTestAnswer(_dir, _testCase);
#define Q_SOLUTION_END() cout << std::endl; cout.close(); QHelper::Score(_dir, _testCase);
#else
#define Q_INPUT_BEGIN() using namespace std;
#define Q_SOLUTION_BEGIN() using namespace std;
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
protected:
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
public: // Singleton
	void Release()
	{
		if (gQBase)
		{
			delete gQBase;
			gQBase = nullptr;
		}
	}
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
	inline static QBase* gQBase;
	int _testCase = 1;
	std::string _dir = "./TestData/Q99999/";
};
#pragma endregion BOJHelper

constexpr int Q_NAME = 17103;

class QSolve : public QBase
{
private:
	QSolve() : QBase(Q_NAME) {

	};
	virtual ~QSolve()
	{
		gQBase = nullptr;
	};
public: // Singleton
	inline static QBase* GetInstance()
	{
		if (!gQBase)
		{
			gQBase = new QSolve();
		}
		return gQBase;
	}
private:
	using uint = unsigned long long;
	using si = uint8_t;
	enum class ePrimeState : si
	{
		NotPrime = 0,
		IsPrime = 1
	};

	std::vector<ePrimeState> _primeCache;
	std::vector<int> _prime;
	std::vector<int> _arr;
	static constexpr int MAX_NUM = 1'000'000;
private:
	bool SetPrimeTable()	// late Initialize
	{
		if (!_primeCache.empty())
			return false;

		_primeCache.resize(MAX_NUM + 1, ePrimeState::IsPrime);

		_primeCache[0] = ePrimeState::NotPrime;
		_primeCache[1] = ePrimeState::NotPrime;
		for (int i = 2; i * i <= MAX_NUM; ++i)
		{
			if (_primeCache[i] == ePrimeState::IsPrime)
				for (int j = i * i; j <= MAX_NUM; j += i)
					_primeCache[j] = ePrimeState::NotPrime;
		}

		_primeCache.reserve(78'498);
		for (int i = 2; i <= MAX_NUM; ++i)
		{
			if (_primeCache[i] == ePrimeState::IsPrime)
				_prime.push_back(i);
		}


		return true;
	}
	inline bool IsPrime(int n)
	{
		assert(n >= 0 && n <= MAX_NUM);
		assert(!_primeCache.empty());

		if (_primeCache[n] == ePrimeState::NotPrime)
			return false;
		else
			return true;
	}
	virtual void Input()
	{
		Q_INPUT_BEGIN();

		SetPrimeTable();

		uint temp;
		cin >> temp;
		_arr.resize(temp);
		for (auto& a : _arr)
			cin >> a;
	}
	virtual void Solution()
	{
		Q_SOLUTION_BEGIN();

		for (const auto& a : _arr)
		{
			int ret = 0;
			for (const auto& i : _prime)
			{
				if (i > a / 2)
					break;
				if (IsPrime(a - i))
					++ret;
			}
			cout << ret << '\n';
		}

		Q_SOLUTION_END();
	}
	virtual void Delete()
	{
		_arr.clear();
	}
};

/*--------------------
* main
--------------------*/
int main()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// QHelper::SaveTest("./TestData/Q" + std::to_string(Q_NAME) + "/", 1);
#endif
	QHelper::Init();

	QSolve::GetInstance()->Solve(1);
	return 0;
}
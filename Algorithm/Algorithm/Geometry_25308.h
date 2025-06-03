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

#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <iomanip>
#include <set>
#include <list>
#include <cmath>
#include <array>

#pragma region BOJHelper

#if defined(DEBUG) || defined(_DEBUG)
	#include <io.h>
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
			getline(ifp2, line2);
			if (line2.empty())
			{
				std::cout << "*Error, [" << i++ << " Line] Test Fail - Type 1\n";
				break;
			}

			if (line2.back() == ' ')
				line2.pop_back();
			else if (line2.back() == '\n')
				line2.pop_back();

			std::cout << line2 << std::endl;
			// assert(line == line2);
			if(line == line2)
				std::cout << "*Info, [" << i++ << " Line] Test Pass\n";
			else
				std::cout << "*Error, [" << i++ << " Line] Test Fail - Type 2\n";
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

#define OUT
#define IN

constexpr int Q_NAME = 25308;

class QSolve : public QBase
{
private:
	QSolve() : QBase(Q_NAME) { };
	virtual ~QSolve(){ gQBase = nullptr; };
public: // Singleton
	inline static QBase* GetInstance() { 
		if (!gQBase)
			gQBase = new QSolve();
		return gQBase;
	}
private:
	using uint = std::uint32_t;
	using integer = std::int32_t;
	using iter = std::list<std::int32_t>::iterator;
	using ull = unsigned long long;
	constexpr static int INF = -1000000007;
	
	std::array<ull, 8> _arr;
	std::array<bool, 8> _visited;
	std::array<ull, 8> arr;
private:
	virtual void Input()
	{
		Q_INPUT_BEGIN();

		for (auto& a : _arr)
			cin >> a;
	}

	// f(x) = -(a/c)*x + a (이때, a0, a1, a2이며, a1의 값은 (a1/root(2),a1/root(2)) 를 가짐)
	bool discriminant(ull a, ull b, ull c)
	{
		return (a + c) * (a + c) * b * b >= 2 * a * a * c * c;
		// return (a + c) * b >= 1.41421356 * a * c;
	}

	void func(ull& ret, const int& cnt) {
		if (cnt == 8)
		{
			if (discriminant(arr[0], arr[1], arr[2]) &&
				discriminant(arr[1], arr[2], arr[3]) &&
				discriminant(arr[2], arr[3], arr[4]) &&
				discriminant(arr[3], arr[4], arr[5]) &&
				discriminant(arr[4], arr[5], arr[6]) &&
				discriminant(arr[5], arr[6], arr[7]) &&
				discriminant(arr[6], arr[7], arr[0]) &&
				discriminant(arr[7], arr[0], arr[1]))
				ret++;
			return;
		}
		for (int i = 0; i < 8; ++i)
		{
			if (_visited[i]) continue;
			_visited[i] = true;
			arr[cnt] = _arr[i];
			func(ret, cnt + 1);
			_visited[i] = false;
		}
	}
	virtual void Solution()
	{
		Q_SOLUTION_BEGIN();

		for (auto& v : _visited)
			v = false;
		ull ret = 0;
		func(ret, 0);
		
		cout << ret;

		Q_SOLUTION_END();
	}

	virtual void Delete() {
	}
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();

#if defined(DEBUG) || defined(_DEBUG)
	const int Q_COUNT = 2;
	const std::string FILE_DIR = "./TestData/Q" + std::to_string(Q_NAME) + "/";
	const std::string FULL_FILE_DIR = FILE_DIR + "Output" + std::to_string(Q_COUNT) + ".txt";
	if (_access(FULL_FILE_DIR.c_str(), 0))
		QHelper::SaveTest(FILE_DIR, Q_COUNT);

	for (int i = 1; i <= Q_COUNT; ++i)
		QSolve::GetInstance()->Solve(i);	// Verification
#else
	QSolve::GetInstance()->Solve(1);
#endif

	return 0;
}
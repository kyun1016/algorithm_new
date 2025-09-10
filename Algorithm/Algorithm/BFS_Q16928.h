#pragma once
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
				std::cout << "*Error, [" << i++ << " Line] Test" << testCase << " Fail - Type 1\n";
				break;
			}

			if (line2.back() == ' ')
				line2.pop_back();
			else if (line2.back() == '\n')
				line2.pop_back();

			std::cout << line2 << std::endl;
			// assert(line == line2);
			if (line == line2)
				std::cout << "*Info, [" << i++ << " Line] Test" << testCase << " Pass\n";
			else
				std::cout << "*Error, [" << i++ << " Line] Test" << testCase << " Fail - Type 2\n";
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

constexpr int Q_NAME = 16928;
constexpr int Q_COUNT = 1;

class QSolve : public QBase
{
private:
	QSolve() : QBase(Q_NAME) {};
	virtual ~QSolve() { gQBase = nullptr; };
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
	using ll = long long;
	constexpr static int INF = -1000000007;

	uint _N, _M;
	std::unordered_map<uint, uint> _map;
	std::vector<uint> _board;
private:
	virtual void Input()
	{
		Q_INPUT_BEGIN();

		cin >> _N >> _M;

		_board.resize(101, 0);
		uint x, y;
		for (uint i = 0; i < _N; ++i)
		{
			cin >> x >> y;
			_map[x] = y;
		}
		for (uint i = 0; i < _M; ++i)
		{
			cin >> x >> y;
			_map[x] = y;
		}
	}


	void push(std::queue<std::pair<uint, uint>>& queue, const uint& node, const uint& cnt)
	{
		for (uint i = 1; i <= 6; ++i)
		{
			if (node + i > 100) continue;
			if (_board[node + i] == 0)
			{
				_board[node + i] = cnt;
				if (_map.find(node + i) != _map.end())
				{
					uint next = _map[node + i];
					if (_board[next] == 0)
					{
						_board[next] = cnt;
						queue.push({ next, cnt });
					}
				}
				else
				{
					queue.push({ node + i, cnt });
				}
			}
		}
	}
	void BFS()
	{
		std::queue<std::pair<uint, uint>> q;
		// uint cnt = 1;
		q.push({ 1, 0 });
		// push(q, 0, cnt);

		while (!q.empty())
		{
			auto [node, c] = q.front();
			if (node == 100)
			{
				std::cout << c << "\n";
				return;
			}
			q.pop();
			push(q, node, c + 1);
		}
	}
	virtual void Solution()
	{
		Q_SOLUTION_BEGIN();

		BFS();

		Q_SOLUTION_END();
	}

	virtual void Delete() {
		_board.clear();
		_map.clear();
	}
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();

#if defined(DEBUG) || defined(_DEBUG)
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
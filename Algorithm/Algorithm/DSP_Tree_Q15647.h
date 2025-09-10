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

constexpr int Q_NAME = 15647;
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
	constexpr static int INF = 1000000007;

	int _N;
	std::vector<std::vector<std::pair<int, int>>> _adj; // {정점, 가중치}
	std::vector<ll> _subtreeSum;    // 서브트리 거리 합
	std::vector<int> _subtreeSize;  // 서브트리 크기
	std::vector<ll> _answer;        // 최종 답

private:
	virtual void Input()
	{
		Q_INPUT_BEGIN();
		cin >> _N;

		_adj.resize(_N + 1);
		_subtreeSum.resize(_N + 1);
		_subtreeSize.resize(_N + 1);
		_answer.resize(_N + 1);

		for (int i = 0; i < _N - 1; ++i) {
			int u, v, d;
			cin >> u >> v >> d;
			_adj[u].push_back({ v, d });
			_adj[v].push_back({ u, d });
		}
	}

	// 첫 번째 DFS: 1번을 루트로 하여 서브트리 정보 계산
	void DFS1(int node, int parent) {
		_subtreeSize[node] = 1;
		_subtreeSum[node] = 0;

		for (auto& [child, weight] : _adj[node]) {
			if (child != parent) {
				DFS1(child, node);
				_subtreeSize[node] += _subtreeSize[child];
				_subtreeSum[node] += _subtreeSum[child] + (ll)_subtreeSize[child] * weight;
			}
		}
	}

	// 두 번째 DFS: 트리 재루팅으로 모든 노드의 답 계산
	void DFS2(int node, int parent, ll parentContribution) {
		_answer[node] = _subtreeSum[node] + parentContribution;

		for (auto& [child, weight] : _adj[node]) {
			if (child != parent) {
				// child를 루트로 했을 때의 부모 기여도
				ll newParentContrib = parentContribution +
					(_subtreeSum[node] - _subtreeSum[child] - (ll)_subtreeSize[child] * weight) +
					(ll)(_N - _subtreeSize[child]) * weight;

				DFS2(child, node, newParentContrib);
			}
		}
	}

	virtual void Solution()
	{
		Q_SOLUTION_BEGIN();

		DFS1(1, -1);        // 서브트리 정보 계산
		DFS2(1, -1, 0);     // 재루팅으로 모든 답 계산

		for (int i = 1; i <= _N; ++i) {
			cout << _answer[i] << '\n';
		}

		Q_SOLUTION_END();
	}

	virtual void Delete() {
		_adj.clear();
		_subtreeSum.clear();
		_subtreeSize.clear();
		_answer.clear();
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
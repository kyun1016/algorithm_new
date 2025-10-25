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
#include <deque>

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
#define OUT
#define IN

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

constexpr int Q_NAME = 20149;
constexpr int Q_COUNT = 10
;

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

	template<typename T = int>
	struct Point {
		T x, y;
		Point() : x(0), y(0) {}
		Point(T x, T y) : x(x), y(y) {}

		Point<T> operator+(const Point<T>& rhs) const {
			return Point(x + rhs.x, y + rhs.y);
		}
		Point<T> operator-(const Point<T>& rhs) const {
			return Point(x - rhs.x, y - rhs.y);
		}
		T dot(const Point<T>& rhs) const {
			return x * rhs.x + y * rhs.y;
		}
		T cross(const Point<T>& rhs) const {
			return x * rhs.y - y * rhs.x;
		}
	};

	enum class CCWResult : int {
		COUNTERCLOCKWISE = -1,
		CLOCKWISE = 1,
		COLINEAR = 0,
	};
	enum class LineRelation : uint8_t {
		PARALLEL = 0,
		INTERSECTING = 1,
		COINCIDENT = 2,
	};
	// CCW 함수: p1, p2, p3의 방향을 판단
	template<typename T = int>
	static inline int CCW(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
		Point<T> v1 = p2 - p1;
		Point<T> v2 = p3 - p1;
		auto cross = v1.cross(v2);
		if (cross > 0) return 1;    // 반시계 방향
		if (cross < 0) return -1;   // 시계 방향
		return 0;                   // 일직선상
	}

	template<typename T = int>
	struct Line {
		Point<T> p1, p2;

		Line() = default;
		Line(const Point<T>& p1, const Point<T>& p2) : p1(p1), p2(p2) {}
		Line(T x1, T y1, T x2, T y2) : p1(x1, y1), p2(x2, y2) {}

		Point<T> direction() const {
			return p2 - p1;
		}
		double slope() const {
			auto dir = direction();
			if (dir.x == 0) return INFINITY;
			return static_cast<double>(dir.y) / dir.x;
		}

		bool contains(const Point<T>& p) const {
			// 세 점이 일직선상에 있고, p가 선분 범위 내에 있는지 확인
			auto v1 = p - p1;
			auto v2 = p2 - p1;

			// 외적이 0이면 일직선상
			if (v1.cross(v2) != 0) return false;

			// 내적으로 범위 확인
			auto dot = v1.dot(v2);
			return dot >= 0 && dot <= v2.dot(v2);
		}
		// 두 선분의 교점 (CCW 알고리즘 사용)
		bool intersects(const Line<T>& other) const {
			int ccw1 = CCW<T>(p1, p2, other.p1);
			int ccw2 = CCW<T>(p1, p2, other.p2);
			int ccw3 = CCW<T>(other.p1, other.p2, p1);
			int ccw4 = CCW<T>(other.p1, other.p2, p2);

			// 일반적인 교차 조건
			if (ccw1 * ccw2 < 0 && ccw3 * ccw4 < 0) return true;

			// 한 점이 다른 선분 위에 있는 경우
			if (ccw1 == 0 && contains(other.p1)) return true;
			if (ccw2 == 0 && contains(other.p2)) return true;
			if (ccw3 == 0 && other.contains(p1)) return true;
			if (ccw4 == 0 && other.contains(p2)) return true;

			return false;
		}
		LineRelation getIntersection(Point<double>& ret, const Line<T>& other) const {
			// 선분이 교차하지 않으면 예외 처리
			if (!intersects(other)) {
				return LineRelation::PARALLEL;
			}

			// 선분 방정식: p1 + t * (p2 - p1)
			auto d1 = direction();
			auto d2 = other.direction();

			// 두 선분의 교차점 계산
			T denom = d1.cross(d2);
			if (denom == 0) {
				return LineRelation::COINCIDENT; // 평행하거나 일치
			}

			double t = static_cast<double>((other.p1 - p1).cross(d2)) / denom;
			ret = Point<double>(p1.x + t * d1.x, p1.y + t * d1.y);
			return LineRelation::INTERSECTING;
		}
	};

	// 타입 별칭
	using PointI = Point<int>;
	using PointF = Point<float>;
	using PointD = Point<double>;
	using LineI = Line<int>;
	using LineF = Line<float>;
	using LineD = Line<double>;
	using PointLL = Point<ll>;
	using LineLL = Line<ll>;

	LineLL L1, L2;  // 선분 두 개
private:
	virtual void Input()
	{
		Q_INPUT_BEGIN();

		cin >> L1.p1.x >> L1.p1.y >> L1.p2.x >> L1.p2.y;
		cin >> L2.p1.x >> L2.p1.y >> L2.p2.x >> L2.p2.y;
	}

	virtual void Solution()
	{
		Q_SOLUTION_BEGIN();

		if (L1.intersects(L2)) {
			cout << "1\n";

			// 교점 계산 및 출력
			Point<double> intersection;
			if (L1.getIntersection(intersection, L2) == LineRelation::INTERSECTING) {
				cout << std::fixed << std::setprecision(9);
				cout << intersection.x << " " << intersection.y << '\n';
			}
		}
		else {
			cout << "0\n";
		}

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
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
* Q16139
--------------------*/
class Q16139 final : public QBase
{
public:
	Q16139() = default;
	virtual ~Q16139() = default;

private:
	virtual void Input(const int& testCase) override
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream cin = QHelper::LoadTestInput(_dir, testCase);
#else
		using namespace std;
#endif
		cin >> _S;
		int q;
		cin >> q;
		_arr.resize(q);
		for (int i = 0; i < q; ++i)
			cin >> _arr[i].alpha >> _arr[i].s >> _arr[i].e;
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
			_sumArr.resize(_S.length() + 2);

			for (int i = 1; i <= _S.length(); ++i)
				_sumArr[i + 1] = _sumArr[i] + _S[i - 1];

			for (const auto& d : _arr)
			{
				uint32_t ret = 0;
				if (d.alpha == 'a') ret = _sumArr[d.e + 1].a - _sumArr[d.s].a;
				else if (d.alpha == 'b') ret = _sumArr[d.e + 1].b - _sumArr[d.s].b;
				else if (d.alpha == 'c') ret = _sumArr[d.e + 1].c - _sumArr[d.s].c;
				else if (d.alpha == 'd') ret = _sumArr[d.e + 1].d - _sumArr[d.s].d;
				else if (d.alpha == 'e') ret = _sumArr[d.e + 1].e - _sumArr[d.s].e;
				else if (d.alpha == 'f') ret = _sumArr[d.e + 1].f - _sumArr[d.s].f;
				else if (d.alpha == 'g') ret = _sumArr[d.e + 1].g - _sumArr[d.s].g;
				else if (d.alpha == 'h') ret = _sumArr[d.e + 1].h - _sumArr[d.s].h;
				else if (d.alpha == 'i') ret = _sumArr[d.e + 1].i - _sumArr[d.s].i;
				else if (d.alpha == 'j') ret = _sumArr[d.e + 1].j - _sumArr[d.s].j;
				else if (d.alpha == 'k') ret = _sumArr[d.e + 1].k - _sumArr[d.s].k;
				else if (d.alpha == 'l') ret = _sumArr[d.e + 1].l - _sumArr[d.s].l;
				else if (d.alpha == 'm') ret = _sumArr[d.e + 1].m - _sumArr[d.s].m;
				else if (d.alpha == 'n') ret = _sumArr[d.e + 1].n - _sumArr[d.s].n;
				else if (d.alpha == 'o') ret = _sumArr[d.e + 1].o - _sumArr[d.s].o;
				else if (d.alpha == 'p') ret = _sumArr[d.e + 1].p - _sumArr[d.s].p;
				else if (d.alpha == 'q') ret = _sumArr[d.e + 1].q - _sumArr[d.s].q;
				else if (d.alpha == 'r') ret = _sumArr[d.e + 1].r - _sumArr[d.s].r;
				else if (d.alpha == 's') ret = _sumArr[d.e + 1].s - _sumArr[d.s].s;
				else if (d.alpha == 't') ret = _sumArr[d.e + 1].t - _sumArr[d.s].t;
				else if (d.alpha == 'u') ret = _sumArr[d.e + 1].u - _sumArr[d.s].u;
				else if (d.alpha == 'v') ret = _sumArr[d.e + 1].v - _sumArr[d.s].v;
				else if (d.alpha == 'w') ret = _sumArr[d.e + 1].w - _sumArr[d.s].w;
				else if (d.alpha == 'x') ret = _sumArr[d.e + 1].x - _sumArr[d.s].x;
				else if (d.alpha == 'y') ret = _sumArr[d.e + 1].y - _sumArr[d.s].y;
				else if (d.alpha == 'z') ret = _sumArr[d.e + 1].z - _sumArr[d.s].z;
				cout << ret << '\n';
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

	}

private:
	std::string _dir = "./TestData/Q16139/";
private:

	std::string _S;
	uint32_t _N;
	struct quest
	{
		char alpha;
		uint32_t s;
		uint32_t e;
	};

	std::vector<quest> _arr;
	struct alphaCount
	{
		uint32_t a;
		uint32_t b;
		uint32_t c;
		uint32_t d;
		uint32_t e;
		uint32_t f;
		uint32_t g;
		uint32_t h;
		uint32_t i;
		uint32_t j;
		uint32_t k;
		uint32_t l;
		uint32_t m;
		uint32_t n;
		uint32_t o;
		uint32_t p;
		uint32_t q;
		uint32_t r;
		uint32_t s;
		uint32_t t;
		uint32_t u;
		uint32_t v;
		uint32_t w;
		uint32_t x;
		uint32_t y;
		uint32_t z;

		alphaCount operator+(const char& rhs)
		{
			if (rhs == 'a') a++;
			else if (rhs == 'b') b++;
			else if (rhs == 'c') c++;
			else if (rhs == 'd') d++;
			else if (rhs == 'e') e++;
			else if (rhs == 'f') f++;
			else if (rhs == 'g') g++;
			else if (rhs == 'h') h++;
			else if (rhs == 'i') i++;
			else if (rhs == 'j') j++;
			else if (rhs == 'k') k++;
			else if (rhs == 'l') l++;
			else if (rhs == 'm') m++;
			else if (rhs == 'n') n++;
			else if (rhs == 'o') o++;
			else if (rhs == 'p') p++;
			else if (rhs == 'q') q++;
			else if (rhs == 'r') r++;
			else if (rhs == 's') s++;
			else if (rhs == 't') t++;
			else if (rhs == 'u') u++;
			else if (rhs == 'v') v++;
			else if (rhs == 'w') w++;
			else if (rhs == 'x') x++;
			else if (rhs == 'y') y++;
			else if (rhs == 'z') z++;

			return *this;
		}
	};

	//static inline alphaCount operator+(const alphaCount& a, const char& b)
	//{
	//	alphaCount ret = a;
	//	if      (b == 'a') ++ret.a;
	//	else if (b == 'b') ++ret.b;
	//	else if (b == 'c') ++ret.c;
	//	else if (b == 'd') ++ret.d;
	//	else if (b == 'e') ++ret.e;
	//	else if (b == 'f') ++ret.f;
	//	else if (b == 'g') ++ret.g;
	//	else if (b == 'h') ++ret.h;
	//	else if (b == 'i') ++ret.i;
	//	else if (b == 'j') ++ret.j;
	//	else if (b == 'k') ++ret.k;
	//	else if (b == 'l') ++ret.l;
	//	else if (b == 'm') ++ret.m;
	//	else if (b == 'n') ++ret.n;
	//	else if (b == 'o') ++ret.o;
	//	else if (b == 'p') ++ret.p;
	//	else if (b == 'q') ++ret.q;
	//	else if (b == 'r') ++ret.r;
	//	else if (b == 's') ++ret.s;
	//	else if (b == 't') ++ret.t;
	//	else if (b == 'u') ++ret.u;
	//	else if (b == 'v') ++ret.v;
	//	else if (b == 'w') ++ret.w;
	//	else if (b == 'x') ++ret.x;
	//	else if (b == 'y') ++ret.y;
	//	else if (b == 'z') ++ret.z;

	//	return ret;
	//}

	std::vector<alphaCount> _sumArr;
};

/*--------------------
* main
--------------------*/
int main()
{
	QHelper::Init();
#if defined(DEBUG) || defined(_DEBUG)
	int TestCase = 1;
	// QHelper::SaveTest("./TestData/Q16139/", TestCase);
	std::unique_ptr<QBase> q = std::make_unique<Q16139>();
	for (int i = 1; i <= TestCase; ++i)
		q->Solve(i);
#else
	std::unique_ptr<QBase> q = std::make_unique<Q16139>();
	q->Solve();
#endif
	return 0;
}
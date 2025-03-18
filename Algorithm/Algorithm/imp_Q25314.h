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

	static inline std::ifstream LoadTestFile(const std::string& dir = "./TestData/Q1/", const std::string& filename = "Input1.txt")
	{
		std::string line;
		std::ifstream fp(dir + filename);

		// std::cout << "*Info, Load Input file: " << dir + filename << "\n";
		assert(fp.is_open());

		// while (getline(fp, line)) {
		// 	std::cout << line << std::endl;
		// }

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
		return LoadTestFile(dir, filename);
	}

	static inline std::ifstream LoadTestOutput(const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::string filename = "Output" + std::to_string(testCase) + ".txt";
		return LoadTestFile(dir, filename);
	}

	static inline void Score(std::vector<std::string>& ans, const std::string& dir = "./TestData/Q1/", const int& testCase = 1)
	{
		std::ifstream ifp = LoadTestOutput(dir, testCase);

		std::string line;
		uint16_t i = 0;
		while (getline(ifp, line)) {
			std::cout << ans[i] << std::endl;
			assert(i <= ans.size());
			assert(line == ans[i++]);
			std::cout << "*Info, [" << i << "/" << ans.size() << "] Test Pass\n";
		}
	}
};

class QBase
{
public:
	QBase() = default;
	QBase(const QBase& rhs) = default;
	QBase& operator=(const QBase& rhs)
	{
		return *this;
	}
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
* Q25314
--------------------*/
class Q25314 : public QBase
{
public:
	Q25314()
		: QBase()
		, _A(4)
	{}
	Q25314(const Q25314& rhs)
		: QBase(rhs)
		, _A(rhs._A)
	{}
	Q25314& operator=(const Q25314& rhs)
	{
		if (&rhs == this) return *this;
		QBase::operator=(rhs);

		_A = rhs._A;

		return *this;
	}
	virtual ~Q25314() = default;

private:
	virtual void Input(const int& testCase)
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::ifstream fp = QHelper::LoadTestInput("./TestData/Q25314/", testCase);
		fp >> _A;
		std::cout << _A << std::endl;
#else
		std::cin >> _A;
#endif

		assert(_A >= 4 && _A <= 1000);
	}
	virtual void Solution(const int& testCase)
	{
#if defined(DEBUG) || defined(_DEBUG)
		std::vector<std::string> ans;
		ans.push_back(std::string());
		for (uint16_t i = 0; i < _A / 4; ++i) ans[0] += "long ";
		ans[0] += "int";
		QHelper::Score(ans, "./TestData/Q25314/", testCase);
#else
		for (uint16_t i = 0; i < _A / 4; ++i) std::cout << "long ";
		std::cout << "int\n";
#endif
	}
	virtual void Delete()
	{
	}

private:
	uint16_t _A;
};

/*--------------------
* main
--------------------*/
int main()
{
#if defined(DEBUG) || defined(_DEBUG) 
	// QHelper::SaveTest("./TestData/Q25314/", 2);
	QHelper::Init();
#endif

	std::unique_ptr<QBase> q = std::make_unique<Q25314>();

	q->Solve(2);
	return 0;
}
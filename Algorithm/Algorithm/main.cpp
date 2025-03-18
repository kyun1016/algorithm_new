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

	static inline std::ifstream LoadTestInput(const int idx = 1)
	{
		std::string line;
		std::string fileName = "TestData/Input/Input" + std::to_string(idx) + ".txt";

		std::ifstream fp(fileName);
		
		if (fp.is_open()) {
			while (getline(fp, line)) {
				std::cout << line << std::endl;
			}
		}
		else {
			std::cout << "Unable to open file: " << fileName << std::endl;
		}

		return fp;
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
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
private:
	virtual void Input() = 0;
	virtual void Solution() = 0;
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
	virtual void Input() 
	{
#if defined(DEBUG) || defined(_DEBUG) 
		std::ifstream fp = QHelper::LoadTestInput();
		
		fp >> _A;
#else
		std::cin >> _A;
#endif
		
		assert(_A >= 4 && _A <= 1000);
	}
	virtual void Solution()
	{
		for (uint16_t i = 0; i < _A / 4; ++i) std::cout << "long ";
		std::cout << "int\n";
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
	QHelper::SaveTest("./TestData/Q25314/", 2);

	/*QHelper::Init();

	std::unique_ptr<QBase> q = std::make_unique<Q25314>();

	q->Solve();
	return 0;*/
}
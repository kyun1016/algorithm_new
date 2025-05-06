#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

class IQBase
{
public:
	IQBase() = default;
	virtual ~IQBase() = default;
	IQBase(const IQBase&) = delete;
	IQBase& operator=(const IQBase&) = delete;

	virtual void Init()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
	}
	virtual void Input() = 0;
	virtual void Solution() = 0;
	virtual void Delete() = 0;
	virtual void Solve()
	{
		Init();
		Input();
		Solution();
		Delete();
	}
};

class Q10101 : public IQBase
{
public:
	Q10101() = default;
	virtual ~Q10101() = default;

	virtual void Input() {
		int a, b, c;
		cin >> a >> b >> c;
		if (a + b + c != 180)
		{
			cout << "Error";
			return;
		}
		if (a == 60 && b == 60 && c == 60)
			cout << "Equilateral";
		else if (a == b || b == c || a == c)
			cout << "Isosceles";
		else
			cout << "Scalene";
	}
	virtual void Solution() {}
	virtual void Delete() {}
};
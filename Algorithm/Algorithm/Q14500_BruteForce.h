#define OUT

#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <numeric>

using namespace std;
/*--------------------
* QBase
--------------------*/
class QBase
{
public:
	QBase() = default;
	virtual ~QBase() = default;

	virtual void Init()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		cout.tie(NULL);
	}
	virtual void Input() {}
	virtual void Solution() {}
	virtual void Delete() {}
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
};
class Q14500 : public QBase
{
public:
	Q14500()
		: _N(0)
		, _M(0)
	{
		_arr.resize(19);
		_arr[0].resize(2, vector<bool>(2, true));

		_arr[1].resize(1, vector<bool>(4, true));
		_arr[2].resize(4, vector<bool>(1, true));

		_arr[3].resize(2, vector<bool>(3, true));
		_arr[3][0][0] = false;
		_arr[3][0][1] = false;
		_arr[4].resize(2, vector<bool>(3, true));
		_arr[4][0][0] = false;
		_arr[4][0][2] = false;
		_arr[5].resize(2, vector<bool>(3, true));
		_arr[5][0][1] = false;
		_arr[5][0][2] = false;
		_arr[6].resize(2, vector<bool>(3, true));
		_arr[6][1][0] = false;
		_arr[6][1][1] = false;
		_arr[7].resize(2, vector<bool>(3, true));
		_arr[7][1][0] = false;
		_arr[7][1][2] = false;
		_arr[8].resize(2, vector<bool>(3, true));
		_arr[8][1][1] = false;
		_arr[8][1][2] = false;
		_arr[9].resize(2, vector<bool>(3, true));
		_arr[9][0][0] = false;
		_arr[9][1][2] = false;
		_arr[10].resize(2, vector<bool>(3, true));
		_arr[10][0][2] = false;
		_arr[10][1][0] = false;

		_arr[11].resize(3, vector<bool>(2, true));
		_arr[11][0][0] = false;
		_arr[11][1][0] = false;
		_arr[12].resize(3, vector<bool>(2, true));
		_arr[12][0][0] = false;
		_arr[12][2][0] = false;
		_arr[13].resize(3, vector<bool>(2, true));
		_arr[13][1][0] = false;
		_arr[13][2][0] = false;
		_arr[14].resize(3, vector<bool>(2, true));
		_arr[14][0][1] = false;
		_arr[14][1][1] = false;
		_arr[15].resize(3, vector<bool>(2, true));
		_arr[15][0][1] = false;
		_arr[15][2][1] = false;
		_arr[16].resize(3, vector<bool>(2, true));
		_arr[16][1][1] = false;
		_arr[16][2][1] = false;
		_arr[17].resize(3, vector<bool>(2, true));
		_arr[17][0][0] = false;
		_arr[17][2][1] = false;
		_arr[18].resize(3, vector<bool>(2, true));
		_arr[18][2][0] = false;
		_arr[18][0][1] = false;
		//for (int i = 0; i < _arr.size(); ++i)
		//{
		//	for (int y = 0; y < _arr[i].size(); ++y)
		//	{
		//		for (int x = 0; x < _arr[i][y].size(); ++x)
		//			cout << _arr[i][y][x] << " ";
		//		cout << endl;
		//	}
		//	cout << endl;
		//}
	}

	virtual void Input()
	{
		cin >> _N >> _M;
		_map.resize(_N, vector<int>(_M));

		for (int y = 0; y < _N; ++y)
			for (int x = 0; x < _M; ++x)
				cin >> _map[y][x];
	}

	virtual void Solution()
	{
		int ret = 0;
		for (int y = 0; y < _N; ++y)
		{
			for (int x = 0; x < _M; ++x)
			{
				for (int i = 0; i < _arr.size(); ++i)
				{
					if (_arr[i].size() + y > _N)
						continue;
					if (_arr[i][0].size() + x > _M)
						continue;

					int sum = 0;
					for (int dy = 0; dy < _arr[i].size(); ++dy)
					{
						for (int dx = 0; dx < _arr[i][0].size(); ++dx)
						{
							if (_arr[i][dy][dx])
								sum += _map[y + dy][x + dx];
						}
					}
					ret = ret > sum ? ret : sum;
				}
			}
		}

		cout << ret << endl;
	}
private:
	int _N;
	int _M;
	vector<vector<int>> _map;
	vector<vector<vector<bool>>> _arr;
};
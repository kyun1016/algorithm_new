#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N;
int K;

vector<pair<int, int>> adj[100001];

void FindParent(int par, int now, int depth, int road_len)
{

}

pair<int, int> FindMinMaxRoad(int a, int b)
{

}

int main()
{
	cin >> N;

	int a, b, dist;
	for (int i = 0; i < N - 1; ++i)
	{
		cin >> a >> b >> dist;
		adj[a].push_back({ b, dist });
		adj[b].push_back({ a, dist });
	}
}
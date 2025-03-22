#pragma once
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int MAX_V = 20001;
const int INF = 1000000007;

int V, E, start;

vector<pair<int, int> > adj[MAX_V];
priority_queue<pair<int, int> > pq;

vector<int> dijkstra(const int& start) {
	vector<int> dist(V + 1, INF);
	dist[start] = 0;
	pq.push(make_pair(0, start));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//만일 이번 정점의 코스트가 최소가 아니라면 생략
		if (dist[here] < cost) continue;
		//인접한 정점들을 모두 검사한다.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	return dist;
}

void dijkstra(const int& start, const int& end)
{
	vector<int> dist(end * 3 + 1, INF);
	dist[start] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0, start });
	int ret = INF;
	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int idx = pq.top().second;
		if (idx == end)
		{
			ret = ret < cost ? ret : cost;
		}
		pq.pop();

		if (cost >= ret)
			continue;
		if (dist[idx] < cost)
			continue;

		if (idx * 2 < end * 3 && dist[idx * 2] > cost)
		{
			dist[idx * 2] = cost;
			pq.push({ -cost, idx * 2 });
		}

		++cost;
		if (idx - 1 >= 0 && dist[idx - 1] > cost)
		{
			dist[idx - 1] = cost;
			pq.push({ -cost, idx - 1 });
		}
		if (idx + 1 < end * 3 && dist[idx + 1] > cost)
		{
			dist[idx + 1] = cost;
			pq.push({ -cost, idx + 1 });
		}
	}

	cout << ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int s, e;
	cin >> s >> e;

	dijkstra(s, e);

	return 0;
}
#pragma once
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
	virtual void Input() {};
	virtual void Solution() {};
	virtual void Delete() {};
	virtual void Solve()
	{
		Input();
		Solution();
		Delete();
	}
};
class Q5670 : public QBase
{
public:
	enum Parameter
	{
		MAX_LEN = 26,
	};
	struct TrieNode
	{
		bool last = false;
		int cnt = 0;
		unique_ptr<TrieNode> arr[MAX_LEN];
	};
	class Trie
	{
	public:
		Trie()
		{
			_root = make_unique<TrieNode>();
		}
		~Trie() = default;

		void Insert(const string& word)
		{
			TrieNode* curNode = _root.get();
			for (const char& c : word)
			{
				int idx = c - 'a';
				if (curNode->arr[idx] == nullptr) {
					curNode->arr[idx] = make_unique<TrieNode>();
					++curNode->cnt;
				}
				curNode = curNode->arr[idx].get();
			}
			curNode->last = true;
			return;
		}

		int FindTypeCount(const string& word)
		{
			int ret = 1;
			int idx = word[0] - 'a';
			TrieNode* curNode = _root->arr[idx].get();
			for (int i = 1; i < word.length(); ++i)
			{
				idx = word[i] - 'a';
				if (curNode->last || curNode->cnt != 1)
					++ret;
				curNode = curNode->arr[idx].get();
			}
			return ret;
		}

	private:
		unique_ptr<TrieNode> _root;
	};

	virtual void Solve() override
	{
		while (true)
		{
			Input();
			if (cin.eof() == true)
				break;
			Solution();
			Delete();
		}
	}
	virtual void Input() override
	{
		cin >> _N;
		_arr.resize(_N);
		for (string& str : _arr)
			cin >> str;

	}
	virtual void Solution() override
	{
		Trie trie;
		for (const string& str : _arr)
			trie.Insert(str);

		double ret = 0;
		for (const string& str : _arr)
		{
			ret += static_cast<double>(trie.FindTypeCount(str));
		}
		cout << fixed << setprecision(2) << ret / _N << endl;
	}

	virtual void Delete() override
	{
		_arr.clear();
	}
private:
	int _N;
	vector<string> _arr;
};
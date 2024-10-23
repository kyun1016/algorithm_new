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
class Q13505 : public QBase
{
public:
	enum Parameter
	{
		DEPTH = 31,
	};
	struct TrieNode
	{
		unique_ptr<TrieNode> childNode[2];
	};
	class Trie
	{
	public:
		Trie()
		{
			_rootNode = make_unique<TrieNode>();
		};
		~Trie() = default;

		void Insert(const int& num)
		{
			TrieNode* curNode = _rootNode.get();
			for (int i = DEPTH; i >= 0; --i)
			{
				int idx = (num & (1 << i)) != 0 ? 1 : 0;
				if (curNode->childNode[idx] == nullptr)
					curNode->childNode[idx] = make_unique<TrieNode>();

				curNode = curNode->childNode[idx].get();
			}
		};

		int QueryXOR(const int& num)
		{
			int ret = 0;
			TrieNode* curNode = _rootNode.get();
			for (int i = DEPTH; i >= 0; --i)
			{
				if (curNode->childNode[1] == nullptr)
					curNode = curNode->childNode[0].get();
				else if (curNode->childNode[0] == nullptr)
				{
					ret += (1 << i);
					curNode = curNode->childNode[1].get();
				}
				else if (num & (1 << i))
					curNode = curNode->childNode[0].get();
				else
				{
					ret += (1 << i);
					curNode = curNode->childNode[1].get();
				}
			}
			return ret;
		}

	private:
		unique_ptr<TrieNode> _rootNode;
	};

	virtual void Input() override
	{
		cin >> _N;
		_arr.resize(_N);


	}
	virtual void Solution() override
	{
		int ret = 0;
		int maxValue;
		Trie trie;
		for (int i = 0; i < _N; ++i)
		{
			cin >> _arr[i];
			trie.Insert(_arr[i]);
			maxValue = trie.QueryXOR(_arr[i]);
			ret = ret >= (maxValue ^ _arr[i]) ? ret : (maxValue ^ _arr[i]);
		}

		cout << ret << endl;
	}
private:
	int _N;
	vector<unsigned int> _arr;
};
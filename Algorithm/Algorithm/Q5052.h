#include "QBase.h"

class Q5052 : public QBase
{
    enum Parameter
    {
        MAX_LEN = 10,
    };
    struct TrieNode
    {
        bool finish = false;
        unique_ptr<TrieNode> children[MAX_LEN];
    };

    class Trie
    {
    public:
        Trie()
        {
            _root = make_unique<TrieNode>();
        };
        ~Trie() = default;

        bool Insert(const string& word)
        {
            TrieNode* curNode = _root.get();
            bool ret = true;
            for (const char& c : word)
            {
                int idx = c - '0';
                if (curNode->children[idx] == nullptr)
                    curNode->children[idx] = make_unique<TrieNode>();
                curNode = curNode->children[idx].get();
                if (curNode->finish)
                    ret = false;
            }
            curNode->finish = true;
            return ret;
        }

        bool Search(const string& word)
        {
            TrieNode* curNode = _root.get();
            for(int i=0; i<word.length(); ++i)
            {
                int idx = word[i] - '0';
                if (curNode->children[idx] == nullptr)
                    return false;
                curNode = curNode->children[idx].get();
                if (curNode->finish && i != word.length() - 1)
                    return true;
            }
            return false;
        }
    private:
        unique_ptr<TrieNode> _root;
    };

    virtual void Solve() final
    {
        int t, n;
        vector<string> arr;
        cin >> t;
        while (t--)
        {
            cin >> n;
            arr.resize(n);
            Trie trie;
            bool ret = true;
            for(int i=0; i<n; ++i)
            {
                cin >> arr[i];
                if (!trie.Insert(arr[i]))
                    ret = false;
            }
            for (int i = 0; i < n; ++i)
            {
                if (trie.Search(arr[i]))
                    ret = false;
            }
            
            if (ret)
                cout << "YES\n";
            else
                cout << "NO\n";
            arr.clear();
        }
    }
};
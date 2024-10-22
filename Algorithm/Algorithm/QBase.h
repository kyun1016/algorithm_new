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
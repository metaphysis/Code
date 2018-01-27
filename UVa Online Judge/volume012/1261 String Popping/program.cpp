// String Popping
// UVa ID: 1261
// Verdict: Accepted
// Submission Date: 2018-01-27
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

set<string> good;

bool dfs(string s)
{
    if (s.length() == 0) return true;
    if (good.find(s) != good.end()) return true;

    for (int i = 1; i < s.length(); i++)
        if (s[i] == s[i - 1])
        {
            int right = 0;
            for (int j = i + 1; j < s.length() && s[j] == s[i]; j++)
                right++;
            string next;
            for (int j = 0; j < i - 1; j++) next += s[j];
            for (int j = i + right + 1; j < s.length(); j++) next += s[j];
            if (dfs(next))
            {
                good.insert(next);
                return true;
            }
            i += right + 1;
        }
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        if (dfs(line)) cout << 1 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}

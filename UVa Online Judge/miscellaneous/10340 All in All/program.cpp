// All in All
// UVa ID: 10340
// Verdict: Accepted
// Submission Date: 2016-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string s, t;
    
    while (cin >> s >> t)
    {
        size_t i = 0, j = 0;
        while (i < s.length() && j < t.length())
        {
            if (s[i] == t[j])
                i++, j++;
            else
                j++;
        }
        
        if (i == s.length()) cout << "Yes\n";
        else cout << "No\n";
    }
    
	return 0;
}

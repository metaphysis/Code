// Hardwood Species
// UVa ID: 10226
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.300s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    
    getline(cin, line);
    int cases = stoi(line);
    getline(cin, line);

    for (int c = 1; c <= cases; c++)
    {
        map<string, int> cnt;
        int total = 0;
        while (getline(cin, line), line.length() > 0)
        {
            cnt[line]++;
            total++;
        }
        
        if (c > 1) cout << '\n';
        for (auto r : cnt)
        {
            cout << r.first << ' ';
            cout << fixed << setprecision(4) << (r.second * 100.0 / total) << '\n';
        }        
    }

    return 0;
}

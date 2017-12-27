// Counting Chaos
// UVa ID: 11309
// Verdict: Accepted
// Submission Date: 2017-12-27
// UVa Run Time: 0.000s
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> chaos;
    for (int i = 0; i <= 23; i++)
        for (int j = 0; j <= 59; j++)
        {
            int n = i * 100 + j;
            int t = 0, b = n;
            while (b > 0)
            {
                t = t * 10 + b % 10;
                b /= 10;
            }
            if (n == t)
            {
                chaos.push_back(i * 60 + j);
            }
        }

    int n;
    string time;
    
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> time;
        int t = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
        int k = upper_bound(chaos.begin(), chaos.end(), t) - chaos.begin();
        if (k == chaos.size()) k = 0;
        t = chaos[k];
        int hh = t / 60;
        int mm = t % 60;
        cout << setw(2) << setfill('0') << hh << ':';
        cout << setw(2) << setfill('0') << mm << '\n';
    }

    return 0;
}

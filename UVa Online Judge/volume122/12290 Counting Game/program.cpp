// Counting Game
// UVa ID: 12290
// Verdict: Accepted
// Submission Date: 2018-02-27
// UVa Run Time: 0.000s
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

    int n, m, k;
    int clap[110], seven[50010] = {0};

    for (int i = 1; i <= 50000; i++)
    {
        if (i % 7 == 0) seven[i] = 1;
        else
        {
            int x = i;
            while (x)
            {
                if (x % 10 == 7)
                {
                    seven[i] = 1;
                    break;
                }
                x /= 10;
            }
        }
    }
    
    while (cin >> n >> m >> k, n > 0)
    {
        memset(clap, 0, sizeof(clap));
        int cnt = 0;
        while (cnt >= 0)
        {
            for (int i = 1; i <= n; i++)
            {
                cnt++;
                if (seven[cnt]) clap[i]++;
                if (i == m && clap[i] == k)
                {
                    cout << cnt << '\n';
                    cnt = -1;
                    break;
                }
            }
            if (cnt < 0) break;
            for (int i = n - 1; i >= 2; i--)
            {
                cnt++;
                if (seven[cnt]) clap[i]++;
                if (i == m && clap[i] == k)
                {
                    cout << cnt << '\n';
                    cnt = -1;
                    break;
                }
            }
            if (cnt < 0) break;
        }
    }

    return 0;
}

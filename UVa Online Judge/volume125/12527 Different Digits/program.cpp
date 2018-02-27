// Different Digits
// UVa ID: 12527
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

    int repeated[5010] = {0};
    for (int i = 1; i < 5010; i++)
    {
        int cnt[10] = {0};
        int x = i;
        while (x)
        {
            if (++cnt[x % 10] > 1)
            {
                repeated[i] = 1;
                break;
            }
            x /= 10;
        }
    }

    int N, M;
    while (cin >> N >> M)
    {
        int total = 0;
        for (int i = N; i <= M; i++)
            total += 1 - repeated[i];
        cout << total << '\n';
    }

    return 0;
}

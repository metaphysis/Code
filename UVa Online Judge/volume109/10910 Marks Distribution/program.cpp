// Marks Distribution
// UVa ID: 10910
// Verdict: Accepted
// Submission Date: 2018-01-18
// UVa Run Time: 0.090s
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

    int K, N, T, P, ways[71][71];

    cin >> K;
    while (K--)
    {
        cin >> N >> T >> P;
        memset(ways, 0, sizeof(ways));
        ways[0][0] = 1;
        for (int i = 1; i <= N; i++)
            for (int j = P; j <= T; j++)
                for (int k = T; k >= i * P; k--)
                {
                    if (k < j) continue;
                    ways[i][k] += ways[i - 1][k - j];
                }    
        cout << ways[N][T] << '\n';
    }

    return 0;
}

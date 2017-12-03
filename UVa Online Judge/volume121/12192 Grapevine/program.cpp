// Grapevine
// UVa ID: 12192
// Verdict: Accepted
// Submission Date: 2017-11-02
// UVa Run Time: 0.350s
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

    int N, M, Q, L, U;
    int g[510][510], d[510][510];
    
    while (cin >> N >> M, N > 0)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> g[i][j];
        cin >> Q;       
        for (int q = 1; q <= Q; q++)
        {
            cin >> L >> U;

            int largest = 0;
            for (int i = 0; i < N; i++)
            {
                int s = lower_bound(g[i], g[i] + M, L) - g[i];
                if (s == M) continue;
                for (int j = largest; j < N; j++)
                {
                    int ii = i + j, jj = s + j;
                    if (ii >= N || jj >= M || g[ii][jj] > U) break;
                    largest = j + 1;
                }
            }

            cout << largest << '\n';
        }
        cout << "-\n";
    }

    return 0;
}

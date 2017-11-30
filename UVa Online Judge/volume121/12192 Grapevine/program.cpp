// Grapevine
// UVa ID: 12192
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                cin >> g[i][j];
        cin >> Q;       
        for (int q = 1; q <= Q; q++)
        {
            cin >> L >> U;
            for (int i = 0; i <= N; i++)
                for (int j = 0; j <= M; j++)
                    d[i][j] = 0;

            int S = 0;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= M; j++)
                {
                    if (L <= g[i][j] && g[i][j] <= U)
                        d[i][j] = min(d[i - 1][j - 1], min(d[i - 1][j], d[i][j - 1])) + 1;
                    S = max(S, d[i][j]);
                }
            cout << S << '\n';
        }
        cout << "-\n";
    }

    return 0;
}
